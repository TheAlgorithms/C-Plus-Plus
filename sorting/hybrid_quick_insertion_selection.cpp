/**
 * @file
 * @brief Hybrid of QuickSort, InsertionSort and SelectionSort
 * https://es.wikipedia.org/wiki/Quicksort
 * https://en.wikipedia.org/wiki/Selection_sort
 * https://en.wikipedia.org/wiki/Insertion_sort
 * @details
 * this is a hybrid sorting algorithm
 * uses quicksort to split the array in two
 * sorts the left half with insertion sort
 * sorts the right half with selection sort
 * created for educational purposes not optimized for speed.
 * @author [Cesar](https://github.com/cesar-011)
 * @see quick_sort.cpp, insertion_sort.cpp, selection_sort_iterative.cpp
 */

#include <algorithm>  /// for std::is_sorted
#include <cassert>    /// for assert
#include <iostream>   /// for IO
#include <vector>     /// for vector

/**
 * @brief swap two elements of a vector
 * @tparam T
 * @param arr
 * @param i
 * @param j
 */
template <typename T>
void swap(std::vector<T>& arr, int i, int j) {
    T aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

/**
 * @brief print the array
 * @tparam T
 * @param arr
 * @param size
 */
template <typename T>
void print_array(const std::vector<T>& arr) {
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
}

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {

/**
 * @namespace hybrid_quick_insert_select
 * @brief Hybrid of QuickSort, InsertionSort and SelectionSort algorithms
 */
namespace hybrid_quick_insert_select {

/**
 * @brief Sorts a vector using a hybrid of QuickSort, Insertion Sort, and
 * Selection Sort.
 *
 * This algorithm partitions the vector using QuickSort's partitioning scheme.
 * It then applies Insertion Sort to the left half and Selection Sort to the
 * right half. This hybrid is intended for educational purposes and not
 * optimized for performance.
 *
 * @tparam T Type of the elements in the vector. Must support comparison
 * operators.
 * @param arr Reference to the vector to be sorted.
 * @param low Starting index of the subarray to sort.
 * @param high Ending index of the subarray to sort (exclusive).
 */
template <typename T>
void hybrid_quick_insertion_selection(std::vector<T>& arr, int low, int high) {
    if (low >= high)
        return;  // Empty range
    // A single iteration of Quicksort partitioning to divide the array into two
    // halves
    int i = low;
    int f = high - 1;
    T pivot = arr[(i + f) / 2];
    while (i <= f) {
        while (arr[i] < pivot) i++;
        while (arr[f] > pivot) f--;
        if (i <= f) {
            swap(arr, i, f);
            i++;
            f--;
        }
    }

    // Insertion at the left
    if (low < f) {
        for (int k = low + 1; k <= f; k++) {
            T key = arr[k];
            int j = k - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Selection at the right
    if (i < high) {
        for (int k = i; k < high; k++) {
            T minimum = arr[k];
            int min_ind = k;
            int j = k + 1;
            while (j < high) {
                if (arr[j] < minimum) {
                    minimum = arr[j];
                    min_ind = j;
                }
                j++;
            }
            swap(arr, k, min_ind);
        }
    }
}
}  // namespace hybrid_quick_insert_select
}  // namespace sorting

static void test() {
    using sorting::hybrid_quick_insert_select::hybrid_quick_insertion_selection;

    // Test 1: empty
    {
        std::vector<int> arr = {};
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    // Test 2: one element
    {
        std::vector<int> arr = {42};
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    // Test 3: positive numbers
    {
        std::vector<int> arr = {1, 2, 3, 4, 5};
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    // Test 4: positive and negative numbers
    {
        std::vector<int> arr = {-5, 4, -3, 2, 1};
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    // Test 5: repeated elements
    {
        std::vector<int> arr = {3, 1, 2, 3, 2, 1, 4};
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    // Test 6: negative numbers
    {
        std::vector<int> arr = {-10, -7, -8, -9, -1, -5};
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    // Test 7: big array
    {
        std::vector<int> arr(1000);
        for (int i = 0; i < 1000; ++i) {
            arr[i] = 1000 - i;
        }
        hybrid_quick_insertion_selection(arr, 0,
                                         static_cast<int>(arr.size()));
        assert(std::is_sorted(arr.begin(), arr.end()));
    }

    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Main program to demonstrate the hybrid sorting algorithm.
 *
 * Runs the built-in self-tests, then sorts a sample array using the hybrid
 * algorithm that combines QuickSort, Insertion Sort, and Selection Sort.
 *
 * The array is printed before and after sorting to show the result.
 *
 * @return int Program exit code (0 indicates successful execution).
 */
int main() {
    test();  // run self-test implementations

    // An example
    std::vector<int> array = {8, 5, 9, 20, 2, 13, 3, 1};
    print_array(array);
    std::cout << '\n';
    sorting::hybrid_quick_insert_select::hybrid_quick_insertion_selection(array,
                                                                          0,
                                                                          static_cast<int>(array.size()));
    print_array(array);
    std::cout << '\n';
    return 0;
}

