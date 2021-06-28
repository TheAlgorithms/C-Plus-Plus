/**
 * @file
 * @brief Program to Count number of subsets 
 *
 * @details Subset problem (https://en.wikipedia.org/wiki/Subset_sum_problem)
 * @author [Swastika Gupta](https://github.com/swastyy)
 */
 
#include <cassert>    /// for assert
#include <iostream>   /// for io operations
#include <vector>     /// for std::vector
 
/**
 * @namespace backtracking
 * @brief subset sum algorithm
 */
namespace backtracking {
/**
 * @namespace Subsets
 * @brief Functions for counting subsets in a given array with a given sum
 */
namespace Subsets {
/**
 * @brief The main function implements count of subsets
 * @param sum is the required sum of any subset
 * @param in_arr is the input array
 * @returns count of the number of subsets with required sum
 */

std::uint64_t subset_sum(int sum, std::vector<int> &in_arr) {
   	int nelement = in_arr.size();	//number of subset element
	int count_of_subset = 0;

	for(int i=0; i < (1 << (nelement)); i++) {
		std::vector<int> subset;
		for( int j=0 ; j < nelement ; j++) {
			if (i & (1<<j)) {
				subset.push_back(in_arr[j]);
			}
		}
		int check=0;
		for( int k=0 ; k < subset.size(); k++) {
			check += subset[k];
		}
		if(check==sum) {
			count_of_subset++;
		}
	}
	return count_of_subset;
}
}  // namespace Subsets
}  // namespace backtracking

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Test 1
    std::cout << "1st test ";
    std::vector<int> array1 = {-7,-3,-2,5,8}; // input array
    assert(backtracking::Subsets::subset_sum(0,array1)==2); // first argument in subset_sum function is the required sum and second is the input array
    std::cout << "passed" << std::endl;

    // Test 2
    std::cout << "2nd test ";
    std::vector<int> array2 = {1, 2, 3, 3}; // input array
    assert(backtracking::Subsets::subset_sum(6,array2)==3); // first argument in subset_sum function is the required sum and second is the input array
    std::cout << "passed" << std::endl;

    // Test 3
    std::cout << "3rd test ";
    std::vector<int> array3 = {1, 1, 1, 1}; // input array
    assert(backtracking::Subsets::subset_sum(1,array3)==4); // first argument in subset_sum function is the required sum and second is the input array
    std::cout << "passed" << std::endl;

    // Test 4
    std::cout << "4th test ";
    std::vector<int> array4 = { 3, 3, 3, 3 }; // input array
    assert(backtracking::Subsets::subset_sum(6,array4)==6); // first argument in subset_sum function is the required sum and second is the input array
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
