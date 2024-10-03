#include<iostream>
#include<vector>

using namespace std;

// Top Down Approach

int recurse(int i,int j,vector<int> &nums,vector<vector<int>> &dp){
    if(i > j){
        return 0;
    }
    if(dp[i][j] != -1) return dp[i][j];
    int maxi = 1e9;
    for(int k = i;k <= j;k++){
        int coins = (nums[i-1] * nums[k] * nums[j+1])+ recurse(i,k-1,nums,dp) + recurse(k+1,j,nums,dp);
        maxi = max(maxi,coins);
    }
    return dp[i][j] = maxi;
}
int maxCoins(vector<int> &nums){
    int n = nums.size();
    nums.insert(nums.begin(),1);
    nums.push_back(1);
    vector<vector<int>> dp(n+2,vector<int>(n+2,-1));
    int ans = recurse(1,n,nums,dp);
    return ans;
}
void solve(){
    int n; // Taking the number of elements in the array
    cin >> n;
    vector<int> nums(n); 
    for(auto &x: nums){
        cin >> x;
    }
    int ans = maxCoins(nums);
    cout << ans << endl;
}
int main(){
    int testcases = 1; // Setting the number of testcases
    // cin >> testcases;
    while(testcases--){
        solve();
    }
    return 0;
}