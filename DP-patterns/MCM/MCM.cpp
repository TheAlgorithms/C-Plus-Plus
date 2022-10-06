// https : //www.youtube.com/watch?v=pEYwLmGJcvs

class Solution
{
public:
    int matrixMultiplication(int N, int arr[])
    {
        int n = N - 1;
        int dp[n][n];
        memset(dp, 0, sizeof(dp));

        for (int g = 0; g < n; ++g)
        {
            for (int l = 0, r = g; r < n; ++l, ++r)
            {
                if (g == 0)
                    dp[l][r] = 0;
                else if (g == 1)
                    dp[l][r] = arr[l] * arr[r] * arr[r + 1];
                else
                {
                    dp[l][r] = INT_MAX;
                    for (int k = l; k < r; ++k)
                    {
                        // left half l, k => dimensions arr[l], arr[k + 1]
                        // right half k + 1, r => dimensions arr[k + 1], arr[r]
                        dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + arr[l] * arr[k + 1] * arr[r + 1]);
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};