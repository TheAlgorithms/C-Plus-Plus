/**
 * @file tournament_sort.cpp
 * @brief Implementation of [Tournament Sort]
 * (https://en.wikipedia.org/wiki/Tournament_sort)
 *
 * @details
 * Tournament Sort is a sorting algorithm that improves upon naive selection
 * sort by using a min-heap (priority queue) to find the next minimum element.
 *
 * Instead of scanning all n elements each round (O(n)), a heap finds the
 * minimum in O(log n), giving an overall time complexity of O(n log n).
 *
 * The name comes from its resemblance to a single-elimination sports
 * tournament where the "winner" (minimum element) is found each round.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 *
 * @author drori12
 */

#include <algorithm>   /// for std::is_sorted
#include <cassert>     /// for assert
#include <iostream>    /// for std::cout
#include <queue>       /// for std::priority_queue
#include <vector>      /// for std::vector

/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {

/**
 * @brief Tournament sort using a min-heap priority queue.
 * @tparam T type of elements in the array (must support < operator)
 * @param arr input vector to be sorted
 * @return sorted vector in ascending order
 */
template <typename T>
std::vector<T> tournament_sort(std::vector<T> arr) {
    // min-heap: smallest element always on top
    std::priority_queue<T, std::vector<T>, std::greater<T>> min_heap(
        arr.begin(), arr.end());

    std::vector<T> sorted;
    sorted.reserve(arr.size());

    while (!min_heap.empty()) {
        sorted.push_back(min_heap.top());
        min_heap.pop();
    }

    return sorted;
}

}  // namespace sorting

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    // Test 1: regular unsorted array
    std::vector<int> arr1 = {5, 3, 1, 4, 2};
    std::vector<int> sorted1 = sorting::tournament_sort(arr1);
    assert(std::is_sorted(sorted1.begin(), sorted1.end()));

    // Test 2: already sorted
    std::vector<int> arr2 = {1, 2, 3, 4, 5};
    std::vector<int> sorted2 = sorting::tournament_sort(arr2);
    assert(std::is_sorted(sorted2.begin(), sorted2.end()));

    // Test 3: reverse sorted
    std::vector<int> arr3 = {5, 4, 3, 2, 1};
    std::vector<int> sorted3 = sorting::tournament_sort(arr3);
    assert(std::is_sorted(sorted3.begin(), sorted3.end()));

    // Test 4: single element
    std::vector<int> arr4 = {42};
    std::vector<int> sorted4 = sorting::tournament_sort(arr4);
    assert(std::is_sorted(sorted4.begin(), sorted4.end()));

    // Test 5: empty array
    std::vector<int> arr5 = {};
    std::vector<int> sorted5 = sorting::tournament_sort(arr5);
    assert(sorted5.empty());

    // Test 6: duplicates
    std::vector<int> arr6 = {3, 1, 2, 1, 3};
    std::vector<int> sorted6 = sorting::tournament_sort(arr6);
    assert(std::is_sorted(sorted6.begin(), sorted6.end()));

    // Test 7: negative numbers
    std::vector<int> arr7 = {-3, 0, -1, 5, 2};
    std::vector<int> sorted7 = sorting::tournament_sort(arr7);
    assert(std::is_sorted(sorted7.begin(), sorted7.end()));

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on successful exit
 */
int main() {
    tests();
    return 0;
}
