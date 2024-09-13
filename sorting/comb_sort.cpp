/**
 *
 * \file
 * \brief [Comb Sort Algorithm
 * (Comb Sort)](https://en.wikipedia.org/wiki/Comb_sort)
 *
 * \author
 *
 * \details
 * - A better version of bubble sort algorithm
 * - Bubble sort compares adjacent values whereas comb sort uses gap larger
 *   than 1
 * - Best case Time complexity O(n)
 *   Worst case Time complexity O(n^2)
 *
 */

#include <algorithm>
#include <cassert>
#include <iostream>

/**
 *
 * Find the next gap by shrinking the current gap by shrink factor of 1.3
 * @param gap current gap
 * @return new gap
 *
 */
int FindNextGap(int gap) {
    gap = (gap * 10) / 13;

    return std::max(1, gap);
}

/** Function to sort array
 *
 * @param arr array to be sorted
 * @param l start index of array
 * @param r end index of array
 *
 */
void CombSort(int *arr, int l, int r) {
    /**
     *
     * initial gap will be maximum and the maximum possible value is
     * the size of the array that is n and which is equal to r in this
     * case so to avoid passing an extra parameter n that is the size of
     * the array we are using r to initialize the initial gap.
     *
     */
    int gap = r;

    /// Initialize swapped as true to make sure that loop runs
    bool swapped = true;

    /// Keep running until gap = 1 or none elements were swapped
    while (gap != 1 || swapped) {
        /// Find next gap
        gap = FindNextGap(gap);

        swapped = false;

        /// Compare all elements with current gap
        for (int i = l; i < r - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void tests() {
    /// Test 1
    int arr1[10] = {34, 56, 6, 23, 76, 34, 76, 343, 4, 76};
    CombSort(arr1, 0, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "Test 1 passed\n";

    /// Test 2
    int arr2[8] = {-6, 56, -45, 56, 0, -1, 8, 8};
    CombSort(arr2, 0, 8);
    assert(std::is_sorted(arr2, arr2 + 8));
    std::cout << "Test 2 Passed\n";
}

/** Main function */
int main() {
    /// Running predefined tests
    tests();

    /// For user interaction
    int n;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) std::cin >> arr[i];
    CombSort(arr, 0, n);
    for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
    delete[] arr;
    return 0;
}
