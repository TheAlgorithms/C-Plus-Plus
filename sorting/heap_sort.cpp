/**
 * \file
 * \brief [Heap Sort Algorithm
 * (heap sort)](https://en.wikipedia.org/wiki/Heapsort) implementation
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
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
#include <iostream>

/**
 *
 * Utility function to print the array after
 * sorting.
 *
 * @param arr array to be printed
 * @param sz size of array
 *
 */
template <typename T>
void printArray(T *arr, int sz) {
    for (int i = 0; i < sz; i++) std::cout << arr[i] << "  ";
    std::cout << "\n";
}

/**
 *
 * \addtogroup sorting Sorting Algorithm
 * @{
 *
 * The heapify procedure can be thought of as building a heap from
 * the bottom up by successively sifting downward to establish the
 * heap property.
 *
 * @param arr array to be sorted
 * @param n size of array
 * @param i node position in Binary Tress or element position in
 *          Array to be compared with it's childern
 *
 */
template <typename T>
void heapify(T *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/**
 * Utilizes heapify procedure to sort
 * the array
 *
 * @param arr array to be sorted
 * @param n size of array
 *
 */
template <typename T>
void heapSort(T *arr, int n) {
    for (int i = n - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/**
 *
 * @}
 * Test cases to test the program
 *
 */
void test() {
    std::cout << "Test 1\n";
    int arr[] = {-10, 78, -1, -6, 7, 4, 94, 5, 99, 0};
    int sz = sizeof(arr) / sizeof(arr[0]);  // sz - size of array
    printArray(arr, sz);  // displaying the array before sorting
    heapSort(arr, sz);    // calling heapsort to sort the array
    printArray(arr, sz);  // display array after sorting
    assert(std::is_sorted(arr, arr + sz));
    std::cout << "Test 1 Passed\n========================\n";

    std::cout << "Test 2\n";
    double arr2[] = {4.5, -3.6, 7.6, 0, 12.9};
    sz = sizeof(arr2) / sizeof(arr2[0]);
    printArray(arr2, sz);
    heapSort(arr2, sz);
    printArray(arr2, sz);
    assert(std::is_sorted(arr2, arr2 + sz));
    std::cout << "Test 2 passed\n";
}

/** Main function */
int main() {
    test();
    return 0;
}
