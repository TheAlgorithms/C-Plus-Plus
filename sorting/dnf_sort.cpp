/**
 * @file
 * @brief Implementation of the [DNF
 * sort](https://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/)
 * implementation
 * @details
 * C++ program to sort an array with 0, 1 and 2 in a single pass(DNF sort).
 * Since one traversal of the array is there hence it works in O(n) time
 * complexity.
 * @author [Sujal Gupta](https://github.com/heysujal)
 */

#include <algorithm>  /// for std::is_sorted
#include <cassert>    /// for assert
#include <iostream>   /// for std::swap and io operations
#include <vector>     /// for std::vector

/**
 * @namespace sorting
 * @breif Sorting algorithms
 */
namespace sorting {
/**
 * @namespace dnf_sort
 * @brief Functions for the [DNF
 * sort](https://en.wikipedia.org/wiki/Dutch_national_flag_problem)
 * implementation
 */
namespace dnf_sort {
/**
 * @brief The main function implements DNF sort
 * @tparam T type of array
 * @param a array to be sorted,
 * @param arr_size size of array
 * @returns void
 */
template <typename T>
std::vector<T> dnfSort(const std::vector<T> &in_arr) {
    std::vector<T> arr(in_arr);
    uint64_t lo = 0;
    uint64_t hi = arr.size() - 1;
    uint64_t mid = 0;

    // Iterate till all the elements
    // are sorted
    while (mid <= hi) {
        switch (arr[mid]) {
            // If the element is 0
            case 0:
                std::swap(arr[lo++], arr[mid++]);
                break;

            // If the element is 1 .
            case 1:
                mid++;
                break;

            // If the element is 2
            case 2:
                std::swap(arr[mid], arr[hi--]);
                break;
        }
    }
    return arr;
}
}  // namespace dnf_sort
}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    // [1, 0, 2, 1] return [0, 1, 1, 2]
    std::vector<uint64_t> array1 = {0, 1, 1, 2};
    std::cout << "Test 1... ";
    std::vector<uint64_t> arr1 = sorting::dnf_sort::dnfSort(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "passed" << std::endl;
    // 2nd test
    // [1, 0, 0, 1, 1, 0, 2, 1] return [0, 0, 0, 1, 1, 1, 1, 2]
    std::vector<uint64_t> array2 = {1, 0, 0, 1, 1, 0, 2, 1};
    std::cout << "Test 2... ";
    std::vector<uint64_t> arr2 = sorting::dnf_sort::dnfSort(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "passed" << std::endl;
    // 3rd test
    // [1, 1, 0, 0, 1, 2, 2, 0, 2, 1] return [0, 0, 0, 1, 1, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array3 = {1, 1, 0, 0, 1, 2, 2, 0, 2, 1};
    std::cout << "Test 3... ";
    std::vector<uint64_t> arr3 = sorting::dnf_sort::dnfSort(array3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));
    std::cout << "passed" << std::endl;
    // 4th test
    // [2, 2, 2, 0, 0, 1, 1] return [0, 0, 1, 1, 2, 2, 2]
    std::vector<uint64_t> array4 = {2, 2, 2, 0, 0, 1, 1};
    std::cout << "Test 4... ";
    std::vector<uint64_t> arr4 = sorting::dnf_sort::dnfSort(array4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
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
