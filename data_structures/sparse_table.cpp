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
 * @todo make stress tests.
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
 * @brief Functions for Implementation of [Sparse
 * Table](https://brilliant.org/wiki/sparse-table/)
 */
namespace sparse_table {

/**
 * @brief A struct to represent sparse table for `min()` as their invariant
 * function, for the given array `A`. The answer to queries are stored in the
 * array ST.
 */
constexpr uint32_t N = 12345;  ///< the maximum size of the array.
constexpr uint8_t M = 14;      ///< ceil(log2(N)).

struct Sparse_table {
    size_t n = 0;  ///< size of input array.

    /** @warning check if `N` is not less than `n`. if so, manually increase the
     * value of N */

    std::array<int64_t, N> A = {};  ///< input array to perform RMQ.
    std::array<std::array<int64_t, N>, M>
        ST{};  ///< the sparse table storing `min()` values for given interval.
    std::array<int64_t, N> LOG = {};  ///< where floor(log2(i)) are precomputed.

    /**
     * @brief Builds the sparse table for computing min/max/gcd/lcm/...etc
     * for any contiguous sub-segment of the array.This is an example of
     * computing the index of the minimum value.
     * @return void
     * @complexity: O(n.log(n))
     */
    void buildST() {
        LOG[0] = -1;

        for (size_t i = 0; i < n; ++i) {
            ST[0][i] = static_cast<int64_t>(i);
            LOG[i + 1] = LOG[i] + !(i & (i + 1));  ///< precomputing `log2(i+1)`
        }

        for (size_t j = 1; static_cast<size_t>(1 << j) <= n; ++j) {
            for (size_t i = 0; static_cast<size_t>(i + (1 << j)) <= n; ++i) {
                /**
                 * @note notice how we deal with the range of length `pow(2,i)`,
                 * and we can reuse the computation that we did for the range of
                 * length `pow(2,i-1)`.
                 *
                 * So, ST[j][i] = min( ST[j-1][i], ST[j-1][i + pow(2,j-1)]).
                 * @example ST[2][3] = min(ST[1][3], ST[1][5])
                 */

                int64_t x = ST[j - 1][i];  ///< represents minimum value over
                                           ///< the range [j,i]
                int64_t y =
                    ST[j - 1]
                      [i + (1 << (j - 1))];  ///< represents minimum value over
                                             ///< the range [j,i + pow(2,j-1)]

                ST[j][i] =
                    (A[x] <= A[y] ? x : y);  ///< represents minimum value over
                                             ///< the range [j,i]
            }
        }
    }

    /**
     * @brief Queries the sparse table for the value of the interval [l, r]
     * (i.e. from l to r inclusive).
     * @param l the left index of the range (inclusive).
     * @param r the right index of the range (inclusive).
     * @return the computed value of the given interval.
     * @complexity: O(1)
     */
    int64_t query(int64_t l, int64_t r) {
        int64_t g = LOG[r - l + 1];  ///< smallest power of 2 covering [l,r]
        int64_t x = ST[g][l];  ///< represents minimum value over the range
                               ///< [g,l]
        int64_t y =
            ST[g][r - (1 << g) + 1];  ///< represents minimum value over the
                                      ///< range [g, r - pow(2,g) + 1]

        return (A[x] <= A[y] ? x : y);  ///< represents minimum value over
                                        ///< the whole range [l,r]
    }
};
}  // namespace sparse_table
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* We take an array as an input on which we need to perform the ranged
     * minimum queries[RMQ](https://en.wikipedia.org/wiki/Range_minimum_query).
     */
    std::array<int64_t, 10> testcase = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10};  ///< array on which RMQ will be performed.
    size_t testcase_size =
        sizeof(testcase) / sizeof(testcase[0]);  ///< size of self test's array

    data_structures::sparse_table::Sparse_table
        st{};  ///< declaring sparse tree

    std::copy(std::begin(testcase), std::end(testcase),
              std::begin(st.A));  ///< copying array to the struct
    st.n = testcase_size;         ///< passing the array's size to the struct

    st.buildST();  ///< precomputing sparse tree

    // pass queries of the form: [l,r]
    assert(st.query(1, 9) == 1);  ///< as 1 is smallest from 1..9
    assert(st.query(2, 6) == 2);  ///< as 2 is smallest from 2..6
    assert(st.query(3, 8) == 3);  ///< as 3 is smallest from 3..8

    std::cout << "Self-test implementations passed!" << std::endl;
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
