/**
 *  \addtogroup sorting Sorting Algorithms
 *  @{
 *  \file
 *  \brief [Merege Sort Algorithm
 *  (MEREGE SORT)](https://en.wikipedia.org/wiki/Merge_sort) implementation
 *
 *  \author [Ayaan Khan](http://github.com/ayaankhan98)
 *
 *  \details
 *  Merge Sort is an efficient, general purpose, comparison
 *  based sorting algorithm.
 *  Merge Sort is a divide and conquer algorithm
 *
 */
#include <iostream>
using namespace std;

/**
 *
 * The merge() function is used for merging two halves.
 * The merge(arr, l, m, r) is key process that assumes that
 * arr[l..m] and arr[m+1..r] are sorted and merges the two
 * sorted sub-arrays into one.
 *
 * @param arr - array with two halves arr[l...m] and arr[m+1...l]
 * @param l - left index or start index of first half array
 * @param m - right index or end index of first half array
 *
 * (The second array starts form m+1 and goes till l)
 *
 * @param l - end index or right index of second half array
 */
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;

    int *L = new int[n1];

    for (i = 0; i < n1; i++) L[i] = arr[l + i];

    i = 0;
    j = m + 1;
    k = l;
    while (i < n1 || j <= r) {
        if (j > r || (i < n1 && L[i] <= arr[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = arr[j];
            j++;
        }
        k++;
    }

    delete[] L;
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
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << "\n";
}

/** Main function */
int main() {
    int size;
    cout << "Enter the number of elements : ";
    cin >> size;
    int *arr = new int[size];
    cout << "Enter the unsorted elements : ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    mergeSort(arr, 0, size - 1);
    std::cout << "Sorted array : ";
    show(arr, size);
    delete[] arr;
    return 0;
}
/** @} */
