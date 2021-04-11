/**
 * @file
 * @brief [Subset Sum DP] Implementation
 * (https://www.geeksforgeeks.org/subset-sum-problem-dp-25)
 *
 * @details
 * Give a value $V$ and set of non-negative integers
 * Determine if there is subset which has $sum = V$
 *
 * ### Algorithm
 * $dp(i, j)$ shows considering i-elements from start, is it possible to get
 * the $sum = j?$. $Sum = 0$ is possible by default, for every other sum we will
 * check if it is obtainable while excluding the current element i from
 * the subset (that is $dp(i-1, sum) == true?$) or obtainable when including
 * element i to the subset (that is $sum \geq A_{i}$ and
 * $dp(i-1, sum - A_{i}) == true?$) in that case we will mark $dp(i, sum)$ as
 * true. $dp(n, V)$ will store the final answer (considering all n elements is
 * it possible to get subset of sum $V$ ?).
 *
 * @author [Syed Faizan](https://github.com/faizan2700)
 */

#include <array>     /// for creating std::array
#include <cassert>   /// for using assert in test function
#include <iostream>  /// for IO operations
#include <vector>    /// for using std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace subset_sum
 * @brief [Subset Sum DP] Implementation
 */
namespace subset_sum {
/**
 * @brief for each sum less than or equal to V calculate if it is possible
 * to get with help of first i elements. By making use of previously
 * calculated info subset sum can be solved in $O(n\astV)$ complexity.
 * @tparam T size of the set
 * @param $A$ set of the allowed values.
 * @param $n$ array size.
 * @param $V$ subset sum to be obtained.
 * @return true if possible to get subset sum of value $V$, false otherwise.
 */
template <size_t T>
bool subset_sum(const std::array<int, T> &A, const int &n, const uint32_t &v) {
    uint32_t S = 0;
    for (int i = 0; i < n; i++) S += A[i];

    if (v > S)
        return false;  // if value is greater than sum of set than not possible.
    if (v == S or v == 0)
        return true;  // 0 is possible by empty set, S is possible by taking
                      // whole set.

    std::vector<std::vector<bool> > dp(n + 1, std::vector<bool>(v + 1, false));

    for (int i = 0; i <= n; i++) dp[i][0] = true;  // 0 sum is always possible.
    for (int i = 1; i <= v; i++)
        dp[0][i] =
            false;  // no sum(>0) is possible when 0 elements are included.

    // outer loop iterates over all the element
    // inner loop iterates over all the possible sum.
    // sum = j is obtainable if we can get this by excluding the current element
    // from subset or we can get this by including the current element from the
    // subset.
    for (int i = 1; i <= n; i++) {
        for (uint32_t j = 1; j <= v; j++) {
            dp[i][j] = dp[i - 1][j] or
                       (j >= A[i - 1] ? dp[i - 1][j - A[i - 1]] : false);
        }
    }

    // 1 if obtainable, 0 otherwise.
    return dp[n][v];
}
}  // namespace subset_sum
}  // namespace dynamic_programming

/**
 * @brief Self-test implementation
 * @returns void
 */
static void test() {
    bool ans = false;
    uint64_t v = 0;
    // 1st test
    const uint32_t N1 = 5;
    v = 9;
    std::array<int, N1> A = {1, 2, 3, 4, 5};
    ans = dynamic_programming::subset_sum::subset_sum(A, N1, v);
    assert(ans);

    // 2nd test
    const uint32_t N2 = 6;
    v = 13;
    std::array<int, N2> B = {2, 4, 6, 8, 10, 12};
    ans = dynamic_programming::subset_sum::subset_sum(B, N2, v);
    assert(!ans);
}

/**
 * @brief Main function
 * @param argc count of command line arguments (ignored)
 * @param argv array of command line arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementation
    return 0;
}
