/**
 * @file
 * @brief Implementation of [Pigeonhole Sort algorithm]
 *(https://en.wikipedia.org/wiki/Pigeonhole_sort)
 * @author [Lownish](https://github.com/Lownish)
 * @details
 *Pigeonhole sorting is a sorting algorithm that is suitable for sorting lists
 *of elements where the number of elements and the number of possible key values
 *are approximately the same. It requires O(n + Range) time where n is number of
 *elements in input array and ‘Range’ is number of possible values in array.
 *
 * The time Complexity of the algorithm is \f$O(n+N)\f$.
 */

#include <algorithm>  //for std::is_sorted
#include <array>      //for std::array
#include <cassert>    //for std::array
#include <iostream>   //for io operations

/**
 *Pigeonhole sorting of array with array size n
 */
template <std::size_t N>
void pigeonSort(std::array<int, N> arr, int n) {
    // Finding min and max*
    int min = arr.at(0);
    int max = arr.at(0);

    for (int i = 0; i < n; i++) {
        if (min > arr[i]) {
            min = arr[i];
        }
        if (max < arr[i]) {
            max = arr[i];
        }
    }

    // Range refers to the number of holes required
    int range = max - min + 1;
    int* hole = new int[range]();

    // Copying all array values to pigeonhole
    for (int i = 0; i < n; i++) {
        hole[arr[i] - min] = arr[i];
    }

    /**
     *Deleting elements from list and
     *storing to original array
     */
    int count = 0;
    for (int i = 0; i < range; i++) {
        while (hole[i] != '\0') {
            arr[count] = hole[i];
            hole[i] = {};
            count++;
        }
    }
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
    std::cout << "Passed\n";

    // Printing sorted array
    for (int i = 0; i < n; i++) {
        std::cout << arr.at(i) << " ";
    }
}

/**
 *Test function 1 with unsorted array
 *{8, 3, 2, 7, 4, 6, 8}
 */
static void test_1() {
    std::array<int, 7> test_array = {8, 3, 2, 7, 4, 6, 8};

    int n = sizeof(test_array) / sizeof(test_array[0]);

    pigeonSort(test_array, n);
}

/**
 *Test function 2 with unsorted array
 *{802, 630, 20, 745, 52, 300, 612, 932, 78, 187}
 */
static void test_2() {
    std::array<int, 10> test_array = {802, 630, 20,  745, 52,
                                      300, 612, 932, 78,  187};

    int n = sizeof(test_array) / sizeof(test_array[0]);

    pigeonSort(test_array, n);
}

/**
 * Main Function
 */
int main() {
    test_1();
    test_2();

    return 0;
}
