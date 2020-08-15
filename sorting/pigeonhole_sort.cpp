/*
https://en.wikipedia.org/wiki/Pigeonhole_sort
Pigeonhole sorting is a sorting algorithm that is suitable for sorting lists of
elements where the number of elements and the number of possible key values are
approximately the same. It requires O(n + Range) time where n is number of
elements in input array and ‘Range’ is number of possible values in array.
*/
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

template <std::size_t N = 7>
void pigeonSort(std::array<int, N> &array, int *n) {
    /*
    Finding min and max*
    */
    int min = array[0];
    int max = array[0];

    for (int i = 0; i < *n; i++) {
        if (min > array[i]) {
            min = array[i];
        }
        if (max < array[i]) {
            max = array[i];
        }
    }
    /*
    range refers to the number of holes required
    */
    int range = max - min + 1;
    std::vector<int> hole[range];

    /*
    Copying all array values to pigeonhole
    */
    for (int i = 0; i < *n; i++) {
        hole[array[i] - min].push_back(array[i]);
    }

    /*
    Deleting elements from list and
    storing to original array
    */
    int count = 0;
    for (int i = 0; i < range; i++) {
        while (!hole[i].empty()) {
            array[count] = *(hole[i].begin());
            hole[i].erase(hole[i].begin());
            count++;
        }
    }
}

template <std::size_t N = 7>
void test() {
    std::array<int, 7> test_array = {8, 3, 2, 7, 4, 6, 8};
    int *n = nullptr;
    int n1 = sizeof(test_array) / sizeof(test_array[0]);
    n = &n1;

    pigeonSort(test_array, n);
    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));
    std::cout << " Passed\n";

    /*
    Printing sorted array
    */
    for (int i = 0; i < n1; i++) {
        std::cout << test_array[i] << " ";
    }
}

int main() {
    test();

    return 0;
}
