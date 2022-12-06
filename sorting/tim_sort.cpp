// C++ program to perform TimSort.
#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>

namespace sorting {
const int RUN = 32;

// this function sorts array from left index to to right index which is of size
// atmost RUN

template <typename T>
void insertionSort(T *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (arr[j] > temp && j >= left) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
// merge function merges the sorted runs
template <typename T>
void merge(T *arr, int l, int m, int r) {
    // original array is broken in two parts, left and right array
    int len1 = m - l + 1, len2 = r - m;
    T *left = new T[len1], *right = new T[len2];
    for (int i = 0; i < len1; i++) left[i] = arr[l + i];
    for (int i = 0; i < len2; i++) right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    // after comparing, we merge those two array in larger sub array
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of left, if any
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    // copy remaining element of right, if any
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
    delete[] left;
    delete[] right;
}
// iterative Timsort function to sort the array[0...n-1] (similar to merge sort)
//using array
template <typename T>
void timSort(T *arr, int n) {
    // Sort individual subarrays of size RUN
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, std::min((i + 31), (n - 1)));

    // start merging from size RUN (or 32). It will merge to form size 64, then
    // 128, 256 and so on ....
    for (int size = RUN; size < n; size = 2 * size) {
        // pick starting point of left sub array. We are going to merge
        // arr[left..left+size-1] and arr[left+size, left+2*size-1] After every
        // merge, we increase left by 2*size
        for (int left = 0; left < n; left += 2 * size) {
            // find ending point of left sub array
            // mid+1 is starting point of right sub array
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            // merge sub array arr[left.....mid] & arr[mid+1....right]
            merge(arr, left, mid, right);
        }
    }
}
}

void tests() {
    // positive case
    int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
    std::cout << "Test 1... ";
    sorting::timSort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << '\n';

    // negative case
    int arr2[8] = {-55, -20, -5, -77, -12, -45, -32, -10};
    std::cout << "Test 2... ";
    sorting::timSort(arr2, 8);
    assert(std::is_sorted(arr2, arr2 + 8));
    std::cout << "passed" << '\n';

    // mix positive and negative
    int arr3[8] = {1028, 45, -60, 0, -14, 35, 7, -4};
    std::cout << "Test 3... ";
    sorting::timSort(arr3, 8);
    assert(std::is_sorted(arr3, arr3 + 8));
    std::cout << "passed" << '\n';

    // float
    float arr4[8] = {4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6};
    std::cout << "Test 4... ";
    sorting::timSort(arr4, 8);
    assert(std::is_sorted(arr4, arr4 + 8));
    std::cout << "passed" << '\n';
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

    sorting::timSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}