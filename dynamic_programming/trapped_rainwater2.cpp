/**
 * @file
 * @brief Implementation of the [Trapped Rainwater
 * Problem](https://www.geeksforgeeks.org/trapping-rain-water/)
 * @details
 * This implementation calculates the total trapped rainwater using a
 * two-pointer approach. It maintains two pointers (`left` and `right`) and
 * tracks the maximum height seen so far from both ends (`leftMax` and
 * `rightMax`). At each step, the algorithm decides which side to process based
 * on which boundary is smaller, ensuring O(n) time and O(1) space complexity.
 * @author [kanavgoyal898](https://github.com/kanavgoyal898)
 */

#include <algorithm>  /// For std::min and std::max
#include <cassert>    /// For assert
#include <cstddef>    /// For std::size_t
#include <cstdint>    /// For std::uint32_t
#include <vector>     /// For std::vector

/*
 * @namespace
 * @brief Dynamic Programming Algorithms
 */
namespace dynamic_programming {
/**
 * @brief Function to calculate the trapped rainwater
 * @param heights Array representing the heights of walls
 * @return The amount of trapped rainwater
 */
uint32_t trappedRainwater(const std::vector<uint32_t>& heights) {
    std::size_t n = heights.size();
    if (n <= 2)
        return 0;  // Not enough walls to trap water

    std::size_t left = 0, right = n - 1;
    uint32_t leftMax = 0, rightMax = 0, trappedWater = 0;

    // Traverse from both ends towards the center
    while (left < right) {
        if (heights[left] < heights[right]) {
            // Water trapped depends on the tallest wall to the left
            if (heights[left] >= leftMax)
                leftMax = heights[left];  // Update left max
            else
                trappedWater +=
                    leftMax - heights[left];  // Water trapped at current left
            ++left;
        } else {
            // Water trapped depends on the tallest wall to the right
            if (heights[right] >= rightMax)
                rightMax = heights[right];  // Update right max
            else
                trappedWater +=
                    rightMax -
                    heights[right];  // Water trapped at current right
            --right;
        }
    }

    return trappedWater;
}

}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::vector<uint32_t> test_basic = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(dynamic_programming::trappedRainwater(test_basic) == 6);

    std::vector<uint32_t> test_peak_under_water = {3, 0, 2, 0, 4};
    assert(dynamic_programming::trappedRainwater(test_peak_under_water) == 7);

    std::vector<uint32_t> test_bucket = {5, 1, 5};
    assert(dynamic_programming::trappedRainwater(test_bucket) == 4);

    std::vector<uint32_t> test_skewed_bucket = {4, 1, 5};
    assert(dynamic_programming::trappedRainwater(test_skewed_bucket) == 3);

    std::vector<uint32_t> test_empty = {};
    assert(dynamic_programming::trappedRainwater(test_empty) == 0);

    std::vector<uint32_t> test_flat = {0, 0, 0, 0, 0};
    assert(dynamic_programming::trappedRainwater(test_flat) == 0);

    std::vector<uint32_t> test_no_trapped_water = {1, 1, 2, 4, 0, 0, 0};
    assert(dynamic_programming::trappedRainwater(test_no_trapped_water) == 0);

    std::vector<uint32_t> test_single_elevation = {5};
    assert(dynamic_programming::trappedRainwater(test_single_elevation) == 0);

    std::vector<uint32_t> test_two_point_elevation = {5, 1};
    assert(dynamic_programming::trappedRainwater(test_two_point_elevation) ==
           0);

    std::vector<uint32_t> test_large_elevation_map_difference = {5, 1, 6, 1,
                                                                 7, 1, 8};
    assert(dynamic_programming::trappedRainwater(
               test_large_elevation_map_difference) == 15);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
