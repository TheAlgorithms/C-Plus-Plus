/**
 * @file
 * @brief C++ program to solve a system of linear congruences using the Chinese
 * Remainder Theorem (CRT).
 *
 * @details
 * The Chinese Remainder Theorem (CRT) is a mathematical theorem that provides a
 * solution to a system of linear congruences. It allows us to find a unique
 * solution to the system if the moduli are pairwise coprime (i.e., the greatest
 * common divisor of any two moduli is 1).
 *
 * This implementation assumes that the moduli are pairwise coprime.
 *
 * @note For the system of congruences to have a solution, the moduli must be
 * pairwise coprime. If they are not, the result obtained may not be valid.
 *
 * @author [Himesh](https://github.com/HimeshKohad)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

struct LinearCongruance {
    const int a;
    const int m;

    LinearCongruance(int a, int m) : a(a), m(m) {}
};

int compute_product_of_all_moduli(
    const std::vector<LinearCongruance> &congruances) {
    int res = 1;
    for (const auto congruance : congruances) {
        res *= congruance.m;
    }
    return res;
}

int compute_inverse(int a, int m) {
    int inv = 1;
    while ((a * inv) % m != 1) {
        inv++;
    }
    return inv;
}

/**
 * @brief Function to solve a system of linear congruences using the Chinese
 * Remainder Theorem (CRT).
 *
 * @param a Array of integers representing the remainders of the congruences.
 * @param m Array of pairwise coprime integers representing the moduli of the
 * congruences.
 * @param n Number of congruences in the system.
 * @return The solution to the system of congruences.
 */
int chinese_remainder_theorem(
    const std::vector<LinearCongruance> &congruances) {
    // Calculate the product of all moduli
    const auto M = compute_product_of_all_moduli(congruances);

    int result = 0;
    for (const auto congruance : congruances) {
        const auto factor = M / congruance.m;
        const auto inv = compute_inverse(factor, congruance.m);

        // Sum up the partial results
        result += (congruance.a * factor * inv) % M;
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
    const std::vector<LinearCongruance> testCase = {
        LinearCongruance(2, 3), LinearCongruance(3, 4), LinearCongruance(1, 5)};
    assert(chinese_remainder_theorem(testCase) == 11);

    std::cout << "One test has successfully passed!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
