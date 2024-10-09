/**
 *  @{
 *  @file
 *  @brief 3-Way Merge Sort Algorithm implementation
 *
 *  @author [Nirmalya Pal](http://github.com/SpEXterXD)
 *
 *  @details
 *  3-Way Merge Sort is an efficient, general-purpose, comparison
 *  based sorting algorithm. It extends the traditional Merge Sort
 *  algorithm by dividing the input array into three parts instead of two.
 *
 */

#include <iostream>
#include <vector>
#include <cassert>

/**
 * @brief Merges three sorted halves of the array.
 * 
 * @param arr - array with three sorted parts
 * @param left - left index or start index of the first part
 * @param mid1 - right index or end index of the first part
 * @param mid2 - right index or end index of the second part
 * @param right - end index or right index of the third part
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
 * @brief 3-Way Merge Sort is a divide and conquer algorithm that divides the
 * input array into three halves, recursively sorts them, and then merges
 * the three sorted halves.
 *
 * @param arr - array to be sorted
 * @param left - left index or start index of the array
 * @param right - right index or end index of the array
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
 * @brief Utility function to print the array after sorting.
 *
 * @param arr - array to be printed
 * @param size - size of the array
 */
void show(const std::vector<int>& arr) {
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

/**
 * @brief Tests for 3-Way Merge Sort algorithm
 */
void testThreeWayMergeSort() {
    // Test case 1: Empty array
    std::vector<int> arr1 = {};
    threeWayMergeSort(arr1, 0, arr1.size() - 1);
    assert(arr1.empty());  // No message needed, assert just checks condition

    // Test case 2: Array with one element
    std::vector<int> arr2 = {5};
    threeWayMergeSort(arr2, 0, arr2.size() - 1);
    assert(arr2.size() == 1 && arr2[0] == 5);  // Correct result check

    // Test case 3: Array with two elements
    std::vector<int> arr3 = {10, 5};
    threeWayMergeSort(arr3, 0, arr3.size() - 1);
    assert(arr3.size() == 2 && arr3[0] == 5 && arr3[1] == 10);  // Correct result check

    // Test case 4: Already sorted array
    std::vector<int> arr4 = {1, 2, 3, 4, 5};
    threeWayMergeSort(arr4, 0, arr4.size() - 1);
    assert(arr4.size() == 5 && arr4[0] == 1 && arr4[1] == 2 && arr4[2] == 3 &&
           arr4[3] == 4 && arr4[4] == 5);  // Correct result check

    // Test case 5: Reverse sorted array
    std::vector<int> arr5 = {5, 4, 3, 2, 1};
    threeWayMergeSort(arr5, 0, arr5.size() - 1);
    assert(arr5.size() == 5 && arr5[0] == 1 && arr5[1] == 2 && arr5[2] == 3 &&
           arr5[3] == 4 && arr5[4] == 5);  // Correct result check

    // Test case 6: Mixed array
    std::vector<int> arr6 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    threeWayMergeSort(arr6, 0, arr6.size() - 1);
    assert(arr6.size() == 11 && arr6[0] == 1 && arr6[1] == 1 && arr6[2] == 2 &&
           arr6[3] == 3 && arr6[4] == 3 && arr6[5] == 4 && arr6[6] == 5 &&
           arr6[7] == 5 && arr6[8] == 5 && arr6[9] == 6 && arr6[10] == 9);  // Correct result check

    std::cout << "All tests passed!" << std::endl;
}

/** Main function */
int main() {
    // Run the tests
    testThreeWayMergeSort();

    return 0;
}
