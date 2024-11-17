/**
 * @file
 * @brief [Quick select implementation](https://en.wikipedia.org/wiki/Median_of_medians)
 * in C++
 *
 * @author [David Leal](https://github.com/Panquesito7)
 * @author [popoapp](https://github.com/popoapp)
 * @author (https://github.com/graph-theorist)
 */

#include <algorithm>  /// for std::sort, std::min, std::swap
#include <cassert>    /// for std::assert
#include <cstdint>
#include <ctime>      /// for std::time
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @brief Sorting algorithms
 * @namespace sorting
 */
namespace sorting {
/**
 * @namespace quick_sort
 * @brief Functions for the [Quick select
 * implementation](https://en.wikipedia.org/wiki/Median_of_medians) in C++
 */
namespace quick_select {
// pivot and select call each other, so forward declare select
template <typename T> int select(std::vector<T> *arr, int low, int high, const int &k);

/** Insertion Sort Function
 *
 * @tparam T type of array
 * @param low first point of the array (starting index)
 * @param high last point of the array (ending index)
 * @param [in,out] arr pointer to array to be sorted
 */
template <typename T>
void insertionSort(std::vector<T> *arr, const int &low, const int &high) {
    /* std::cout << "arr size: " << arr[0].size() << std::endl;
    std::cout << "low: " << low << std::endl; */
    for (size_t i = low + 1; i < high; i++) {
        // std::cout << arr[0][i] << std::endl;
        T temp = arr[0][i];
        int32_t j = i - 1;
        while (j >= 0 && temp < arr[0][j]) {
            arr[0][j + 1] = arr[0][j];
            j--;
        }
        arr[0][j + 1] = temp;
    }
}

/**
 * @brief Partitions the array based on the value at pivotIndex
 * @details
 * This function takes last element as pivot, places
 * the pivot element at its correct position in array,
 * and places all smaller (smaller than pivot) to left
 * of pivot and all greater elements to right of pivot
 * @tparam T array type
 * @param arr the array with contents given by the user
 * @param low first point of the array (starting index)
 * @param high last point of the array (ending index)
 * @param pivotIndex index of value of pivot
 * @returns index of the smaller element
 */
template <typename T>
int partition(std::vector<T> *arr, const int &low, const int &high, const int &pivotIndex) {
    T pivot = (*arr)[pivotIndex];
    int i = (low - 1);       // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or
        // equal to pivot
        if ((*arr)[j] <= pivot) {
            i++;  // increment index of smaller element
            std::swap((*arr)[i], (*arr)[j]);
        }
    }

    std::swap((*arr)[i + 1], (*arr)[high]);
    return (i + 1);
}

/**
 * @brief Sort and return the index of the median out of 1 to 5 elements
 * @details
 * Uses insertion sort
 * @tparam T array type
 * @param arr the array with contents given by the user
 * @param low first point of the array (starting index)
 * @param high last point of the array (ending index)
 * @returns index of the median
 */
template <typename T>
int partition5(std::vector<T> *arr, const int &low, const int &high) {
    insertionSort(arr, low, high);
    return low + (high - low) / 2;
}

/**
 * @brief the main function that implements Quick Sort.
 *
 * Void function used in T (array type) function, which then
 * can be used as self-tests or other functionalities.
 * @tparam T array type
 * @param arr array to be sorted
 * @param low starting index
 * @param high ending index
 */
template <typename T>
void quick_sort(std::vector<T> *arr, const int &low, const int &high) {
    if (low < high) {
        int p = partition(arr, low, high, high);

        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

/**
 * @brief the main function that implements Quick Sort.
 *
 * T (array type) function which calls the void function. Can
 * be used for self-tests and other functionalities.
 * @tparam T array type
 * @param arr array to be sorted
 * @param low starting index
 * @param high ending index
 */
template <typename T>
std::vector<T> quick_sort(std::vector<T> arr, const int &low, const int &high) {
    if (low < high) {
        int p = partition(&arr, low, high, high);

        quick_sort(&arr, low, p - 1);
        quick_sort(&arr, p + 1, high);
    }
    return arr;
}

/**
 * @brief finds the median of medians
 *
 * T (array type) Can be used for self-tests and other functionalities.
 * @tparam T array type
 * @param arr array of elements
 * @param low starting index
 * @param high ending index
 */
template <typename T>
int pivot(std::vector<T> *arr, const int &low, const int &high) {
    if (high - low < 5) {
        return partition5(arr, low, high);
    }

    for (int i = low; i <= high; i += 5) {
        // std::cout << "i: " << i << std::endl;
        int subHigh = std::min(i + 4, high);
        int median5 = partition5(arr, i, subHigh);
        // std::cout << "median5: " << median5 << std::endl;
        std::swap(arr[0][median5], arr[0][low + (i - low) / 5]);
    }

    int mid = (high - low) / 10 + low + 1;
    return select(arr, low, low + (high - low) / 5, mid);
}

/**
 * @brief finds the index of the kth-smallest element
 *
 * T (array type) Can be used for self-tests and other functionalities.
 * @tparam T array type
 * @param arr array of elements
 * @param low starting index
 * @param high ending index
 * @param k desired order statistic (zero-based)
 */
template <typename T>
int select(std::vector<T> *arr, int low, int high, const int &k) {
    while (true) {
        if (low == high) {
            return low;
        }

        int pivotIndex = pivot(arr, low, high);
        std::cout << "pivotIndex: " << pivotIndex << std::endl;
        pivotIndex = partition(arr, low, high, pivotIndex);

        if (k == pivotIndex) {
            return k;
        }

        if (k < pivotIndex) {
            high = pivotIndex - 1;
        } else {
            low = pivotIndex + 1;
        }
    }
}

/**
 * @brief the main function that implements Quick Select.
 *
 * T (array type) Can be used for self-tests and other functionalities.
 * @tparam T array type
 * @param arr array to be sorted
 * @param k desired order statistic
 */
template <typename T>
T quick_select(std::vector<T> *arr, const int &k) {
    int index = select(arr, 0, arr->size() - 1, k);
    return (*arr)[index];
}

/**
 * @brief Utility function to print the array contents
 * @param arr the array to be printed
 * @param size size of the given array
 * @returns void
 */
template <typename T>
void show(const std::vector<T> &arr, const int &size) {
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << "\n";
}

}  // namespace quick_sort
}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    int k = 5;

