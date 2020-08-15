/*
https://en.wikipedia.org/wiki/Pigeonhole_sort
Pigeonhole sorting is a sorting algorithm that is suitable for sorting lists of
elements where the number of elements and the number of possible key values are
approximately the same. It requires O(n + Range) time where n is number of
elements in input array and ‘Range’ is number of possible values in array.
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>

void pigeonSort(int array[], int n) {
    /*
Finding min and max*
*/
    int min = array[0];
    int max = array[0];

    for (int i = 0; i < n; i++) {
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
    std::list<int> hole[range];

    /*
    Copying all array values to pigeonhole
    */
    for (int i = 0; i < n; i++) {
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

void test() {
    int test_array[] = {8, 3, 2, 7, 4, 6, 8};
    int n = sizeof(test_array) / sizeof(test_array[0]);

    pigeonSort(test_array, 7);
    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));
    std::cout << " Passed\n";

    /*
    Printing sorted array
    */
    for (int i = 0; i < 7; i++) {
        std::cout << test_array[i] << " ";
    }
}

int main() {
    test();

    return 0;
}
