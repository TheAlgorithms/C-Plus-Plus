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
#include <algorithm>
#include <cassert>
#include <vector>

namespace sorting {
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
//using array
 template <typename T>
 void merge(T *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    T *L = new T[n1], *R = new T[n2];

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
 template <typename T>
 void mergeSort(T *arr, int l, int r) {
     if (l < r) {
         int m = l + (r - l) / 2;
         mergeSort(arr, l, m);
         mergeSort(arr, m + 1, r);
         merge(arr, l, m, r);
     }
 }

 //using vector
 template <typename T>
 void merge(std::vector<T> *arr, int l, int m, int r) {
     int i, j, k;
     int n1 = m - l + 1;
     int n2 = r - m;

     T *L = new T[n1], *R = new T[n2];

     for (i = 0; i < n1; i++) L[i] = arr[0][l + i];
     for (j = 0; j < n2; j++) R[j] = arr[0][m + 1 + j];

     i = 0;
     j = 0;
     k = l;
     while (i < n1 || j < n2) {
         if (j >= n2 || (i < n1 && L[i] <= R[j])) {
             arr[0][k] = L[i];
             i++;
         } else {
             arr[0][k] = R[j];
             j++;
         }
         k++;
     }

     delete[] L;
     delete[] R;
 }
 template <typename T>
 void mergeSort(std::vector<T> *arr, int l, int r) {
     if (l < r) {
         int m = l + (r - l) / 2;
         mergeSort(arr, l, m);
         mergeSort(arr, m + 1, r);
         merge(arr, l, m, r);
     }
 }
 }

void tests() {
     // positive case
     int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
     std::cout << "Test 1... ";
     sorting::mergeSort(arr1, 0, 9);
     assert(std::is_sorted(arr1, arr1 + 10));
     std::cout << "passed" << '\n';

     // negative case
     int arr2[8] = {-55, -20, -5, -77, -12, -45, -32, -10};
     std::cout << "Test 2... ";
     sorting::mergeSort(arr2, 0, 7);
     assert(std::is_sorted(arr2, arr2 + 8));
     std::cout << "passed" << '\n';

     // mix positive and negative
     int arr3[8] = {1028, 45, -60, 0, -14, 35, 7, -4};
     std::cout << "Test 3... ";
     sorting::mergeSort(arr3, 0, 7);
     assert(std::is_sorted(arr3, arr3 + 8));
     std::cout << "passed" << '\n';

     // float
     float arr4[8] = {4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6};
     std::cout << "Test 4... ";
     sorting::mergeSort(arr4, 0, 7);
     assert(std::is_sorted(arr4, arr4 + 8));
     std::cout << "passed" << '\n';

     // using vector
     std::vector<float> arr5({4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6});
     std::cout << "Test 5... ";
     sorting::mergeSort(&arr5, 0, arr5.size()-1);
     assert(std::is_sorted(std::begin(arr5), std::end(arr5)));
     std::cout << "passed" << std::endl;
 }

int main() { 
    tests(); 

    // For user interaction
    size_t n;
    std::cout << "Enter the length of array (0 to exit)";
    std::cin >> n;

    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter any" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::mergeSort(arr, 0, n-1);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}