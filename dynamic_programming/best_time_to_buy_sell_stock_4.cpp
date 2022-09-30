#include<bits/stdc++.h>

using namespace std;

int f(vector<int>& prices, int n, int k, int i, int trans, vector<vector<int>>& dp){
    if (trans == 2 * k || i == n) return 0;
    if (dp[i][trans] != -1) return dp[i][trans];

    int profit = 0;
    if (trans % 2 == 0){
        profit = max(-prices[i] + f(prices, n, k, i + 1, trans + 1, dp), f(prices, n, k, i + 1, trans, dp));
    }
    else{
        profit = max(prices[i] + f(prices, n, k, i + 1, trans + 1, dp), f(prices, n, k, i + 1, trans, dp));
    }

    return dp[i][trans] = profit;
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<int> prev(2 * k + 1, 0);
    for (int i = n - 1; i >= 0; i--){
        for (int trans = 2 * k - 1; trans >= 0; trans--){
            int profit = 0;
            if (trans % 2 == 0)
                profit = max(-prices[i] + prev[trans + 1], prev[trans]);
            else
                profit = max(prices[i] + prev[trans + 1], prev[trans]);

            prev[trans] = profit;
        }
    }

    return prev[0];
}

int main(){
    int k = 2;
    vector<int> prices {3,2,6,5,0,3};
    cout<<maxProfit(k, prices);

    return 0;
}