/*
    let, dp[i] = min dollors you need to travel till ith day
    we can reach here by 3 options,
    1) 1 day plan
        dp[i] = dp[i - 1] + cost[1 day plan]
    2) 7 day plan
        dp[i] = max(0th day or dp[i - 7]) + cost[7 day plan]
    3) 30 day plan
        dp[i] = max(0th day or dp[i - 30]) + cost[30 day plan]
    
    return dp[n]
*/

class Solution
{
public:
    int mincostTickets(vector<int> &days, vector<int> &cost)
    {
        unordered_set<int> st(days.begin(), days.end());
        int n = days.back(); // the last day of travel

        int dp[n + 1];
        dp[0] = 0; // initial cost = 0

        for (int i = 1; i <= n; ++i)
        {
            if (st.find(i) == st.end())
                dp[i] = dp[i - 1]; // as it's not necesarry to travel on said day
            else
            {
                int op1 = dp[i - 1] + cost[0];          // day option
                int op2 = dp[max(0, i - 7)] + cost[1];  // 7 day option
                int op3 = dp[max(0, i - 30)] + cost[2]; // 30 day option
                dp[i] = min(op1, min(op2, op3));        // take min of all options
            }
        }

        return dp[n];
    }
};