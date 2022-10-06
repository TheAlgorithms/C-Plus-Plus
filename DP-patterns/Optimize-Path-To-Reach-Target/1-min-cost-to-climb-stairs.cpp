/*
    dp[i] => min cost to reach ith stair
    we can come to the ith position by either climbing 1 step or 2 steps
    therefore,
        dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        
    since there are 'n-1' stairs, target = nth stair i.e dp[n]
    
    since, we can start from 0th or 1st index, min cost to reach 0th or 1st index = 0
    therefore, dp[0] = dp[1] = 0
*/

class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        int dp[n + 1];
        dp[0] = 0;
        dp[1] = 0;

        for (int i = 2; i <= n; ++i)
        {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }

        return dp[n];
    }
};