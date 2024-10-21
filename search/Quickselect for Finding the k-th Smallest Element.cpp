#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


/**
 * @brief Partition the array and return the pivot index.
 * 
 * This function rearranges the elements in the array such that elements
 * less than or equal to the pivot are on the left, and elements greater
 * than the pivot are on the right.
 * 
 * @param arr The array of integers to partition.
 * @param left The starting index of the segment to partition.
 * @param right The ending index of the segment to partition.
 * @returns The index of the pivot after partitioning.
 */
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

/**
 * @brief Find the k-th smallest element using QuickSelect algorithm.
 * 
 * This function uses a recursive approach to partition the array and find
 * the k-th smallest element.
 * 
 * @param arr The array of integers to search.
 * @param left The starting index of the segment to search.
 * @param right The ending index of the segment to search.
 * @param k The index of the k-th smallest element (0-based).
 * @returns The k-th smallest element in the array.
 */
int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left]; // Base case: only one element

    int pivotIndex = partition(arr, left, right);

    if (k == pivotIndex) {
        return arr[k]; // Found the k-th smallest element
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k); // Search left
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k); // Search right
    }
}

/**
 * @brief Self-test implementations
 * 
 * This function contains test cases to validate the QuickSelect algorithm
 * using assertions.
 * 
 * @returns void
 */
static void test() {
    vector<int> testArr1 = {3, 2, 1, 5, 6, 4};
    assert(quickSelect(testArr1, 0, testArr1.size() - 1, 0) == 1);
    assert(quickSelect(testArr1, 0, testArr1.size() - 1, 1) == 2);
    assert(quickSelect(testArr1, 0, testArr1.size() - 1, 2) == 3);
    assert(quickSelect(testArr1, 0, testArr1.size() - 1, 3) == 4);
    assert(quickSelect(testArr1, 0, testArr1.size() - 1, 4) == 5);
    assert(quickSelect(testArr1, 0, testArr1.size() - 1, 5) == 6);

    vector<int> testArr2 = {10, 4, 5, 8, 6, 11, 26};
    assert(quickSelect(testArr2, 0, testArr2.size() - 1, 0) == 4);
    assert(quickSelect(testArr2, 0, testArr2.size() - 1, 3) == 8);
    assert(quickSelect(testArr2, 0, testArr2.size() - 1, 6) == 26);

    cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * 
 * @param argc Command-line argument count (ignored)
 * @param argv Command-line array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // Run self-test implementations
    return 0;
}
