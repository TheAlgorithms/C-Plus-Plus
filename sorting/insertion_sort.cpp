/**
 * \file
 * \brief [Recursive Insertion Sort Algorithm
 * (Insertion Sort)](https://en.wikipedia.org/wiki/Insertion_sort)
 *
 * \details
 * Insertion sort is a simple sorting algorithm that builds the final
 * sorted array one at a time. The recursive version applies the same
 * logic but sorts the sub-array recursively before inserting the current
 * element in its correct position.
 */

#include <algorithm>  // for std::is_sorted and std::swap
#include <cassert>    // for assert
#include <iostream>   // for std::cout and std::endl
#include <vector>     // for std::vector

/** \namespace sorting
 * \brief Sorting algorithms
 */
namespace sorting {
/** 
 * \brief Recursive Insertion Sort Function for an array
 *
 * @tparam T Type of the elements in the array
 * @param[in,out] arr Pointer to the array to be sorted
 * @param[in] n Size of the array
 */
template <typename T>
void recursiveInsertionSort(T *arr, int n) {
    // Base case: Array of size 1 is already sorted
    if (n <= 1) {
        return;
    }

    // Sort the first n-1 elements recursively
    recursiveInsertionSort(arr, n - 1);

    // Insert the nth element at its correct position in the sorted array
    T last = arr[n - 1];
    int j = n - 2;

    // Move elements of arr[0..n-1] that are greater than last to one
    // position ahead of their current position
    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;
}

/** 
 * \brief Recursive Insertion Sort Function for a vector
 *
 * @tparam T Type of the elements in the vector
 * @param[in,out] arr Pointer to the vector to be sorted
 * @param[in] n Size of the vector
 */
template <typename T>
void recursiveInsertionSort(std::vector<T> *arr, size_t n) {
    // Base case: If the vector has one or fewer elements, it's already sorted
    if (n <= 1) {
        return;
    }

    // Sort the first n-1 elements recursively
    recursiveInsertionSort(arr, n - 1);

    // Insert the nth element at its correct position in the sorted vector
    T last = arr->at(n - 1);
    int j = n - 2;

    while (j >= 0 && arr->at(j) > last) {
        arr->at(j + 1) = arr->at(j);
        j--;
    }
    arr->at(j + 1) = last;
}

}  // namespace sorting

/** 
 * \brief Helper function to create a random array
 *
 * @tparam T Type of array elements
 * @param[out] arr Pointer to the array to be filled
 * @param[in] N Size of the array
 */
template <typename T>
static void create_random_array(T *arr, int N) {
    while (N--) {
        double r = (std::rand() % 10000 - 5000) / 100.f;
        arr[N] = static_cast<T>(r);
    }
}

/** 
 * \brief Test cases to validate the recursive insertion sort algorithm 
 */
void tests() {
    int arr1[10] = {78, 34, 35, 6, 34, 56, 3, 56, 2, 4};
    std::cout << "Test 1... ";
    sorting::recursiveInsertionSort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << std::endl;

    int arr2[5] = {5, -3, 7, -2, 1};
    std::cout << "Test 2... ";
    sorting::recursiveInsertionSort(arr2, 5);
    assert(std::is_sorted(arr2, arr2 + 5));
    std::cout << "passed" << std::endl;

    float arr3[5] = {5.6, -3.1, -3.0, -2.1, 1.8};
    std::cout << "Test 3... ";
    sorting::recursiveInsertionSort(arr3, 5);
    assert(std::is_sorted(arr3, arr3 + 5));
    std::cout << "passed" << std::endl;

    std::vector<float> arr4({5.6, -3.1, -3.0, -2.1, 1.8});
    std::cout << "Test 4... ";
    sorting::recursiveInsertionSort(&arr4, arr4.size());
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;

    int arr5[50];
    std::cout << "Test 5... ";
    create_random_array(arr5, 50);
    sorting::recursiveInsertionSort(arr5, 50);
    assert(std::is_sorted(arr5, arr5 + 50));
    std::cout << "passed" << std::endl;

    float arr6[50];
    std::cout << "Test 6... ";
    create_random_array(arr6, 50);
    sorting::recursiveInsertionSort(arr6, 50);
    assert(std::is_sorted(arr6, arr6 + 50));
    std::cout << "passed" << std::endl;
}

/** 
 * \brief Main function
 * 
 * Empty except for the call to `tests()`.
 * 
 * @return 0 Always returns 0.
 */
int main() {
    tests();
    return 0;
}
