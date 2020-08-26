/**
 * @file
 * @brief Implementation of [Pigeonhole Sort algorithm]
 * (https://en.wikipedia.org/wiki/Pigeonhole_sort)
 * @author [Lownish](https://github.com/Lownish)
 * @details
 * Pigeonhole sorting is a sorting algorithm that is suitable for sorting lists
 * of elements where the number of elements and the number of possible key
 * values are approximately the same. It requires O(n + Range) time where n is
 * number of elements in input array and ‘Range’ is number of possible values in
 * array.
 *
 * The time Complexity of the algorithm is \f$O(n+N)\f$.
 */

#include <algorithm>  //for std::is_sorted
#include <array>      //for std::array
#include <cassert>    //for assert
#include <iostream>   //for io operations

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {

/**
 * Pigeonhole sorting of array of size n
 * The function will sort the array through Pigeonhole algorithm and print
 * @param arr unsorted array of elements
 * @returns sorted array of elements
 */
template <std::size_t N>
std::array<int, N> pigeonSort(std::array<int, N> arr) {
    // Finding min and max*
    auto min = std::min_element(std::begin(arr), std::end(arr));
    auto max = std::max_element(std::begin(arr), std::end(arr));

    // Range refers to the number of holes required
    int range = *max - *min + 1;
    int *hole = new int[range]();

    // Copying all array values to pigeonhole
    for (int i = 0; i < N; i++) {
        hole[arr[i] - *min] = arr[i];
    }

    // Deleting elements from list and storing to original array
    int count = 0;
    for (int i = 0; i < range; i++) {
        while (hole[i] != '\0') {
            arr[count] = hole[i];
            hole[i] = {};
            count++;
        }
    }
    delete[] hole;

    return arr;
}
}  // namespace sorting

/**
 * Test function 1 with unsorted array
 * {8, 3, 2, 7, 4, 6, 8}
 * @returns none
 */
static void test_1() {
    const int n = 7;
    std::array<int, n> test_array = {8, 3, 2, 7, 4, 6, 8};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));

    // Printing sorted array
    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}

/**
 * Test function 2 with unsorted array
 * {802, 630, 20, 745, 52, 300, 612, 932, 78, 187}
 * @returns none
 */
static void test_2() {
    const int n = 10;
    std::array<int, n> test_array = {802, 630, 20,  745, 52,
                                     300, 612, 932, 78,  187};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));

    // Printing sorted array
    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}

/**
 * Test function 1 with unsorted array
 * {11,13,12,14}
 * @returns none
 */
static void test_3() {
    const int n = 4;
    std::array<int, n> test_array = {11, 13, 12, 14};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));

    // Printing sorted array
    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}

/**
 * Main function
 */
int main() {
    test_1();
    test_2();
    test_3();

    return 0;
}
