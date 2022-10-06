// at most k transactions
// using this we can easily solve for 2 transactions

// at each we have 2 situations
// 1. we own a stock
// ----> We can sell it if we have transactions > 0
// ----> We don't sell it
// 2. we do not own a stock
// ----> We buy a stock
// ----> We don't buy a stock

// states -> [day][own][transactions]

// recurrence relation
// 1. dp[i][own][transactions] = max(A[i] + dp[i + 1][!own][transactions - 1], dp[i + 1][own][transactions]);
// 2. dp[i][!own][transactions] = max(-A[i] + dp[i + 1][own][transactions], dp[i + 1][!own][transactions]);

class Solution
{
    int dp[1001][2][101];

    int solve(int day, bool own, int transactions, vector<int> &A)
    {
        if (day == A.size() || transactions == 0)
            return 0;
        if (dp[day][own][transactions] != -1)
            return dp[day][own][transactions];

        if (own)
        {
            int sell = A[day] + solve(day + 1, 0, transactions - 1, A);
            int doNotSell = solve(day + 1, 1, transactions, A);
            return dp[day][own][transactions] = max(sell, doNotSell);
        }

        int buy = -A[day] + solve(day + 1, 1, transactions, A);
        int doNotBuy = solve(day + 1, 0, transactions, A);
        return dp[day][own][transactions] = max(buy, doNotBuy);
    }

public:
    int maxProfit(int k, vector<int> &prices)
    {
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, k, prices);
    }
};