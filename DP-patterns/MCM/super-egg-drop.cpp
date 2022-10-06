// TODO -> EFFICIENT APPROACHES

// BRUTE DP
class Solution
{
public:
    int superEggDrop(int e, int f)
    {
        int dp[e + 1][f + 1];
        memset(dp[0], 0, sizeof(dp[0]));

        // for 1 egg
        iota(dp[1], dp[1] + f + 1, 0);

        // for 0f and 1f
        for (int i = 1; i <= e; ++i)
        {
            dp[i][0] = 0;
            dp[i][1] = 1;
        }

        for (int i = 2; i <= e; ++i)
        {
            for (int j = 2; j <= f; ++j)
            {
                dp[i][j] = INT_MAX;
                int mn = INT_MAX;

                for (int k = 1; k <= j; ++k)
                {
                    int survive = dp[i][j - k];
                    int breaks = dp[i - 1][k - 1];

                    mn = min(mn, max(survive, breaks));
                }

                dp[i][j] = 1 + mn;
            }
        }

        return dp[e][f];
    }
};