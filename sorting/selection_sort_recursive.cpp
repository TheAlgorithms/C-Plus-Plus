/**
 * @file
 * @brief Implementation of the [Selection
 * sort](https://en.wikipedia.org/wiki/Selection_sort)
 * implementation using recursion
 * @details
 * The selection sort algorithm divides the input list into two parts: a sorted
 * sublist of items which is built up from left to right at the front (left) of
 * the list, and a sublist of the remaining unsorted items that occupy the rest
 * of the list. Initially, the sorted sublist is empty, and the unsorted sublist
 * is the entire input list. The algorithm proceeds by finding the smallest (or
 * largest, depending on the sorting order) element in the unsorted sublist,
 * exchanging (swapping) it with the leftmost unsorted element (putting it in
 * sorted order), and moving the sublist boundaries one element to the right.
 *
 * ### Implementation
 * FindMinIndex
 * This function finds the minimum element of the array(list) recursively by
 * simply comparing the minimum element of array reduced size by 1 and compares
 * it to the last element of the array to find the minimum of the whole array.
 *
 * SelectionSortRecursive
 * Just like selection sort, it divides the list into two parts (i.e.: sorted
 * and unsorted) and finds the minimum of the unsorted array. By calling the
 * `FindMinIndex` function, it swaps the minimum element with the first element
 * of the list, and then solves recursively for the remaining unsorted list.
 * @author [Tushar Khanduri](https://github.com/Tushar-K24)
 */

#include <algorithm>  /// for std::is_sorted
#include <cassert>    /// for assert
#include <iostream>   /// for std::swap and io operations
#include <vector>     /// for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace selection_sort_recursive
 * @brief Functions for the [Selection
 * sort](https://en.wikipedia.org/wiki/Selection_sort)
 * implementation using recursion
 */
namespace selection_sort_recursive {
/**
 * @brief The main function finds the index of the minimum element
 * @tparam T type of array
 * @param in_arr array whose minimum element is to be returned
 * @param current_position position/index from where the in_arr starts
 * @returns index of the minimum element
 */
template <typename T>
uint64_t findMinIndex(const std::vector<T> &in_arr,
                      uint64_t current_position = 0) {
    if (current_position + 1 == in_arr.size()) {
        return current_position;
    }
    uint64_t answer = findMinIndex(in_arr, current_position + 1);
    if (in_arr[current_position] < in_arr[answer]) {
        answer = current_position;
    }
    return answer;
}

/**
 * @brief The main function implements Selection sort
 * @tparam T type of array
 * @param in_arr array to be sorted,
 * @param current_position position/index from where the in_arr starts
 * @returns void
 */
template <typename T>
void selectionSortRecursive(std::vector<T> &in_arr,
                            uint64_t current_position = 0) {
    if (current_position == in_arr.size()) {
        return;
    }
    uint64_t min_element_idx =
        selection_sort_recursive::findMinIndex(in_arr, current_position);
    if (min_element_idx != current_position) {
        std::swap(in_arr[min_element_idx], in_arr[current_position]);
    }
    selectionSortRecursive(in_arr, current_position + 1);
}
}  // namespace selection_sort_recursive
}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    // [1, 0, 2, 1] return [0, 1, 1, 2]
    std::vector<uint64_t> array1 = {0, 1, 1, 2};
    std::cout << "1st test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array1);
    assert(std::is_sorted(std::begin(array1), std::end(array1)));
    std::cout << "passed" << std::endl;
    // 2nd test
    // [1, 0, 0, 1, 1, 0, 2, 1] return [0, 0, 0, 1, 1, 1, 1, 2]
    std::vector<uint64_t> array2 = {1, 0, 0, 1, 1, 0, 2, 1};
    std::cout << "2nd test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array2);
    assert(std::is_sorted(std::begin(array2), std::end(array2)));
    std::cout << "passed" << std::endl;
    // 3rd test
    // [1, 1, 0, 0, 1, 2, 2, 0, 2, 1] return [0, 0, 0, 1, 1, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array3 = {1, 1, 0, 0, 1, 2, 2, 0, 2, 1};
    std::cout << "3rd test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array3);
    assert(std::is_sorted(std::begin(array3), std::end(array3)));
    std::cout << "passed" << std::endl;
    // 4th test
    // [2, 2, 2, 0, 0, 1, 1] return [0, 0, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array4 = {2, 2, 2, 0, 0, 1, 1};
    std::cout << "4th test... ";
    sorting::selection_sort_recursive::selectionSortRecursive(array4);
    assert(std::is_sorted(std::begin(array4), std::end(array4)));
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
