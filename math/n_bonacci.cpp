/**
 * @file
 * @brief Implementation of [N-bonacci](http://oeis.org/wiki/N-bonacci_numbers) series
 *
 * @details
 * In general, in N-bonacci sequence,
 * we generate sum of preceding N numbers from the next term.
 *
 * For example, a 3-bonacci sequence is the following:
 * 0, 0, 1, 1, 2, 4, 7, 13, 24, 44, 81
 * In this code we take N and M as input where M is the number of terms
 * to be printed of the N-bonacci series
 *
 * @author [Swastika Gupta](https://github.com/swastyy)
 */
#include <algorithm>  /// for std::is_sorted, std::swap
#include <cassert>    /// for assert
#include <iostream>   /// for io operations
#include <vector>     /// for std::vector

namespace math {
/**
 * @namespace math
 * @brief Function for n-bonacci series
 */
namespace n_bonacci {
/**
 * @brief Function implements n-bonacci series
 * @tparam T type of array
 * @param n,m m is the number of terms in n-bonacci sequence
 * @returns the n-bonacci sequence as vector array
 */
template <typename T>
std::vector<T> N_bonacci(const std::vector<T> &in_arr) {
    /**
     * This function finds N-bonacci series for
     * @param n value and @param m terms
     */
    int n = in_arr[0];
    int m = in_arr[1];
    std::vector<int> a(m, 0);  // we create an empty array of size m
                              
    int i = 0;
    a[n - 1] = 1;  /// we initialise the (n-1)th term as 1 which is the sum of
                   /// preceding N zeros
    a[n] = 1;  /// similarily the sum of preceding N zeros and the (N+1)th 1 is
               /// also 1
    for (i = n + 1; i < m; i++) {
        /*this is an optimized solution which works in O(M) time and takes O(M)
         *extra space here we use the concept of sliding window the current term
         *can be computed using the given formula
         */
        a[i] = 2 * a[i - 1] - a[i - 1 - n];
    }
    return a;
}
}
}


/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // n = array1[0] m = array1[1] return [1, 1]
    std::vector<int> array1 = {1, 1};
    std::cout << "Test 1... ";
    std::vector<int> arr1 = math::n_bonacci::N_bonacci(array1);
    std::vector<int> output_array1 = {1, 1};
    assert(std::equal(std::begin(arr1), std::end(arr1), std::begin(output_array1)));
    std::cout << "passed" << std::endl;

    // n = array2[0] m = array2[1] return [0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 31, 61, 120, 236, 464]
    std::vector<int> array2 = {5, 15};
    std::cout << "Test 2... ";
    std::vector<int> arr2 = math::n_bonacci::N_bonacci(array2);
    std::vector<int> output_array2 = {0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 31, 61, 120, 236, 464};
    assert(std::equal(std::begin(arr2), std::end(arr2), std::begin(output_array2)));
    std::cout << "passed" << std::endl;

    // n = array3[0] m = array3[1] return [0, 0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 63, 125, 248, 492, 976]
    std::vector<int> array3 = {6, 17};
    std::cout << "Test 3... ";
    std::vector<int> arr3 = math::n_bonacci::N_bonacci(array3);
    std::vector<int> output_array3 = {0, 0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 63, 125, 248, 492, 976};
    assert(std::equal(std::begin(arr3), std::end(arr3), std::begin(output_array3)));
    std::cout << "passed" << std::endl;

    // n = array4[0] m = array4[1] return [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    std::vector<int> array4 = {56, 15};
    std::cout << "Test 4... ";
    std::vector<int> arr4 = math::n_bonacci::N_bonacci(array4);
    std::vector<int> output_array4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    assert(std::equal(std::begin(arr4), std::end(arr4), std::begin(output_array4)));
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
