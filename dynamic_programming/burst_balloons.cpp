/**
 * @file
 * @brief Implementation of Burst Balloons problem
 *
 * @details
 * You are given `n` balloons, each with a number on it represented by an array
 * `nums`. You are asked to burst all the balloons. If you burst the `i-th`
 * balloon, you will get `nums[i - 1] * nums[i] * nums[i + 1]` coins. The goal
 * is to maximize the coins collected by bursting the balloons wisely.
 *
 * ### Algorithm
 * We use dynamic programming with memoization. For each subproblem defined by
 * bursting a balloon at index `k`, we calculate the maximum coins from two
 * smaller subproblems and store the results for future use to avoid recalculations.
 *
 * @author [Saptarshi Ghosh](https://github.com/codec404)
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace burst_balloons
 * @brief Implementation of the Burst Balloons problem
 */
namespace burst_balloons {

/**
 * @brief Recursive function to calculate maximum coins
 * @param i Start index of the range of balloons
 * @param j End index of the range of balloons
 * @param nums Vector of balloon numbers
 * @param dp Memoization table to store intermediate results
 * @return Maximum coins obtainable by bursting balloons from index i to j
 */
int recurse(int i, int j, vector<int> &nums, vector<vector<int>> &dp) {
    if (i > j) {
        return 0;
    }
    if (dp[i][j] != -1) return dp[i][j];

    int maxi = 0;
    for (int k = i; k <= j; k++) {
        int coins = (nums[i - 1] * nums[k] * nums[j + 1])
                    + recurse(i, k - 1, nums, dp)
                    + recurse(k + 1, j, nums, dp);
        maxi = max(maxi, coins);
    }
    return dp[i][j] = maxi;
}

/**
 * @brief Function to calculate the maximum coins obtainable by bursting balloons
 * @param nums Vector of balloon numbers
 * @return Maximum coins that can be collected
 */
int maxCoins(vector<int> &nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);  // Add 1 at the beginning
    nums.push_back(1);  // Add 1 at the end
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));  // Memoization table
    return recurse(1, n, nums, dp);  // Solve the problem for the full array
}

}  // namespace burst_balloons
}  // namespace dynamic_programming

/**
 * @brief Function to test the Burst Balloons algorithm
 * @returns void
 */
static void test() {
    // Test 1: Example from the problem statement
    vector<int> nums1 = {3, 1, 5, 8};  // Input array
    int expected_result1 = 167;  // Expected output
    int result1 = dynamic_programming::burst_balloons::maxCoins(nums1);
    assert(result1 == expected_result1);
    cout << "Test 1 passed: Maximum coins = " << result1 << endl;

    // Test 2: Another example
    vector<int> nums2 = {1, 5};  // Input array
    int expected_result2 = 10;  // Expected output
    int result2 = dynamic_programming::burst_balloons::maxCoins(nums2);
    assert(result2 == expected_result2);
    cout << "Test 2 passed: Maximum coins = " << result2 << endl;

    // Test 3: Single balloon
    vector<int> nums3 = {9};  // Input array
    int expected_result3 = 9;  // Expected output
    int result3 = dynamic_programming::burst_balloons::maxCoins(nums3);
    assert(result3 == expected_result3);
    cout << "Test 3 passed: Maximum coins = " << result3 << endl;

    // Test 4: Larger input
    vector<int> nums4 = {100,23,15,10,24,12,22,10};  // Input array
    int expected_result4 = 156336;  // Expected output
    int result4 = dynamic_programming::burst_balloons::maxCoins(nums4);
    assert(result4 == expected_result4);
    cout << "Test 4 passed: Maximum coins = " << result4 << endl;
}

/**
 * @brief Main function to run tests
 * @returns 0 on exit
 */
int main() {
    // Run tests
    test();
    return 0;
}
