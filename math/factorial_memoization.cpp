/**
 * @file
 * @brief [Factorial calculation using recursion and memoization (dynamic programming)](https://en.wikipedia.org/wiki/Factorial)
 * @details
 * This program computes the factorial of a non-negative integer using recursion
 * with memoization (top-down dynamic programming). It stores intermediate results
 * to avoid redundant calculations for improved efficiency.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * @author [Vedant Mukhedkar](https://github.com/git5v)
 */

#include <iostream>
#include <cassert>  // For test cases
#include <array> 
/// Array to store computed factorials for memoization
std::array<__uint128_t, 1000> memo{0};

/**
 * @brief Computes the factorial of a non-negative integer using recursion and memoization.
 * @param n The integer whose factorial is to be computed
 * @returns The factorial of n
 */
__uint128_t fact_rec(__uint128_t  n) {
    if (n == 0) return 1;        // Base case: 0! = 1
    if (memo[n] != 0) return memo[n]; // Return already computed value
    memo[n] = n * fact_rec(n - 1);    // Store and return the computed value
    return memo[n];
}

/**
 * @brief Self-test implementations for the fact_rec function.
 * @returns void
 */
void test_fact_rec() {
    // Test cases for factorial computation
    assert(fact_rec(0) == 1);
    assert(fact_rec(1) == 1);
    assert(fact_rec(5) == 120);
    assert(fact_rec(10) == 3628800);
    std::cout << "All test cases passed!\n";
}

/**
 * @brief Main function to run test cases and interact with the user.
 * @returns 0 on program success
 */
int main() {
    // Run test cases
    test_fact_rec();
    return 0;
}
