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
#include <vector>

namespace sorting {
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
template <typename T>
void CombSort(T * arr, int len) {
    /**
     *
     * initial gap will be maximum and the maximum possible value is
     * the size of the array that is n and which is equal to r in this
     * case so to avoid passing an extra parameter n that is the size of
     * the array we are using r to initialize the initial gap.
     *
     */
    int gap = len;

    /// Initialize swapped as true to make sure that loop runs
    bool swapped = true;

    /// Keep running until gap = 1 or none elements were swapped
    while (gap != 1 || swapped) {
        /// Find next gap
        gap = FindNextGap(gap);

        swapped = false;

        /// Compare all elements with current gap
        for (int i = 0; i < len - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

//using vector
template <typename T>
void CombSort(std::vector<T> *arr) {
    size_t len = arr->size();
    int gap = len;

    bool swapped = true;

    while (gap != 1 || swapped) {

        gap = FindNextGap(gap);

        swapped = false;

        for (int i = 0; i < len - gap; ++i) {
            if (arr[0][i] > arr[0][i + gap]) {
                std::swap(arr[0][i], arr[0][i + gap]);
                swapped = true;
            }
        }
    }
}
}  // namespace sorting

void tests() {
    /// Test 1 positive case
    int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
    std::cout << "Test 1... ";
    sorting::CombSort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << '\n';

    /// Test 2 negative case
    int arr2[8] = {-55, -20, -5, -77, -12, -45, -32, -10};
    std::cout << "Test 2... ";
    sorting::CombSort(arr2, 8);
    assert(std::is_sorted(arr2, arr2 + 8));
    std::cout << "passed" << '\n';

     // mix positive and negative
    int arr3[8] = {1028, 45, -60, 0, -14, 35, 7, -4};
    std::cout << "Test 3... ";
    sorting::CombSort(arr3, 8);
    assert(std::is_sorted(arr3, arr3 + 8));
    std::cout << "passed" << '\n';

     // float
    float arr4[8] = {4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6};
    std::cout << "Test 4... ";
    sorting::CombSort(arr4, 8);
    assert(std::is_sorted(arr4, arr4 + 8));
    std::cout << "passed" << '\n';

    // using vector
    std::vector<float> arr5({4.0, -7.4, 0, 17.5, -2.3, 6.4, 1.5, -6.6});
    std::cout << "Test 5... ";
    sorting::CombSort(&arr5);
    assert(std::is_sorted(std::begin(arr5), std::end(arr5)));
    std::cout << "passed" << std::endl;

}

/** Main function */
int main() {
    // Running tests to test algorithm
    tests();

    // For user interaction
    size_t n;
    std::cout << "Enter the length of array (0 to exit)";
    std::cin >> n;

    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter Any" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::CombSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}