    // 1st test (normal numbers)
    std::vector<uint64_t> arr = {5, 3, 8, 12, 14, 16, 28, 96, 2, 5977};
    int kthSmallest = sorting::quick_select::quick_select(
        &arr, k);
    /* std::cout << "kthSmallest: " << kthSmallest << std::endl;
    std::vector<uint64_t> arr_sorted = sorting::quick_select::quick_sort(
        arr, 0, int(std::end(arr) - std::begin(arr)) - 1); */

    std::sort(arr.begin(), arr.end());
    assert(kthSmallest == arr[k - 1]);
    std::cout << "\n1st test: passed!\n";

    // 2nd test (normal and negative numbers)
    std::vector<int64_t> arr2 = {9,    15,   28,   96,  500, -4, -58,
                                 -977, -238, -800, -21, -53, -55};
    std::vector<int64_t> arr_sorted2 = sorting::quick_select::quick_sort(
        arr2, 0, std::end(arr2) - std::begin(arr2));

    assert(std::is_sorted(std::begin(arr_sorted2), std::end(arr_sorted2)));
    std::cout << "2nd test: passed!\n";

    // 3rd test (decimal and normal numbers)
    std::vector<double> arr3 = {29,  36,   1100, 0,      77,     1,
                                6.7, 8.97, 1.74, 950.10, -329.65};
    std::vector<double> arr_sorted3 = sorting::quick_select::quick_sort(
        arr3, 0, int(std::end(arr3) - std::begin(arr3)) - 1);

    assert(std::is_sorted(std::begin(arr_sorted3), std::end(arr_sorted3)));
    std::cout << "3rd test: passed!\n";

    // 4th test (random decimal and negative numbers)
    size_t size = std::rand() % 750 + 100;

    std::vector<float> arr4(size);
    for (uint64_t i = 0; i < size; i++) {
        arr4[i] = static_cast<float>(std::rand()) /
                      static_cast<float>(RAND_MAX / 999.99 - 0.99) -
                  250;
    }

    std::vector<float> arr4_sorted = sorting::quick_select::quick_sort(
        arr4, 0, int(std::end(arr4) - std::begin(arr4)) - 1);
    assert(std::is_sorted(std::begin(arr4_sorted), std::end(arr4_sorted)));

    std::cout << "4th test: passed!\n";

    // Printing all sorted arrays
    std::cout << "\n\tPrinting all sorted arrays:\t\n";

    /* std::cout << "1st array:\n";
    sorting::quick_select::show(arr_sorted, std::end(arr) - std::begin(arr));
    std::cout << std::endl; */
    std::cout << "2nd array:\n";
    sorting::quick_select::show(arr_sorted2, std::end(arr2) - std::begin(arr2));
    std::cout << std::endl;
    std::cout << "3rd array:\n";
    sorting::quick_select::show(arr_sorted3,
                              int(std::end(arr3) - std::begin(arr3)) - 1);
    std::cout << std::endl;
    std::cout << "Start: 4th array:\n\n";
    sorting::quick_select::show(
        arr4_sorted, int(std::end(arr4_sorted) - std::begin(arr4_sorted)) - 1);
    std::cout << "\nEnd: 4th array.\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int choice = 0;

    std::cout << "\tAvailable modes\t\n\n";
    std::cout << "1. Self-tests mode\n2. Interactive mode";

    std::cout << "\nChoose a mode: ";
    std::cin >> choice;
    std::cout << "\n";

    while ((choice != 1) && (choice != 2)) {
        std::cout << "Invalid option. Choose between the valid modes: ";
        std::cin >> choice;
    }

    if (choice == 1) {
        std::srand(std::time(nullptr));
        tests();  // run self-test implementations
    } else if (choice == 2) {
        int size = 0;
        std::cout << "\nEnter the number of elements: ";

        std::cin >> size;
        std::vector<float> arr(size);

        std::cout
            << "\nEnter the unsorted elements (can be negative/decimal): ";

        for (int i = 0; i < size; ++i) {
            std::cout << "\n";
            std::cin >> arr[i];
        }
        sorting::quick_select::quick_sort(&arr, 0, size - 1);
        std::cout << "\nSorted array: \n";
        sorting::quick_select::show(arr, size);
    }
    return 0;
}
