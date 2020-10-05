/**
 * @file
 * @brief Implementation of [Cycle
 *sort](https://en.wikipedia.org/wiki/Cycle_sort) algorithm
 *
 *@details
 *Cycle Sort is a sorting algorithm that works in \f$O(n^2)\f$ time in best case
 *and works in \f$O(n^2)\f$ in worst case.
 *
 *@author [TsungHan Ho](https://github.com/dalaoqi)
 */

#include <iostream>
#include <vector>

void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// Function sort the array using Cycle sort
void cycleSort(std::vector<int> *arr, int n) {
    // count number of memory writes
    int writes = 0;

    // traverse array elements and put it to on
    // the right place
    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        // initialize item as starting point
        int item = (*arr)[cycle_start];

        // Find position where we put the item. We basically
        // count all smaller elements on right side of item.
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if ((*arr)[i] < item)
                pos++;

        // If item is already in correct position
        if (pos == cycle_start)
            continue;

        // ignore all duplicate  elements
        while (item == (*arr)[pos]) pos += 1;

        // put the item to it's right position
        if (pos != cycle_start) {
            swap(&item, &(*arr)[pos]);
            writes++;
        }

        // Rotate rest of the cycle
        while (pos != cycle_start) {
            pos = cycle_start;

            // Find position where we put the element
            for (int i = cycle_start + 1; i < n; i++)
                if ((*arr)[i] < item)
                    pos += 1;

            // ignore all duplicate  elements
            while (item == (*arr)[pos]) pos += 1;

            // put the item to it's right position
            if (item != (*arr)[pos]) {
                swap(&item, &(*arr)[pos]);
                writes++;
            }
        }
    }
}

/* Test function */
void test() {
    // [1, 8, 3, 9, 10, 10, 2, 4] return [1, 2, 3, 4, 8, 9, 10, 10]
    std::vector<int> array = {1, 8, 3, 9, 10, 10, 2, 4};
    std::vector<int> *arr = &array;
    int n = array.size();
    cycleSort(arr, n);
    std::cout << "After sort : " << std::endl;
    for (int i = 0; i < n; i++) std::cout << (*arr)[i] << " ";
}

/* Main function */
int main() {
    test();  // execute the test
    return 0;
}
