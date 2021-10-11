/*
Qus: * Given weights and values of n items, put these items in a knapsack of
 * capacity `W` to get the maximum total value in the knapsack. In other words,
 * given two integer arrays `val[0..n-1]` and `wt[0..n-1]` which represent
 * values and weights associated with n items respectively. Also given an
 * integer W which represents knapsack capacity, find out the maximum value
 * subset of `val[]` such that sum of the weights of this subset is smaller than
 * or equal to W. You cannot break an item, either pick the complete item or
 * don’t pick it (0-1 property)
 *
 * ### Algorithm
 * The idea is to consider all subsets of items and calculate the total weight
 * and value of all subsets. Consider the only subsets whose total weight is
 * smaller than `W`. From all such subsets, pick the maximum value subset.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    // write your code here
    ll n,wi;
    cin>>n;
    ll weighs[n];
    for(int i=0;i<n;i++){
        cin>>weighs[i];
    }
    ll vals[n];
    for(int j=0;j<n;j++){
        cin>>vals[j];
    }
    cin>>wi;
    ll dp[2][wi+1]={0};//here I am taking the knapsack as 2d array rather taking a multi dimensional array of n*wi
    for(int i=0;i<2;i++){
        for(int j=0;j<=wi;j++)
            dp[i][j]=0;//initialising the 2d array here
    }
    int curr,other;
    curr=0;
    other=1;
    for(ll i=0;i<n;i++){
        for(ll j=1;j<=wi;j++){
            if(j>=weighs[i]){
                dp[curr][j]=max(dp[other][j-weighs[i]]+vals[i],max(dp[other][j],dp[curr][j-1]));// now i can include the curr bag when there is a space and space is only in 
            }//the bag which is greater than weighs[i] also i will have three values to compare with one which is the previous value of current weight other on s the new value 
          //and other one is value of previous weight
          // if the ith item's weight(in actual array it will be at i-1)
                // is less than or equal to the allowed weight i.e. j then we
                // can pick that item for our knapsack. maxValue will be the
                // obtained either by picking the current item or by not picking
                // current item
            else{
                dp[curr][j]=dp[other][j];// as weight of current item is greater than allowed weight, so
                // maxProfit will be profit obtained by excluding current item
            }
        }
        swap(curr,other);//switching the rows and only taking care of the previous row and moving to current row
    }
    cout<<dp[other][wi]<<endl;
    return 0;
}
