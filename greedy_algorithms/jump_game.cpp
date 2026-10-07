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
bool can_jump(const std::vector<int> &nums) {
    size_t lastPos = nums.size() - 1;
    for (size_t i = lastPos; i != static_cast<size_t>(-1); i--) {
        if (i + nums[i] >= lastPos) {
            lastPos = i;
        }
    }
    return lastPos == 0;
}
}  // namespace greedy_algorithms

/**
 * @brief Function to test the above algorithm
 * @returns void
 */
static void test() {
    assert(greedy_algorithms::can_jump(std::vector<int>({4, 3, 1, 0, 5})));
    assert(!greedy_algorithms::can_jump(std::vector<int>({3, 2, 1, 0, 4})));
    assert(greedy_algorithms::can_jump(std::vector<int>({5, 9, 4, 7, 15, 3})));
    assert(!greedy_algorithms::can_jump(std::vector<int>({1, 0, 5, 8, 12})));
    assert(greedy_algorithms::can_jump(std::vector<int>({2, 1, 4, 7})));

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
