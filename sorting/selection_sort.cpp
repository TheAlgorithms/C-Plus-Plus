/******************************************************************************
 * @file
 * @brief Implementation of the [Selection
 *sort](https://en.wikipedia.org/wiki/Selection_sort) implementation using
 *swapping
 * @details
 * The selection sort algorithm divides the input array into two parts: a sorted
 * subarray of items which is built up from left to right at the front (left) of
 * the array, and a subarray of the remaining unsorted items that occupy the
 *rest of the array. Initially, the sorted subarray is empty, and the unsorted
 *subarray is the entire input array. The algorithm proceeds by finding the
 *smallest (or largest, depending on the sorting order) element in the unsorted
 *subarray, exchanging (swapping) it with the leftmost unsorted element (putting
 *it in sorted order), and moving the subarray boundaries one element to the
 *right.
 *
 * ### Implementation
 *
 * SelectionSort
 * The algorithm divides the input array into two parts: the subarray of items
 * already sorted, which is built up from left to right. Initially, the sorted
 * subarray is empty and the unsorted subarray is the entire input array. The
 * algorithm proceeds by finding the smallest element in the unsorted subarray,
 * exchanging (swapping) it with the leftmost unsorted element (putting it in
 * sorted order), and moving the subarray boundaries one element to the right.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *******************************************************************************/
#include <algorithm>  ///for std::is_sorted
#include <array>      ///for std::array
#include <cassert>    ///for assert
#include <iostream>   ///for io operations

/******************************************************************************
 * @namespace sorting
 * @brief Sorting algorithms
 *******************************************************************************/
namespace sorting {

/******************************************************************************
 * @brief The main function which implements Selection sort
 * @param nums array to be sorted:-> array datatype, array length,
 * @param len length of array to be sorted,
 * @returns void
 *******************************************************************************/

void selectionSort(
    std::array<int, 8> &arr,
    int len) {  // Array size is const, can be modified by replacing "8" at (Ln
                // 45, Col 21) & (Ln 45, Col 60).
    for (auto it = 0; it < len; ++it) {
        int min = it;  // set min value
        for (auto it2 = it + 1; it2 < len + 1; ++it2) {
            if (arr[it2] < arr[min]) {  // check which element is smaller
                min = it2;  // store index of smallest element to min
            }
        }

        if (min != it) {  // swap if min does not match to i
            int tmp = arr[min];
            arr[min] = arr[it];
            arr[it] = tmp;
        }
    }
}
}  // namespace sorting

/*******************************************************************************
 * @brief Self-test implementations
 * @returns void
 *******************************************************************************/
static void test() {
    // testcase #1
    // [1, 0, 0, 1, 1, 0, 2, 1] return [0, 0, 0, 1, 1, 1, 1, 2]
    std::array<int, 8> array1 = {
        {1, 0, 0, 1, 1, 0, 2, 1}};  // Array size is const, can be modified by
                                    // replacing "8" at (Ln 71, Col 21).
    int array1size = array1.size();
    std::cout << "1st test... ";
    sorting::selectionSort(array1, array1size);
    assert(std::is_sorted(array1.begin(), array1.end()));
    std::cout << "Passed" << std::endl;

    // testcase #2
    // [19, 22, 540, 241, 156, 140, 12, 1] return [1, 12, 19, 22, 140, 156, 241,
    // 540]
    std::array<int, 8> array2 = {{19, 22, 540, 241, 156, 140, 12,
                                  1}};  // Array size is const, can be modified
                                        // by replacing "8" at (Ln 81, Col 21).
    int array2size = array2.size();
    std::cout << "2nd test... ";
    sorting::selectionSort(array2, array2size);
    assert(std::is_sorted(array2.begin(), array2.end()));
    std::cout << "Passed" << std::endl;

    // testcase #3
    // [11, 20, 30, 41, 15, 60, 82, 15] return [11, 15, 15, 20, 30, 41, 60, 82]
    std::array<int, 8> array3 = {{11, 20, 30, 41, 15, 60, 82,
                                  15}};  // Array size is const, can be modified
                                         // by replacing "8" at (Ln 90, Col 21).
    int array3size = array3.size();
    std::cout << "3rd test... ";
    sorting::selectionSort(array3, array3size);
    assert(std::is_sorted(array3.begin(), array3.end()));
    std::cout << "Passed" << std::endl;

    // testcase #4
    // [1, 9, 11, 546, 26, 65, 212, 14] return [1, 9, 11, 14, 26, 65, 212, 546]
    std::array<int, 8> array4 = {{1, 9, 11, 546, 26, 65, 212,
                                  14}};  // Array size is const, can be modified
                                         // by replacing "8" at (Ln 99, Col 21).
    int array4size = array2.size();
    std::cout << "4th test... ";
    sorting::selectionSort(array4, array4size);
    assert(std::is_sorted(array4.begin(), array4.end()));
    std::cout << "Passed" << std::endl;
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    test();  // run self-test implementations
    return 0;
}
