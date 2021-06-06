/**
 *
 * @file
 * @brief Implementation of Sparse Table
 *
 * @author [Mann Patel](https://github.com/manncodes)
 *
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
 * @warning this sparse table is made for min(a1,a2,...an) duplicate invariant
 * function. This implementation can be changed to other functions like
 * gcd(),lcm(),max() by changing few lines of code.
 */

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {

/**
 * @namespace sparse_table
 * @brief Implementation of Sparse Table for function : min()
 *
 */
namespace sparse_table {

/**
 * @brief A struct to represent sparse table
 *
 */
struct Sparse_table {
    // N : the maximum size of the array.
    // M : ceil(log2(N)).
    const static int N = 12345, M = 14;

    // The array to compute its sparse table.
    int n;
    std::array<int, N> a;

    //
    // Sparse table related variables.
    //
    // ST[j][i] : the sparse table value (min, max, ...etc) in the interval [i,
    // i + (2^j) - 1]. LOG[i]   : floor(log2(i)).
    std::array<std::array<int, N>, M> ST;
    std::array<int, N> LOG;

    /**
     *
     * Builds the sparse table for computing min/max/gcd/lcm/...etc
     * for any contiguous sub-segment of the array.
     *
     * This is an example of computing the index of the minimum value.
     *
     * Complexity: O(n.log(n))
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

                ST[j][i] = (a[x] <= a[y] ? x : y);
            }
        }
    }

    /**
     * Queries the sparse table for the value of the interval [l, r]
     * (i.e. from l to r inclusive).
     *
     * Complexity: O(1)
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
        return (a[x] <= a[y] ? x : y);
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

    // copying testcase to the struct
    std::copy(std::begin(testcase), std::end(testcase), std::begin(st.a));
    st.n = testcase_size;

    // precomputing sparse tree
    st.buildST();
    // pass queries of form [l,r]
    assert(st.query(1, 9) == 1);  // as 1 is smallest from 1..9
    assert(st.query(2, 6) == 2);  // as 2 is smallest from 2..6
    assert(st.query(3, 8) == 3);  // as 3 is smallest from 3..8

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
