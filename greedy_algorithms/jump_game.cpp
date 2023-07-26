/**
 * @file
 * @brief [Jumping Game](https://leetcode.com/problems/jump-game/)
 * algorithm implementation
 * @details
 *
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array. Each element in the array represents your maximum
 * jump length at that position. Determine if you are able to reach the last
 * index. This solution takes in input as a vector and output as a boolean to
 * check if you can reach the last position. We name the indices good and bad
 * based on whether we can reach the destination if we start at that position.
 * We initialize the last index as lastPos.
 * Here, we start from the end of the array and check if we can ever reach the
 * first index. We check if the sum of the index and the maximum jump count
 * given is greater than or equal to the lastPos. If yes, then that is the last
 * position you can reach starting from the back. After the end of the loop, if
 * we reach the lastPos as 0, then the destination can be reached from the start
 * position.
 *
 * @author [Rakshaa Viswanathan](https://github.com/rakshaa2000)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cout
#include <vector>    /// for std::vector

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @brief Checks whether the given element (default is `1`) can jump to the last
 * index.
 * @param nums array of numbers containing the maximum jump (in steps) from that
 * index
 * @returns true  if the index can be reached
 * @returns false if the index can NOT be reached
 */
template <typename T>
bool can_jump(const std::vector<T> &nums, int index = 1) {
    const int size = nums.size() + 1 - nums[index];
    if (nums[index] >= size) { // `>=` because the number can be higher than the size of the array.
        return true;
    }
    return false;
}
}  // namespace greedy_algorithms

/**
 * @brief Function to test above algorithm
 * @returns void
 */
static void test() {
    // 1st test
    std::vector<int> nums = { 4, 3, 1, 0, 5 };
    assert(greedy_algorithms::can_jump(nums) == true);

    // 2nd test
    nums = { 3, 2, 1, 0, 4 };
    assert(greedy_algorithms::can_jump(nums) == false);

    // 3rd test
    nums = { 5, 9, 4, 7, 15, 3 };
    assert(greedy_algorithms::can_jump(nums) == true);

    // 4th test
    nums = { 4, 2, 8, 9, 6 };
    assert(greedy_algorithms::can_jump(nums) == false);

    // 5th test
    nums = {7, 4, 8, 13, 2, 11};
    assert(greedy_algorithms::can_jump(nums) == true);

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
