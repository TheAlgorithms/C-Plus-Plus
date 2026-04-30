/**
 * @file recursive_binary_search.cpp
 * @brief Recursive Binary Search implementation
 */

#include <cassert>
#include <iostream>
#include <vector>

namespace search {

namespace recursive_binary_search {

int binarySearch(const std::vector<int>& arr,
                 int left,
                 int right,
                 int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    }

    if (arr[mid] > target) {
        return binarySearch(arr, left, mid - 1, target);
    }

    return binarySearch(arr, mid + 1, right, target);
}

}  // namespace recursive_binary_search

}  // namespace search

static void test() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7};

    int result = search::recursive_binary_search::binarySearch(
        arr, 0, arr.size() - 1, 5);

    assert(result == 4);

    std::cout << "Test passed!\n";
}

int main() {
    test();
    return 0;
}