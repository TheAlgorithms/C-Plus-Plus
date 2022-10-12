/**
 * @file
 * @brief Implementation of the [Subset
 * Sum](https://en.wikipedia.org/wiki/Subset_sum_problem) problem.
 * @details
 * We are given an array and a sum value. The algorithm finds all
 * the subsets of that array with sum equal to the given sum and return such
 * subsets count. This approach will have exponential time complexity.
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace Subsets
 * @brief Functions for the [Subset
 * Sum](https://en.wikipedia.org/wiki/Subset_sum_problem) problem.
 */
namespace subset_sum {
/**
 * @brief The main function implements count of subsets
 * @param sum is the required sum of any subset
 * @param in_arr is the input array
 * @returns count of the number of subsets with required sum
 */
uint64_t number_of_subsets(int32_t sum, const std::vector<int32_t> &in_arr) {
    int32_t nelement = in_arr.size();
    uint64_t count_of_subset = 0;

    for (int32_t i = 0; i < (1 << (nelement)); i++) {
        int32_t check = 0;
        for (int32_t j = 0; j < nelement; j++) {
            if (i & (1 << j)) {
                check += (in_arr[j]);
            }
        }
        if (check == sum) {
            count_of_subset++;
        }
    }
    return count_of_subset;
}
}  // namespace subset_sum
}  // namespace backtracking

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::cout << "1st test ";
    std::vector<int32_t> array1 = {-7, -3, -2, 5, 8};  // input array
    assert(backtracking::subset_sum::number_of_subsets(0, array1) ==
           2);  // first argument in subset_sum function is the required sum and
                // second is the input array
    std::cout << "passed" << std::endl;

    // 2nd test
    std::cout << "2nd test ";
    std::vector<int32_t> array2 = {1, 2, 3, 3};
    assert(backtracking::subset_sum::number_of_subsets(6, array2) ==
           3);  // here we are expecting 3 subsets which sum up to 6 i.e.
                // {(1,2,3),(1,2,3),(3,3)}
    std::cout << "passed" << std::endl;

    // 3rd test
    std::cout << "3rd test ";
    std::vector<int32_t> array3 = {1, 1, 1, 1};
    assert(backtracking::subset_sum::number_of_subsets(1, array3) ==
           4);  // here we are expecting 4 subsets which sum up to 1 i.e.
                // {(1),(1),(1),(1)}
    std::cout << "passed" << std::endl;

    // 4th test
    std::cout << "4th test ";
    std::vector<int32_t> array4 = {3, 3, 3, 3};
    assert(backtracking::subset_sum::number_of_subsets(6, array4) ==
           6);  // here we are expecting 6 subsets which sum up to 6 i.e.
                // {(3,3),(3,3),(3,3),(3,3),(3,3),(3,3)}
    std::cout << "passed" << std::endl;

    // Test 5
    std::cout << "5th test ";
    std::vector<int32_t> array5 = {};
    assert(backtracking::subset_sum::number_of_subsets(6, array5) ==
           0);  // here we are expecting 0 subsets which sum up to 6 i.e. we
                // cannot select anything from an empty array
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
