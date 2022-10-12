/**
 * @file
 * @brief [Subset-sum](https://en.wikipedia.org/wiki/Subset_sum_problem) (only
 * continuous subsets) problem
 * @details We are given an array and a sum value. The algorithms find all
 * the subarrays of that array with sum equal to the given sum and return such
 * subarrays count. This approach will have \f$O(n)\f$ time complexity and
 * \f$O(n)\f$ space complexity. NOTE: In this problem, we are only referring to
 * the continuous subsets as subarrays everywhere. Subarrays can be created
 * using deletion operation at the end of the front of an array only. The parent
 * array is also counted in subarrays having 0 number of deletion operations.
 *
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>        /// for assert
#include <iostream>       /// for IO operations
#include <unordered_map>  /// for unordered_map
#include <vector>         /// for std::vector

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace subarray_sum
 * @brief Functions for the [Subset
 * sum](https://en.wikipedia.org/wiki/Subset_sum_problem) implementation
 */
namespace subarray_sum {
/**
 * @brief The main function that implements the count of the subarrays
 * @param sum is the required sum of any subarrays
 * @param in_arr is the input array
 * @returns count of the number of subsets with required sum
 */
uint64_t subarray_sum(int64_t sum, const std::vector<int64_t> &in_arr) {
    int64_t nelement = in_arr.size();
    int64_t count_of_subset = 0;
    int64_t current_sum = 0;
    std::unordered_map<int64_t, int64_t>
        sumarray;  // to store the subarrays count
                   // frequency having some sum value

    for (int64_t i = 0; i < nelement; i++) {
        current_sum += in_arr[i];

        if (current_sum == sum) {
            count_of_subset++;
        }
        // If in case current_sum is greater than the required sum
        if (sumarray.find(current_sum - sum) != sumarray.end()) {
            count_of_subset += (sumarray[current_sum - sum]);
        }
        sumarray[current_sum]++;
    }
    return count_of_subset;
}
}  // namespace subarray_sum
}  // namespace backtracking

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::cout << "1st test ";
    std::vector<int64_t> array1 = {-7, -3, -2, 5, 8};  // input array
    assert(
        backtracking::subarray_sum::subarray_sum(0, array1) ==
        1);  // first argument in subarray_sum function is the required sum and
             // second is the input array, answer is the subarray {(-3,-2,5)}
    std::cout << "passed" << std::endl;

    // 2nd test
    std::cout << "2nd test ";
    std::vector<int64_t> array2 = {1, 2, 3, 3};
    assert(backtracking::subarray_sum::subarray_sum(6, array2) ==
           2);  // here we are expecting 2 subsets which sum up to 6 i.e.
                // {(1,2,3),(3,3)}
    std::cout << "passed" << std::endl;

    // 3rd test
    std::cout << "3rd test ";
    std::vector<int64_t> array3 = {1, 1, 1, 1};
    assert(backtracking::subarray_sum::subarray_sum(1, array3) ==
           4);  // here we are expecting 4 subsets which sum up to 1 i.e.
                // {(1),(1),(1),(1)}
    std::cout << "passed" << std::endl;

    // 4rd test
    std::cout << "4th test ";
    std::vector<int64_t> array4 = {3, 3, 3, 3};
    assert(backtracking::subarray_sum::subarray_sum(6, array4) ==
           3);  // here we are expecting 3 subsets which sum up to 6 i.e.
                // {(3,3),(3,3),(3,3)}
    std::cout << "passed" << std::endl;

    // 5th test
    std::cout << "5th test ";
    std::vector<int64_t> array5 = {};
    assert(backtracking::subarray_sum::subarray_sum(6, array5) ==
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
