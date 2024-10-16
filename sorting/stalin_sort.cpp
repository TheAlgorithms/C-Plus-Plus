/**
 * @file StalinSort.cpp
 * @brief Implementation of the StalinSort algorithm in C++.
 *
 * @details This file contains the implementation of StalinSort algorithm which
 * retains only non-decreasing elements in the list. Named after Stalin for its
 * ruthless removal of elements that don't meet the criteria.
 *
 * @see https://medium.com/@kaweendra/the-ultimate-sorting-algorithm-6513d6968420
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

/**
 * @brief Function to sort an array using StalinSort algorithm
 * @param array Vector of elements to be sorted
 * @return Vector of sorted elements
 */
template <typename T>
std::vector<T> stalinSort(std::vector<T> array) {
    if (array.empty()) return array;

    std::vector<T> result;
    result.push_back(array[0]);

    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i] >= result.back()) {
            result.push_back(array[i]);
        }
    }

    return result;
}

/**
 * @brief Function to sort an array using Adaptive Merge Sort algorithm
 * @param array Vector of elements to be sorted
 * @return Vector of sorted elements
 */
template <typename T>
void merge(std::vector<T>& array, std::vector<T>& aux, int low, int mid, int high) {
    std::copy(array.begin() + low, array.begin() + high + 1, aux.begin() + low);

    int i = low;
    int j = mid + 1;
    for (int k = low; k <= high; ++k) {
        if (i > mid) {
            array[k] = aux[j++];
        } else if (j > high) {
            array[k] = aux[i++];
        } else if (aux[j] < aux[i]) {
            array[k] = aux[j++];
        } else {
            array[k] = aux[i++];
        }
    }
}

template <typename T>
void sort(std::vector<T>& array, std::vector<T>& aux, int low, int high) {
    if (low >= high) return;

    int mid = low + (high - low) / 2;
    sort(array, aux, low, mid);
    sort(array, aux, mid + 1, high);
    merge(array, aux, low, mid, high);
}

template <typename T>
std::vector<T> adaptiveMergeSort(std::vector<T> array) {
    if (array.size() <= 1) return array;

    std::vector<T> aux(array.size());
    sort(array, aux, 0, array.size() - 1);
    return array;
}

void testStalinSort() {
    // Test Integer Input
    std::vector<int> integers = {4, 23, 6, 78, 1, 54, 231, 9, 12};
    std::vector<int> expectedIntegers = {4, 23, 78, 231};
    assert(stalinSort(integers) == expectedIntegers);

    // Test String Input
    std::vector<std::string> strings = {"c", "a", "e", "b", "d"};
    std::vector<std::string> expectedStrings = {"c", "e"};
    assert(stalinSort(strings) == expectedStrings);

    // Test with duplicates
    std::vector<int> duplicates = {1, 3, 2, 2, 5, 4};
    std::vector<int> expectedDuplicates = {1, 3, 5};
    assert(stalinSort(duplicates) == expectedDuplicates);

    // Test empty array
    std::vector<int> empty = {};
    std::vector<int> expectedEmpty = {};
    assert(stalinSort(empty) == expectedEmpty);

    // Test single element
    std::vector<int> single = {42};
    std::vector<int> expectedSingle = {42};
    assert(stalinSort(single) == expectedSingle);

    std::cout << "All StalinSort tests passed!" << std::endl;
}

void testAdaptiveMergeSort() {
    // Test Integer Input
    std::vector<int> integers = {4, 23, 6, 78, 1, 54, 231, 9, 12};
    std::vector<int> expectedIntegers = {1, 4, 6, 9, 12, 23, 54, 78, 231};
    assert(adaptiveMergeSort(integers) == expectedIntegers);

    // Test String Input
    std::vector<std::string> strings = {"c", "a", "e", "b", "d"};
    std::vector<std::string> expectedStrings = {"a", "b", "c", "d", "e"};
    assert(adaptiveMergeSort(strings) == expectedStrings);

    // Test with duplicates
    std::vector<int> duplicates = {1, 3, 2, 2, 5, 4};
    std::vector<int> expectedDuplicates = {1, 2, 2, 3, 4, 5};
    assert(adaptiveMergeSort(duplicates) == expectedDuplicates);

    // Test empty array
    std::vector<int> empty = {};
    std::vector<int> expectedEmpty = {};
    assert(adaptiveMergeSort(empty) == expectedEmpty);

    // Test single element
    std::vector<int> single = {42};
    std::vector<int> expectedSingle = {42};
    assert(adaptiveMergeSort(single) == expectedSingle);

    std::cout << "All AdaptiveMergeSort tests passed!" << std::endl;
}

int main() {
    testStalinSort();
    testAdaptiveMergeSort();
    return 0;
}
