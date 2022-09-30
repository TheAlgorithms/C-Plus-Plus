#include<bits/stdc++.h>

using namespace std;

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<int> prev(2, 0);
    vector<int> curr(2, 0);
    for (int i = n - 1; i >= 0; i--){
            curr[1] = max(-prices[i] + prev[0], prev[1]);
            curr[0] = max(prices[i] - fee + prev[1], prev[0]);
            prev = curr;
    }
    return prev[1];
}

int main(){
    vector<int> prices {1,3,2,8,4,9};
    int fee = 2;
    cout<<maxProfit(prices, fee);

    return 0;
}