#include<bits/stdc++.h>

using namespace std;

int f(vector<int>& prices, int n, int i, bool buy, int cap, vector<vector<vector<int>>>& dp){
    if (!cap || i == n) return 0;

    if (dp[i][buy][cap] != -1) return dp[i][buy][cap];

    int profit = 0;
    if (buy)
        profit = max(-prices[i] + f(prices, n, i + 1, !buy, cap, dp), f(prices, n, i + 1, buy, cap, dp));
    else
        profit = max(prices[i] + f(prices, n, i + 1, !buy, cap - 1, dp), f(prices, n, i + 1, buy, cap, dp));

    return dp[i][buy][cap] = profit;
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> prev(2, vector<int>(3, 0));
    for (int i = n - 1; i >= 0; i--){
        vector<vector<int>> curr(2, vector<int>(3, 0));
        for (int buy = 0; buy <= 1; buy++){
            for (int cap = 1; cap <= 2; cap++){
                int profit = 0;
                if (buy)
                    profit = max(-prices[i] + prev[!buy][cap], prev[buy][cap]);
                else
                    profit = max(prices[i] + prev[!buy][cap - 1], prev[buy][cap]);

                curr[buy][cap] = profit;
            }
            prev = curr;
        }
    }

    return prev[1][2];
}

int main(){
    vector<int> prices {3,3,5,0,0,3,1,4};
    cout<<maxProfit(prices);

    return 0;
}