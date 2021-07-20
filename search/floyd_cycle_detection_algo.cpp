/**
 * @file
 * @brief Implementation of [Floyd's Cycle
 * Detection](https://en.wikipedia.org/wiki/Cycle_detection) algorithm
 * @details
 * Given an array of integers containing 'n + 1' integers, where each
 * integer is in the range [1, n] inclusive. If there is only one duplicate
 * number in the input array, this algorithm returns the duplicate number in
 * O(1) space and the time complexity is less than O(n^2) without modifying the
 * original array, otherwise, it returns -1.
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace search
 * @brief Search algorithms
 */
namespace search {
/**
 * @namespace cycle_detection
 * @brief Functions for the [Floyd's Cycle
 * Detection](https://en.wikipedia.org/wiki/Cycle_detection) algorithm
 */
namespace cycle_detection {
/**
 * @brief The main function implements search algorithm
 * @tparam T type of array
 * @param in_arr the input array
 * @param n size of array
 * @returns the duplicate number
 */
template <typename T>
int32_t duplicateNumber(const std::vector<T> &in_arr, const uint32_t &n) {
    if (n == 0 ||
        n == 1) {  // to find duplicate in an array its size should be atleast 2
        return -1;
    }
    uint32_t tortoise = in_arr[0];  // variable tortoise is used for the longer
                                    // jumps in the array
    uint32_t hare =
        in_arr[0];  // variable hare is used for shorter jumps in the array
    do {
        tortoise = in_arr[tortoise];
        hare = in_arr[in_arr[hare]];
    } while (tortoise != hare);
    tortoise = in_arr[0];
    while (tortoise != hare) {
        tortoise = in_arr[tortoise];
        hare = in_arr[hare];
    }
    return tortoise;
}
}  // namespace cycle_detection
}  // namespace search

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    // [3, 4, 8, 5, 9, 1, 2, 6, 7, 4] return 4
    std::vector<uint32_t> array1 = {3, 4, 8, 5, 9, 1, 2, 6, 7, 4};
    std::cout << "Test 1... ";
    assert(search::cycle_detection::duplicateNumber(array1, array1.size()) ==
           4);  // here the duplicate number is 4
    std::cout << "passed" << std::endl;

    // 2nd test
    // [1, 2, 3, 4, 2] return 2
    std::vector<uint32_t> array2 = {1, 2, 3, 4, 2};
    std::cout << "Test 2... ";
    assert(search::cycle_detection::duplicateNumber(array2, array2.size()) ==
           2);  // here the duplicate number is 2
    std::cout << "passed" << std::endl;

    // 3rd test
    // [] return -1
    std::vector<uint32_t> array3 = {};
    std::cout << "Test 3... ";
    assert(search::cycle_detection::duplicateNumber(array3, array3.size()) ==
           -1);  // since the input array is empty no duplicate number exists in
                 // this case
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
