// Unlimited transactions with fee
// at ith day we have 2 situations
// 1. we own a stock -> we have a choice to sell or don't sell
// 2. we do not own a stock -> we have a choice buy or don't buy

// dp[i][own] = max(dp[i + 1][own], prices[i] + dp[i + 1][!own]);
// dp[i][!own] = max(dp[i + 1][!own], -(prices[i] + fee) + dp[i + 1][own]);

class Solution
{
    int dp[50001][2];
    int solve(vector<int> &A, int fee, int idx, int own)
    {
        if (idx == A.size())
            return 0;
        if (dp[idx][own] != -1)
            return dp[idx][own];

        int res;

        if (own)
            res = max(solve(A, fee, idx + 1, 1), A[idx] + solve(A, fee, idx + 1, 0));
        else
            res = max(solve(A, fee, idx + 1, 0), -(A[idx] + fee) + solve(A, fee, idx + 1, 1));

        return dp[idx][own] = res;
    }

public:
    int maxProfit(vector<int> &prices, int fee)
    {
        memset(dp, -1, sizeof(dp));
        return solve(prices, fee, 0, 0);
    }
};