/*
    Path Optimisation problem
    
    dp[i][j] be the min path sum till i, j from top
    there are 2 ways to arrive at dp[i][j]
    
    1) i - 1, j
    2) i - 1, j - 1
    
    dp[i][j] = min(dp[i-1][j], dp[i-1][j-1])
    (take extra care of edge cases)
*/

class Solution
{
public:
    int minimumTotal(vector<vector<int>> &dp)
    {
        int m = dp.size(), n = dp.back().size();

        for (int i = 1; i < m; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                dp[i][j] += min(dp[i - 1][max(0, j - 1)], dp[i - 1][min(i - 1, j)]);
            }
        }

        return *min_element(dp[m - 1].begin(), dp[m - 1].end());
    }
};