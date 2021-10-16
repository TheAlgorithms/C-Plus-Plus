/**
 * @file
 * @brief Efficient implementation for maximum contiguous subarray sum by
 * [Kadane's
 * algorithm](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/).
 * @details
 * Our task is to take length of array and then the whole array as input from
 * the user and then calculate the maximum contiguos subarray sum for the
 * input array, using the kadane's algorithm.
 *
 * There can be a case that all the elements in the input array are negative.
 * In that case, the least value among all elements is the maximum sum with
 * subarray length = 1.
 * @author [Abhijeet Tiwari](https://github.com/thisabhijeet)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <climits>   /// for INT_MIN value
#include <iostream>  /// for IO operations

/**
 * @brief Utility function to check the current maximum number
 * \param arr input array
 * \param length length of the input array
 * \returns maximum contiguous subarray sum
 */
template <std::size_t SIZE>
int max_subarray_sum(std::array<int64_t, SIZE> arr, uint64_t length) {
    int64_t current_max = INT_MIN, current_sum = 0;
    for (int i = 0; i < length; i++) {
        current_sum = current_sum + arr[i];
        if (current_max < current_sum) {
            current_max = current_sum;
        }

        if (current_sum < 0) {
            current_sum = 0;
        }
    }
    return current_max;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::array<int64_t, 4> arr = {1, 2, 3, 4};
    std::array<int64_t, 5> arr1 = {-1, -2, -4, -6, 7};
    assert(max_subarray_sum(arr, 4) == 10);
    assert(max_subarray_sum(arr1, 5) == 7);
    std::cout << "All test cases have passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Below is the code for accepting array from the user and then
    // calling the function for the required output.
    // It has been commented for now so that the test() function can run
    // and the test cases can be verified.
    // code for accepting array from user starts

    // std::size_t n;  // variable for length of input array
    // std::cout << "Enter length of the array: ";
    // std::cin >> n;
    // std::array<int64_t, 100> arr = {0};
    // // we need to give a constant in size. Hence we have allocated 100
    // for now.
    // for (int i = 0; i < n; i++)
    // taking input of each element of the array
    // {
    //     std::cin >> arr[i];
    // }
    // code for accepting array from user ends

    // int max_sum = max_subarray_sum(arr, n);
    // std::cout << "Maximum contiguous sum for this array is : " << max_sum
    //           << std::endl;

    test();  // run self-test implementations
    return 0;
}
