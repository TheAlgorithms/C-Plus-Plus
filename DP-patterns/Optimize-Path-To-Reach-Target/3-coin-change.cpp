/*
    statement - min coins to reach target
    
    let coins = {a, b, c}
    let dp[i] = min coins to reach 'i'
    
    since, i can be made using i-a, i-b, i-c
    
    for(k : a, b, c)
        dp[i] = min(dp[i], dp[i - k] + 1)
    
    return dp[target]
*/

class Solution
{
public:
    int coinChange(vector<int> &coins, int target)
    {
        int dp[target + 1];

        for (int i = 1; i <= target; ++i)
            dp[i] = INT_MAX - 1;

        dp[0] = 0;

        for (int i = 1; i <= target; ++i)
        {
            for (auto &k : coins)
            {
                if (k <= i)
                {
                    dp[i] = min(dp[i], dp[i - k] + 1);
                }
            }
        }

        return dp[target] == INT_MAX - 1 ? -1 : dp[target];
    }
};