/**
 * @file
 * @brief find the length of the Longest Increasing Subsequence (LIS)
 * using [Binary Search](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)
 * @details
 * Given an integer array nums, return the length of the longest strictly
 * increasing subsequence.
 * The longest increasing subsequence is described as a subsequence of an array
 * where: All elements of the subsequence are in increasing order. This subsequence
 * itself is of the longest length possible.

 * For solving this problem we have Three Approaches :-

 * Approach 1 :- Using Brute Force
 * The first approach that came to your mind is the Brute Force approach where we
 * generate all subsequences and then manually filter the subsequences whose
 * elements come in increasing order and then return the longest such subsequence.
 * Time Complexity :- O(2^n)
 * It's time complexity is exponential. Therefore we will try some other
 * approaches.

 * Approach 2 :- Using Dynamic Programming
 * To generate all subsequences we will use recursion and in the recursive logic we
 * will figure out a way to solve this problem. Recursive Logic to solve this
 * problem:-
 * 1. We only consider the element in the subsequence if the element is grater then
 * the last element present in the subsequence
 * 2. When we consider the element we will increase the length of subsequence by 1
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N) + O(N)

 * This approach is better then the previous Brute Force approach so, we can
 * consider this approach.

 * But when the Constraints for the problem is very larger then this approach fails

 * Approach 3 :- Using Binary Search
 * Other approaches use additional space to create a new subsequence Array.
 * Instead, this solution uses the existing nums Array to build the subsequence
 * array. We can do this because the length of the subsequence array will never be
 * longer than the current index.

 * Time complexity: O(n∗log(n))
 * Space complexity: O(1)

 * This approach consider Most optimal Approach for solving this problem

 * @author [Naman Jain](https://github.com/namanmodi65)
 */

#include <cassert>   /// for std::assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <algorithm> /// for std::lower_bound
#include <cstdint>   /// for std::uint32_t

/**
 * @brief Function to find the length of the Longest Increasing Subsequence (LIS)
 * using Binary Search
 * @tparam T The type of the elements in the input vector
 * @param nums The input vector of elements of type T
 * @return The length of the longest increasing subsequence
 */
template <typename T>
std::uint32_t longest_increasing_subsequence_using_binary_search(std::vector<T>& nums) {
    if (nums.empty()) return 0;

    std::vector<T> ans;
    ans.push_back(nums[0]);
    for (std::size_t i = 1; i < nums.size(); i++) {
        if (nums[i] > ans.back()) {
            ans.push_back(nums[i]);
        } else {
            auto idx = std::lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();
            ans[idx] = nums[i];
        }
    }
    return static_cast<std::uint32_t>(ans.size());
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

    std::vector<int> arr4 = {-10, -1, -5, 0, 5, 1, 2};
    assert(longest_increasing_subsequence_using_binary_search(arr4) == 5);

    std::vector<double> arr5 = {3.5, 1.2, 2.8, 3.1, 4.0};
    assert(longest_increasing_subsequence_using_binary_search(arr5) == 4);

    std::vector<char> arr6 = {'a', 'b', 'c', 'a', 'd'};
    assert(longest_increasing_subsequence_using_binary_search(arr6) == 4);

    std::vector<int> arr7 = {};
    assert(longest_increasing_subsequence_using_binary_search(arr7) == 0);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function to run tests
 * @returns 0 on exit
 */
int main() {
    tests();  // run self test implementation
    return 0;
}
