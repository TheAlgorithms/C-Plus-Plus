/**
 * @file
 * @brief Implements [Sub-set sum problem]
 * (https://en.wikipedia.org/wiki/Subset_sum_problem) algorithm, which tells
 * whether a subset with target sum exists or not.
 *
 * @details
 * In this problem, we use dynamic programming to find if we can pull out a
 * subset from an array whose sum is equal to a given target sum. The overall
 * time complexity of the problem is O(n * targetSum) where n is the size of
 * the array. For example, array = [1, -10, 2, 31, -6], targetSum = -14.
 * Output: true => We can pick subset [-10, 2, -6] with sum as
 * (-10) + 2 + (-6) = -14.
 * @author [KillerAV](https://github.com/KillerAV)
 */

#include <cassert>        /// for std::assert
#include <iostream>       /// for IO operations
#include <unordered_map>  /// for unordered map
#include <vector>         /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace subset_sum
 * @brief Functions for [Sub-set sum problem]
 * (https://en.wikipedia.org/wiki/Subset_sum_problem) algorithm
 */
namespace subset_sum {

/**
 * Recursive function using dynamic programming to find if the required sum
 * subset exists or not.
 * @param arr input array
 * @param targetSum the target sum of the subset
 * @param dp the map storing the results
 * @returns true/false based on if the target sum subset exists or not.
 */
bool subset_sum_recursion(const std::vector<int> &arr, int targetSum,
                          std::vector<std::unordered_map<int, bool>> *dp,
                          int index = 0) {
    if (targetSum == 0) {  // Found a valid subset with required sum.
        return true;
    }
    if (index == arr.size()) {  // End of array
        return false;
    }

    if ((*dp)[index].count(targetSum)) {  // Answer already present in map
        return (*dp)[index][targetSum];
    }

    bool ans =
        subset_sum_recursion(arr, targetSum - arr[index], dp, index + 1) ||
        subset_sum_recursion(arr, targetSum, dp, index + 1);
    (*dp)[index][targetSum] = ans;  // Save ans in dp map.
    return ans;
}

/**
 * Function implementing subset sum algorithm using top-down approach
 * @param arr input array
 * @param targetSum the target sum of the subset
 * @returns true/false based on if the target sum subset exists or not.
 */
bool subset_sum_problem(const std::vector<int> &arr, const int targetSum) {
    size_t n = arr.size();
    std::vector<std::unordered_map<int, bool>> dp(n);
    return subset_sum_recursion(arr, targetSum, &dp);
}
}  // namespace subset_sum
}  // namespace dynamic_programming

/**
 * @brief Test Function
 * @return void
 */
static void test() {
    // custom input vector
    std::vector<std::vector<int>> custom_input_arr(3);
    custom_input_arr[0] = std::vector<int>{1, -10, 2, 31, -6};
    custom_input_arr[1] = std::vector<int>{2, 3, 4};
    custom_input_arr[2] = std::vector<int>{0, 1, 0, 1, 0};

    std::vector<int> custom_input_target_sum(3);
    custom_input_target_sum[0] = -14;
    custom_input_target_sum[1] = 10;
    custom_input_target_sum[2] = 2;

    // calculated output vector by pal_part Function
    std::vector<int> calculated_output(3);

    for (int i = 0; i < 3; i++) {
        calculated_output[i] =
            dynamic_programming::subset_sum::subset_sum_problem(
                custom_input_arr[i], custom_input_target_sum[i]);
    }

    // expected output vector
    std::vector<bool> expected_output{true, false, true};

    // Testing implementation via assert function
    // It will throw error if any of the expected test fails
    // Else it will give nothing
    for (int i = 0; i < 3; i++) {
        assert(expected_output[i] == calculated_output[i]);
    }

    std::cout << "All tests passed successfully!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
