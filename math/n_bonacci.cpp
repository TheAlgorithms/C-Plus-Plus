/**
 * @file
 * @brief Implementation of the
 * [N-bonacci](http://oeis.org/wiki/N-bonacci_numbers) series
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
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <algorithm>  /// for std::is_equal, std::swap
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace n_bonacci
 * @brief Functions for the [N-bonacci](http://oeis.org/wiki/N-bonacci_numbers)
 * implementation
 */
namespace n_bonacci {
/**
 * @brief Finds the N-Bonacci series for the `n` parameter value and `m`
 * parameter terms
 * @param n is in the N-Bonacci series
 * @param m is the number of terms in the N-Bonacci sequence
 * @returns the n-bonacci sequence as vector array
 */
std::vector<uint64_t> N_bonacci(const uint64_t &n, const uint64_t &m) {
    std::vector<uint64_t> a(m, 0);  // we create an empty array of size m

    a[n - 1] = 1;  /// we initialise the (n-1)th term as 1 which is the sum of
                   /// preceding N zeros
    a[n] = 1;  /// similarily the sum of preceding N zeros and the (N+1)th 1 is
               /// also 1
    for (uint64_t i = n + 1; i < m; i++) {
        // this is an optimized solution that works in O(M) time and takes O(M)
        // extra space here we use the concept of the sliding window the current
        // term can be computed using the given formula
        a[i] = 2 * a[i - 1] - a[i - 1 - n];
    }
    return a;
}
}  // namespace n_bonacci
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n = 1 m = 1 return [1, 1]
    std::cout << "1st test";
    std::vector<uint64_t> arr1 = math::n_bonacci::N_bonacci(
        1, 1);  // first input is the param n and second one is the param m for
                // N-bonacci func
    std::vector<uint64_t> output_array1 = {
        1, 1};  // It is the expected output series of length m
    assert(std::equal(std::begin(arr1), std::end(arr1),
                      std::begin(output_array1)));
    std::cout << "passed" << std::endl;

    // n = 5 m = 15 return [0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 31, 61, 120, 236,
    // 464]
    std::cout << "2nd test";
    std::vector<uint64_t> arr2 = math::n_bonacci::N_bonacci(
        5, 15);  // first input is the param n and second one is the param m for
                 // N-bonacci func
    std::vector<uint64_t> output_array2 = {
        0, 0,  0,  0,  1,   1,   2,  4,
        8, 16, 31, 61, 120, 236, 464};  // It is the expected output series of
                                        // length m
    assert(std::equal(std::begin(arr2), std::end(arr2),
                      std::begin(output_array2)));
    std::cout << "passed" << std::endl;

    // n = 6 m = 17 return [0, 0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 63, 125, 248,
    // 492, 976]
    std::cout << "3rd test";
    std::vector<uint64_t> arr3 = math::n_bonacci::N_bonacci(
        6, 17);  // first input is the param n and second one is the param m for
                 // N-bonacci func
    std::vector<uint64_t> output_array3 = {
        0, 0,  0,  0,  0,   1,   1,   2,  4,
        8, 16, 32, 63, 125, 248, 492, 976};  // It is the expected output series
                                             // of length m
    assert(std::equal(std::begin(arr3), std::end(arr3),
                      std::begin(output_array3)));
    std::cout << "passed" << std::endl;

    // n = 56 m = 15 return [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    std::cout << "4th test";
    std::vector<uint64_t> arr4 = math::n_bonacci::N_bonacci(
        56, 15);  // first input is the param n and second one is the param m
                  // for N-bonacci func
    std::vector<uint64_t> output_array4 = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0};  // It is the expected output series of length m
    assert(std::equal(std::begin(arr4), std::end(arr4),
                      std::begin(output_array4)));
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
