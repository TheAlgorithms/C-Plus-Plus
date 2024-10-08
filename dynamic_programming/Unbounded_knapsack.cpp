/**
 * @file
 * @brief Unbounded Knapsack problem using Dynamic Programming
 * @details 
 * The Unbounded Knapsack problem allows you to take unlimited quantities of each item. The goal is to maximize the total 
 * value without exceeding the given knapsack capacity. Unlike the 0/1 knapsack, where each item can be taken only once, 
 * in this variation, you can pick any item as many times as needed, as long as the total weight stays within the knapsack's capacity. 
 * 
 * @task Given a set of N items, each with a weight and a value, represented by the array `wt` and `val` respectively, and a knapsack 
 * with a weight limit W, the task is to fill the knapsack in such a way that the maximum profit is obtained. Return the maximum profit.
 * 
 * Note: Each item can be taken any number of times.
 *
 * @author [Sanskruti Yeole](https://github.com/yeolesanskruti)
 * @see dynamic_programming/Unbounded_knapsack.cpp
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint> // for std::uint16_t

/**
 * @brief Recursive function to calculate the maximum value that can be obtained
 *        using an unbounded knapsack approach.
 *
 * @param i Current index in the value and weight vectors.
 * @param W Remaining capacity of the knapsack.
 * @param val Vector of values corresponding to the items.
 * @param wt Vector of weights corresponding to the items.
 * @param dp 2D vector for memoization to avoid redundant calculations.
 * @return The maximum value that can be obtained for the given index and capacity.
 */
int KnapSackFilling(std::uint16_t i, std::uint16_t W, const std::vector<std::uint16_t>& val, const std::vector<std::uint16_t>& wt, std::vector<std::vector<int>>& dp) {
    if (i == 0) {
        if (wt[0] <= W) {
            return (W / wt[0]) * val[0];
        } else {
            return 0;
        }
    }
    if (dp[i][W] != -1) return dp[i][W];
    
    int nottake = KnapSackFilling(i - 1, W, val, wt, dp);
    int take = 0;
    if (W >= wt[i]) {
        take = val[i] + KnapSackFilling(i, W - wt[i], val, wt, dp);
    }
    return dp[i][W] = std::max(take, nottake);
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
int unboundedKnapsack(std::uint16_t N, std::uint16_t W, const std::vector<std::uint16_t>& val, const std::vector<std::uint16_t>& wt) {
    std::vector<std::vector<int>> dp(N, std::vector<int>(W + 1, -1));
    return KnapSackFilling(N - 1, W, val, wt, dp);
}

/**
 * @brief Function to run test cases for the unbounded knapsack implementation.
 */
void test_cases() {
    std::uint16_t N = 4; // Number of items
    std::vector<std::uint16_t> wt = {1, 3, 4, 5}; // Weights of the items
    std::vector<std::uint16_t> val = {6, 1, 7, 7}; // Values of the items
    std::uint16_t W = 8; // Maximum capacity of the knapsack

    // Test the function and assert the expected output
    assert(unboundedKnapsack(N, W, val, wt) == 48);
    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_cases();
    return 0;
}
