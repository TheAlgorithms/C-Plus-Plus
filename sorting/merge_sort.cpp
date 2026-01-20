/**
 *  \addtogroup sorting Sorting Algorithms
 *  @{
 *  \file
 *  \brief [Merge Sort Algorithm
 *  (MERGE SORT)](https://en.wikipedia.org/wiki/Merge_sort) implementation
 *
 *  \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 *  \details
 *  Merge Sort is an efficient, general purpose, comparison
 *  based sorting algorithm.
 *  Merge Sort is a divide and conquer algorithm
 *  Time  Complexity: O(n log n) 
 *  It is  same for all best case, worst case or average case 
 *  Merge Sort is very efficient when for the small data. 
 *  In built-in sort function merge sort along with quick sort is used. 
 */
#include <iostream>
#include <vector>

/**
 *
 * The merge() function is used for merging two halves.
 * The merge(arr, l, m, r) is key process that assumes that
 * arr[l..m] and arr[m+1..r] are sorted and merges the two
 * sorted sub-arrays into one.
 *
 * @param arr - array with two halves arr[l...m] and arr[m+1...r]
 * @param l - left index or start index of first half array
 * @param m - right index or end index of first half array
 *
 * (The second array starts form m+1 and goes till r)
 *
 * @param r - end index or right index of second half array
 */
void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Merge sort is a divide and conquer algorithm, it divides the
 * input array into two halves and calls itself for the two halves
 * and then calls merge() to merge the two halves
 *
 * @param arr - array to be sorted
 * @param l - left index or start index of array
 * @param r - right index or end index of array
 *
 */
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/**
 * Utility function used to print the array after
 * sorting
 */
void show(int *arr, int size) {
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << "\n";
}

/** Main function */
int main() {
    int size;
    std::cout << "Enter the number of elements: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Invalid size.\n";
        return 1;
    }

    int *arr = new int[size];
    std::cout << "Enter the unsorted elements: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    mergeSort(arr, 0, size - 1);
    std::cout << "Sorted array: ";
    show(arr, size);
    delete[] arr;
    return 0;
}
/** @} */
