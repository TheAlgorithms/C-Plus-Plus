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
#include <cassert>   ///for assert
#include <iostream>  ///for input-output operations

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
 * @param r - end index or right index of second half array
 */

namespace sorting {
namespace mergesort {

int *merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1], *R = new int[n2];

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 || j < n2) {
        if (j >= n2 || (i < n1 && L[i] <= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    delete[] L;
    delete[] R;
    return arr;
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
int *mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        arr = merge(arr, l, m, r);
    }
    return arr;
}

/**
 * Utility function used to print the array after
 * sorting
 */
void show(int *arr, int size) {
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << "\n";
}

}  // namespace mergesort

}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // test case 1
    int arr1[] = {10, 5, 9, 1, 29, 4, 15};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    sorting::mergesort::mergeSort(arr1, 0, size1 - 1);
    std::cout << "Passed\n";
    sorting::mergesort::mergeSort(arr1, 0, size1 - 1);
    for (int i = 0; i < size1; i++) {
        std::cout << arr1[i] << ", ";
    }
    std::cout << std::endl;

    // test case 2
    int arr2[] = {69, 100, 24, 32, 78, 1, 55, 63, 30};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    sorting::mergesort::mergeSort(arr2, 0, size2 - 1);
    std::cout << "Passed\n";
    sorting::mergesort::mergeSort(arr2, 0, size2 - 1);
    for (int i = 0; i < size2; i++) {
        std::cout << arr2[i] << ", ";
    }
    std::cout << std::endl;

    // test case 3
    int arr3[] = {20, 11, 29, 60, 0, 55, 47, 80, 96, 98};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    sorting::mergesort::mergeSort(arr3, 0, size3 - 1);
    std::cout << "Passed\n";
    sorting::mergesort::mergeSort(arr3, 0, size3 - 1);
    for (int i = 0; i < size3; i++) {
        std::cout << arr3[i] << ", ";
    }
    std::cout << std::endl;

    // test case 4
    int arr4[] = {20, 11, 29, 60, 0, 55, 47, 80, 96, 98};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    sorting::mergesort::mergeSort(arr4, 0, size4 - 1);
    std::cout << "Passed\n";
    sorting::mergesort::mergeSort(arr4, 0, size4 - 1);
    for (int i = 0; i < size4; i++) {
        std::cout << arr4[i] << ", ";
    }
    std::cout << std::endl;
}

/** Main function */
int main() {
    int x;
    std::cout << "Enter your mode of operation : (1) Interactive Mode (2) "
                 "Self Test Mode \n";
    std::cin >> x;
    if (x == 1) {
        int size;
        std::cout << "Enter the number of elements : ";
        std::cin >> size;
        int *arr = new int[size];
        std::cout << "Enter the unsorted elements : ";
        for (int i = 0; i < size; ++i) {
            std::cin >> arr[i];
        }
        sorting::mergesort::mergeSort(arr, 0, size - 1);
        std::cout << "Sorted array : ";
        sorting::mergesort::show(arr, size);
        delete[] arr;
    } else {
        test();
    }

    return 0;
}
/** @} */
