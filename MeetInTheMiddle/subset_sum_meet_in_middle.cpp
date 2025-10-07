/**
 * @file subset_sum_meet_in_middle.cpp
 * @brief Count subsets with sum <= target using the Meet in the Middle
 * technique.
 * @details
 * The Meet in the Middle algorithm splits the array into two halves,
 * generates all subset sums for each half, then efficiently counts
 * valid combinations using binary search.
 * @see https://cp-algorithms.com/combinatorics/meet_in_the_middle.html
 * @author [Your Name](https://github.com/your-github-handle)
 */

#include <algorithm>  ///< for std::sort, std::upper_bound
#include <cassert>    ///< for assert()
#include <iostream>   ///< for std::cout
#include <vector>     ///< for std::vector

/**
 * @brief Generates all subset sums for the range arr[start..end]
 * @param arr Input array
 * @param sums Vector to store generated sums
 * @param start Start index
 * @param end End index
 * @param curr Current sum (default 0)
 */
void generateSubsetSums(const std::vector<int>& arr,
                        std::vector<long long>& sums, int start, int end,
                        long long curr = 0) {
    if (start > end) {
        sums.push_back(curr);
        return;
    }
    generateSubsetSums(arr, sums, start + 1, end,
                       curr);  // Exclude current element
    generateSubsetSums(arr, sums, start + 1, end,
                       curr + arr[start]);  // Include current element
}

/**
 * @brief Counts subsets with sum <= target using Meet in the Middle
 * @param arr Input array
 * @param target Maximum allowed sum
 * @return Number of subsets with sum <= target
 */
long long countSubsetsMeetInMiddle(const std::vector<int>& arr, int target) {
    int n = arr.size();
    std::vector<long long> left, right;

    // Generate subset sums for left and right halves
    generateSubsetSums(arr, left, 0, n / 2 - 1);
    generateSubsetSums(arr, right, n / 2, n - 1);

    std::sort(right.begin(), right.end());

    long long count = 0;
    for (auto s : left) {
        // Count combinations with sum <= target using binary search
        count += std::upper_bound(right.begin(), right.end(), target - s) -
                 right.begin();
    }

    return count;
}

/**
 * @brief Self-test to verify the implementation
 */
static void tests() {
    // Test case 1
    std::vector<int> arr1 = {3, 5, 7, 9};
    assert(countSubsetsMeetInMiddle(arr1, 12) == 9);

    // Test case 2
    std::vector<int> arr2 = {1, 2, 3};
    assert(countSubsetsMeetInMiddle(arr2, 3) == 5);

    // Test case 3
    std::vector<int> arr3 = {4, 5, 6, 7};
    assert(countSubsetsMeetInMiddle(arr3, 10) == 7);

    std::cout << "All self-tests passed successfully!\n";
}

/**
 * @brief Main function
 */
int main() {
    tests();
    return 0;
}
