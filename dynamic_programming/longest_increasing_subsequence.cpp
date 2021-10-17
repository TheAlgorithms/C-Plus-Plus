/**
 * @file
 * @brief Calculate the length of the [longest increasing
 * subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) in
 * an array
 *
 * @details
 * In computer science, the longest increasing subsequence problem is to find a
 * subsequence of a given sequence in which the subsequence's elements are in
 * sorted order, lowest to highest, and in which the subsequence is as long as
 * possible. This subsequence is not necessarily contiguous, or unique. Longest
 * increasing subsequences are studied in the context of various disciplines
 * related to mathematics, including algorithmics, random matrix theory,
 * representation theory, and physics. The longest increasing subsequence
 * problem is solvable in time O(n log n), where n denotes the length of the
 * input sequence.
 *
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @author [David Leal](https://github.com/Panquesito7)
 */

#include <cassert>   /// for assert
#include <climits>   /// for std::max
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @brief Calculate the longest increasing subsequence for the specified numbers
 * @param a the array used to calculate the longest increasing subsequence
 * @param n the size used for the arrays
 * @returns the length of the longest increasing
 * subsequence in the `a` array of size `n`
 */
uint64_t LIS(const std::vector<uint64_t> &a, const uint32_t &n) {
    std::vector<int> lis(n);
    for (int i = 0; i < n; ++i) {
        lis[i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = std::max(res, lis[i]);
    }
    return res;
}
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::vector<uint64_t> a = {15, 21, 2, 3, 4, 5, 8, 4, 1, 1};
    uint32_t n = a.size();

    uint32_t result = dynamic_programming::LIS(a, n);
    assert(result ==
           5);  ///< The longest increasing subsequence is `{2,3,4,5,8}`

    std::cout << "Self-test implementations passed!" << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const *argv[]) {
    uint32_t n = 0;

    std::cout << "Enter size of array: ";
    std::cin >> n;

    std::vector<uint64_t> a(n);

    std::cout << "Enter array elements: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cout << "\nThe result is: " << dynamic_programming::LIS(a, n)
              << std::endl;
    test();  // run self-test implementations

    return 0;
}
