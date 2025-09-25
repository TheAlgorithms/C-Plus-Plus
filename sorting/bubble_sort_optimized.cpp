/**
 * @file bubble_sort.cpp
 * @brief Implementation of the Bubble Sort algorithm with self-tests.
 *
 * This file contains an implementation of the bubble sort algorithm
 * inside the `sorting` namespace. It includes an optimized version
 * of bubble sort that reduces the number of passes when the input
 * is already sorted or becomes sorted before completing all iterations.
 *
 * Additionally, it contains a set of self-tests to verify correctness
 * using the C++ standard library's `assert` mechanism.
 *
 * Example:
 * @code
 * std::vector<int> nums = {5, 4, 3, 2, 1};
 * sorting::bubble_sort(nums);
 * // nums becomes {1, 2, 3, 4, 5}
 * @endcode
 *
 * @author Rohith A K
 * @date 2025-09-25
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <utility>   /// for std::swap
#include <vector>    /// for std::vector

namespace sorting {

/**
 * @brief Sorts the given vector using the bubble sort algorithm.
 *
 * This optimized bubble sort reduces the number of passes in average cases
 * by checking if the array is already sorted during each pass.
 *
 * @param nums the vector of integers to be sorted
 * @return reference to the sorted vector
 */
std::vector<int>& bubble_sort(std::vector<int>& nums) {
  for (std::size_t i = 0; i < nums.size() - 1; i++) {
    bool swapped = false;
    for (std::size_t j = 0; j < nums.size() - 1 - i; j++) {
      if (nums[j] > nums[j + 1]) {
        std::swap(nums[j], nums[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
  return nums;
}

}  // namespace sorting

/**
 * @brief Self-test implementations of the bubble_sort function.
 *
 * Runs a set of predefined test cases using `assert` to ensure
 * the correctness of the bubble_sort implementation.
 *
 * @returns void
 */
static void tests() {
  std::vector<int> v1 = {2, 8, 1, 6, 2, 0, 3, 6};
  const std::vector<int> expected1 = {0, 1, 2, 2, 3, 6, 6, 8};
  assert(sorting::bubble_sort(v1) == expected1);

  std::vector<int> v2 = {5, 4, 3, 2, 1};
  const std::vector<int> expected2 = {1, 2, 3, 4, 5};
  assert(sorting::bubble_sort(v2) == expected2);

  std::vector<int> v3 = {1, 2, 3, 4, 5};
  const std::vector<int> expected3 = {1, 2, 3, 4, 5};
  assert(sorting::bubble_sort(v3) == expected3);

  std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 *
 * Executes the self-test suite for bubble_sort.
 *
 * @returns 0 on successful execution
 */
int main() {
  tests();  // run self-test implementations
  return 0;
}
