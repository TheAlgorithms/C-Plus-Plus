/**
 *  \addtogroup sorting Sorting Algorithms
 *  @{
 *  \file
 *  \brief [3-Way Merge Sort Algorithm
 *  (3-WAY MERGE SORT)](https://en.wikipedia.org/wiki/Merge_sort) implementation
 *
 *  \author [Nirmalya Pal](http://github.com/SpEXterXD)
 *
 *  \details
 *  3-Way Merge Sort is an efficient, general-purpose, comparison
 *  based sorting algorithm. It extends the traditional Merge Sort
 *  algorithm by dividing the input array into three parts instead of two.
 *
 */
#include <iostream>
#include <vector>

/**
 * The merge() function merges three sorted halves of the array.
 * The merge(arr, left, mid1, mid2, right) assumes that
 * arr[left..mid1], arr[mid1+1..mid2], and arr[mid2+1..right] are sorted,
 * and merges these three sorted sub-arrays into one.
 *
 * @param arr - array with three sorted parts
 * @param left - left index or start index of first part
 * @param mid1 - right index or end index of first part
 * @param mid2 - right index or end index of second part
 * @param right - end index or right index of third part
 */
void merge(std::vector<int>& arr, int left, int mid1, int mid2, int right) {
    int n1 = mid1 - left + 1; // Size of the first sub-array
    int n2 = mid2 - mid1;     // Size of the second sub-array
    int n3 = right - mid2;    // Size of the third sub-array

    std::vector<int> leftArr(n1), midArr(n2), rightArr(n3);

    // Fill the sub-arrays
    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++) midArr[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < n3; i++) rightArr[i] = arr[mid2 + 1 + i];

    // Merging the sub-arrays back into the original array
    int i = 0, j = 0, k = 0, index = left;

    // Merging all three arrays
    while (i < n1 || j < n2 || k < n3) {
        if (i < n1 && (j >= n2 || leftArr[i] <= midArr[j]) && (k >= n3 || leftArr[i] <= rightArr[k])) {
            arr[index++] = leftArr[i++];
        } else if (j < n2 && (k >= n3 || midArr[j] <= rightArr[k])) {
            arr[index++] = midArr[j++];
        } else if (k < n3) {
            arr[index++] = rightArr[k++];
        }
    }
}

/**
 * 3-Way Merge Sort is a divide and conquer algorithm that divides the
 * input array into three halves, recursively sorts them, and then merges
 * the three sorted halves.
 *
 * @param arr - array to be sorted
 * @param left - left index or start index of array
 * @param right - right index or end index of array
 */
void threeWayMergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Finding mid points to divide the array into three parts
        int mid1 = left + (right - left) / 3;
        int mid2 = left + 2 * (right - left) / 3;

        // Recursively sorting the three parts
        threeWayMergeSort(arr, left, mid1);
        threeWayMergeSort(arr, mid1 + 1, mid2);
        threeWayMergeSort(arr, mid2 + 1, right);

        // Merging the sorted parts
        merge(arr, left, mid1, mid2, right);
    }
}

/**
 * Utility function to print the array after sorting.
 *
 * @param arr - array to be printed
 * @param size - size of the array
 */
void show(const std::vector<int>& arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

/** Main function */
int main() {
    int size;
    std::cout << "Enter the number of elements: ";
    std::cin >> size;

    std::vector<int> arr(size);
    std::cout << "Enter the unsorted elements: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    threeWayMergeSort(arr, 0, size - 1);
    std::cout << "Sorted array: ";
    show(arr, size);

    return 0;
}
/** @} */
