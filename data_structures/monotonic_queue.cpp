/**
 * @file
 * @brief Implementation of the [Monotonic Queue](https://en.wikipedia.org/wiki/Monotone_priority_queue) data structure.
 * @details
 * A Monotonic Queue is a specialized queue that maintains its elements in a monotonically
 * increasing or decreasing order. It supports efficient O(1) amortized insertion, deletion,
 * and minimum/maximum retrieval. It is frequently applied to sliding window problems to achieve
 * an optimal O(N) overall time complexity, outperforming O(N * K) brute-force or O(N log K) heap approaches.
 *
 * ### Complexity Analysis
 * - **Push**: O(1) amortized (each element is added and removed from the deque at most once)
 * - **Pop**: O(1)
 * - **Max / Min Query**: O(1)
 * - **Space Complexity**: O(K), bounded by the maximum window capacity
 *
 * @author [Pitta Rupesh Vinay](https://github.com/rupeshvinay2122)
 * @see data_structures/queue_using_array.cpp
 */

#include <cassert>   /// for assert
#include <deque>     /// for std::deque
#include <functional> /// for std::less
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {
/**
 * @namespace monotonic_queue
 * @brief Functions and classes for the Monotonic Queue implementation
 */
namespace monotonic_queue {

/**
 * @brief Monotonic Queue template class.
 * @details Defaults to maintaining elements in monotonically decreasing order
 * to support constant-time O(1) maximum queries.
 * @tparam T data type of elements stored in the queue
 * @tparam Compare comparator functor, defaults to std::less<T>
 */
template <typename T, typename Compare = std::less<T>>
class MonotonicQueue {
 private:
    std::deque<T> deque_;  ///< Internal double-ended queue storing monotonic elements
    Compare comp_;         ///< Comparator instance

 public:
    /**
     * @brief Default constructor
     */
    MonotonicQueue() : comp_(Compare()) {}

    /**
     * @brief Inserts a new element into the queue while preserving monotonicity.
     * @details Pops elements from the back that violate the monotonic invariant.
     * @param val value to be inserted
     */
    void push(const T& val) {
        while (!deque_.empty() && comp_(deque_.back(), val)) {
            deque_.pop_back();
        }
        deque_.push_back(val);
    }

    /**
     * @brief Removes an element from the queue if it matches the current front.
     * @details Used when an element leaves the sliding window.
     * @param val value exiting the window
     */
    void pop(const T& val) {
        if (!deque_.empty() && deque_.front() == val) {
            deque_.pop_front();
        }
    }

    /**
     * @brief Returns the extreme (maximum/minimum) element in O(1) time.
     * @return T the extreme element at the front of the queue
     */
    [[nodiscard]] T top() const {
        assert(!deque_.empty() && "Cannot query top from an empty MonotonicQueue");
        return deque_.front();
    }

    /**
     * @brief Checks whether the internal deque is empty.
     * @return true if empty, false otherwise
     */
    [[nodiscard]] bool empty() const {
        return deque_.empty();
    }

    /**
     * @brief Returns the number of elements in the internal monotonic deque.
     * @return size_t number of elements
     */
    [[nodiscard]] size_t size() const {
        return deque_.size();
    }

    /**
     * @brief Clears all elements from the queue.
     */
    void clear() {
        deque_.clear();
    }
};

/**
 * @brief Computes the maximum element for every sliding window of size k in O(N) time.
 * @tparam T element type
 * @param nums input sequence of numbers
 * @param k sliding window size
 * @return std::vector<T> vector of maximum elements for each window position
 */
template <typename T>
std::vector<T> sliding_window_maximum(const std::vector<T>& nums, size_t k) {
    if (nums.empty() || k == 0 || k > nums.size()) {
        return {};
    }

    std::vector<T> result;
    result.reserve(nums.size() - k + 1);
    MonotonicQueue<T> mq;

    // Initialize first window
    for (size_t i = 0; i < k; ++i) {
        mq.push(nums[i]);
    }
    result.push_back(mq.top());

    // Slide window across the rest of the array
    for (size_t i = k; i < nums.size(); ++i) {
        mq.pop(nums[i - k]);   // Remove outgoing element
        mq.push(nums[i]);       // Insert incoming element
        result.push_back(mq.top());
    }

    return result;
}

}  // namespace monotonic_queue
}  // namespace data_structures

