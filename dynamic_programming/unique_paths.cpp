/**
 * @file
 * @brief Implementation of Unique Paths (LeetCode 62) using Dynamic Programming.
 * @details
 * A robot is located at the top-left corner of an m × n grid.
 * The robot can move either down or right at any point in time.
 * This program computes the total number of unique paths to reach
 * the bottom-right corner.
 *
 * Note: This is **Unique Paths I** (no obstacles). Obstacles are handled in
 * the separate problem **Unique Paths II**.
 *
 * Approaches:
 * - **Memoization (Top-Down)**: Recursively explores solutions while
 *   storing intermediate results in a cache (`memoization_table`) to avoid redundant
 *   computation. Typically more intuitive and easy to write, but
 *   relies on recursion and has associated call-stack overhead.
 *
 * - **Tabulation (Bottom-Up)**: Iteratively builds the solution using
 *   a DP table, starting from the base cases and filling up the table.
 *   Offers consistent performance without recursion overhead and
 *   is generally more space-efficient when optimized.
 *
 * @see https://leetcode.com/problems/unique-paths/
 */

#include <iostream>
#include <vector>
#include <cassert>

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {

/**
 * @class UniquePathsSolver
 * @brief Solves the Unique Paths problem using both memoization and tabulation.
 */
class UniquePathsSolver {
   private:
    std::vector<std::vector<int>> memoization_table;  ///< Memoization table to cache intermediate results (-1 = uncomputed)
    std::size_t m;  ///< Number of rows in the grid
    std::size_t n;  ///< Number of columns in the grid

    /**
     * @brief Bottom-up Tabulation solution.
     * @return int Number of unique paths from (0, 0) to (m-1, n-1)
     */
    int solveTabulation() {
        std::vector<std::vector<int>> table(m, std::vector<int>(n, 0));

        // base cases: last column and last row
        for (std::size_t i = 0; i < m; i++) table[i][n - 1] = 1;
        for (std::size_t j = 0; j < n; j++) table[m - 1][j] = 1;

        // fill the table from bottom-right to top-left
        for (std::size_t i = m - 1; i-- > 0;) {
            for (std::size_t j = n - 1; j-- > 0;) {
                table[i][j] = table[i + 1][j] + table[i][j + 1];
            }
        }
        return table[0][0];
    }

   public:
    /**
     * @brief Constructor initializes dimensions and memoization table
     * @param rows number of rows in the grid (must be > 0)
     * @param cols number of columns in the grid (must be > 0)
     */
    UniquePathsSolver(std::size_t rows, std::size_t cols) : m(rows), n(cols) {
        memoization_table.assign(m, std::vector<int>(n, -1));
    }

    /**
     * @brief Get number of unique paths using Memoization (Top-Down)
     * @param i current row index (default = 0)
     * @param j current column index (default = 0)
     * @return int Number of unique paths from (i, j) to (m-1, n-1)
     */
    int uniquePathsMemo(std::size_t i = 0, std::size_t j = 0) {
        if (i >= m || j >= n) return 0;
        if (i == m - 1 && j == n - 1) return 1;
        if (memoization_table.at(i).at(j) != -1) return memoization_table.at(i).at(j);

        memoization_table.at(i).at(j) =
            uniquePathsMemo(i + 1, j) + uniquePathsMemo(i, j + 1);
        return memoization_table.at(i).at(j);
    }

    /**
     * @brief Get number of unique paths using Tabulation (Bottom-Up)
     * @return int Number of unique paths from (0, 0) to (m-1, n-1)
     */
    int uniquePathsTabulation() { return solveTabulation(); }
};

}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 */
static void test() {
    using namespace dynamic_programming;

    UniquePathsSolver solver1(3, 7);
    assert(solver1.uniquePathsMemo() == 28);
    assert(solver1.uniquePathsTabulation() == 28);

    UniquePathsSolver solver2(3, 2);
    assert(solver2.uniquePathsMemo() == 3);
    assert(solver2.uniquePathsTabulation() == 3);

    UniquePathsSolver solver3(1, 1);
    assert(solver3.uniquePathsMemo() == 1);
    assert(solver3.uniquePathsTabulation() == 1);

    UniquePathsSolver solver4(2, 2);
    assert(solver4.uniquePathsMemo() == 2);
    assert(solver4.uniquePathsTabulation() == 2);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on successful execution
 */
int main() {
    test();  // run self-tests
    return 0;
}
