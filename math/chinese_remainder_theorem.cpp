/**
 * @file
 * @brief C++ program to solve a system of linear congruences using the Chinese Remainder Theorem (CRT).
 *
 * @details
 * The Chinese Remainder Theorem (CRT) is a mathematical theorem that provides a solution
 * to a system of linear congruences. It allows us to find a unique solution to the system
 * if the moduli are pairwise coprime (i.e., the greatest common divisor of any two moduli is 1).
 *
 * This implementation assumes that the moduli are pairwise coprime.
 *
 * @note For the system of congruences to have a solution, the moduli must be pairwise coprime.
 * If they are not, the result obtained may not be valid.
 *
 * @author [Himesh](https://github.com/HimeshKohad)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
using namespace std;

/**
 * @brief Function to solve a system of linear congruences using the Chinese Remainder Theorem (CRT).
 *
 * @param a Array of integers representing the remainders of the congruences.
 * @param m Array of pairwise coprime integers representing the moduli of the congruences.
 * @param n Number of congruences in the system.
 * @return The solution to the system of congruences.
 */
int chinese_remainder_theorem(int a[], int m[], int n) {
    // Calculate the product of all moduli
    int M = 1;
    for (int i = 0; i < n; ++i) {
        M *= m[i];
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        // Calculate the factor for each congruence
        int factor = M / m[i];

        // Calculate the modular inverse of the factor modulo m[i]
        int inv = 1;
        while ((factor * inv) % m[i] != 1) {
            inv++;
        }

        // Sum up the partial results
        result += (a[i] * factor * inv) % M;
    }

    // Make sure the result is non-negative
    result = (result + M) % M;

    return result;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
void test() {
    int a[] = {2, 3, 1};
    int m[] = {3, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);

    // chinese_remainder_theorem(a, m, n) returns 11.
    assert(chinese_remainder_theorem(a, m, n) == 11);

    cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
