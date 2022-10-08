/**
 * @file
 * @brief Implementation of [modular multiplicative
 * inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) using
 * [Extended Euclidean Algorithm](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
 *
 * @details
 * this algorithm calculates the modular inverse x^{-1} \mod y using extended euclidean algorithm in logarithmic time complexity.
 */

#include <bits/stdc++.h>

/**
 * @brief Function imod
 * Calculates the modular inverse of a with respect to m, a^{-1} \mod m
 * @param a number
 * @param m number
 * @returns the modular inverse
 * we solve equation a*x + m*y = 1
 * taking modulo both sides
 * a*x mod m = 1 mod m
 * so x in the required modular inverse
 */

long long imod(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1){
        // base case
        return 0;
    }

    while (a > 1) {
        // q is quotient
        long long q = a / m;
        long long t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;


    return x;
}

/**
 * @brief  self-test implementations
 * @returns void
 */
static void test() {


    std::cout << "First case testing... \n";
    // for a = 3 and b = 11 return 4
    assert(imod(3, 11) == 4);
    std::cout << "\nPassed!\n";

    std::cout << "Second case testing... \n";
    // for a = 3 and b = 26 return 9
    assert(imod(3, 26) == 9);
    std::cout << "\nPassed!\n";

    std::cout << "Third case testing... \n";
    // for a = 7 and b = 26 return 15
    assert(imod(7, 26) == 15);
    std::cout << "\nPassed!\n";

    std::cout << "\nAll test cases have successfully passed!\n";
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
};


