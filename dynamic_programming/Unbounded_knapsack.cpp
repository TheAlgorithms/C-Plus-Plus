/* 
The Unbounded Knapsack problem allows you to take unlimited quantities of each item. The goal is to maximize the total value 
without exceeding the given knapsack capacity. Unlike the 0/1 knapsack, where each item can be taken only once, in this 
variation, you can pick any item as many times as needed, as long as the total weight stays within the knapsack's capacity. 
The problem is commonly solved using dynamic programming.

TASK - Given a set of N items, each with a weight and a value, represented by the array wt and val respectively. Also, a knapsack with weight limit W.
The task is to fill the knapsack in such a way that we can get the maximum profit. Return the maximum profit.
Note: Each item can be taken any number of times.

Test Cases -
Input: 
N = 4, W = 8, val[] = {6, 1, 7, 7}, wt[] = {1, 3, 4, 5}
Output:
48
*/

// Code
#include <bits/stdc++.h>
using namespace std;

int KnapSackFilling(int i,int W, vector<int> val,vector<int> wt, vector<vector<int>> &dp){
    if(i==0){
        if(wt[0]<=W){
            return (W/wt[0])*val[0];
        }else{
            return 0;
        }
     }
     if(dp[i][W]!=-1)return dp[i][W];
     int nottake=KnapSackFilling(i-1,W,val,wt,dp);
     int take=0;
     if(W>=wt[i]){
         take=val[i]+KnapSackFilling(i,W-wt[i],val,wt,dp);
     }
     return dp[i][W]=max(take,nottake);
}
int unboundedKnapsack(int N, int W, vector<int> val, vector<int> wt)
{
    vector<vector<int>> dp(N,vector<int>(W+1,-1));
    return KnapSackFilling(N-1,W,val,wt,dp);
}
int main() {
    int N;
    N=4;
    vector<int> wt= {1, 3, 4, 5};
    vector<int> val= {6, 1, 7, 7}; 
    int W = 8;
  
    cout << "The Maximum value of items is " << unboundedKnapsack(N, W, val, wt) << endl;

    return 0; 
}

