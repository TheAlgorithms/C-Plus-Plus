/**
 * @file
 * @brief [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)
 * 
 * Given an integer array `nums` and an integer `k`, this program splits the 
 * array into `k` non-empty subarrays such that the largest sum of any subarray is minimized.
 * This function returns the minimized largest sum of the split.
 * 
 * @details
 * ### Problem Explanation:
 * Example 1:
 * - Input: nums = [7,2,5,10,8], k = 2
 * - Output: 18
 * - Explanation: The best way to split it into two subarrays is [7,2,5] and [10,8],
 *   where the largest sum among the two subarrays is 18.
 * 
 * Example 2:
 * - Input: nums = [1,2,3,4,5], k = 2
 * - Output: 9
 * - Explanation: The best way to split it into two subarrays is [1,2,3] and [4,5],
 *   where the largest sum among the two subarrays is 9.
 * 
 * ### Approach:
 * Dynamic Programming is used to minimize the largest subarray sum by 
 * splitting the array into `k` subarrays.
 * 
 * ### Time Complexity:
 * O(n^2 * k), where `n` is the size of the array and `k` is the number of subarrays.
 * 
 * ### Space Complexity:
 * O(n * k), for the DP table.
 * 
 * @author 
 * [ARYA PRATAP SINGH](https://github.com/ARYPROGRAMMER)
 */

#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <cassert>

namespace dynamic_programming {
    namespace split_array_largest_sum {

        // DP table for memoization
        int dp[1003][53];

        /**
         * @brief Recursive function to calculate minimum largest sum of split
         * @param i current index in the array
         * @param j number of subarrays remaining
         * @param v reference to input vector of numbers
         * @return minimized largest sum for current split configuration
         */
        int f(int i, int j, const std::vector<int> &v) {
            if (j < 0) return (i < 0) ? -1 : INT_MAX;
            if (i < 0) return INT_MAX;
            if (dp[i][j] != -1) return dp[i][j];

            int res = INT_MAX, sum = 0;
            for (int k = i; k >= 0; --k) {
                sum += v[k];
                res = std::min(res, std::max(sum, f(k - 1, j - 1, v)));
            }
            return dp[i][j] = res;
        }

        /**
         * @brief Function to split array and find minimized largest sum
         * @param nums vector of integers representing the array
         * @param k number of subarrays
         * @return minimized largest sum of any subarray after split
         */
        int splitArray(const std::vector<int> &nums, int k) {
            std::memset(dp, -1, sizeof(dp));
            return f(nums.size() - 1, k - 1, nums);
        }
    }
}

/**
 * @brief Test Function
 * This function tests the `splitArray` function by using custom input.
 */
static void test() {
    std::vector<int> test_array = {7, 2, 5, 10, 8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int k = 5;
    
    // Calling the function
    int result = dynamic_programming::split_array_largest_sum::splitArray(test_array, k);
    
    // Expected output
    int expected = 30;

    // Testing using assert
    assert(result == expected);
    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Function to handle user input and output.
 * This function gathers input from the user and calls the `splitArray` function.
 */
void handleUserIO() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    std::vector<int> nums(n);
    std::cout << "Enter the elements of the array: ";
    for (int &num : nums) {
        std::cin >> num;
    }

    int k;
    std::cout << "Enter the value of k: ";
    std::cin >> k;

    int result = dynamic_programming::split_array_largest_sum::splitArray(nums, k);
    std::cout << "The minimum largest sum of the split is: " << result << std::endl;
}

/**
 * @brief Main Function (driver code)
 * This function calls test cases and handles user input/output.
 */
int main() {
    // Running test cases
    test();

    // Handling user input/output
    handleUserIO();

    return 0;
}
