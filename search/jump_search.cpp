/**
 * \file
 * \brief C++ program to implement [Jump
 * Search](https://en.wikipedia.org/wiki/Jump_search)
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

/** jump search implementation
 */
int jumpSearch(int arr[], int x, int n) {
    if (n <= 0) {
        return -1;
    }

    // Finding block size to be jumped
    int step = std::sqrt(n);

    // Finding the block where element is
    // present (if it is present)
    int prev = 0;
    while (arr[std::min(step, n) - 1] < x) {
        prev = step;
        step += std::sqrt(n);
        if (prev >= n)
            return -1;
    }

    // Doing a linear search for x in block
    // beginning with prev.
    while (arr[prev] < x) {
        prev++;

        // If we reached next block or end of
        // array, element is not present.
        if (prev == std::min(step, n))
            return -1;
    }
    // If element is found
    if (arr[prev] == x)
        return prev;

    return -1;
}

/**
 * @brief Check empty input and small search boundaries.
 * @returns void
 */
static void tests() {
    assert(jumpSearch(nullptr, 7, 0) == -1);
    int backing[] = {99, 7};
    assert(jumpSearch(backing + 1, 7, 0) == -1);
    int singleton[] = {7};
    assert(jumpSearch(singleton, 7, 1) == 0);
    assert(jumpSearch(singleton, 8, 1) == -1);
    int values[] = {1, 3, 3, 7};
    assert(jumpSearch(values, 3, 4) == 1);
    assert(jumpSearch(values, 7, 4) == 3);
    assert(jumpSearch(values, 8, 4) == -1);
}

// Driver program to test function
int main() {
    tests();
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);

    // Find the index of 'x' using Jump Search
    int index = jumpSearch(arr, x, n);

    // Print the index where 'x' is located
    std::cout << "\nNumber " << x << " is at index " << index;
    return 0;
}
