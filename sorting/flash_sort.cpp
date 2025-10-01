/**
 * @file
 * @brief Implementation of the Flash Sort algorithm with self-tests.
 * @details
 * Flash Sort is an in-place, linear-time sorting algorithm for uniformly distributed data.
 * It divides the data into classes, rearranges elements into their respective classes,
 * and then sorts each class using insertion sort.
 * @see https://en.wikipedia.org/wiki/Flashsort
 * @note Flash Sort is not a stable sorting algorithm.
 * @author [Sachin Pangal](https://github.com/orthodox-64)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Sorts an array using the Flash Sort algorithm.
 * @param arr The array to be sorted.
 */
void flashSort(std::vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    float minVal = *std::min_element(arr.begin(), arr.end());
    float maxVal = *std::max_element(arr.begin(), arr.end());
    if (minVal == maxVal) return;

    int numClasses = 0.45 * n;
    if (numClasses < 2) numClasses = 2;

    std::vector<int> count(numClasses, 0);
    for (int i = 0; i < n; ++i) {
        int index = numClasses * (arr[i] - minVal) / (maxVal - minVal);
        if (index >= numClasses) index = numClasses - 1;  // prevent overflow
        count[index]++;
    }

    std::vector<int> pos(numClasses, 0);
    pos[0] = 0;
    for (int i = 1; i < numClasses; ++i) {
        pos[i] = pos[i - 1] + count[i - 1];
    }

    std::vector<float> temp = arr;
    for (int i = 0; i < n; ++i) {
        int index = numClasses * (arr[i] - minVal) / (maxVal - minVal);
        if (index >= numClasses) index = numClasses - 1;
        arr[pos[index]++] = temp[i];
    }

    for (int i = 0; i < numClasses; ++i) {
        int start = pos[i] - count[i];
        int end = pos[i];
        std::sort(arr.begin() + start, arr.begin() + end);
    }
}

/**
 * @brief Self-test implementations
 */
static void test() {
    // Test 1
    std::vector<float> array1 = {0.897f, 0.565f, 0.656f, 0.1234f, 0.665f, 0.3434f};
    std::cout << "Test 1... ";
    flashSort(array1);
    assert(std::is_sorted(array1.begin(), array1.end()));
    std::cout << "passed" << std::endl;

    // Test 2
    std::vector<float> array2 = {1.2f, 3.4f, 0.5f, 2.2f, 1.1f};
    std::cout << "Test 2... ";
    flashSort(array2);
    assert(std::is_sorted(array2.begin(), array2.end()));
    std::cout << "passed" << std::endl;

    // Test 3
    std::vector<float> array3 = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    std::cout << "Test 3... ";
    flashSort(array3);
    assert(std::is_sorted(array3.begin(), array3.end()));
    std::cout << "passed" << std::endl;

    // Test 4
    std::vector<float> array4 = {0.1f, 0.1f, 0.1f, 0.1f};
    std::cout << "Test 4... ";
    flashSort(array4);
    assert(std::is_sorted(array4.begin(), array4.end()));
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 */
int main() {
    test();  // execute the tests
    return 0;
}