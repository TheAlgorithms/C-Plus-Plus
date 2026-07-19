/**
 * @file
 * @brief Implementation of the [Chinese Remainder
 * Theorem](https://en.wikipedia.org/wiki/Chinese_remainder_theorem)
 * @details
 * The Chinese Remainder Theorem (CRT) states that if \f$\gcd(a, b) = 1\f$,
 * then for any remainder \f$r_a\f$ modulo \f$a\f$ and any remainder \f$r_b\f$
 * modulo \f$b\f$, there exists a unique integer \f$n\f$ (modulo \f$a \cdot
 * b\f$) such that:
 * \f{eqnarray*}{
 *  n &\equiv& r_a \;\text{mod}\; a\\
 *  n &\equiv& r_b \;\text{mod}\; b
 * \f}
 *
 * **Algorithm:**
 * 1. Use the Extended Euclidean Algorithm to find \f$x, y\f$ such that
 *    \f$a \cdot x + b \cdot y = 1\f$
 * 2. Compute \f$n = r_a \cdot b \cdot y + r_b \cdot a \cdot x\f$
 * 3. Return \f$n \mod (a \cdot b)\f$
 *
 * An alternate approach computes modular inverses explicitly using the
 * Extended Euclidean Algorithm before combining the remainders.
 *
 * @author [Parv Jain](https://github.com/parvjain)
 * @see math/extended_euclid_algorithm.cpp,
 * math/modular_inverse_fermat_little_theorem.cpp
 */

#include <cassert>   /// for assert
#include <cstdint>   /// for std::int64_t
#include <iostream>  /// for IO operations
#include <tuple>     /// for std::tuple

/**
 * @namespace math
 * @brief Maths algorithms.
 */
namespace math {
/**
 * @namespace chinese_remainder_theorem
 * @brief Functions for the
 * [Chinese Remainder
 * Theorem](https://en.wikipedia.org/wiki/Chinese_remainder_theorem) algorithm.
 */
namespace chinese_remainder_theorem {

/**
 * @brief Extended Euclidean Algorithm to find coefficients \f$x\f$ and
 * \f$y\f$ such that \f$a \cdot x + b \cdot y = \gcd(a, b)\f$.
 * @param a first integer
 * @param b second integer
 * @return std::tuple containing coefficients (x, y)
 */
std::tuple<std::int64_t, std::int64_t> extended_euclid(std::int64_t a,
                                                       std::int64_t b) {
    if (b == 0) {
        return {1, 0};
    }
    auto [x, y] = extended_euclid(b, a % b);
    std::int64_t k = a / b;
    return {y, x - k * y};
}

/**
 * @brief Finds the unique solution \f$n\f$ modulo \f$(n_1 \cdot n_2)\f$ such
 * that \f$n \equiv r_1 \;(\text{mod}\; n_1)\f$ and
 * \f$n \equiv r_2 \;(\text{mod}\; n_2)\f$.
 *
 * Uses the direct formula derived from the Extended Euclidean Algorithm.
 *
 * @param n1 first modulus (must be coprime with n2)
 * @param r1 remainder when divided by n1
 * @param n2 second modulus (must be coprime with n1)
 * @param r2 remainder when divided by n2
 * @return the unique non-negative solution modulo \f$(n_1 \cdot n_2)\f$
 */
std::int64_t chinese_remainder_theorem(std::int64_t n1, std::int64_t r1,
                                       std::int64_t n2, std::int64_t r2) {
    auto [x, y] = extended_euclid(n1, n2);
    std::int64_t m = n1 * n2;
    std::int64_t n = r2 * x * n1 + r1 * y * n2;
    return ((n % m) + m) % m;  // ensure non-negative result
}

/**
 * @brief Computes the modular inverse of \f$a\f$ modulo \f$n\f$, i.e., finds
 * \f$a^{-1}\f$ such that \f$a \cdot a^{-1} \equiv 1 \;(\text{mod}\; n)\f$.
 * @param a the integer to invert
 * @param n the modulus
 * @return the modular inverse of a modulo n
 */
std::int64_t invert_modulo(std::int64_t a, std::int64_t n) {
    auto [b, _unused] = extended_euclid(a, n);
    if (b < 0) {
        b = ((b % n) + n) % n;
    }
    return b;
}

/**
 * @brief Alternate implementation of the Chinese Remainder Theorem that
 * explicitly computes modular inverses before combining the remainders.
 *
 * This computes the same result as chinese_remainder_theorem() but makes the
 * modular inverse step explicit, which can be useful for educational purposes.
 *
 * @param n1 first modulus (must be coprime with n2)
 * @param r1 remainder when divided by n1
 * @param n2 second modulus (must be coprime with n1)
 * @param r2 remainder when divided by n2
 * @return the unique non-negative solution modulo \f$(n_1 \cdot n_2)\f$
 */
std::int64_t chinese_remainder_theorem2(std::int64_t n1, std::int64_t r1,
                                        std::int64_t n2, std::int64_t r2) {
    std::int64_t x = invert_modulo(n1, n2);
    std::int64_t y = invert_modulo(n2, n1);
    std::int64_t m = n1 * n2;
    std::int64_t n = r2 * x * n1 + r1 * y * n2;
    return ((n % m) + m) % m;  // ensure non-negative result
}

}  // namespace chinese_remainder_theorem
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using math::chinese_remainder_theorem::chinese_remainder_theorem;
    using math::chinese_remainder_theorem::chinese_remainder_theorem2;
    using math::chinese_remainder_theorem::extended_euclid;
    using math::chinese_remainder_theorem::invert_modulo;

