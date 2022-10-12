/**
 * \addtogroup sorting Sorting Algorithms
 * @{
 * \file
 * \brief [Wiggle Sort Algorithm]
 * (https://leetcode.com/problems/wiggle-sort-ii/) Implementation
 *
 * \author [Roshan Kanwar](http://github.com/roshan0708)
 *
 * \details
 * Wiggle Sort sorts the array into a wave like array.
 * An array ‘arr[0..n-1]’ is sorted in wave form,
 * if arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] >= …..
 *
 * \example
 * arr = [1,1,5,6,1,4], after wiggle sort arr will become equal to [1,1,6,1,5,4]
 * arr = [2,8,9,1,7], after wiggle sort arr will become equal to [8,2,9,1,7]
 */

#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>  /// for io operations
#include <vector>

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @namespace wiggle_sort
 * @brief Functions for [Wiggle
 * Sort](https://leetcode.com/problems/wiggle-sort-ii/) algorithm
 */
namespace wiggle_sort {

/**
 *
 * @brief Function used for sorting the elements in wave form.
 * @details
 * Checking whether the even indexed elements are greater than
 * their adjacent odd elements.
 * Traversing all even indexed elements of the input arr.
 * If current element is smaller than the previous odd element, swap them.
 * If current element is smaller than the next odd element, swap them.
 *
 * @param arr input array (unsorted elements)
 *
 */
template <typename T>  // this allows to have vectors of ints, double, float,
                       // etc
                       std::vector<T> wiggleSort(const std::vector<T> &arr) {
    uint32_t size = arr.size();

    std::vector<T> out(
        arr);  // create a copy of input vector. this way, the original input
               // vector does not get modified. a sorted array is is returned.

    for (int i = 0; i < size; i += 2) {
        if (i > 0 && out[i - 1] > out[i]) {
            std::swap(out[i], out[i - 1]);  // swapping the two values
        }

        if (i < size - 1 && out[i] < out[i + 1]) {
            std::swap(out[i], out[i + 1]);  // swapping the two values
        }
    }

    return out;  // returns the sorted vector
}
}  // namespace wiggle_sort
}  // namespace sorting

/**
 *
 * @brief Utility function used for printing the elements.
 * Prints elements of the array after they're sorted using wiggle sort
 * algorithm.
 *
 * @param arr array containing the sorted elements
 *
 */
template <typename T>
static void displayElements(const std::vector<T> &arr) {
    uint32_t size = arr.size();

    std::cout << "Sorted elements are as follows: ";

    std::cout << "[";

    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i != size - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}

/**
 * Test function
 * @returns void
 */
static void test() {
    std::srand(std::time(nullptr));  // initialize random number generator

    std::vector<float> data1(100);
    for (auto &d : data1) {  // generate random numbers between -5.0 and 4.99
        d = float(std::rand() % 1000 - 500) / 100.f;
    }

    std::vector<float> sorted = sorting::wiggle_sort::wiggleSort<float>(data1);

    displayElements(sorted);

    for (uint32_t j = 0; j < data1.size(); j += 2) {
        assert(data1[j] <= data1[j + 1] &&
               data1[j + 1] >= data1[j + 2]);  // check the validation condition
    }

    std::cout << "Test 1 passed\n";
}

/** Driver Code */
int main() {
    test();
    return 0;
}

/** @} */
