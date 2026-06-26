/**
 * @file
 * @brief Implementation of the [Maximum of all Subarrays of Size
 * k](https://leetcode.com/problems/sliding-window-maximum/) algorithm.
 * @details This algorithm finds the maximum element in every contiguous sliding
 * window of size `k` within a given vector. It uses a monotonic deque to
 * achieve linear time complexity.
 * @author [Your Name](https://github.com/your-username)
 */
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

namespace others {
/**
 * @brief Finds the maximum element in each sliding window of size k.
 * @details The function maintains a deque of indices. The elements
 * corresponding to these indices are sorted in descending order (monotonic
 * decreasing property). This ensures that the front of the deque always holds
 * the maximum element of the current window.
 * * ### Complexity Analysis
 * - **Time Complexity:** $\mathcal{O}(N)$, where $N$ is the number of elements
 * in the vector. Each element is pushed and popped at most twice.
 * - **Space Complexity:** $\mathcal{O}(K)$, where $K$ is the size of the
 * window, used by the deque to store indices.
 * * @param nums The input array of integers.
 * @param k The size of the sliding window.
 * @return std::vector<int> A vector containing the maximums of each window.
 * Returns an empty vector if input constraints are violated.
 */
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    if (nums.empty() || k <= 0 || k > static_cast<int>(nums.size())) {
        return {};
    }

    std::vector<int> result;
    std::deque<int> dq;

    for (size_t i = 0; i < nums.size(); i++) {
        if (!dq.empty() && dq.front() == static_cast<int>(i) - k) {
            dq.pop_front();
        }

        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        if (i >= static_cast<size_t>(k - 1)) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}
}  // namespace others

static void test() {
    // Test Case 1: Standard functional test
    std::vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    std::vector<int> expected1 = {3, 3, 5, 5, 6, 7};
    assert(others::maxSlidingWindow(nums1, 3) == expected1);

    // Test Case 2: Empty input vector boundary check
    std::vector<int> empty_vec = {};
    assert(others::maxSlidingWindow(empty_vec, 3).empty());

    // Test Case 3: Window size out of bounds
    std::vector<int> nums2 = {1, 2};
    assert(others::maxSlidingWindow(nums2, 5).empty());

    std::cout << "All algorithmic assertion checks passed successfully!"
              << std::endl;
}

int main() {
    test();
    return 0;
}