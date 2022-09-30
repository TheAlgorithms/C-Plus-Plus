#include<bits/stdc++.h>

using namespace std;

int f(vector<int>& prices, int n, int i, bool buy, vector<vector<int>>& dp){
    if (i >= n) return 0;

    int profit = 0;
    if (buy && i < n)
        profit = max(-prices[i] + f(prices, n, i + 1, !buy, dp), f(prices, n, i + 1, buy, dp));
    else if (i < n)
        profit = max(prices[i] + f(prices, n, i + 2, !buy, dp), f(prices, n, i + 1, buy, dp));

    return profit;
}

int maxProfit(vector<int>& prices){
    int n = prices.size();
    vector<int> front2(2, 0);
    vector<int> front1(2, 0);
    vector<int> curr(2, 0);
    for (int i = n - 1; i >= 0; i--){
            curr[1] = max(-prices[i] + front1[0], front1[1]);
            curr[0] = max(prices[i] + front2[1], front1[0]);
            front2 = front1;
            front1 = curr;
    }
    return front1[1];
}

int main(){
    vector<int> prices {1,2,3,0,2};
    cout<<maxProfit(prices);

    return 0;
}