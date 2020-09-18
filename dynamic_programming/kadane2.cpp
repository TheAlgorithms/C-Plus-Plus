/**
 * @file kadane.cpp
 * @brief Implementation of [Kadane
 * Algorithm] (https://en.wikipedia.org/wiki/Kadane%27s_algorithm)
 *
 * @details
 * Kadane algorithm is used to find the maximum sum subarray in an array and
 * maximum sum subarray problem is the task of finding a contiguous subarray
 * with the largest sum
 *
 * ### Algorithm
 * The simple idea of the algorithm is to search for all positive
 * contiguous segments of the array and keep track of maximum sum contiguous
 * segment among all positive segments(curr_sum is used for this)
 * Each time we get a positive sum we compare it with max_sum and update max_sum
 * if it is greater than curr_sum
 *
 * @author [Ayush Singh](https://github.com/ayush523)
 */
#include <array>
#include <climits>
#include <iostream>

/**
 * @brief maxSubArray function
 * @param n array of values and size of the array
 * @returns the value of maximum subarray sum
 */
int maxSubArray(const std::array<int, 5> &n) {
    int curr_sum =
        0;  // declaring a variable named as curr_sum and initialized it to 0
    int max_sum = INT_MIN;  // Initialized max_sum to INT_MIN
    for (int i : n) {  // for loop to iterate over the elements of the array
        curr_sum += n[i];
        max_sum = std::max(max_sum, curr_sum);  // getting the maximum value
        curr_sum = std::max(curr_sum, 0);  // updating the value of curr_sum
    }
    return max_sum;  // returning the value of max_sum
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    std::array<int, 5> n{};  // declaring array

    // taking values of elements from user
    for (int i = 0; i < n.size(); i++) {
        std::cout << "Enter value of n[" << i << "]"
                  << "\n";
        std::cin >> n[i];
    }
    int max_sum = maxSubArray(n);  // calling maxSubArray function
    std::cout << "Maximum subarray sum is " << max_sum;  // Printing the answer

    return 0;
}
