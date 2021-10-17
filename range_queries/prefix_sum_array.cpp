/**
 * @file
 * @brief
 * [Prefix Sum
 * Array](https://en.wikipedia.org/wiki/Prefix_sum) data structure
 * implementation.
 *
 * @details
 * Prefix Sum Array is a data structure, that allows answering sum in some range
 * queries. It can answer most sum range queries in O(1), with a build time
 * complexity of O(N). But it hasn't an update querie.
 *
 * * Running Time Complexity \n
 * * Build : O(N) \n
 * * Range Query : O(1) \n
 * @author [Paulo Vitor Lima Borges](https://github.com/PauloVLB)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace range_queries
 * @brief Range Queries algorithms
 */
namespace range_queries {
/**
 * @namespace prefix_sum_array
 * @brief Range sum queries using prefix-sum-array
 */
namespace prefix_sum_array {

std::vector<int64_t> PSA(1, 0);

/**
 * @brief function that builds the PSA
 * @param original_array original array of values
 * @returns void
 */
void build(std::vector<int64_t> original_array) {
    for (int i = 1; i <= static_cast<int>(original_array.size()); i++) {
        PSA.push_back(PSA[i - 1] + original_array[i]);
    }
}
/**
 * @brief query function
 * @param beg begin of the interval to sum
 * @param end end of the interval to sum
 * @returns sum of the range [beg, end]
 */
int64_t query(int64_t beg, int64_t end) { return PSA[end] - PSA[beg - 1]; }

}  // namespace prefix_sum_array
}  // namespace range_queries

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::vector<int64_t> values{0,  123, 0,  2,  -2, 5,
                                24, 0,   23, -1, -1};  // original array

    range_queries::prefix_sum_array::build(values);
    // queries are of the type: sum of the range [a, b] = psa[b] - psa[a-1]

    assert(range_queries::prefix_sum_array::query(1, 10) ==
           173);  // sum of the entire array
    assert(range_queries::prefix_sum_array::query(4, 6) ==
           27);  // the sum of the interval [4, 6]
    assert(range_queries::prefix_sum_array::query(5, 9) ==
           51);  // the sum of the interval [5, 9]
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
