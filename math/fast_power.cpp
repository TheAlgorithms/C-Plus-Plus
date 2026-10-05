/**
 * @file
 * @brief Faster computation for \f$a^b\f$
 *
 * Implements recursive and iterative binary exponentiation
 * for efficient computation of a raised to the power b in
 * O(log n) time.
 * It is based on the following formulas:
 * 1. if \f$b\f$ is even:
 *  \f$a^b = a^\frac{b}{2} \cdot a^\frac{b}{2} = {a^\frac{b}{2}}^2\f$
 * 2. if \f$b\f$ is odd: \f$a^b = a^\frac{b-1}{2}
 *  \cdot a^\frac{b-1}{2} \cdot a = {a^\frac{b-1}{2}}^2 \cdot a\f$
 *
 * The recursive implementation applies these identities to compute
 * \f$a^b\f$ efficiently.
 */

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * @brief Computes a^b using recursive binary exponentiation.
 *
 * @tparam T Numeric type.
 * @param a Base value.
 * @param b Exponent.
 * @returns a raised to the power b.
 *
 * @note Time Complexity: O(log b)
 * @note Space Complexity: O(log b) due to recursion.
 */
template <typename T>
double fast_power_recursive(T a, T b) {
    // Handle negative exponents using a^(-b) = 1 / a^b.
    if (b < 0)
        return 1.0 / fast_power_recursive(a, -b);

    if (b == 0)
        return 1;
    const T half_power = fast_power_recursive(a, b >> 1);
    // Since integer division gives b/2 == (b-1)/2 for odd b,
    // the odd exponent case is handled naturally.

    if ((b & 1) == 0) {
        return half_power * half_power;
    }

    return half_power * half_power * a;
}

/**
 * @brief Computes a^b using iterative binary exponentiation.
 *
 * @tparam T Numeric type.
 * @param a Base value.
 * @param b Exponent.
 * @returns a raised to the power b.
 *
 * @note Time Complexity: O(log b)
 * @note Space Complexity: O(1)
 */
template <typename T>
double fast_power_linear(T a, T b) {
    // Handle negative exponents using a^(-b) = 1 / a^b.
    if (b < 0)
        return 1.0 / fast_power_linear(a, -b);

    double result = 1;
    while (b) {
        if (b & 1)
            result *= a;
        a *= a;
        b >>= 1;
    }
    return result;
}
/**
 * @brief Demonstrates and tests the fast exponentiation algorithms.
 *
 * @return 0 on successful execution.
 */
int main() {
    std::srand(std::time(nullptr));
    std::ios_base::sync_with_stdio(false);

    std::cout << "Testing..." << std::endl;

    for (int i = 0; i < 20; i++) {
        int a = std::rand() % 20 - 10;
        int b = std::rand() % 20 - 10;

        std::cout << std::endl << "Calculating " << a << "^" << b << std::endl;

        assert(fast_power_recursive(a, b) == std::pow(a, b));
        assert(fast_power_linear(a, b) == std::pow(a, b));

        std::cout << "------ " << a << "^" << b << " = "
                  << fast_power_recursive(a, b) << std::endl;
    }

    int64_t a, b;
    std::cin >> a >> b;

    std::cout << a << "^" << b << " = " << fast_power_recursive(a, b)
              << std::endl;

    std::cout << a << "^" << b << " = " << fast_power_linear(a, b)
              << std::endl;

    return 0;
}
   