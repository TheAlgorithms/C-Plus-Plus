/**
 * @file
 * @brief Iterative Binary Search implementation
 */

#include <iostream>
#include <vector>

namespace search {

/**
 * @brief Iterative Binary Search
 * @param arr Sorted vector of integers
 * @param target Element to search
 * @return Index of target, -1 if not found
 */
int binary_search_iterative(const std::vector<int> &arr, int target) {
    int low = 0, high = (int)arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

}  // namespace search

// Example usage
int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9};
    int target = 7;

    int result = search::binary_search_iterative(arr, target);

    if (result != -1) {
        std::cout << "Found at index: " << result << '\n';
    } else {
        std::cout << "Not found\n";
    }
}
