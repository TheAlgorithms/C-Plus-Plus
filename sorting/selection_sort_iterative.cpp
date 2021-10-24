/******************************************************************************
 * @file
 * @brief Implementation of the [Selection
 * sort](https://en.wikipedia.org/wiki/Selection_sort) implementation using
 * swapping
 * @details
 * The selection sort algorithm divides the input vector into two parts: a
 * sorted subvector of items which is built up from left to right at the front
 * (left) of the vector, and a subvector of the remaining unsorted items that
 * occupy the rest of the vector. Initially, the sorted subvector is empty, and
 * the unsorted subvector is the entire input vector. The algorithm proceeds by
 * finding the smallest (or largest, depending on the sorting order) element in
 * the unsorted subvector, exchanging (swapping) it with the leftmost unsorted
 * element (putting it in sorted order), and moving the subvector boundaries one
 * element to the right.
 *
 * ### Implementation
 *
 * SelectionSort
 * The algorithm divides the input vector into two parts: the subvector of items
 * already sorted, which is built up from left to right. Initially, the sorted
 * subvector is empty and the unsorted subvector is the entire input vector. The
 * algorithm proceeds by finding the smallest element in the unsorted subvector,
 * exchanging (swapping) it with the leftmost unsorted element (putting it in
 * sorted order), and moving the subvector boundaries one element to the right.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 * @author Unknown author
 *******************************************************************************/
#include <algorithm>  /// for std::is_sorted
#include <cassert>    /// for std::assert
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/******************************************************************************
 * @namespace sorting
 * @brief Sorting algorithms
 *******************************************************************************/
namespace sorting {
/******************************************************************************
 * @brief The main function which implements Selection sort
 * @param arr vector to be sorted
 * @param len length of vector to be sorted
 * @returns @param array resultant sorted vector
 *******************************************************************************/

std::vector<uint64_t> selectionSort(const std::vector<uint64_t> &arr,
                                    uint64_t len) {
    std::vector<uint64_t> array(
        arr.begin(),
        arr.end());  // declare a vector in which result will be stored
    for (uint64_t it = 0; it < len; ++it) {
        uint64_t min = it;  // set min value
        for (uint64_t it2 = it + 1; it2 < len; ++it2) {
            if (array[it2] < array[min]) {  // check which element is smaller
                min = it2;  // store index of smallest element to min
            }
        }

        if (min != it) {  // swap if min does not match to i
            uint64_t tmp = array[min];
            array[min] = array[it];
            array[it] = tmp;
        }
    }

    return array;  // return sorted vector
}
}  // namespace sorting

/*******************************************************************************
 * @brief Self-test implementations
 * @returns void
 *******************************************************************************/
static void test() {
    // testcase #1
    // [1, 0, 0, 1, 1, 0, 2, 1] returns [0, 0, 0, 1, 1, 1, 1, 2]
    std::vector<uint64_t> vector1 = {1, 0, 0, 1, 1, 0, 2, 1};
    uint64_t vector1size = vector1.size();
    std::cout << "1st test... ";
    std::vector<uint64_t> result_test1;
    result_test1 = sorting::selectionSort(vector1, vector1size);
    assert(std::is_sorted(result_test1.begin(), result_test1.end()));
    std::cout << "Passed" << std::endl;

    // testcase #2
    // [19, 22, 540, 241, 156, 140, 12, 1] returns [1, 12, 19, 22, 140, 156,
    // 241,540]
    std::vector<uint64_t> vector2 = {19, 22, 540, 241, 156, 140, 12, 1};
    uint64_t vector2size = vector2.size();
    std::cout << "2nd test... ";
    std::vector<uint64_t> result_test2;
    result_test2 = sorting::selectionSort(vector2, vector2size);
    assert(std::is_sorted(result_test2.begin(), result_test2.end()));
    std::cout << "Passed" << std::endl;

    // testcase #3
    // [11, 20, 30, 41, 15, 60, 82, 15] returns [11, 15, 15, 20, 30, 41, 60, 82]
    std::vector<uint64_t> vector3 = {11, 20, 30, 41, 15, 60, 82, 15};
    uint64_t vector3size = vector3.size();
    std::cout << "3rd test... ";
    std::vector<uint64_t> result_test3;
    result_test3 = sorting::selectionSort(vector3, vector3size);
    assert(std::is_sorted(result_test3.begin(), result_test3.end()));
    std::cout << "Passed" << std::endl;

    // testcase #4
    // [1, 9, 11, 546, 26, 65, 212, 14, -11] returns [-11, 1, 9, 11, 14, 26, 65,
    // 212, 546]
    std::vector<uint64_t> vector4 = {1, 9, 11, 546, 26, 65, 212, 14};
    uint64_t vector4size = vector2.size();
    std::cout << "4th test... ";
    std::vector<uint64_t> result_test4;
    result_test4 = sorting::selectionSort(vector4, vector4size);
    assert(std::is_sorted(result_test4.begin(), result_test4.end()));
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