    // Test 1: Extended Euclidean Algorithm
    // 10 * (-1) + 6 * 2 = 2 = gcd(10, 6)
    assert((extended_euclid(10, 6) ==
            std::make_tuple<std::int64_t, std::int64_t>(-1, 2)));
    // 7 * (-2) + 5 * 3 = 1 = gcd(7, 5)
    assert((extended_euclid(7, 5) ==
            std::make_tuple<std::int64_t, std::int64_t>(-2, 3)));

    // Test 2: Modular Inverse
    // 2 * 3 = 6 ≡ 1 (mod 5)
    assert(invert_modulo(2, 5) == 3);
    // 8 ≡ 1 (mod 7), so 8^{-1} ≡ 1 (mod 7)
    assert(invert_modulo(8, 7) == 1);

    // Test 3: Chinese Remainder Theorem (direct method)
    // Find n such that n % 5 == 1 and n % 7 == 3
    // n = 31: 31 % 5 = 1 ✓ and 31 % 7 = 3 ✓
    assert(chinese_remainder_theorem(5, 1, 7, 3) == 31);

    // Test 4: Chinese Remainder Theorem (modular inverse method)
    assert(chinese_remainder_theorem2(5, 1, 7, 3) == 31);

    // Test 5: n % 3 == 2 and n % 5 == 3 → n = 8 (mod 15)
    // 8 % 3 = 2 ✓ and 8 % 5 = 3 ✓
    assert(chinese_remainder_theorem(3, 2, 5, 3) == 8);
    assert(chinese_remainder_theorem2(3, 2, 5, 3) == 8);

    // Test 6: n % 7 == 0 and n % 11 == 5 → n = 49 (mod 77)
    // 49 % 7 = 0 ✓ and 49 % 11 = 5 ✓
    assert(chinese_remainder_theorem(7, 0, 11, 5) == 49);
    assert(chinese_remainder_theorem2(7, 0, 11, 5) == 49);

    // Test 7: Larger coprime moduli — verify result satisfies both congruences
    std::int64_t result = chinese_remainder_theorem(11, 4, 13, 6);
    assert(result % 11 == 4);
    assert(result % 13 == 6);

    std::int64_t result2 = chinese_remainder_theorem2(11, 4, 13, 6);
    assert(result2 % 11 == 4);
    assert(result2 % 13 == 6);

    // Test 8: Both methods should always agree
    assert(chinese_remainder_theorem(17, 9, 23, 14) ==
           chinese_remainder_theorem2(17, 9, 23, 14));

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
