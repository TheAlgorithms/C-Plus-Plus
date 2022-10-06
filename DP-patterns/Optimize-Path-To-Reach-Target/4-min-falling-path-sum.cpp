/*
    dp[i][j] -> be the minimum falling path sum at i,j position
    
    since, we can come to a position dp[i][j] using only 3 paths
    1) i-1, j-1
    2) i-1, j
    3) i-1, j+1
    
    therefore, dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i+1][j]) + cost[i][j]
    
    we have to return min element in dp[m-1][0.......n]
    i.e the min element in the last row pf dp array
*/

class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &dp)
    {
        int n = dp.size();
        if (n == 1)
            return dp[0][0];

        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                dp[i][j] += min(dp[i - 1][j], min(dp[i - 1][max(0, j - 1)], dp[i - 1][min(n - 1, j + 1)]));

                // if(j == 0) {
                //     dp[i][j] += min(dp[i - 1][j], dp[i - 1][j + 1]);
                // } else if(j == n - 1) {
                //     dp[i][j] += min(dp[i - 1][j - 1], dp[i - 1][j]);
                // } else {
                //     dp[i][j] += min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i - 1][j + 1]));
                // }
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};