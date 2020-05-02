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

    return 0;
}
