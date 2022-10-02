/**
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
#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>

namespace {
/**
 * Operator to print the array.
 * @param out std::ostream object to write to
 * @param arr array to write
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        out << arr[i];
        if (i < arr.size() - 1) {
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
namespace {  // using un-named namespace here to prevent partition function
             // being visible to end-users
/** This function partitions `arr[]` in three parts
 * 1. \f$arr[l\ldots i]\f$ contains all elements smaller than pivot
 * 2. \f$arr[(i+1)\ldots (j-1)]\f$ contains all occurrences of pivot
 * 3. \f$arr[j\ldots r]\f$ contains all elements greater than pivot
 * @tparam T type of data in the vector array
 * @param [in,out] arr vector array being partitioned
 * @param [in] low lower limit of window to partition
 * @param [in] high upper limit of window to partition
 * @param [out] i updated lower limit of partition
 * @param [out] j updated upper limit of partition
 */
template <typename T>
void partition3(std::vector<T> *arr, int32_t low, int32_t high, int32_t *i,
                int32_t *j) {
    // To handle 2 elements
    if (high - low <= 1) {
        if ((*arr)[high] < (*arr)[low]) {
            std::swap((*arr)[high], (*arr)[low]);
        }
        *i = low;
        *j = high;
        return;
    }

    int32_t mid = low;
    T pivot = (*arr)[high];
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
}  // namespace

/** 3-way partition based quick sort. This function accepts array pointer and
 * modified the input array.
 * @tparam T type of data in the vector array
 * @param [in,out] arr vector array to sort
 * @param [in] low lower limit of window to partition
 * @param [in] high upper limit of window to partition
 */
template <typename T>
void quicksort(std::vector<T> *arr, int32_t low, int32_t high) {
    if (low >= high) {  // 1 or 0 elements
        return;
    }

    int32_t i = 0, j = 0;

    // i and j are passed as reference
    partition3(arr, low, high, &i, &j);

    // Recur two halves
    quicksort(arr, low, i);
    quicksort(arr, j, high);
}

/** 3-way partition based quick sort. This function accepts array by value and
 * creates a copy of it. The array copy gets sorted and returned by the
 * function.
 * @tparam T type of data in the vector array
 * @param [in] arr vector array to sort
 * @param [in] low lower limit of window to partition
 * @param [in] high upper limit of window to partition
 * @returns sorted array vector
 */
template <typename T>
std::vector<T> quicksort(std::vector<T> arr, int32_t low, int32_t high) {
    if (low >= high) {  // 1 or 0 elements
        return arr;
    }

    int32_t i = 0, j = 0;

    // i and j are passed as reference
    partition3(&arr, low, high, &i, &j);

    // Recur two halves
    quicksort(&arr, low, i);
    quicksort(&arr, j, high);

    return arr;
}
}  // namespace sorting

/** Test function for integer type arrays */
static void test_int() {
    std::cout << "\nTesting integer type arrays\n";

    for (int num_tests = 1; num_tests < 21; num_tests++) {
        size_t size = std::rand() % 500;
        std::vector<int> arr(size);
        for (auto &a : arr) {
            a = std::rand() % 500 - 250;  // random numbers between -250, 249
        }

        std::cout << "Test " << num_tests << "\t Array size:" << size << "\t ";
        std::vector<int> sorted = sorting::quicksort(arr, 0, int32_t(size) - 1);
        if (size < 20) {
            std::cout << "\t Sorted Array is:\n\t";
            std::cout << sorted << "\n";
        }
        assert(std::is_sorted(std::begin(sorted), std::end(sorted)));
        std::cout << "\t Passed\n";
    }
}

/** Test function for double type arrays */
static void test_double() {
    std::cout << "\nTesting Double type arrays\n";
    for (int num_tests = 1; num_tests < 21; num_tests++) {
        size_t size = std::rand() % 500;
        std::vector<double> arr(size);
        for (auto &a : arr) {
            a = double(std::rand() % 500) -
                250.f;   // random numbers between -250, 249
            a /= 100.f;  // convert to -2.5 to 2.49
        }

        std::cout << "Test " << num_tests << "\t Array size:" << size << "\t ";
        std::vector<double> sorted =
            sorting::quicksort(arr, 0, int32_t(size) - 1);
        if (size < 20) {
            std::cout << "\t Sorted Array is:\n\t";
            std::cout << sorted << "\n";
        }
        assert(std::is_sorted(std::begin(sorted), std::end(sorted)));
        std::cout << "\t Passed\n";
    }
}

/** Driver program for above functions */
int main() {
    std::srand(std::time(nullptr));
    test_int();
    test_double();
    return 0;
}
