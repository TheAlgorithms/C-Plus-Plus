/**
 * @file
 * @brief Implementation of [Sparse
 * Table](https://brilliant.org/wiki/sparse-table/) for `min()` function.
 * @author [Mann Patel](https://github.com/manncodes)
 * @details
 * Sparse Table is a data structure, that allows answering range queries.
 * It can answer most range queries in O(logn), but its true power is answering
 * range minimum queries (or equivalent range maximum queries). For those
 * queries it can compute the answer in O(1) time. The only drawback of this
 * data structure is, that it can only be used on immutable arrays. This means,
 * that the array cannot be changed between two queries.
 *
 * If any element in the array changes, the complete data structure has to be
 * recomputed.
 *
 * @warning
 * This sparse table is made for `min(a1,a2,...an)` duplicate invariant
 * function. This implementation can be changed to other functions like
 * `gcd()`, `lcm()`, and `max()` by changing a few lines of code.
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {

/**
 * @namespace sparse_table
 * @brief Functions for Implementation of [Sparse Table](https://brilliant.org/wiki/sparse-table/)
 */
namespace sparse_table {

/**
 * @brief A struct to represent sparse table for `min()` as their invariant
 * function, for the given array `A`. The answer to queries are stored in array
 * ST.
 */
struct Sparse_table {
    const static int N = 12345;  ///< the maximum size of the array.
    const static int M = 14;     ///< ceil(log2(N)).
    int n;                       ///< size of input array.

    /** @warning check if `N` is not less than `n`. if so, manually increase the
     * value of N */

    std::array<int, N> A;  ///< input array to perform RMQ.
    std::array<std::array<int, N>, M>
        ST;  ///< the sparse table storing `min()` values for given interval.
    std::array<int, N> LOG;  ///< where floor(log2(i)) are precomputed.

    /**
     * @brief Builds the sparse table for computing min/max/gcd/lcm/...etc
     * for any contiguous sub-segment of the array.This is an example of
     * computing the index of the minimum value.
     * @return void
     * @complexity: O(n.log(n))
     */
    void buildST() {
        LOG[0] = -1;

        for (int i = 0; i < n; ++i) {
            ST[0][i] = i;
            LOG[i + 1] = LOG[i] + !(i & (i + 1));
        }

        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; (i + (1 << j)) <= n; ++i) {
                int x = ST[j - 1][i];
                int y = ST[j - 1][i + (1 << (j - 1))];

                ST[j][i] = (A[x] <= A[y] ? x : y);
            }
        }
    }

    /**
     * @brief Queries the sparse table for the value of the interval [l, r]
     * (i.e. from l to r inclusive).
     *
     * @complexity: O(1)
     *
     * @param l the left index of the range (inclusive).
     * @param r the right index of the range (inclusive).
     *
     * @return the computed value of the given interval.
     */
    int query(int l, int r) {
        int g = LOG[r - l + 1];
        int x = ST[g][l];
        int y = ST[g][r - (1 << g) + 1];
        return (A[x] <= A[y] ? x : y);
    }
};
}  // namespace sparse_table
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::array<int, 10> testcase = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int testcase_size = sizeof(testcase) / sizeof(testcase[0]);

    data_structures::sparse_table::Sparse_table st{};

    std::copy(std::begin(testcase), std::end(testcase),
              std::begin(st.A));  ///< copying testcase to the struct
    st.n = testcase_size;

    st.buildST();  ///< precomputing sparse tree

    // pass queries of the form: [l,r]
    assert(st.query(1, 9) == 1);  ///< as 1 is smallest from 1..9
    assert(st.query(2, 6) == 2);  ///< as 2 is smallest from 2..6
    assert(st.query(3, 8) == 3);  ///< as 3 is smallest from 3..8

    std::cout << "Testcase passed!" << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
