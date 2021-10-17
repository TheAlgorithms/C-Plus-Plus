/**
 * @file
 * @brief [Primality test](https://en.wikipedia.org/wiki/Primality_test)
 * implementation.
 *
 * A simple and efficient implementation of a function to test if a number is
 * prime, based on the fact that
 * > Every Prime number, except 2 and 3, are of the form \f$6k\pm1\f$ for
 * > integer values of k.
 * This gives a 3x speed improvement.
 */
#include <iostream>

/** Check if a number is prime
 * \param[in] number number to check
 * \returns true if prime else false
 */
bool IsPrime(int number) {
    if (((!(number & 1)) && number != 2) || (number < 2) ||
        (number % 3 == 0 && number != 3))
        return false;

    for (int k = 1; 36 * k * k - 12 * k < number; ++k) {
        if ((number % (6 * k + 1) == 0) || (number % (6 * k - 1) == 0))
            return false;
    }
    return true;
}

/** main function */
int main() {
    // Main Function
    std::cout << "Enter the value of n to check if Prime\n";
    int n;
    std::cin >> n;
    if (IsPrime(n))
        std::cout << n << " is Prime" << std::endl;
    else
        std::cout << n << " is not Prime" << std::endl;

    return 0;
}
