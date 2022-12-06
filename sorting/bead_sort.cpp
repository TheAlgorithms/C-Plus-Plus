// C++ program to implement gravity/bead sort
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#define BEAD(i, j) beads[i * max + j]

namespace sorting {
    template <typename T>
    void beadSort(T *arr, int len) {
        // Find the maximum element
        int max = arr[0];
        for (int i = 1; i < len; i++)
            if (arr[i] > max)
                max = arr[i];

        // allocating memory
        unsigned char *beads = new unsigned char[max * len];
        memset(beads, 0, static_cast<size_t>(max) * len);

        // mark the beads
        for (int i = 0; i < len; i++)
            for (int j = 0; j < arr[i]; j++) BEAD(i, j) = 1;

        for (int j = 0; j < max; j++) {
            // count how many beads are on each post
            int sum = 0;
            for (int i = 0; i < len; i++) {
                sum += BEAD(i, j);
                BEAD(i, j) = 0;
            }

            // Move beads down
            for (int i = len - sum; i < len; i++) BEAD(i, j) = 1;
        }

        // Put sorted values in array using beads
        for (int i = 0; i < len; i++) {
            int j;
            for (j = 0; j < max && BEAD(i, j); j++) {
            }

            arr[i] = j;
        }
        delete[] beads;
    }
    
    template <typename T>
    void beadSort(std::vector<T> *arr) {
        size_t len = arr->size();
        // Find the maximum element
        int max = arr[0][0];
        for (int i = 1; i < len; i++)
            if (arr[0][i] > max)
                max = arr[0][i];

        // allocating memory
        unsigned char *beads = new unsigned char[max * len];
        memset(beads, 0, static_cast<size_t>(max) * len);

        // mark the beads
        for (int i = 0; i < len; i++)
            for (int j = 0; j < arr[0][i]; j++) BEAD(i, j) = 1;

        for (int j = 0; j < max; j++) {
            // count how many beads are on each post
            int sum = 0;
            for (int i = 0; i < len; i++) {
                sum += BEAD(i, j);
                BEAD(i, j) = 0;
            }

            // Move beads down
            for (int i = len - sum; i < len; i++) BEAD(i, j) = 1;
        }

        // Put sorted values in array using beads
        for (int i = 0; i < len; i++) {
            int j;
            for (j = 0; j < max && BEAD(i, j); j++) {
            }

            arr[0][i] = j;
        }
        delete[] beads;
    }
    

}

void tests() {
    // using array
    int arr1[10] = {10, 99, 56, 8, 128, 1, 76, 48, 300, 4};
    std::cout << "Test 1... ";
    sorting::beadSort(arr1, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "passed" << '\n';

    // using vector
    std::vector<float> arr2({8, 56, 23, 7, 120, 55, 161, 17});
    std::cout << "Test 2... ";
    sorting::beadSort(&arr2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "passed" << std::endl;
}

int main() {
    // Running tests to test algorithm
    tests();

    // For user interaction
    size_t n;
    std::cout << "Enter the length of array (0 to exit)";
    std::cin >> n;

    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter Positive Integer" << n << "Numbers for Unsorted Array : ";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    sorting::beadSort(arr, n);

    std::cout << "\nSorted Array : ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    delete[] arr;
    return 0;
}