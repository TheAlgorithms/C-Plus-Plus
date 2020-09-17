/**
 * @file
 * @brief Implementation of [Kadane Algorithm](https://en.wikipedia.org/wiki/Kadane%27s_algorithm)
 *
 * @details
 * <full-description here>
 *
 * @author [Ayush Singh](https://github.com/ayush523)
 */
#include <array>
#include <climits>
#include <iostream>

/**
 * @brief description
 * @param n description
 * @returns description
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
