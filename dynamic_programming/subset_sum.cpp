/**
 * @file
 * @brief [Subset Sum Problem](https://en.wikipedia.org/wiki/Subset_sum_problem)
 *                      (https://www.geeksforgeeks.org/subset-sum-problem-dp-25)
 * @details
 * Given a set of non-negative integers, and a value sum, determine if there is
 * a subset of the given set with sum equal to given sum. 
 *
 * This problem can be solved using 2 methods:
 * 1. Top down approach  : memoization approach
 * 2. Bottom up appraoch : tabular approach
 * Overall time complexity of coin change problem is O(n*sum)
 *
 * 
 * Example 1:
 * Input: set[] = {3, 34, 4, 12, 5, 2}, sum = 9
 * Output: true
 * Explanation: Return true because There is a subset (4, 5) with sum 9.
 *
 * Example 2:
 * Input: set[] = {3, 34, 4, 12, 5, 2}, sum = 30
 * Output: false
 * Explanation: There is no subset that add up to 30.
 *
 * @author [Vinay Garg] (https://github.com/Vinay-Garg)
 */

#include <array>       /// for std::array
#include <cassert>    /// for assert
#include <iostream>   /// for io operations
#include <vector>     /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace subset_sum_bottomup
* @brief Bottom up implementation of [Subset Sum Problem](https://en.wikipedia.org/wiki/Subset_sum_problem)
 */
namespace subset_sum_bottomup {
/**
 * @brief This is bottom up implemenation for checking if a subset 
 * exists for the given sum value
 * @tparam n size of the set array
 * @param set an array of numbers in set of size<=n
 * @param sum subset sum value
 * @returns true if there is a subset of set with sum equal to given sum
 */
template <size_t n>
bool subset_sum(const std::array<int, n> &set, const int sum) {
	// The value of subset[i][j] will be true if
    // there is a subset of set[0..j-1] with sum
    // equal to i
	std::vector<std::vector<bool>> subset(n + 1 , std::vector<bool> (sum + 1));
 
    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
        subset[i][0] = true;
 
    // If sum is not 0 and set is empty,
    // then answer is false
    for (int i = 1; i <= sum; i++)
        subset[0][i] = false;
 
    // Fill the subset table in botton up manner
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j >= set[i - 1]) {
                subset[i][j] = subset[i - 1][j] || 
							   subset[i - 1][j - set[i - 1]];
			}
			else {
                subset[i][j] = subset[i - 1][j];
			}
        }
    }
	bool ans = subset[n][sum];
	return ans;
} 

}  // namespace subset_sum_bottomup


/**
 * @namespace subset_sum_topdown
 * @brief Top down implementation of [Subset Sum Problem](https://en.wikipedia.org/wiki/Subset_sum_problem)
 */
namespace subset_sum_topdown {
/**
 * @brief This is top down implemenation is for checking if a subset 
 * exists for the given sum value
 * @tparam T template-type to use any kind of value
 * @param set 	: an array of numbers in set of size<=n
 * @param n 	: size of the set array
 * @param sum 	: subset sum value
 * @param dp initilised to -1
 * @returns true if there is a subset of set with sum equal to given sum
 */
template <typename T>
bool subset_sum(const std::vector<T> &set, const T &n, const T &sum,
						 std::vector<std::vector<T>> &dp) {
    if (sum == 0) {   // if sum is zero , return true
        return true;
    }
    if (sum < 0) {   // if sum is negative , return true
        return false;
	}
    if (n < 1) {
        return false;
	}
    if(dp[n][sum] != -1) {
        return dp[n][sum];
	}

	// include last element of set in vector v and
	// search for sunset with sum value equals sum-set[n-1] 
    bool inc =  subset_sum(set, n - 1, sum - set[n - 1],dp);

    // exclude last element of set in vector v and
	// search for sunset with sum value equals sum
    bool exc =  subset_sum(set, n - 1, sum,dp);

    return dp[n][sum] = inc || exc;
}

}  // namespace subset_sum_topdown

}  // namespace dynamic_programming

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Test 1
    const int n1 = 6;
	std::array<int, n1> set1 = { 3, 34, 4, 12, 5, 2 };
	const int sum1 = 9;
    const bool ans1 =
        dynamic_programming::subset_sum_bottomup::subset_sum(set1,sum1);
    const bool expected_ans1 = true;
    assert(ans1 == expected_ans1);
    std::cout << "subset exists with sum " << sum1 
              << std::endl;

    // Test 2
    const int n2 = 6;
	std::array<int, n2> set2 = { 3, 34, 4, 12, 5, 2 };
	const int sum2 = 30;
    const bool ans2 =
        dynamic_programming::subset_sum_bottomup::subset_sum(set2,sum2);
    const bool expected_ans2 = false;
    assert(ans2 == expected_ans2);
    std::cout << "subset doesn't exists with sum " << sum2 
              << std::endl;

    // Test 3
    const int n3 = 6;
	std::vector<int> set3 = { 3, 34, 4, 12, 5, 2 };
	const int sum3 = 9;
	const int a3 = -1;
    std::vector<std::vector<int>> dp3(n3 + 1 , std::vector<int> (sum3+1, -1));
    const bool ans3 =
        dynamic_programming::subset_sum_topdown::subset_sum(set3,n3,sum3,dp3);
    const bool expected_ans3 = true;
    assert(ans3 == expected_ans3);
    std::cout << "subset exists with sum " << sum3 
              << std::endl;

    // Test 4
    const int n4 = 6;
	std::vector<int> set4 = { 3, 34, 4, 12, 5, 2 };
	const int sum4 = 30;
	const int a4 = -1;
	std::vector<std::vector<int>> dp4(n4 + 1 , std::vector<int> (sum4+1, -1));
    const bool ans4 =
        dynamic_programming::subset_sum_topdown::subset_sum(set4,n4,sum4,dp4);
    const bool expected_ans4 = false;
    assert(ans4 == expected_ans4);
    std::cout << "subset doesn't exists with sum " << sum4
              << std::endl;

}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // call the test function :)
}
