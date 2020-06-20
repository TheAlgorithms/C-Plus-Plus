/**
 * \addtogroup sorting Sorting Algorithm
 * @{
 * \file
 * \brief [Heap Sort Algorithm
 * (HEAP SORT)](https://en.wikipedia.org/wiki/Heapsort) implementation
 *
 * \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 * \details
 *  heapsort is a comparison-based sorting algorithm.
 *  Heapsort can be thought of as an improved selection sort:
 *  like selection sort, heapsort divides its input into a sorted
 *  and an unsorted region, and it iteratively shrinks the unsorted
 *  region by extracting the largest element from it and inserting
 *  it into the sorted region. Unlike selection sort,
 *  heapsort does not waste time with a linear-time scan of the
 *  unsorted region; rather, heap sort maintains the unsorted region
 *  in a heap data structure to more quickly find the largest element
 *  in each step.
 *
 *  Time Complexity - O(nlog(n))
 *
 */
#include <iostream>

/**
 *
 * Utility Lambda function to print the array after
 * sorting.
 *
 * @param arr array to be printed
 * @param sz size of array
 *
 */
auto printArray = [](int *arr, int sz) {
    for (int i = 0; i < sz; i++) std::cout << arr[i] << "  ";
    std::cout << "\n";
};

/**
 *
 * The heapify procedure can be thought of as building a heap from
 * the bottom up by successively sifting downward to establish the
 * heap property.
 *
 * @param arr array be to sorted
 * @param
 */
void (*heapify)(int *arr, int n, int i) = [](int *arr, int n, int i) {
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
};

/**
 * heapSort lambda function utilizes heapify procedure to sort
 * the array
 *
 * @param arr array to be sorted
 * @param n size of array
 *
 */
auto heapSort = [](int *arr, int n) {
    for (int i = n - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
};

/** Main function */
int main() {
    int arr[] = {-10, 78, -1, -6, 7, 4, 94, 5, 99, 0};
    int sz = sizeof(arr) / sizeof(arr[0]);  // sz - size of array
    printArray(arr, sz);  // displaying the array before sorting
    heapSort(arr, sz);    // calling heapsort to sort the array
    printArray(arr, sz);  // display array after sorting
    return 0;
}
/** @} */