/**
 * @brief Self-test implementations verifying MonotonicQueue correctness and edge cases.
 * @returns void
 */
static void test() {
    using data_structures::monotonic_queue::MonotonicQueue;
    using data_structures::monotonic_queue::sliding_window_maximum;

    // Test 1: Basic Push, Top, and Pop operations
    {
        MonotonicQueue<int> mq;
        assert(mq.empty());
        assert(mq.size() == 0);

        mq.push(1);
        mq.push(3);
        assert(mq.top() == 3);

        mq.push(-1);
        assert(mq.top() == 3);

        mq.push(5);
        assert(mq.top() == 5);

        mq.pop(3);  // 3 was already popped when 5 entered, top remains 5
        assert(mq.top() == 5);

        mq.pop(5);  // Now 5 is popped
        assert(mq.empty());
    }

    // Test 2: Standard Sliding Window Maximum (Classic LeetCode 239 Case)
    {
        std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        size_t k = 3;
        std::vector<int> expected = {3, 3, 5, 5, 6, 7};
        std::vector<int> actual = sliding_window_maximum(nums, k);
        assert(actual == expected);
    }

    // Test 3: Window size k = 1 (each element is its own maximum)
    {
        std::vector<int> nums = {4, 2, 7, 1, 9};
        std::vector<int> expected = {4, 2, 7, 1, 9};
        std::vector<int> actual = sliding_window_maximum(nums, 1);
        assert(actual == expected);
    }

    // Test 4: Window size k equal to array length
    {
        std::vector<int> nums = {10, 20, 5, 35, 15};
        std::vector<int> expected = {35};
        std::vector<int> actual = sliding_window_maximum(nums, nums.size());
        assert(actual == expected);
    }

    // Test 5: Monotonically strictly decreasing array
    {
        std::vector<int> nums = {9, 8, 7, 6, 5, 4};
        size_t k = 3;
        std::vector<int> expected = {9, 8, 7, 6};
        std::vector<int> actual = sliding_window_maximum(nums, k);
        assert(actual == expected);
    }

    // Test 6: Monotonically strictly ascending array
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6};
        size_t k = 3;
        std::vector<int> expected = {3, 4, 5, 6};
        std::vector<int> actual = sliding_window_maximum(nums, k);
        assert(actual == expected);
    }

    // Test 7: Array with all identical elements
    {
        std::vector<int> nums = {2, 2, 2, 2, 2};
        size_t k = 2;
        std::vector<int> expected = {2, 2, 2, 2};
        std::vector<int> actual = sliding_window_maximum(nums, k);
        assert(actual == expected);
    }

    // Test 8: Negative numbers and zero
    {
        std::vector<int> nums = {-7, -8, -7, 0, -3, -1};
        size_t k = 3;
        std::vector<int> expected = {-7, 0, 0, 0};
        std::vector<int> actual = sliding_window_maximum(nums, k);
        assert(actual == expected);
    }

    // Test 9: Floating-point types
    {
        std::vector<double> nums = {1.5, 3.2, 2.1, 4.8, 0.5};
        size_t k = 2;
        std::vector<double> expected = {3.2, 3.2, 4.8, 4.8};
        std::vector<double> actual = sliding_window_maximum(nums, k);
        assert(actual == expected);
    }

    // Test 10: Invalid inputs (k = 0 or k > array size)
    {
        std::vector<int> nums = {1, 2, 3};
        assert(sliding_window_maximum(nums, 0).empty());
        assert(sliding_window_maximum(nums, 5).empty());
        assert(sliding_window_maximum(std::vector<int>{}, 2).empty());
    }

    std::cout << "All Monotonic Queue tests successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
