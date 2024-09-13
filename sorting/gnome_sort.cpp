/**
 * @file
 * @brief Implementation of [gnome
 * sort](https://en.wikipedia.org/wiki/Gnome_sort) algorithm.
 * @author [beqakd](https://github.com/beqakd)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @details
 * Gnome sort algorithm is not the best one but it is widely used.
 * The algorithm iteratively checks the order of pairs in the array. If they are
 * on right order it moves to the next successive pair, otherwise it swaps
 * elements. This operation is repeated until no more swaps are made thus
 * indicating the values to be in ascending order.
 *
 * The time Complexity of the algorithm is \f$O(n^2)\f$ and in some cases it
 * can be \f$O(n)\f$.
 */

#include <algorithm>  // for std::swap
#include <array>      // for std::array
#include <cassert>    // for assertions
#include <iostream>   // for io operations

/**
 * @namespace sorting
 * Sorting algorithms
 */
namespace sorting {
/**
 * This implementation is for a C-style array input that gets modified in place.
 * @param [in,out] arr our array of elements.
 * @param size size of given array
 */
template <typename T>
void gnomeSort(T *arr, int size) {
    // few easy cases
    if (size <= 1) {
        return;
    }

    int index = 0;  // initialize some variables.
    while (index < size) {
        // check for swap
        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;
        } else {
            std::swap(arr[index], arr[index - 1]);  // swap
            index--;
        }
    }
}

/**
 * This implementation is for a C++-style array input. The function argument is
 * a pass-by-value and hence a copy of the array gets created which is then
 * modified by the function and returned.
 * @tparam T type of data variables in the array
 * @tparam size size of the array
 * @param [in] arr our array of elements.
 * @return array with elements sorted
 */
template <typename T, size_t size>
std::array<T, size> gnomeSort(std::array<T, size> arr) {
    // few easy cases
    if (size <= 1) {
        return arr;
    }

    int index = 0;  // initialize loop index
    while (index < size) {
        // check for swap
        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;
        } else {
            std::swap(arr[index], arr[index - 1]);  // swap
            index--;
        }
    }
    return arr;
}
}  // namespace sorting

/**
 * Test function
 */
static void test() {
    // Example 1. Creating array of int,
    std::cout << "Test 1 - as a C-array...";
    const int size = 6;
    std::array<int, size> arr = {-22, 100, 150, 35, -10, 99};
    sorting::gnomeSort(arr.data(),
                       size);  // pass array data as a C-style array pointer
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;

    // Example 2. Creating array of doubles.
    std::cout << "\nTest 2 - as a std::array...";
    std::array<double, size> double_arr = {-100.2, 10.2, 20.0, 9.0, 7.5, 7.2};
    std::array<double, size> sorted_arr = sorting::gnomeSort(double_arr);
    assert(std::is_sorted(std::begin(sorted_arr), std::end(sorted_arr)));
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";
    }
    std::cout << std::endl;

    // Example 3. Creating random array of float.
    std::cout << "\nTest 3 - 200 random numbers as a std::array...";
    const int size2 = 200;
    std::array<float, size2> rand_arr{};

    for (auto &a : rand_arr) {
        // generate random numbers between -5.0 and 4.99
        a = float(std::rand() % 1000 - 500) / 100.f;
    }

    std::array<float, size2> float_arr = sorting::gnomeSort(rand_arr);
    assert(std::is_sorted(std::begin(float_arr), std::end(float_arr)));
    std::cout << " Passed\n";
    // for (int i = 0; i < size; i++) std::cout << double_arr[i] << ", ";
    std::cout << std::endl;
}

/**
 * Our main function with example of sort method.
 */
int main() {
    test();
    return 0;
}
