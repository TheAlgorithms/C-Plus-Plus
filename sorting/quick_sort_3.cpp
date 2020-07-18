/*
 * @file
 * @brief Implementation Details
 * @details Quick sort 3 works on Dutch National Flag Algorithm
 * The major difference between simple quicksort and quick sort 3 comes in the
 * function partition3 In quick_sort_partition3 we divide the vector/array into
 * 3 parts. quick sort 3 works faster in some cases as compared to simple
 * quicksort.
 * @author immortal-j
 * @author [Krishna Vedala](https://github/kvedala)
 */
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

namespace {
/**
 * Operator to print the array.
 * @param out std::ostream object to write to
 * @param arr array to write
 */
template <typename T, size_t size>
std::ostream &operator<<(std::ostream &out, const std::array<T, size> &arr) {
    for (size_t i = 0; i < size; ++i) {
        out << arr[i];
        if (i < size - 1) {
            out << ", ";
        }
    }
    return out;
}

}  // namespace

/**
 * @namespace sorting
 * @brief Sorting Algorithms
 */
namespace sorting {
/** This function partitions `arr[]` in three parts
 * 1. \f$arr[l\ldots i]\f$ contains all elements smaller than pivot
 * 2. \f$arr[(i+1)\ldots (j-1)]\f$ contains all occurrences of pivot
 * 3. \f$arr[j\ldots r]\f$ contains all elements greater than pivot
 */
template <typename T, size_t N>
void partition3(std::array<T, N> *arr, int low, int high, int *i, int *j) {
    // To handle 2 elements
    if (high - low <= 1) {
        if ((*arr)[high] < (*arr)[low]) {
            std::swap((*arr)[high], (*arr)[low]);
        }
        *i = low;
        *j = high;
        return;
    }

    int mid = low;
    int pivot = arr[high];
    while (mid <= high) {
        if ((*arr)[mid] < pivot) {
            std::swap((*arr)[low++], (*arr)[mid++]);
        } else if ((*arr)[mid] == pivot) {
            mid++;
        } else if ((*arr)[mid] > pivot) {
            std::swap((*arr)[mid], (*arr)[high--]);
        }
    }

    // update i and j
    *i = low - 1;
    *j = mid;  // or high-1
}

// 3-way partition based quick sort
template <typename T, size_t N>
void quicksort(std::array<T, N> *arr, int low, int high) {
    if (low >= high) {  // 1 or 0 elements
        return;
    }

    int i, j;

    // i and j are passed as reference
    partition3(arr, low, high, &i, &j);

    // Recur two halves
    quicksort(arr, low, i);
    quicksort(arr, j, high);
}

template <typename T, size_t N>
std::array<T, N> quicksort(std::array<T, N> arr, int low, int high) {
    if (low >= high) {  // 1 or 0 elements
        return;
    }

    int i, j;

    // i and j are passed as reference
    partition3(&arr, low, high, &i, &j);

    // Recur two halves
    quicksort(&arr, low, i);
    quicksort(&arr, j, high);

    return arr;
}
}  // namespace sorting

// Driver program for above functions
int main() {
    int size, i;
    std::cout << "Enter Number of elements\n";
    std::cin >> size;
    std::array<int, size> arr{};
    for (auto &a : arr) {
        a = std::rand() % 100 - 50;  // random numbers between -50, 49
    }

    std::array<int, size> sorted = sorting::quicksort(arr, 0, size - 1);
    std::cout << "Sorted Array is:\n\t";
    std::cout << sorted << "\n";
    return 0;
}
