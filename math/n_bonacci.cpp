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

#include <cassert>   /// for assert
#include <iostream>  /// for std::cout
#include <vector>    /// for std::vector

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
    std::vector<uint64_t> a(
        m, 0);  // we create an array of size m filled with zeros
    if (m < n || n == 0) {
        return a;
    }

    a[n - 1] = 1;  /// we initialise the (n-1)th term as 1 which is the sum of
                   /// preceding N zeros
    if (n == m) {
        return a;
    }
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
    struct TestCase {
        const uint64_t n;
        const uint64_t m;
        const std::vector<uint64_t> expected;
        TestCase(const uint64_t in_n, const uint64_t in_m,
                 std::initializer_list<uint64_t> data)
            : n(in_n), m(in_m), expected(data) {
            assert(data.size() == m);
        }
    };
    const std::vector<TestCase> test_cases = {
        TestCase(0, 0, {}),
        TestCase(0, 1, {0}),
        TestCase(0, 2, {0, 0}),
        TestCase(1, 0, {}),
        TestCase(1, 1, {1}),
        TestCase(1, 2, {1, 1}),
        TestCase(1, 3, {1, 1, 1}),
        TestCase(5, 15, {0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 31, 61, 120, 236, 464}),
        TestCase(
            6, 17,
            {0, 0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 63, 125, 248, 492, 976}),
        TestCase(56, 15, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})};

    for (const auto &tc : test_cases) {
        assert(math::n_bonacci::N_bonacci(tc.n, tc.m) == tc.expected);
    }
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
