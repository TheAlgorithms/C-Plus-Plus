/**
 * \file
 * \brief [Heap Sort Algorithm
 * (heap sort)](https://en.wikipedia.org/wiki/Heapsort) implementation
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 * \author [Shlok Shah](https://github.com/ShlokShah2007)
 *
 * \details
 *  Heap-sort is a comparison-based sorting algorithm.
 *  Heap-sort can be thought of as an improved selection sort:
 *  like selection sort, heap sort divides its input into a sorted
 *  and an unsorted region, and it iteratively shrinks the unsorted
 *  region by extracting the largest element from it and inserting
 *  it into the sorted region. Unlike selection sort,
 *  heap sort does not waste time with a linear-time scan of the
 *  unsorted region; rather, heap sort maintains the unsorted region
 *  in a heap data structure to more quickly find the largest element
 *  in each step.
 *
 *  Time Complexity - \f$O(n \log(n))\f$
 *
 */
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

/**
 * \addtogroup sorting Sorting Algorithm
 * @{
 * \namespace heap_sort
 * \brief Functions for [Heap Sort
 * Algorithm](https://en.wikipedia.org/wiki/Heapsort) implementation
 */
namespace sorting {
namespace heap_sort {

/**
 * \brief The heapify procedure restores the max-heap property iteratively
 * by successively sifting downward.
 *
 * \tparam T Type of elements in the array
 * \param arr Pointer to the array to be heapified
 * \param n Size of the heap
 * \param i Index of the element to sift down
 */
template <typename T>
void heapify(T *arr, std::size_t n, std::size_t i) {
    while (true) {
        std::size_t largest = i;
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest == i) {
            break;
        }

        std::swap(arr[i], arr[largest]);
        i = largest;
    }
}

/**
 * \brief Sorts an array using the heap sort algorithm.
 *
 * \tparam T Type of elements in the array
 * \param arr Pointer to the array to be sorted
 * \param n Size of array
 */
template <typename T>
void heapSort(T *arr, std::size_t n) {
    if (n <= 1) {
        return;
    }

    // Build max heap from the last non-leaf node down to 0
    for (std::size_t i = n / 2; i > 0; --i) {
        heapify(arr, n, i - 1);
    }

    // Extract elements from heap one by one
    for (std::size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

}  // namespace heap_sort
}  // namespace sorting

/**
 * @}
 * \brief Test cases to test the heap sort algorithm
 */
static void test() {
    std::cout << "Test 1: Integer array\n";
    int arr[] = {-10, 78, -1, -6, 7, 4, 94, 5, 99, 0};
    std::size_t sz = sizeof(arr) / sizeof(arr[0]);
    sorting::heap_sort::heapSort(arr, sz);
    assert(std::is_sorted(arr, arr + sz));
    std::cout << "Test 1 Passed\n========================\n";

    std::cout << "Test 2: Double precision array\n";
    double arr2[] = {4.5, -3.6, 7.6, 0.0, 12.9};
    sz = sizeof(arr2) / sizeof(arr2[0]);
    sorting::heap_sort::heapSort(arr2, sz);
    assert(std::is_sorted(arr2, arr2 + sz));
    std::cout << "Test 2 Passed\n========================\n";

    std::cout << "Test 3: Single element array\n";
    int arr3[] = {42};
    sorting::heap_sort::heapSort(arr3, 1);
    assert(std::is_sorted(arr3, arr3 + 1));
    std::cout << "Test 3 Passed\n========================\n";

    std::cout << "Test 4: Already sorted array\n";
    int arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sz = sizeof(arr4) / sizeof(arr4[0]);
    sorting::heap_sort::heapSort(arr4, sz);
    assert(std::is_sorted(arr4, arr4 + sz));
    std::cout << "Test 4 Passed\n========================\n";

    std::cout << "Test 5: Reverse sorted array\n";
    int arr5[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    sz = sizeof(arr5) / sizeof(arr5[0]);
    sorting::heap_sort::heapSort(arr5, sz);
    assert(std::is_sorted(arr5, arr5 + sz));
    std::cout << "Test 5 Passed\n========================\n";
}

/** Main function */
int main() {
    test();
    return 0;
}
