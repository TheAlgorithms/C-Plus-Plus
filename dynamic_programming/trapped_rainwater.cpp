/**
 * @file
 * @brief Implementation of the [Trapped Rainwater
 * Problem](https://www.geeksforgeeks.org/trapping-rain-water/)
 * @details
 * This implementation calculates the amount of rainwater that can be trapped
 * between walls represented by an array of heights.
 */

#include <algorithm>  /// For std::min and std::max
#include <cassert>    /// For assert
#include <vector>     /// For vector container

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
int trappedRainwater(const std::vector<int>& heights) {
    int n = heights.size();
    if (n <= 2)
        return 0;  // No water can be trapped with less than 3 walls

    std::vector<int> leftMax(n), rightMax(n);

    // Calculate the maximum height of wall to the left of each wall
    leftMax[0] = heights[0];
    for (int i = 1; i < n; ++i) {
        leftMax[i] = std::max(leftMax[i - 1], heights[i]);
    }

    // Calculate the maximum height of wall to the right of each wall
    rightMax[n - 1] = heights[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        rightMax[i] = std::max(rightMax[i + 1], heights[i]);
    }

    // Calculate the trapped rainwater between walls
    int trappedWater = 0;
    for (int i = 0; i < n; ++i) {
        trappedWater +=
            std::max(0, std::min(leftMax[i], rightMax[i]) - heights[i]);
    }

    return trappedWater;
}

}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::vector<int> test_basic = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(dynamic_programming::trappedRainwater(test_basic) == 6);

    std::vector<int> test_peak_under_water = {3, 0, 2, 0, 4};
    assert(dynamic_programming::trappedRainwater(test_peak_under_water) == 7);

    std::vector<int> test_bucket = {5, 1, 5};
    assert(dynamic_programming::trappedRainwater(test_bucket) == 4);

    std::vector<int> test_skewed_bucket = {4, 1, 5};
    assert(dynamic_programming::trappedRainwater(test_skewed_bucket) == 3);

    std::vector<int> test_empty = {};
    assert(dynamic_programming::trappedRainwater(test_empty) == 0);

    std::vector<int> test_flat = {0, 0, 0, 0, 0};
    assert(dynamic_programming::trappedRainwater(test_flat) == 0);

    std::vector<int> test_no_trapped_water = {1, 1, 2, 4, 0, 0, 0};
    assert(dynamic_programming::trappedRainwater(test_no_trapped_water) == 0);

    std::vector<int> test_single_elevation = {5};
    assert(dynamic_programming::trappedRainwater(test_single_elevation) == 0);

    std::vector<int> test_two_point_elevation = {5, 1};
    assert(dynamic_programming::trappedRainwater(test_two_point_elevation) ==
           0);

    std::vector<int> test_large_elevation_map_difference = {5, 1, 6, 1,
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
