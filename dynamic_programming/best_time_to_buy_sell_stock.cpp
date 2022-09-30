#include<bits/stdc++.h>

using namespace std;

// We iterate through the array just once
// During the iteration we maintain a minVal at all times which has the minimum value for the array
// As we can only sell after the minVal is found or on the same day, we check for all days following the
// minVal if they give th maxProfit
int maxProfit(vector<int>& prices) {
    // minVal is initialized as first item
    int minVal = prices[0];
    // maxProfit is minimum possible value i.e. 0
    int maxProfit = 0;
    for (int i = 1; i < prices.size(); i++){
        int profit = prices[i] - minVal;
        // We check if the minVal gives better profit for the current value
        maxProfit = max(maxProfit, profit);
        // If the current value is minimum yet, the minVal is changed
        minVal = min(minVal, prices[i]);
    }

    return maxProfit;
}

int main(){
    vector<int> prices {7,1,5,3,6,4};
    cout<<maxProfit(prices);

    return 0;
}