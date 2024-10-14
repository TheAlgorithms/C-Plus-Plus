/**
 * @file
 * @brief Given an integer array nums and an integer k, split nums into k
 * non-empty subarrays such that the largest sum of any subarray is minimized.
 * Return the minimized largest sum of the split.

 * @details
 * Example 1:

    * Input: nums = [7,2,5,10,8], k = 2
    * Output: 18
    * Explanation: There are four ways to split nums into two subarrays.
    * The best way is to split it into [7,2,5] and [10,8], where the largest sum
    * among the two subarrays is only 18.
  
 * Example 2:

    * Input: nums = [1,2,3,4,5], k = 2
    * Output: 9
    * Explanation: There are four ways to split nums into two subarrays.
    * The best way is to split it into [1,2,3] and [4,5], where the largest sum
    * among the two subarrays is only 9.

 * @author [ARYA PRATAP SINGH](https://github.com/ARYPROGRAMMER)
 * [Leetcode](https://leetcode.com/problems/split-array-largest-sum/description/?envType=problem-list-v2&envId=dynamic-programming)
 */

// header files
#include <iostream>
#include <iomanip>
#include <cstdint>

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming{
    /**
     * @namespace split_array_largest_sum
     * @brief split_array_largest_sum algorithm
     */
    namespace split_array_largest_sum{

        /**
         * @brief This function calculates the minimum largest sum of the split
         * @param nums integer array
         * @param k integer
         * @
         */

        int dp[1003][53];

        int f(int i, int j, vector<int>& v) {
            if (j < 0) {
                if (i < 0)
                    return -1;
                return INT_MAX;
            }
            if (i < 0)
                return INT_MAX;
            if (dp[i][j] != -1)
                return dp[i][j];

            int res = INT_MAX, sum = 0;
            for (int k = i; k >= 0; k--) {
                sum += v[k];
                res = min(res, max(sum, f(k - 1, j - 1, v)));
            }

            return dp[i][j] = res;
            }

        int splitArray(vector<int>& nums, int k) {
            memset(dp, -1, sizeof(dp));
            return f(nums.size() - 1, k - 1, nums);
        }
    }
}

/**
 * Test Function
 * @return void
 */
static void test() {
    // custom input vector
    std::vector<int> v{
        7,2,5,10,8,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
    };
    // custom value of k
    int k = 5;
   
    //calling the function
    int ans = dynamic_programming::split_array_largest_sum::splitArray(v, k);

    // expected output
    int expectedOutput = 30;
    
    // Testing implementation via assert function
    // It will throw error if any of the expected test fails
    // Else it will give nothing
    assert(ans == expectedOutput);

    std::cout << "All tests passed successfully!\n";
    return;
}

/** Main function (driver code)*/
int main() {
    // test for implementation
    test();

    // user input
    int n;
    std::cout << "Enter the number of elements in the array : ";
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Enter the elements of the array : ";
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    int k;
    std::cout << "Enter the value of k : ";
    std::cin >> k;

    int ans;

    // user output
    ans = dynamic_programming::split_array_largest_sum::splitArray(v, k);
    std::cout << "The minimum largest sum of the split is : " << ans << std::endl;
    return 0;
}
