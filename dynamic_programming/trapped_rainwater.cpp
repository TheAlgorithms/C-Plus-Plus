/**
 * @file
 * @brief Implementation of the [Trapped Rainwater
 * Problem](https://www.geeksforgeeks.org/trapping-rain-water/)
 * @details
 * This implementation calculates the amount of rainwater that can be trapped
 * between walls represented by an array of heights.
 * @author [SOZEL](https://github.com/TruongNhanNguyen)
 */

#include <algorithm>  /// For std::min and std::max
#include <cassert>    /// For assert
#include <cstddef>    /// For std::size_t
#include <cstdint>
#include <vector>  /// For std::vector

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
        return 0;  // No water can be trapped with less than 3 walls

    std::vector<uint32_t> leftMax(n), rightMax(n);

    // Calculate the maximum height of wall to the left of each wall
    leftMax[0] = heights[0];
    for (std::size_t i = 1; i < n; ++i) {
        leftMax[i] = std::max(leftMax[i - 1], heights[i]);
    }

    // Calculate the maximum height of wall to the right of each wall
    rightMax[n - 1] = heights[n - 1];
    for (std::size_t i = n - 2; i < n; --i) {
        rightMax[i] = std::max(rightMax[i + 1], heights[i]);
    }

    // Calculate the trapped rainwater between walls
    uint32_t trappedWater = 0;
    for (std::size_t i = 0; i < n; ++i) {
        trappedWater +=
            std::max(0u, std::min(leftMax[i], rightMax[i]) - heights[i]);
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
