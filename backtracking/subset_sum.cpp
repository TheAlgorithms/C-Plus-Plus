/**
 * @file
 * @brief Implementation of the [Subset
 * Sum](https://en.wikipedia.org/wiki/Subset_sum_problem) problem.
 * @details
 * We are given an array and a sum value. The algorithm finds all
 * the subsets of that array with sum equal to the given sum and return such
 * subsets count. This approach will have exponential time complexity.
 * @author [Swastika Gupta](https://github.com/Swastyy)
 * 
 * Second Method added : This method used dynamic programming to  
 * reduce the time complexity of solution from exponential ,i.e, O(n*2^n) to O(n*sum_of_elements)
 * dp[{i,j}] defines the number of possible subsets with sum 'j' , by considering only the first 'i' elements
 * of the array
 * 
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <map>       /// for std::map
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
 
//1st Method
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

//2nd Method
uint64_t number_of_subsets2(int32_t sum, const std::vector<int32_t> &in_arr) {
    int32_t nelement = in_arr.size();
    int32_t sum_of_elements = 0 ; 
    int32_t minimum = 0 ; 
    for (int32_t i = 0; i < nelement  ; i++) {
        if(in_arr[i]<0){
            minimum += in_arr[i];
        }
        else{
            sum_of_elements += in_arr[i];
        }
    }
    
    std::map<std::pair<int32_t,int32_t>,uint64_t> dp ; 
    dp[{-1,0}]=1;
    for(int32_t i = 0 ; i < nelement ; i++){
        for(int32_t j = minimum; j <= sum_of_elements ;j++) {
            dp[{i,j}] = dp[{i-1,j-in_arr[i]}] + dp[{i-1,j}] ; 
        }
    }
    return dp[{nelement-1,sum}];
}
}  // namespace subset_sum
}  // namespace backtracking




 









/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Test 1
    // 1st Method
    std::cout << "1st test 1st Method ";
    std::vector<int32_t> array1 = {-7, -3, -2, 5, 8};  // input array
    assert(backtracking::subset_sum::number_of_subsets(0, array1) ==
           2);  // first argument in subset_sum function is the required sum and
                // second is the input array
    std::cout << "passed" << std::endl;
    
    // Test 1 
    // 2nd Method 
    // input array = same as used in 1st test above.
    std::cout << "1st test 2nd Method ";
    assert(backtracking::subset_sum::number_of_subsets2(0, array1) ==
           2);  // first argument in subset_sum function is the required sum and
                // second is the input array
    std::cout << "passed" << std::endl;

    // Test 2
    // 1st Method
    std::cout << "2nd test 1st Method ";
    std::vector<int32_t> array2 = {1, 2, 3, 3};
    assert(backtracking::subset_sum::number_of_subsets(6, array2) ==
           3);  // here we are expecting 3 subsets which sum up to 6 i.e.
                // {(1,2,3),(1,2,3),(3,3)}
    std::cout << "passed" << std::endl;
    
    // Test 2
    // 2nd Method 
    // input array = same as used in 2nd test above.
    std::cout << "2nd test 2nd Method ";
    assert(backtracking::subset_sum::number_of_subsets2(6, array2) ==
           3);  // here we are expecting 3 subsets which sum up to 6 i.e.
                // {(1,2,3),(1,2,3),(3,3)}
    std::cout << "passed" << std::endl;
    
    // Test 3
    // 1st Method
    std::cout << "3rd test 1st Method ";
    std::vector<int32_t> array3 = {1, 1, 1, 1};
    assert(backtracking::subset_sum::number_of_subsets(1, array3) ==
           4);  // here we are expecting 4 subsets which sum up to 1 i.e.
                // {(1),(1),(1),(1)}
    std::cout << "passed" << std::endl;
    
    // Test 3
    // 2nd Method
    // input array = same as used in 3rd test above.
    std::cout << "3rd test 2nd Method ";
    assert(backtracking::subset_sum::number_of_subsets2(1, array3) ==
           4);  // here we are expecting 4 subsets which sum up to 1 i.e.
                // {(1),(1),(1),(1)}
    std::cout << "passed" << std::endl;
    
    // Test 4
    // 1st Method
    std::cout << "4th test 1st Method ";
    std::vector<int32_t> array4 = {3, 3, 3, 3};
    assert(backtracking::subset_sum::number_of_subsets(6, array4) ==
           6);  // here we are expecting 6 subsets which sum up to 6 i.e.
                // {(3,3),(3,3),(3,3),(3,3),(3,3),(3,3)}
    std::cout << "passed" << std::endl;

    // Test 4
    // 2nd Method
    // input array = same as used in 4th test above.
    std::cout << "4th test 2nd Method ";
    assert(backtracking::subset_sum::number_of_subsets2(6, array4) ==
           6);  // here we are expecting 6 subsets which sum up to 6 i.e.
                // {(3,3),(3,3),(3,3),(3,3),(3,3),(3,3)}
    std::cout << "passed" << std::endl;

    // Test 5
    // 1st Method
    std::cout << "5th test 1st Method ";
    std::vector<int32_t> array5 = {};
    assert(backtracking::subset_sum::number_of_subsets(6, array5) ==
           0);  // here we are expecting 0 subsets which sum up to 6 i.e. we
                // cannot select anything from an empty array
    std::cout << "passed" << std::endl;
    
    // Test 5 
    // 2nd Method
    // input array = same as used in 5th test above.
    std::cout << "5th test 2nd Method ";
    assert(backtracking::subset_sum::number_of_subsets2(6, array5) ==
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
