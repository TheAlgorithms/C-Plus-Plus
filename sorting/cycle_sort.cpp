/**
 * @file
 * @brief Implementation of [Cycle sort](https://en.wikipedia.org/wiki/Cycle_sort) algorithm
 *
 *@details
 *Cycle Sort is a sorting algorithm that works in \f$O(n^2)\f$ time in best cas and works in \f$O(n^2)\f$ in worst case.
 *If a element is already at its correct  position, do nothing.
 *If a element is not at its correct position, we then need to move it to its correct position by computing the correct positions.Therefore, we should make sure the duplicate elements.
 *
 *@author [TsungHan Ho](https://github.com/dalaoqi)
 */

#include <iostream>
#include <vector>

void swap(int *a, int *b) {
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void cycleSort(std::vector<int> *arr) {
    for (int cycle_start = 0; cycle_start <= (*arr).size() - 1; cycle_start++) {
        // initialize item
        int item = (*arr)[cycle_start];

        // Count the number of elements smaller than item, this  number is the correct index of item.
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < (*arr).size(); i++) {
            if ((*arr)[i] < item) {
                pos++;
            }
        }

        // item is already in correct position
        if (pos == cycle_start) {
            continue;
        }

        // duplicate  elements
        while (item == (*arr)[pos]) pos += 1;
        swap(&item, &(*arr)[pos]);

        // Rest of the  elements
        while (pos != cycle_start) {
            pos = cycle_start;
            // Find position where we put the element
            for (int i = cycle_start + 1; i < (*arr).size(); i++) {
                if ((*arr)[i] < item) {
                    pos += 1;
                }
            }
            // duplicate  elements
            while (item == (*arr)[pos]) pos += 1;
            swap(&item, &(*arr)[pos]);
        }
    }
}

/* Test function */
void test() {
    // [506, 48, 123, 79, 0, 362, 951, 500, 0] return [0, 0, 48, 79, 123, 362, 500, 506, 951]
    std::vector<int> array = {506, 48, 123, 79, 0, 362, 951, 500, 0};
    std::vector<int> *arr = &array;
    cycleSort(arr);
    std::cout << "Sorted : ";
    for (int i : *arr) std::cout << i << " ";
}

/* Main function */
int main() {
    test();  // execute the test
    return 0;
}
