/**
 * @file
 * @brief Implementation of [Cycle
 * sort](https://en.wikipedia.org/wiki/Cycle_sort) algorithm
 *
 * @details
 * Cycle Sort is a sorting algorithm that works in \f$O(n^2)\f$ time in best cas
 * and works in \f$O(n^2)\f$ in worst case. If a element is already at its
 * correct  position, do nothing. If a element is not at its correct position,
 * we then need to move it to its correct position by computing the correct
 * positions.Therefore, we should make sure the duplicate elements.
 *
 * @author [TsungHan Ho](https://github.com/dalaoqi)
 */

#include <algorithm>  /// for std::is_sorted, std::swap
#include <cassert>    /// for assert
#include <iostream>   /// for io operations
#include <vector>     /// for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace cycle_sort
 * @brief Functions for [Cycle sort](https://en.wikipedia.org/wiki/Cycle_sort)
 * algorithm
 */
namespace cycle_sort {
/**
 * @brief The main function implements cycleSort
 * @tparam T type of array
 * @param in_arr array to be sorted
 * @returns void
 */
template <typename T>
std::vector<T> cycleSort(const std::vector<T> &in_arr) {
    std::vector<T> arr(in_arr);
    for (size_t cycle_start = 0; cycle_start <= arr.size() - 1; cycle_start++) {
        // initialize item
        T item = arr[cycle_start];

        // Count the number of elements smaller than item, this  number is the
        // correct index of item.
        int pos = cycle_start;
        for (size_t i = cycle_start + 1; i < arr.size(); i++) {
            if (arr[i] < item) {
                pos++;
            }
        }

        // item is already in correct position
        if (pos == cycle_start) {
            continue;
        }

        // duplicate  elements
        while (item == arr[pos]) pos += 1;
        std::swap(item, arr[pos]);

        // Rest of the  elements
        while (pos != cycle_start) {
            pos = cycle_start;
            // Find position where we put the element
            for (size_t i = cycle_start + 1; i < arr.size(); i++) {
                if (arr[i] < item) {
                    pos += 1;
                }
            }
            // duplicate  elements
            while (item == arr[pos]) pos += 1;
            std::swap(item, arr[pos]);
        }
    }
    return arr;
}
}  // namespace cycle_sort
}  // namespace sorting

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // [506, 48, 123, 79, 0, 362, 951, 500, 0] return [0, 0, 48, 79, 123, 362,
    // 500, 506, 951]
    std::vector<int> array1 = {506, 48, 123, 79, 0, 362, 951, 500, 0};
    std::cout << "Test 1... ";
    std::vector<int> arr1 = sorting::cycle_sort::cycleSort(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "passed" << std::endl;

    // [4.3, -6.5, -7.4, 0, 2.7, 1.8] return [-7.4, -6.5, 0, 1.8, 2.7, 4.3]
    std::vector<double> array2 = {4.3, -6.5, -7.4, 0, 2.7, 1.8};
    std::cout << "Test 2... ";
    std::vector<double> arr2 = sorting::cycle_sort::cycleSort(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
