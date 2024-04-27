/**
 * @file
 * @brief Implementation of [Unbounded Knapsack
 * Problem](https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/)
 *
 * @details
 * Given weights and values of n items, put these items in a knapsack
 * of capacity `W` to get the maximum total value in the knapsack. In other
 * words, given two integer arrays `val[0..n-1]` and `wt[0..n-1]` which
 * represent values and weights associated with n items respectively. Also given
 * an integer W which represents knapsack capacity, find out the maximum value
 * subset of `val[]` such that sum of the weights of this subset is smaller than
 * or equal to W. You cannot break an item, either pick the complete item or
 * don’t pick it, and you can use an item multiple times (unbounded property).
 *
 * @author [mrmagic2020](https://github.com/mrmagic2020)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations
#include <vector>    /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace unbounded_knapsack
 * @brief Implementation of Unbounded Knapsack Problem
 */
namespace unbounded_knapsack {

/**
 * @brief Calculates the maximum value that can be obtained by filling a
 * knapsack of given capacity.
 *
 * @param capacity The maximum weight capacity of the knapsack.
 * @param weight The vector of weights of the items.
 * @param value The vector of values of the items.
 * @return The maximum value that can be obtained by filling the knapsack.
 */
int maxKnapsackValue(const int capacity, const std::vector<int> &weight,
                     const std::vector<int> &value) {
    size_t n = weight.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    // Outer loop will select no of items allowed
    // Inner loop will select the capacity of the knapsack bag
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 0; j <= capacity; j++) {
            if (weight[i - 1] <= j) {
                // If the weight of the current item is less than or equal to
                // the capacity of the knapsack, then we have two choices:

                // 1. Do not take the item.
                int no_take = dp[i - 1][j];

                // 2. Take the item. Because we can
                // take the same item multiple times,
                // we use dp[i] instead of dp[i-1].
                int take = value[i - 1] + dp[i][j - weight[i - 1]];

                // Select the maximum value.
                dp[i][j] = std::max(no_take, take);
            } else {
                // If the weight of the current item is greater than the
                // capacity of the knapsack, then we cannot take the item.
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][capacity];
}
}  // namespace unbounded_knapsack
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Test case 1
    const int capacity1 = 100;
    std::vector<int> weight1 = {10, 20, 30};
    std::vector<int> value1 = {60, 100, 120};
    const int max_value1 =
        dynamic_programming::unbounded_knapsack::maxKnapsackValue(
            capacity1, weight1, value1);
    const int expected_value1 = 600;
    assert(max_value1 == expected_value1);
    std::cout << "Maximum knapsack value with 3 items is " << max_value1
              << std::endl;

    // Test case 2
    const int capacity2 = 100;
    std::vector<int> weight2 = {77, 22, 29, 50, 99};
    std::vector<int> value2 = {92, 22, 87, 46, 90};
    const int max_value2 =
        dynamic_programming::unbounded_knapsack::maxKnapsackValue(
            capacity2, weight2, value2);
    const int expected_value2 = 261;
    assert(max_value2 == expected_value2);
    std::cout << "Maximum knapsack value with 5 items is " << max_value2
              << std::endl;

    // Test case 3
    const int capacity3 = 5;
    std::vector<int> weight3 = {1, 2, 3, 4};
    std::vector<int> value3 = {2, 4, 4, 5};
    const int max_value3 =
        dynamic_programming::unbounded_knapsack::maxKnapsackValue(
            capacity3, weight3, value3);
    const int expected_value3 = 10;
    assert(max_value3 == expected_value3);
    std::cout << "Maximum knapsack value with 4 items is " << max_value3
              << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Run self-test implementations
    test();
    return 0;
}