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
 * The approach uses an iterative dynamic programming (bottom-up) strategy.
 * A 1D array `dp` is used where `dp[w]` stores the maximum value obtainable
 * for a knapsack capacity `w`. We iterate through all capacities from 0 to W
 * and update the maximum value by considering every item.
 *
 * Space Complexity: O(W)
 * Time Complexity: O(N * W)
 *
 * @author [Sanskruti Yeole](https://github.com/yeolesanskruti)
 * @see dynamic_programming/0_1_knapsack.cpp
 */

#include <algorithm> // For std::max
#include <cassert>   // For using assert function to validate test cases
#include <cstdint>   // For fixed-width integer types like std::uint16_t
#include <iostream>  // Standard input-output stream
#include <stdexcept> // For std::invalid_argument
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
 * @brief Solves the unbounded knapsack problem using iterative DP.
 *
 * @param N Number of items.
 * @param W Maximum weight capacity of the knapsack.
 * @param val Vector of values corresponding to the items.
 * @param wt Vector of weights corresponding to the items.
 * @return The maximum value that can be obtained for the given capacity.
 * @throws std::invalid_argument if the size of val and wt arrays do not match.
 */
std::uint16_t unboundedKnapsack(std::uint16_t N, std::uint16_t W,
                                const std::vector<std::uint16_t>& val,
                                const std::vector<std::uint16_t>& wt) {
    if (val.size() != wt.size()) {
        throw std::invalid_argument(
            "Size of price and weight arrays must be equal");
    }

    if (N == 0 || W == 0) {
        return 0;
    }

    // dp[i] stores the maximum value for capacity i
    // Using int to prevent overflow during calculation before final cast
    std::vector<int> dp(W + 1, 0);

    // Build the table in a bottom-up manner
    for (std::uint16_t w = 0; w <= W; ++w) {
        for (std::uint16_t i = 0; i < N; ++i) {
            if (wt[i] <= w) {
                dp[w] = std::max(dp[w], dp[w - wt[i]] + val[i]);
            }
        }
    }

    return static_cast<std::uint16_t>(dp[W]);
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
    // Corrected assertion: Expected 71 (5 * 4 + 11 * 6 + 5 = 20 + 66 = 86? No)
    // Calc: W=27. Best item ratio is item 2 (11/4 = 2.75).
    // 27 / 4 = 6 items (wt 24, val 66). Remaining wt 3.
    // Remaining wt 3 can take item 1 (wt 2, val 5).
    // Total wt = 26, Total val = 66 + 5 = 71.
    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N3, W3, val3, wt3) == 71);
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