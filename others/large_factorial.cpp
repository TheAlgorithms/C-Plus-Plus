#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

/**
 * Store large unsigned numbers as a C++ vector
 * The class provides convenience functions to add a
 * digit to the number, perform multiplication of
 * large number with long unsigned integers.
 **/
class large_number
{
public:
    large_number() /**< initializer */
    {
        _digits.push_back(1);
    }

    /**
     * add a digit to the large number
     **/
    void add_digit(unsigned int value)
    {
        if (value > 9)
        {
            fprintf(stderr, "digit > 9!!\n");
            exit(EXIT_FAILURE);
        }

        _digits.push_back(value);
    }

    /**
     * Get number of digits in the number
     **/
    const size_t num_digits() const
    {
        return _digits.size();
    }

    /**
     * operator over load to access the
     * i^th digit conveniently and also
     * assign value to it
     **/
    unsigned char &operator[](size_t n)
    {
        return this->_digits[n];
    }

    /**
     * multiply large number with another integer and
     * store the result in the same large number
     **/
    void multiply(const unsigned long n)
    {
        size_t i;
        unsigned long long carry = 0, temp;
        for (i = 0; i < this->num_digits(); i++)
        {
            temp = (*this)[i] * n;
            temp += carry;
            if (temp < 10)
                carry = 0;
            else
            {
                carry = temp / 10;
                temp = temp % 10;
            }
            (*this)[i] = temp;
        }

        while (carry != 0)
        {
            this->add_digit(carry % 10);
            carry /= 10;
        }
    };

    /**
     * print the large number
     **/
    void print()
    {
        for (size_t i = num_digits(); i > 0; i--)
            putchar(_digits[i - 1] + '0');
    };

private:
    vector<unsigned char> _digits; /**< where individual digits are stored */
};

bool test1()
{
    cout << "---- Check 1\t";
    unsigned int i, number = 10;
    large_number result;
    for (i = 2; i <= number; i++)
        /* Multiply every number from 2 thru N */
        result.multiply(i);

    const char *known_reslt = "3628800";

    /* check 1 */
    if (strlen(known_reslt) != result.num_digits())
    {
        cerr << "Result lengths dont match! " << strlen(known_reslt) << " != " << result.num_digits() << endl;
        return false;
    }

    size_t N = result.num_digits();
    for (i = 0; i < N; i++)
    {
        if (known_reslt[i] != (result[N - i - 1] + '0'))
        {
            cerr << i << "^th digit mismatch! " << known_reslt[i] << " != " << result[N - i - 1] << endl;
            return false;
        }
    }

    cout << "Passed!" << endl;
    return true;
}

bool test2()
{
    cout << "---- Check 2\t";
    unsigned int i, number = 100;
    large_number result;
    for (i = 2; i <= number; i++)
        /* Multiply every number from 2 thru N */
        result.multiply(i);

    const char *known_reslt = "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000";

    /* check 1 */
    if (strlen(known_reslt) != result.num_digits())
    {
        cerr << "Result lengths dont match! " << strlen(known_reslt) << " != " << result.num_digits() << endl;
        return false;
    }

    size_t N = result.num_digits();
    for (i = 0; i < N; i++)
    {
        if (known_reslt[i] != (result[N - i - 1] + '0'))
        {
            cerr << i << "^th digit mismatch! " << known_reslt[i] << " != " << result[N - i - 1] << endl;
            return false;
        }
    }

    cout << "Passed!" << endl;
    return true;
}

/**
 * Main program
 **/
int main(int argc, char *argv[])
{
    int number, i;

    //Asks for the number/position of term in Fibonnacci sequence
    if (argc == 2)
        number = atoi(argv[1]);
    else
    {
        printf("Enter the value of n(n starts from 0 ): ");
        scanf("%d", &number);
    }

    large_number result;

    auto start_time = chrono::high_resolution_clock::now();
    for (i = 2; i <= number; i++)
        /* Multiply every number from 2 thru N */
        result.multiply(i);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_taken = end_time - start_time;

    cout << number << "! = ";
    result.print();
    cout << endl
         << "Number of digits: " << result.num_digits() << endl
         << "Time taken: " << time_taken.count() << " s"
         << endl;

    test1();
    test2();

    return 0;
}
