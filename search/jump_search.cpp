/**
 * \file
 * \brief [Jump Search Algorithm](https://en.wikipedia.org/wiki/Jump_search)
 *
 * \details
 * Jump Search is a searching algorithm for sorted arrays. It works by
 * jumping ahead by fixed steps of size sqrt(n), then doing a linear
 * scan backward once the target range is identified.
 *
 * Time Complexity:  O(sqrt(n))
 * Space Complexity: O(1)
 *
 * @author [SaiEashwarKS](https://github.com/SaiEashwarKS)
 * @author [Your Name](https://github.com/YOUR_USERNAME)
 */

#include <algorithm>  /// for std::min
#include <cassert>    /// for assert
#include <cmath>      /// for std::sqrt
#include <iostream>   /// for std::cout
#include <vector>     /// for std::vector

/**
 * \brief Jump Search implementation
 * \param arr sorted input array
 * \param x element to search for
 * \returns index of x in arr
 * \returns -1 if x is not found
 */
int jumpSearch(const std::vector<int>& arr, int x) {
    int n = static_cast<int>(arr.size());
    if (n == 0) return -1;

    int step = static_cast<int>(std::sqrt(n));  // compute once
    int prev = 0;

    while (arr[std::min(step, n) - 1] < x) {
        prev = step;
        step += static_cast<int>(std::sqrt(n));
        if (prev >= n)
            return -1;
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == std::min(step, n))
            return -1;
    }

    return (arr[prev] == x) ? prev : -1;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::vector<int> arr = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};

    assert(jumpSearch(arr, 55)  == 10);  // element in middle
    assert(jumpSearch(arr, 0)   == 0);   // first element
    assert(jumpSearch(arr, 610) == 15);  // last element
    assert(jumpSearch(arr, 100) == -1);  // not present
    assert(jumpSearch(arr, -1)  == -1);  // below range

    std::vector<int> single = {42};
    assert(jumpSearch(single, 42) == 0);   // single element found
    assert(jumpSearch(single, 10) == -1);  // single element not found

    std::vector<int> empty = {};
    assert(jumpSearch(empty, 1) == -1);    // empty array

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}