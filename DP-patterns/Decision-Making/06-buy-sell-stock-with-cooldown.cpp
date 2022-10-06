// 3 dp states
// dp[day][own][cooldown]

// dp[day][!own][cooldown] = cannot buy on this day
// dp[day][!own][!cooldown] = we may or may not buy on this day
// dp[day][own][x] = we may or may not sell on this day (cooldown has no relevance here)

class Solution
{
    int dp[5001][2][2];
    int solve(vector<int> &A, int day, bool own, bool cooldown)
    {
        if (day == A.size())
            return 0;
        if (dp[day][own][cooldown] != -1)
            return dp[day][own][cooldown];

        if (own)
        {
            int sell = A[day] + solve(A, day + 1, 0, 1);
            int doNotSell = solve(A, day + 1, 1, 0);
            return dp[day][own][cooldown] = max(sell, doNotSell);
        }

        int doNotBuy = solve(A, day + 1, 0, 0);
        int buy = cooldown ? 0 : -A[day] + solve(A, day + 1, 1, 0);
        return dp[day][own][cooldown] = max(buy, doNotBuy);
    }

public:
    int maxProfit(vector<int> &prices)
    {
        memset(dp, -1, sizeof(dp));
        return solve(prices, 0, 0, 0);
    }
};