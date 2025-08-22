/**
 * @file
 * @brief [Factorial](https://en.wikipedia.org/wiki/Factorial) calculation using recursion and [memoization](https://en.wikipedia.org/wiki/Memoization) 
 * @details
 * This program computes the factorial of a non-negative integer using recursion
 * with memoization (top-down dynamic programming). It stores intermediate results
 * to avoid redundant calculations for improved efficiency.
 * 
 * Memoization is a form of caching where the result to an expensive function call
 * is stored and returned.
 * Example:
 * Input: n = 5
 * Output: 120
 * 
 * Explanation: 5! = 5 × 4 × 3 × 2 × 1 = 120
 * 
 * The program uses a recursive function fact_recursion which caches computed 
 * results in a memo array to avoid recalculating factorials for the same numbers.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * @author [Vedant Mukhedkar](https://github.com/git5v)
 */

#include <iostream> // for std::cout
#include <cassert>  // For test cases
#include <array>    // For std::array
#include <cstdint>  // For uint64_t

/// Array to store computed factorials for memoization
std::array<uint64_t, 1000> memo{0};

/**
 * @namespace math
 * @brief Math algorithms
 */
namespace math {

/**
 * @brief Computes the factorial of a non-negative integer using recursion and memoization.
 * @param n The integer whose factorial is to be computed
 * @returns The factorial of n
 */
uint64_t fact_recursion(uint64_t n) {
    if (n == 0) return 1;        // Base case: 0! = 1
    if (memo[n] != 0) return memo[n]; // Return already computed value
    memo[n] = n * fact_recursion(n - 1);    // Store and return the computed value
    return memo[n];
}

} // namespace math
/**
 * @brief Self-test implementations for the fact_recursion function.
 * @returns void
 */
void test_fact_recursion() {
    // Test cases for factorial computation
    assert(math::fact_recursion(0) == 1);
    assert(math::fact_recursion(1) == 1);
    assert(math::fact_recursion(5) == 120);
    assert(math::fact_recursion(10) == 3628800);
    std::cout << "All test cases passed!\n";
}

/**
 * @brief Main function to run test cases and interact with the user.
 * @returns 0 on program success
 */
int main() {
    // Run test cases
    test_fact_recursion();
    return 0;
}
