#include <iostream>
#include <string.h>
#include <chrono>
#include "large_number.h"

using namespace std;

bool test1()
{
    cout << "---- Check 1\t";
    unsigned int i, number = 10;
    large_number result;
    for (i = 2; i <= number; i++)
        /* Multiply every number from 2 thru N */
        result *= i;

    const char *known_reslt = "3628800";

    /* check 1 */
    if (strlen(known_reslt) != result.num_digits())
    {
        cerr << "Result lengths dont match! " << strlen(known_reslt) << " != " << result.num_digits() << endl;
        return false;
    }

    const size_t N = result.num_digits();
    for (i = 0; i < N; i++)
    {
        if (known_reslt[i] != result.digit_char(i))
        {
            cerr << i << "^th digit mismatch! " << known_reslt[i] << " != " << result.digit_char(i) << endl;
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
        result *= i;

    const char *known_reslt = "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000";

    /* check 1 */
    if (strlen(known_reslt) != result.num_digits())
    {
        cerr << "Result lengths dont match! " << strlen(known_reslt) << " != " << result.num_digits() << endl;
        return false;
    }

    const size_t N = result.num_digits();
    for (i = 0; i < N; i++)
    {
        if (known_reslt[i] != result.digit_char(i))
        {
            cerr << i << "^th digit mismatch! " << known_reslt[i] << " != " << result.digit_char(i) << endl;
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
        result *= i;
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_taken = end_time - start_time;

    cout << number << "! = " << result << endl
         << "Number of digits: " << result.num_digits() << endl
         << "Time taken: " << time_taken.count() << " s"
         << endl;

    test1();
    test2();
    result.test();

    return 0;
}
