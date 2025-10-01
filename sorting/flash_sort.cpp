/**
 * @file
 * @brief Implementation of the Flash Sort algorithm.
 * @details
 * Flash Sort is an in-place, linear-time sorting algorithm for uniformly distributed data.
 * It divides the data into classes, rearranges elements into their respective classes,
 * and then sorts each class using insertion sort.
 * @see https://en.wikipedia.org/wiki/Flashsort
 * @note Flash Sort is not a stable sorting algorithm.
 * @author [Sachin Pangal](https://github.com/orthodox-64)
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Sorts an array using the Flash Sort algorithm.
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
 
 void flashSort(std::vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // Step 1: Find the minimum and maximum values in the array
    float minVal = *std::min_element(arr.begin(), arr.end());
    float maxVal = *std::max_element(arr.begin(), arr.end());

    // Step 2: Calculate the number of classes (buckets)
    int numClasses = 0.45 * n;
    if (numClasses < 2) numClasses = 2;

    // Step 3: Create a histogram of the data
    std::vector<int> count(numClasses, 0);
    for (int i = 0; i < n; ++i) {
        int index = numClasses * (arr[i] - minVal) / (maxVal - minVal);
        count[index]++;
    }

    // Step 4: Calculate the starting index of each class
    std::vector<int> pos(numClasses, 0);
    pos[0] = 0;
    for (int i = 1; i < numClasses; ++i) {
        pos[i] = pos[i - 1] + count[i - 1];
    }

    // Step 5: Rearrange the array into classes
    std::vector<float> temp = arr;
    for (int i = 0; i < n; ++i) {
        int index = numClasses * (arr[i] - minVal) / (maxVal - minVal);
        arr[pos[index]++] = temp[i];
    }

    // Step 6: Sort each class using insertion sort
    for (int i = 0; i < numClasses; ++i) {
        int start = pos[i] - count[i];
        int end = pos[i];
        std::sort(arr.begin() + start, arr.begin() + end);
    }
}

// Driver code to test the Flash Sort
int main() {
    std::vector<float> arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    flashSort(arr);

    std::cout << "Sorted array is: ";
    for (float num : arr) {
        std::cout << num << " ";
    }
    return 0;
}