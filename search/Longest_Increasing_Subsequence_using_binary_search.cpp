#include <cassert>   /// for std::assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <algorithm> /// for std::lower_bound

/**
 * @brief Function to find the length of the Longest Increasing Subsequence (LIS)
 * using Binary Search
 * @param nums The input vector of integers
 * @return The length of the longest increasing subsequence
 */
int longest_increasing_subsequence_using_binary_search(std::vector<int>& nums) {
    if (nums.empty()) return 0;

    std::vector<int> ans;
    ans.push_back(nums[0]);
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > ans.back()) {
            ans.push_back(nums[i]);
        } else {
            int idx = std::lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();
            ans[idx] = nums[i];
        }
    }
    return ans.size();
}

/**
 * @brief Test cases for Longest Increasing Subsequence function
 * @returns void
 */
static void tests() {
    std::vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(longest_increasing_subsequence_using_binary_search(arr) == 4);

    std::vector<int> arr2 = {0, 1, 0, 3, 2, 3};
    assert(longest_increasing_subsequence_using_binary_search(arr2) == 4);

    std::vector<int> arr3 = {7, 7, 7, 7, 7, 7, 7};
    assert(longest_increasing_subsequence_using_binary_search(arr3) == 1);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function to run tests
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
