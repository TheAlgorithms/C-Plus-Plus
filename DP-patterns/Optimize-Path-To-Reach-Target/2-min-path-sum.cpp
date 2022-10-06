/*
    let, dp[i][j] be the min path sum at i, j
    there are only 2 ways to reach the i, j position
    i.e
        1) from i-1, j (from the top)
        2) from i, j-1 (from the left)
    
    therefore, dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + cost[i][j];
    
    since, we have to reach m-1, n-1 position, 
    dp[m-1][n-1] will have our final answer
*/

class Solution
{
public:
    int minPathSum(vector<vector<int>> &g)
    {
        int m = g.size(), n = g[0].size();
        int dp[m][n];
        dp[0][0] = g[0][0];

        for (int i = 1; i < n; ++i)
            dp[0][i] = dp[0][i - 1] + g[0][i];

        for (int i = 1; i < m; ++i)
        {
            dp[i][0] = dp[i - 1][0] + g[i][0];

            for (int j = 1; j < n; ++j)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + g[i][j];
            }
        }

        return dp[m - 1][n - 1];
    }
};

// SPACE OPTIMIZATION
// SPACE OPTIMIZATION
class Solution
{
public:
    int minPathSum(vector<vector<int>> &g)
    {
        int m = g.size(), n = g[0].size();

        for (int i = 1; i < n; ++i)
            g[0][i] += g[0][i - 1];

        for (int i = 1; i < m; ++i)
            g[i][0] += g[i - 1][0];

        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                g[i][j] += min(g[i - 1][j], g[i][j - 1]);

        return g[m - 1][n - 1];
    }
};