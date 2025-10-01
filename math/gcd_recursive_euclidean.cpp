/**
 * @file
 * @brief Implementation of the [Euclidean
 * algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm) to find the
 * Greatest Common Divisor (GCD) using a recursive approach.
 *
 * @details
 * The Euclidean algorithm computes the GCD of two integers efficiently:
 * - Uses modulus instead of repeated subtraction (faster)
 * - Handles negative numbers and zero correctly
 *
 * ### Algorithm
 * For integers a and b:
 * 1. If b is 0, return |a|
 * 2. Otherwise, recursively compute GCD(b, a % b)
 *
 * ### Complexity
 * - Time Complexity: O(log(min(|a|, |b|)))
 * - Space Complexity: O(log(min(|a|, |b|))) due to recursion stack
 *
 * @author [Contributor](Optimize Recursive GCD: Use Modulus-Based Euclidean
 * Algorithm with Robust Edge Case Handling(https://github.com/kokatesaurabh))
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace math {
namespace gcd_recursive {

/**
 * @brief Compute GCD of two integers using recursive Euclidean algorithm
 * @param a First integer
 * @param b Second integer
 * @returns GCD of a and b
 * @throws std::invalid_argument if both a and b are zero
 */
int64_t gcd(int64_t a, int64_t b) {
    a = std::abs(a);
    b = std::abs(b);

    if (a == 0 && b == 0)
        throw std::invalid_argument("GCD(0,0) is undefined");

    if (b == 0)
        return a;

    return gcd(b, a % b);
}

}  // namespace gcd_recursive
}  // namespace math

/**
 * @brief Run comprehensive test cases
 */
static void test() {
    using math::gcd_recursive::gcd;

    // Basic positive numbers
    assert(gcd(48, 18) == 6);
    assert(gcd(56, 42) == 14);
    assert(gcd(17, 13) == 1);

    // Zero cases
    assert(gcd(0, 5) == 5);
    assert(gcd(7, 0) == 7);

    // Both zero (should throw)
    try {
        gcd(0, 0);
        assert(false);  // Should not reach here
    } catch (const std::invalid_argument&) {
    }

    // Negative numbers
    assert(gcd(-48, 18) == 6);
    assert(gcd(48, -18) == 6);
    assert(gcd(-48, -18) == 6);

    // Equal numbers
    assert(gcd(15, 15) == 15);
    assert(gcd(100, 100) == 100);

    // Multiples
    assert(gcd(25, 100) == 25);
    assert(gcd(17, 51) == 17);

    // Large numbers
    assert(gcd(123456789, 987654321) == 9);
    assert(gcd(1000000007, 1000000009) == 1);

    std::cout << "All GCD tests passed successfully!\n";
}

/**
 * @brief Demonstrate example usage
 */
static void demonstrate_usage() {
    using math::gcd_recursive::gcd;

    std::cout << "GCD Examples:\n";
    std::cout << "GCD(48, 18) = " << gcd(48, 18) << "\n";
    std::cout << "GCD(17, 13) = " << gcd(17, 13) << " (co-prime)\n";
    std::cout << "GCD(0, 15) = " << gcd(0, 15) << "\n";
    std::cout << "GCD(-48, 18) = " << gcd(-48, 18) << "\n";
    std::cout << "GCD(123456789, 987654321) = " << gcd(123456789, 987654321)
              << "\n";
}

int main() {
    test();
    demonstrate_usage();
    return 0;
}
