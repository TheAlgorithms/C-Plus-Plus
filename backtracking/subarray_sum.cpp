/**
 * @file
 * @brief We are given with an array and a sum value. The algorithms find all
 * the subarrays of that array with sum equal to given sum and return such subarrays
 * count. This approach will have \f$O(n)\f$ time complexity and \f$O(n)\f$ space complexity.
 * NOTE: In this problem, we are only refering to the continuous subsets as subarrays everywhere. Subarrays can be created using deletion operation at the end or the front of an array only. The parent array is also counted in subarrays having 0 number of deletion operations.
 * @details Subset sum(only continuous subsets) problem (https://en.wikipedia.org/wiki/Subset_sum_problem)
 * @author [Swastika Gupta](https://github.com/swastyy)
 */

#include <cassert>        /// for assert
#include <iostream>       /// for io operations
#include <vector>         /// for std::vector
#include <unordered_map>  /// for unordered_map

/**
 * @namespace backtracking
 * @brief subarray sum algorithm
 */
namespace backtracking {
/**
 * @namespace Subarrays
 * @brief Functions for counting subsets(only continuous subarrays) in a given array with a given sum Time Complexity: O(n),
 * where ‘n’ is the number of elements in the given array.
 */
namespace Subarrays {
/**
 * @brief The main function implements count of subarrays
 * @param sum is the required sum of any subarrays
 * @param in_arr is the input array
 * @returns count of the number of subsets with required sum
 */

std::uint64_t subarray_sum(int sum, const std::vector<int> &in_arr) {
    int nelement = in_arr.size();
    int count_of_subset = 0;
    int current_sum = 0;
    std::unordered_map<int, int> sumarray; // to store the subarrays count frequency having some sum value

    for (int i = 0; i < nelement; i++) {
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
}  // namespace Subarrays
}  // namespace backtracking

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Test 1
    std::cout << "1st test ";
    std::vector<int> array1 = {-7, -3, -2, 5, 8};  // input array
    assert(backtracking::Subarrays::subarray_sum(0, array1) == 1);  // first argument in subarray_sum function is the required sum and second is the input array, answer is the subarray {(-3,-2,5)}
    std::cout << "passed" << std::endl;

    // Test 2
    std::cout << "2nd test ";
    std::vector<int> array2 = {1, 2, 3, 3};
    assert(backtracking::Subarrays::subarray_sum(6, array2) == 2);  // here we are expecting 2 subsets which sum up to 6 i.e. {(1,2,3),(3,3)}
    std::cout << "passed" << std::endl;

    // Test 3
    std::cout << "3rd test ";
    std::vector<int> array3 = {1, 1, 1, 1};
    assert(backtracking::Subarrays::subarray_sum(1, array3) == 4);  // here we are expecting 4 subsets which sum up to 1 i.e. {(1),(1),(1),(1)}
    std::cout << "passed" << std::endl;

    // Test 4
    std::cout << "4th test ";
    std::vector<int> array4 = {3, 3, 3, 3};
    assert(backtracking::Subarrays::subarray_sum(6, array4) == 3);  // here we are expecting 3 subsets which sum up to 6 i.e. {(3,3),(3,3),(3,3)}
    std::cout << "passed" << std::endl;

    // Test 5
    std::cout << "5th test ";
    std::vector<int> array5 = {};
    assert(backtracking::Subarrays::subarray_sum(6, array5) == 0);  // here we are expecting 0 subsets which sum up to 6 i.e. we cannot select anything from an empty array
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
