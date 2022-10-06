// at most 2 transactions
// refer next solution

class Solution
{
    int dp[100001][2][3];

    int solve(int day, bool own, int k, vector<int> &A)
    {
        if (day == A.size() || k == 0)
            return 0;
        if (dp[day][own][k] != -1)
            return dp[day][own][k];

        if (own)
        {
            int sell = A[day] + solve(day + 1, 0, k - 1, A);
            int doNotSell = solve(day + 1, 1, k, A);
            return dp[day][own][k] = max(sell, doNotSell);
        }

        int buy = -A[day] + solve(day + 1, 1, k, A);
        int doNotBuy = solve(day + 1, 0, k, A);
        return dp[day][own][k] = max(buy, doNotBuy);
    }

public:
    int maxProfit(vector<int> &prices)
    {
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, 2, prices);
    }
};