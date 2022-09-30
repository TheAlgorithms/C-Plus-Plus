#include<bits/stdc++.h>

using namespace std;

int maxProfit(vector<int>& prices) {
    int minVal = prices[0];
    int maxProfit = 0;
    for (int i = 1; i < prices.size(); i++){
        int profit = prices[i] - minVal;
        maxProfit = max(maxProfit, profit);
        minVal = min(minVal, prices[i]);
    }

    return maxProfit;
}

int main(){
    vector<int> prices {7,1,5,3,6,4};
    cout<<maxProfit(prices);

    return 0;
}