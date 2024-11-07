/**
 * @file
 * @brief Implementation of the Unbounded 0/1 Knapsack Problem
 *
 * @details
 * The Unbounded 0/1 Knapsack problem allows taking unlimited quantities of each
 * item. The goal is to maximize the total value without exceeding the given
 * knapsack capacity. Unlike the 0/1 knapsack, where each item can be taken only
 * once, in this variation, any item can be picked any number of times as long
 * as the total weight stays within the knapsack's capacity.
 *
 * Given a set of N items, each with a weight and a value, represented by the
 * arrays `wt` and `val` respectively, and a knapsack with a weight limit W, the
 * task is to fill the knapsack to maximize the total value.
 *
 * @note weight and value of items is greater than zero
 *
 * ### Algorithm
 * The approach uses dynamic programming to build a solution iteratively.
 * A 2D array is used for memoization to store intermediate results, allowing
 * the function to avoid redundant calculations.
 *
 * @author [Sanskruti Yeole](https://github.com/yeolesanskruti)
 * @see dynamic_programming/0_1_knapsack.cpp
 */

#include <cassert>   // For using assert function to validate test cases
#include <cstdint>   // For fixed-width integer types like std::uint16_t
#include <iostream>  // Standard input-output stream
#include <vector>    // Standard library for using dynamic arrays (vectors)

/**
 * @namespace dynamic_programming
 * @brief Namespace for dynamic programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace Knapsack
 * @brief Implementation of unbounded 0-1 knapsack problem
 */
namespace unbounded_knapsack {

/**
 * @brief Recursive function to calculate the maximum value obtainable using
 *        an unbounded knapsack approach.
 *
 * @param i Current index in the value and weight vectors.
 * @param W Remaining capacity of the knapsack.
 * @param val Vector of values corresponding to the items.
 * @note "val" data type can be changed according to the size of the input.
 * @param wt Vector of weights corresponding to the items.
 * @note "wt" data type can be changed according to the size of the input.
 * @param dp 2D vector for memoization to avoid redundant calculations.
 * @return The maximum value that can be obtained for the given index and
 * capacity.
 */
std::uint16_t KnapSackFilling(std::uint16_t i, std::uint16_t W,
                              const std::vector<std::uint16_t>& val,
                              const std::vector<std::uint16_t>& wt,
                              std::vector<std::vector<int>>& dp) {
    if (i == 0) {
        if (wt[0] <= W) {
            return (W / wt[0]) *
                   val[0];  // Take as many of the first item as possible
        } else {
            return 0;  // Can't take the first item
        }
    }
    if (dp[i][W] != -1)
        return dp[i][W];  // Return result if available

    int nottake =
        KnapSackFilling(i - 1, W, val, wt, dp);  // Value without taking item i
    int take = 0;
    if (W >= wt[i]) {
        take = val[i] + KnapSackFilling(i, W - wt[i], val, wt,
                                        dp);  // Value taking item i
    }
    return dp[i][W] =
               std::max(take, nottake);  // Store and return the maximum value
}

/**
 * @brief Wrapper function to initiate the unbounded knapsack calculation.
 *
 * @param N Number of items.
 * @param W Maximum weight capacity of the knapsack.
 * @param val Vector of values corresponding to the items.
 * @param wt Vector of weights corresponding to the items.
 * @return The maximum value that can be obtained for the given capacity.
 */
std::uint16_t unboundedKnapsack(std::uint16_t N, std::uint16_t W,
                                const std::vector<std::uint16_t>& val,
                                const std::vector<std::uint16_t>& wt) {
    if (N == 0)
        return 0;  // Expect 0 since no items
    std::vector<std::vector<int>> dp(
        N, std::vector<int>(W + 1, -1));  // Initialize memoization table
    return KnapSackFilling(N - 1, W, val, wt, dp);  // Start the calculation
}

}  // namespace unbounded_knapsack

}  // namespace dynamic_programming

/**
 * @brief self test implementation
 * @return void
 */
static void tests() {
    // Test Case 1
    std::uint16_t N1 = 4;                            // Number of items
    std::vector<std::uint16_t> wt1 = {1, 3, 4, 5};   // Weights of the items
    std::vector<std::uint16_t> val1 = {6, 1, 7, 7};  // Values of the items
    std::uint16_t W1 = 8;  // Maximum capacity of the knapsack
    // Test the function and assert the expected output
    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N1, W1, val1, wt1) == 48);
    std::cout << "Maximum Knapsack value "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N1, W1, val1, wt1)
              << std::endl;

    // Test Case 2
    std::uint16_t N2 = 3;                              // Number of items
    std::vector<std::uint16_t> wt2 = {10, 20, 30};     // Weights of the items
    std::vector<std::uint16_t> val2 = {60, 100, 120};  // Values of the items
    std::uint16_t W2 = 5;  // Maximum capacity of the knapsack
    // Test the function and assert the expected output
    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N2, W2, val2, wt2) == 0);
    std::cout << "Maximum Knapsack value "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N2, W2, val2, wt2)
              << std::endl;

    // Test Case 3
    std::uint16_t N3 = 3;                           // Number of items
    std::vector<std::uint16_t> wt3 = {2, 4, 6};     // Weights of the items
    std::vector<std::uint16_t> val3 = {5, 11, 13};  // Values of the items
    std::uint16_t W3 = 27;  // Maximum capacity of the knapsack
    // Test the function and assert the expected output
    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N3, W3, val3, wt3) == 27);
    std::cout << "Maximum Knapsack value "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N3, W3, val3, wt3)
              << std::endl;

    // Test Case 4
    std::uint16_t N4 = 0;                  // Number of items
    std::vector<std::uint16_t> wt4 = {};   // Weights of the items
    std::vector<std::uint16_t> val4 = {};  // Values of the items
    std::uint16_t W4 = 10;                 // Maximum capacity of the knapsack
    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N4, W4, val4, wt4) == 0);
    std::cout << "Maximum Knapsack value for empty arrays: "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N4, W4, val4, wt4)
              << std::endl;

    std::cout << "All test cases passed!" << std::endl;
}

/**
 * @brief main function
 * @return 0 on successful exit
 */
int main() {
    tests();  // Run self test implementation
    return 0;
}
