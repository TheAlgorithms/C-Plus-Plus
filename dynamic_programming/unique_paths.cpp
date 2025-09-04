/**
 * @file
 * @brief Implementation of Unique Paths problem using Dynamic Programming.
 * @details
 * A robot is located at the top-left corner of an m × n grid.
 * The robot can move either down or right at any point in time.
 * This program computes the total number of unique paths to reach
 * the bottom-right corner.
 *
 * Approaches:
 * - **Memoization (Top-Down)**: Recursively explores solutions while
 *   storing intermediate results in a cache (`dp`) to avoid redundant
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
    std::vector<std::vector<int>> dp;  ///< Memoization table
    int m, n;

    /**
     * @brief Bottom-up Tabulation solution.
     * @return int Number of unique paths from (0, 0) to (m-1, n-1)
     */
    int solveTab() {
        std::vector<std::vector<int>> table(m, std::vector<int>(n, 0));

        for (int i = 0; i < m; i++) table[i][n - 1] = 1;  ///< last column
        for (int j = 0; j < n; j++) table[m - 1][j] = 1;  ///< last row

        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                table[i][j] = table[i + 1][j] + table[i][j + 1];
            }
        }
        return table[0][0];
    }

   public:
    /**
     * @brief Constructor initializes dimensions and memo table
     */
    UniquePathsSolver(int rows, int cols) : m(rows), n(cols) {
        dp.assign(m, std::vector<int>(n, -1));
    }

    /**
     * @brief Get number of unique paths using Memoization (Top-Down)
     */
    int uniquePathsMemo(int i = 0, int j = 0) {
        if (i >= m || j >= n) return 0;
        if (i == m - 1 && j == n - 1) return 1;
        if (dp.at(i).at(j) != -1) return dp.at(i).at(j);

        dp.at(i).at(j) = uniquePathsMemo(i + 1, j) + uniquePathsMemo(i, j + 1);
        return dp.at(i).at(j);
    }

    /**
     * @brief Get number of unique paths using Tabulation (Bottom-Up)
     */
    int uniquePathsTab() { return solveTab(); }
};

}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 */
static void test() {
    using namespace dynamic_programming;

    UniquePathsSolver solver1(3, 7);
    assert(solver1.uniquePathsMemo() == 28);
    assert(solver1.uniquePathsTab() == 28);

    UniquePathsSolver solver2(3, 2);
    assert(solver2.uniquePathsMemo() == 3);
    assert(solver2.uniquePathsTab() == 3);

    UniquePathsSolver solver3(1, 1);
    assert(solver3.uniquePathsMemo() == 1);
    assert(solver3.uniquePathsTab() == 1);

    UniquePathsSolver solver4(2, 2);
    assert(solver4.uniquePathsMemo() == 2);
    assert(solver4.uniquePathsTab() == 2);

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
