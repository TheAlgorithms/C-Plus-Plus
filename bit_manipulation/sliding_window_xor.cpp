/**
 * @file
 * @brief Implementation to [calculate XOR of sliding window of size k in an
 * array of n integers] (https://cses.fi/problemset/task/3426)
 *
 * @details
 * We are given an array of n integers. Our task is to calculate the bitwise XOR
 * of each window of k elements, from left to right, and cumulatively XOR the
 * results into a single value.
 *
 * Worst Case Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @author [Abhiraj Mandal](https://github.com/DataWorshipper)
 */

#include <cassert>  /// for assert
#include <cstdint>  /// for std::uint32_t
#include <iostream>  /// for IO operations
#include <vector>

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace sliding_window_xor
 * @brief Functions for cumulative XOR of sliding windows in arrays
 */
namespace sliding_window_xor {

/**
 * @brief Computes cumulative XOR of all windows of size k
 *
 * @param n Size of the array
 * @param k Window size
 * @param x Initial value to generate the array
 * @param a Multiplier in array generation
 * @param b Increment in array generation
 * @param c Modulo in array generation
 * @returns std::uint64_t The cumulative XOR of all windows of size k
 *
 * @details
 * This function generates the array using the recurrence:
 *   arr[0] = x
 *   arr[i] = (a * arr[i-1] + b) % c
 *
 * It maintains a sliding window of size k using two pointers l and r:
 * - x1 stores the XOR of the current window
 * - x2 stores the cumulative XOR of all valid windows
 *
 * This approach ensures that the algorithm runs in O(n) time.
 */
std::uint64_t compute(std::uint64_t n, std::uint64_t k, std::uint64_t x,
                      std::uint64_t a, std::uint64_t b, std::uint64_t c) {
    // Generate the array of n elements
    std::vector<std::uint64_t> arr(n);
    arr[0] = x;  // First element of the array

    for (std::uint64_t i = 1; i < n; ++i) {
        arr[i] = (a * arr[i - 1] + b) % c;  // recurrence relation
    }

    std::uint64_t x1 = 0;  // XOR of the current window
    std::uint64_t x2 = 0;  // Cumulative XOR of all windows of size k
    std::uint64_t l = 0;   // Left pointer of sliding window
    std::uint64_t r = 0;   // Right pointer of sliding window

    // Slide the window over the array
    while (r < n) {
        x1 ^= arr[r];  // include current element in window XOR

        // Shrink window from left if size exceeds k
        while (r - l + 1 > k) {
            x1 ^= arr[l];  // remove leftmost element from window XOR
            ++l;
        }

        // If window size equals k, add it to cumulative XOR
        if (r - l + 1 == k) {
            x2 ^= x1;
        }

        ++r;  // Move right pointer
    }

    return x2;  // Return cumulative XOR of all windows
}

}  // namespace sliding_window_xor
}  // namespace bit_manipulation

/**
 * @brief Self-test implementation
 */
static void test() {
    using bit_manipulation::sliding_window_xor::compute;

    // Testcase 1: n = 100, k = 20, expected = 1019
    assert(compute(100, 20, 3, 7, 1, 997) == 1019);

    // Testcase 2: n = 2, k = 1, expected = 2
    assert(compute(2, 1, 2, 3, 4, 5) == 2);

    // Testcase 3: n = 5, k = 2
    assert(compute(5, 2, 1, 1, 1, 100) == 0 ^ 3 ^ 1 ^ 7);

    // Testcase 4: n = 3, k = 5, expected = 0
    assert(compute(3, 5, 5, 2, 1, 100) == 0);

    // Testcase 5: n = 4, k = 4, expected = 0
    assert(compute(4, 4, 3, 1, 0, 10) == 0);

    std::cout << "All test cases successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}