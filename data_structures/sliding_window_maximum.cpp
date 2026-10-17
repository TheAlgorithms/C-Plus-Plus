/**
 * @file
 * @brief Implementation of the [Sliding Window
 * Maximum](https://en.wikipedia.org/wiki/Sliding_window_protocol) algorithm
 * using a monotonic deque.
 *
 * @details
 * Given an array of elements and a sliding window of size `k` moving from left
 * to right, this algorithm finds the maximum element in every contiguous window
 * of size `k`.
 *
 * ### Monotonic Deque Approach:
 * A double-ended queue (`std::deque`) stores indices of array elements such
 * that the corresponding values in the array are always in strictly decreasing
 * order from front to back.
 *
 * In each step for element at index `i`:
 * 1. Remove indices from the front that have fallen out of the current window
 * (`index <= i - k`).
 * 2. Remove indices from the back whose corresponding values are less than or
 * equal to `nums[i]`, as they can never be the maximum while `nums[i]` is in
 * the window.
 * 3. Push the current index `i` to the back of the deque.
 * 4. Once `i >= k - 1`, the element at `nums[dq.front()]` is the maximum for
 * the current window.
 *
 * ### Complexity:
 * - Time Complexity: \f$O(N)\f$ where \f$N\f$ is the number of elements in the
 * array. Each index is pushed and popped from the deque at most once.
 * - Auxiliary Space Complexity: \f$O(k)\f$ for the deque storing at most `k`
 * indices.
 *
 * @author [Akhila Pynam](https://github.com/akhila-pynam)
 */

#include <algorithm>  /// for std::max_element
#include <cassert>    /// for assert
#include <cstdint>    /// for std::int64_t
#include <deque>      /// for std::deque
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {

/**
 * @namespace sliding_window_maximum
 * @brief Functions for the Sliding Window Maximum algorithm
 */
namespace sliding_window_maximum {

/**
 * @brief Computes the maximum value in every sliding window of size `k`.
 * @tparam T The element type (must support `<=` and `<` comparison operators).
 * @param nums The input vector of elements.
 * @param k The size of the sliding window.
 * @return A vector containing the maximum element of each sliding window.
 */
template <typename T>
std::vector<T> sliding_window_max(const std::vector<T>& nums, size_t k) {
    if (nums.empty() || k == 0) {
        return {};
    }

    if (k >= nums.size()) {
        return {*std::max_element(nums.begin(), nums.end())};
    }

    std::vector<T> result;
    result.reserve(nums.size() - k + 1);

    std::deque<size_t> dq;  // Stores indices in decreasing order of nums[index]

    for (size_t i = 0; i < nums.size(); ++i) {
        // Step 1: Remove indices that are outside the current window
        if (!dq.empty() && dq.front() + k <= i) {
            dq.pop_front();
        }

        // Step 2: Maintain monotonic decreasing order by removing smaller
        // elements from the back
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        // Step 3: Push the current index
        dq.push_back(i);

        // Step 4: Record the window maximum once the first window is fully
        // formed
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

}  // namespace sliding_window_maximum

}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using data_structures::sliding_window_maximum::sliding_window_max;

    // Test 1: Standard case with mixed positive and negative values
    std::vector<int64_t> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    std::vector<int64_t> expected1 = {3, 3, 5, 5, 6, 7};
    assert(sliding_window_max(nums1, 3) == expected1);

    // Test 2: k = 1 (every window has 1 element, output matches input)
    std::vector<int64_t> nums2 = {4, -2, 7, 1};
    std::vector<int64_t> expected2 = {4, -2, 7, 1};
    assert(sliding_window_max(nums2, 1) == expected2);

    // Test 3: k equal to array size (output is a single maximum)
    std::vector<int64_t> nums3 = {2, 8, 4, 1, 9, 3};
    std::vector<int64_t> expected3 = {9};
    assert(sliding_window_max(nums3, 6) == expected3);

    // Test 4: Strictly increasing elements
    std::vector<int64_t> nums4 = {1, 2, 3, 4, 5};
    std::vector<int64_t> expected4 = {3, 4, 5};
    assert(sliding_window_max(nums4, 3) == expected4);

    // Test 5: Strictly decreasing elements
    std::vector<int64_t> nums5 = {9, 8, 7, 6, 5};
    std::vector<int64_t> expected5 = {9, 8, 7};
    assert(sliding_window_max(nums5, 3) == expected5);

    // Test 6: Array with duplicate elements
    std::vector<int64_t> nums6 = {4, 4, 4, 4, 4};
    std::vector<int64_t> expected6 = {4, 4, 4};
    assert(sliding_window_max(nums6, 3) == expected6);

    // Test 7: All negative numbers
    std::vector<int64_t> nums7 = {-5, -2, -9, -1, -8};
    std::vector<int64_t> expected7 = {-2, -1, -1};
    assert(sliding_window_max(nums7, 3) == expected7);

    // Test 8: Empty array and edge cases
    std::vector<int64_t> empty_nums = {};
    std::vector<int64_t> empty_expected = {};
    assert(sliding_window_max(empty_nums, 3) == empty_expected);
    assert(sliding_window_max(nums1, 0) == empty_expected);

    // Test 9: Floating-point numbers
    std::vector<double> nums9 = {1.5, 3.2, 2.8, 5.1, 4.9};
    std::vector<double> expected9 = {3.2, 5.1, 5.1};
    assert(sliding_window_max(nums9, 3) == expected9);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
