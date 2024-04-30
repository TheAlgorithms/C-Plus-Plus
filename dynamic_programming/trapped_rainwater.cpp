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
#include <iostream>   /// For IO operations
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
    std::vector<int> heights0 = {0, 1};
    assert(dynamic_programming::trappedRainwater(heights0) == 0);

    std::vector<int> heights1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    assert(dynamic_programming::trappedRainwater(heights1) == 6);

    std::vector<int> heights2 = {3, 0, 0, 2, 0, 4};
    assert(dynamic_programming::trappedRainwater(heights2) == 10);

    std::vector<int> heights3 = {1, 2, 3, 4, 5};
    assert(dynamic_programming::trappedRainwater(heights3) == 0);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
