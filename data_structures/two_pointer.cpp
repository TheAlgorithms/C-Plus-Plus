#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Calculates the maximum water that can be trapped between vertical
 * lines on a 2D plane.
 *
 * Given an array of non-negative integers representing vertical lines on a 2D
 * plane, where the width of each line is 1, the function finds two lines that,
 * together with the x-axis, form a container that can hold the most water.
 *
 * The problem can be efficiently solved using a two-pointer approach. We
 * initialize two pointers, 'left' and 'right', at the beginning and end of the
 * array, respectively. The width of the container is determined by the
 * difference between the 'right' and 'left' pointers. To maximize the water
 * trapped, we choose the minimum height between the lines at the 'left' and
 * 'right' positions. We then calculate the water trapped by multiplying the
 * width and height. We move the pointers towards each other, adjusting them
 * based on the shorter line, as moving the pointer with the smaller height has
 * the potential to increase the water volume.
 *
 * @param height Vector representing the heights of vertical lines.
 * @return int Maximum water that can be trapped.
 */

int maxArea(const std::vector<int>& height) {
    int maxWater = 0;
    int left = 0;
    int right = height.size() - 1;

    while (left < right) {
        int width = right - left;
        int h = std::min(height[left], height[right]);
        int currentWater = width * h;
        maxWater = std::max(maxWater, currentWater);

        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return maxWater;
}

/**
 * @brief Tests the maxArea function with various test cases.
 *
 * The function iterates through each test case, calculates the result using the
 * maxArea function, checks if the result matches the expected result, and
 * prints a success message for each test case.
 */

void testContainerWithMostWater() {
    // Test cases with expected maximum water values
    std::vector<std::pair<std::vector<int>, int>> testCases = {
        {{1, 8, 6, 2, 5, 4, 8, 3, 7}, 49},
        {{1, 1}, 1},
        {{4, 3, 2, 1, 4}, 16},
        {{1, 2, 1}, 2},
    };
    for (const auto& testCase : testCases) {
        const std::vector<int>& input = testCase.first;
        int expected = testCase.second;

        // Calculate the result using the maxArea function
        int result = maxArea(input);
        assert(result == expected);
        std::cout << "Test passed!" << std::endl;
    }
}

int main() {
    testContainerWithMostWater();
    return 0;
}
