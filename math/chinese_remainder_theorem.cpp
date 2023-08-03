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
#include <stdexcept> // for handling exceptions
#include <numeric>   // for std::gcd function

/**
 * @struct LinearCongruance
 * @brief Represents a congruence of the type x == a mod m
 */
struct LinearCongruance {
    const int a; ///< The remainder of the congruence (x == a mod m)
    const int m; ///< The modulus of the congruence (x == a mod m)

    /**
     * @brief Constructor to initialize a LinearCongruance object.
     * @param a The remainder of the congruence (x == a mod m)
     * @param m The modulus of the congruence (x == a mod m)
     */
    LinearCongruance(int a, int m) : a(a), m(m) {}
};

int compute_product_of_all_moduli(
    const std::vector<LinearCongruance> &congruances) {
    int res = 1;
    for (const auto congruance : congruances) {
        if (congruance.m == 0) {
            throw std::invalid_argument("Modulus 'm' cannot be zero.");
        }
        res *= congruance.m;
    }
    return res;
}

int compute_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) {
        return 0; // No inverse exists
    }

    // Apply extended Euclidean Algorithm
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

bool are_moduli_pairwise_coprime(
    const std::vector<LinearCongruance> &congruances) {
    for (size_t i = 0; i < congruances.size(); ++i) {
        for (size_t j = i + 1; j < congruances.size(); ++j) {
            if (std::gcd(congruances[i].m, congruances[j].m) != 1) {
                return false; // Found a pair with a common factor, not pairwise coprime
            }
        }
    }
    return true; // All moduli are pairwise coprime
}

/**
 * @brief Function to solve a system of linear congruences using the Chinese
 * Remainder Theorem (CRT).
 *
 * @param an Array of integers representing the remainders of the congruences.
 * @param m Array of pairwise coprime integers representing the moduli of the
 * congruences.
 * @param n Number of congruences in the system.
 * @return The solution to the system of congruences.
 */
int chinese_remainder_theorem(
    const std::vector<LinearCongruance> &congruances) {
    if (congruances.empty()) {
        throw std::invalid_argument("The system of congruences is empty.");
    }

    if (!are_moduli_pairwise_coprime(congruances)) {
        throw std::invalid_argument("Moduli must be pairwise coprime.");
    }

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
    const std::vector<LinearCongruance> testCase1 = {
        LinearCongruance(2, 3), LinearCongruance(3, 4), LinearCongruance(1, 5)};
    assert(chinese_remainder_theorem(testCase1) == 11);

    // Additional test cases to handle various scenarios
    const std::vector<LinearCongruance> testCase2 = {
        LinearCongruance(2, 8), LinearCongruance(3, 4)};
    try {
        chinese_remainder_theorem(testCase2);
        assert(false); // The test should throw an exception, so this line won't be reached
    } catch (const std::exception &ex) {
        std::cout << "Caught exception: " << ex.what() << std::endl;
    }

    std::cout << "All tests have passed successfully!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    try {
        test(); // run self-test implementations
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1; // Return a non-zero value to indicate an error
    }
    return 0;
}
