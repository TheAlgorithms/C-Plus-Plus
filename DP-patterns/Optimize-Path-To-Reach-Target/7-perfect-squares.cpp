/*
    let dp[i] be the min number of perfect sq that sum up to 'i'
    
    how can we reach 'i'?
    dp[i] = 1 + dp[i - (some perfect sq <= i)]
    for all valid perfect squares
    
    return dp[target]
*/

class Solution
{
public:
    int numSquares(int n)
    {
        int dp[n + 1];
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            dp[i] = INT_MAX;

            // find all perf sqs <= i
            for (int j = 1; j * j <= i; ++j)
            {
                dp[i] = min(dp[i], 1 + dp[i - j * j]);
            }
        }

        return dp[n];
    }
};