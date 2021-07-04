/**
 * @file
 * @brief Implementation of [Wave sort] algorithm
 * @details
 * Wave Sort is a sorting algorithm that works in \f$O(nlogn)\f$ time assuming the sort function used works in \f$O(nlogn)\f$ time.
 * @author [Swastika Gupta](https://github.com/swastyy)
 */

#include <cassert>    /// for assert
#include <algorithm>  /// for std::is_sorted, std::swap
#include <iostream>   /// for io operations
#include <vector>     /// for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace wave_sort
 * @brief Functions for [Wave sort] algorithm
 */
namespace wave_sort {
/**
 * @brief The main function implements waveSort
 * @tparam T type of array
 * @param in_arr array to be sorted
 * @returns arr the wave sorted array
 */
template <typename T>
std::vector<T> waveSort(const std::vector<T> &in_arr, int n) {
    std::vector<T> arr(in_arr);

    for (int i=0;i<n;i++) {
        arr[i] = in_arr[i];
    }
    std::sort(arr.begin(),arr.end());
    for (int i=0; i<n-1; i+=2) { // swap all the adjacent elements
        std::swap(arr[i], arr[i+1]);
    }
    return arr;
}
}  // namespace wave_sort
}  // namespace sorting

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // [10, 90, 49, 2, 1, 5, 23] return [2, 1, 10, 5, 49, 23, 90]
    std::vector<int> array1 = {10, 90, 49, 2, 1, 5, 23};
    std::cout << "Test 1... ";
    std::vector<int> arr1 = sorting::wave_sort::waveSort(array1,7);
    const std::vector<int> o1 = {2, 1, 10, 5, 49, 23, 90};
    assert(arr1==o1);
    std::cout << "passed" << std::endl;

    // [1, 3, 4, 2, 7, 8] return [2, 1, 4, 3, 8, 7]
    std::vector<int> array2 = {1, 3, 4, 2, 7, 8};
    std::cout << "Test 2... ";
    std::vector<int> arr2 = sorting::wave_sort::waveSort(array2,6);
    const std::vector<int> o2 = {2, 1, 4, 3, 8, 7};
    assert(arr2==o2);
    std::cout << "passed" << std::endl;

    // [3, 3, 3, 3] return [3, 3, 3, 3]
    std::vector<int> array3 = {3, 3, 3, 3};
    std::cout << "Test 3... ";
    std::vector<int> arr3 = sorting::wave_sort::waveSort(array3,4);
    const std::vector<int> o3 = {3, 3, 3, 3};
    assert(arr3==o3);
    std::cout << "passed" << std::endl;

    // [9, 4, 6, 8, 14, 3] return [4, 3, 8, 6, 14, 9]
    std::vector<int> array4 = {9, 4, 6, 8, 14, 3};
    std::cout << "Test 4... ";
    std::vector<int> arr4 = sorting::wave_sort::waveSort(array4,6);
    const std::vector<int> o4 = {4, 3, 8, 6, 14, 9};
    assert(arr4==o4);
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
