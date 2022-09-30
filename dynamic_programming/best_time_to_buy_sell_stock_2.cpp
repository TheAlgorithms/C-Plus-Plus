#include<bits/stdc++.h>

using namespace std;

// Memoization Solution
// Time Complexity - O(N * 2)
// Space Complexity - O(N * 2) + Auxiliary Stack Space O(N)
int f(vector<int>& prices, int n, int i, bool buy, vector<vector<int>>& dp){
    if (i == n - 1){
        if (!buy) return prices[i];
        return 0;
    }

    if (dp[i][buy] != -1) return dp[i][buy];

    int profit = 0;
    if (buy)
        profit = max(-prices[i] + f(prices, n, i + 1, !buy, dp), f(prices, n, i + 1, buy, dp));
    else
        profit = max(prices[i] + f(prices, n, i + 1, !buy, dp), f(prices, n, i + 1, buy, dp));

    return dp[i][buy] = profit;
}

// Dynamic Programming solution using 2D Matrix
// Time Complexity - O(N * 2)
// Space Complexity - O(N * 2)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[n - 1][0] = prices[n - 1];

    for (int i = n - 2; i >= 0; i--){
        for (int buy = 0; buy < 2; buy++){
            int profit = 0;
            if (buy){
                profit = max(-prices[i] + dp[i + 1][!buy], dp[i + 1][buy]);
            }
            else{
                profit = max(prices[i] + dp[i + 1][!buy], dp[i + 1][buy]);
            }
            dp[i][buy] = profit;
        }
    }

    return dp[0][1];
}

// Space Optimized DP with only two 1D arrays
// Time Complexity - O(N * 2)
// Space Complexity - O(N)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<int> prev(2, 0);
    prev[0] = prices[n - 1];

    for (int i = n - 2; i >= 0; i--){
        for (int buy = 0; buy < 2; buy++){
            int profit = 0;
            if (buy){
                profit = max(-prices[i] + prev[!buy], prev[buy]);
            }
            else{
                profit = max(prices[i] + prev[!buy], prev[buy]);
            }
            prev[buy] = profit;
        }
    }

    return prev[1];
}

int main(){
    vector<int> prices {7,1,5,3,6,4};
    cout<<maxProfit(prices);

    return 0;
}