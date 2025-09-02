#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int solveMem(int i, int j, int m, int n, vector<vector<int>> &dp) {
    if (i >= m || j >= n) return 0;
    if (i == m - 1 && j == n - 1) return 1;
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = solveMem(i + 1, j, m, n, dp) + solveMem(i, j + 1, m, n, dp);
    return dp[i][j];
}

int solveTab(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) dp[i][n - 1] = 1;  // last column paths = 1
    for (int j = 0; j < n; j++) dp[m - 1][j] = 1;  // last row paths = 1
    for (int i = m - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1];  // paths from right + down
        }
    }
    return dp[0][0];
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    // return solveMem(0, 0, m, n, dp);
    return solveTab(m, n);
}

static void test() {
    assert(uniquePaths(3, 7) == 28);
    assert(uniquePaths(3, 2) == 3);
    assert(uniquePaths(1, 1) == 1);
    assert(uniquePaths(2, 2) == 2);
    cout << "All tests have successfully passed!\n";
}

int main() {
    test();  // run self-tests
    return 0;
}
