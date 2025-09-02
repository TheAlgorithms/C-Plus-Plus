/**
 * @file
 * @brief Implementation of Unique Paths problem using
 * Dynamic Programming (Memoization + Tabulation).
 * @details
 * A robot is located at the top-left corner of an m x n grid.
 * The robot can move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner.
 * This program computes the total number of unique paths.
 *
 * @see https://leetcode.com/problems/unique-paths/
 */

#include <iostream>  
#include <vector> 
#include <cassert>   
using namespace std;

/**
 * @namespace dp
 * @brief Dynamic Programming algorithms
 */
namespace dp {

/**
 * @brief Recursive + Memoization solution.
 * @param i Current row index
 * @param j Current column index
 * @param m Number of rows
 * @param n Number of columns
 * @param dp Memoization table
 * @return int Number of unique paths from (i, j) to (m-1, n-1)
 */
int solveMem(int i, int j, int m, int n, vector<vector<int>> &dp) {
    if (i >= m || j >= n) return 0;
    if (i == m - 1 && j == n - 1) return 1;
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = solveMem(i + 1, j, m, n, dp) + solveMem(i, j + 1, m, n, dp);
    return dp[i][j];
}

/**
 * @brief Bottom-up Tabulation solution.
 * @param m Number of rows
 * @param n Number of columns
 * @return int Number of unique paths from (0, 0) to (m-1, n-1)
 */
int solveTab(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) dp[i][n - 1] = 1;  ///< last column paths = 1
    for (int j = 0; j < n; j++) dp[m - 1][j] = 1;  ///< last row paths = 1
    for (int i = m - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1];  ///< from down + right
        }
    }
    return dp[0][0];
}

/**
 * @brief Returns number of unique paths in an m x n grid.
 * @param m Number of rows
 * @param n Number of columns
 * @return int Total number of unique paths
 */
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    // return solveMem(0, 0, m, n, dp);  
    return solveTab(m, n);             

}  // namespace dp

/**
 * @brief Self-test implementations
 */
static void test() {
    assert(dp::uniquePaths(3, 7) == 28);
    assert(dp::uniquePaths(3, 2) == 3);
    assert(dp::uniquePaths(1, 1) == 1);
    assert(dp::uniquePaths(2, 2) == 2);
    cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on successful execution
 */
int main() {
    test();  // run self-tests
    return 0;
}
