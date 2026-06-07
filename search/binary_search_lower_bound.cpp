/**
 * @file
 * @brief Implementation of lower bound binary search algorithm.
 * @details
 * The lower bound algorithm finds the index of the first element in a sorted
 * array that is greater than or equal to a target value.
 * Time Complexity: O(log N)
 * Space Complexity: O(1)
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Finds the lower bound of a target in a sorted vector.
 * @param arr The sorted vector.
 * @param target The value to find the lower bound for.
 * @return The index of the lower bound, or the size of the array if all
 * elements are smaller.
 */
int binary_search_lower_bound(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

/**
 * @brief Test function to verify the algorithm
 */
void test() {
    std::vector<int> nums = {1, 3, 5, 5, 5, 7, 9, 11};

    // Test 1: Target exists (should find the first occurrence)
    assert(binary_search_lower_bound(nums, 5) == 2);

    // Test 2: Target does not exist, falls between elements
    assert(binary_search_lower_bound(nums, 6) == 5);

    // Test 3: Target is smaller than all elements
    assert(binary_search_lower_bound(nums, 0) == 0);

    // Test 4: Target is greater than all elements
    assert(binary_search_lower_bound(nums, 15) == 8);

    std::cout << "All lower bound tests passed successfully!" << std::endl;
}

int main() {
    test();
    return 0;
}