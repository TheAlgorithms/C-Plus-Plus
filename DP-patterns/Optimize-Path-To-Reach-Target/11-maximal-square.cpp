class Solution
{
public:
    int maximalSquare(vector<vector<char>> &mat)
    {
        int mx = 0, m = mat.size(), n = mat[0].size();
        int dp[m][n];
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (mat[i][j] == '1')
                {
                    mx = 1;
                    dp[i][j] = 1;
                }

        // solve for matrix
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                if (mat[i][j] == '1')
                {
                    dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
                    mx = max(mx, dp[i][j]);
                }

        return mx * mx;
    }
};