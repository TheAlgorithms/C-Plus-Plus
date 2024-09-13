/**
 * \file
 * \brief [Binary Insertion Sort Algorithm
 * (Insertion Sort)](https://en.wikipedia.org/wiki/Insertion_sort)
 *
 * \details
 * If the cost of comparisons exceeds the cost of swaps, as is the case for
 * example with string keys stored by reference or with human interaction (such
 * as choosing one of a pair displayed side-by-side), then using binary
 * insertion sort may yield better performance. Binary insertion sort employs a
 * binary search to determine the correct location to insert new elements, and
 * therefore performs ⌈log2 n⌉ comparisons in the worst case. When each element
 * in the array is searched for and inserted this is O(n log n). The algorithm
 * as a whole still has a running time of O(n2) on average because of the series
 * * of swaps required for each insertion. However it has several advantages
 * such as
 * 1. Easy to implement
 * 2. For small set of data it is quite efficient
 * 3. More efficient that other Quadratic complexity algorithms like
 *    Selection sort or bubble sort.
 * 4. It is efficient to use it when the cost of comparison is high.
 * 5. It's stable that is it does not change the relative order of
 *    elements with equal keys.
 * 6. It can sort the array or list as it receives.
 *
 * Example execution steps:
 * 1. Suppose initially we have
 * \f{bmatrix}{40 &30 &20 &50 &10\f}
 * 2. We start traversing from 40 till we reach 10
 * when we reach at 30 we find that it is not at it's correct place so we take
 * 30 and place it at a correct position thus the array will become
 * \f{bmatrix}{30 &40 &20 &50 &10\f}
 * 3. In the next iteration we are at 20 we find that this is also misplaced so
 * we place it at the correct sorted position thus the array in this iteration
 * becomes
 * \f{bmatrix}{20 &30 &40 &50 &10\f}
 * 4. We do not do anything with 50 and move on to the next iteration and
 * select 10 which is misplaced and place it at correct position. Thus, we have
 * \f{bmatrix}{10 &20 &30 &40 &50\f}
 */

#include <algorithm>  /// for algorithm functions
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <vector>     /// for working with vectors

/**
 * \namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {

/**
 * \brief Binary search function to find the most suitable pace for an element.
 * \tparam T The generic data type.
 * \param arr The actual vector in which we are searching a suitable place for
 * the element. \param val The value for which suitable place is to be found.
 * \param low The lower bound of the range we are searching in.
 * \param high The upper bound of the range we are searching in.
 * \returns the index of most suitable position of val.
 */
template <class T>
int64_t binary_search(std::vector<T> &arr, T val, int64_t low, int64_t high) {
    if (high <= low) {
        return (val > arr[low]) ? (low + 1) : low;
    }
    int64_t mid = low + (high - low) / 2;
    if (arr[mid] > val) {
        return binary_search(arr, val, low, mid - 1);
    } else if (arr[mid] < val) {
        return binary_search(arr, val, mid + 1, high);
    } else {
        return mid + 1;
    }
}

/**
 * \brief Insertion sort function to sort the vector.
 * \tparam T The generic data type.
 * \param arr The actual vector to sort.
 * \returns Void.
 */
template <typename T>
void insertionSort_binsrch(std::vector<T> &arr) {
    int64_t n = arr.size();

    for (int64_t i = 1; i < n; i++) {
        T key = arr[i];
        int64_t j = i - 1;
        int64_t loc = sorting::binary_search(arr, key, 0, j);
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    /* 1st test:
       [5, -3, -1, -2, 7] returns [-3, -2, -1, 5, 7] */
    std::vector<int64_t> arr1({5, -3, -1, -2, 7});
    std::cout << "1st test... ";
    sorting::insertionSort_binsrch(arr1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "passed" << std::endl;

    /* 2nd test:
       [12, 26, 15, 91, 32, 54, 41] returns [12, 15, 26, 32, 41, 54, 91] */
    std::vector<int64_t> arr2({12, 26, 15, 91, 32, 54, 41});
    std::cout << "2nd test... ";
    sorting::insertionSort_binsrch(arr2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "passed" << std::endl;

    /* 3rd test:
       [7.1, -2.5, -4.0, -2.1, 5.7] returns [-4.0, -2.5, -2.1, 5.7, 7.1] */
    std::vector<float> arr3({7.1, -2.5, -4.0, -2.1, 5.7});
    std::cout << "3rd test... ";
    sorting::insertionSort_binsrch(arr3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));
    std::cout << "passed" << std::endl;

    /* 4th test:
       [12.8, -3.7, -20.7, -7.1, 2.2] returns [-20.7, -7.1, -3.7, 2.2, 12.8] */
    std::vector<float> arr4({12.8, -3.7, -20.7, -7.1, 2.2});
    std::cout << "4th test... ";
    sorting::insertionSort_binsrch(arr4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @return 0 on exit.
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
