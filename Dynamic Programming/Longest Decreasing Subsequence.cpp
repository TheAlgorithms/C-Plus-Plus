//Longest decreasing subsequence - Dynamic Programming
#include<iostream>
#include <vector> 
#include<climits>

using namespace std;


int longestDecreasingSub(vector<int> arr){

    int n = arr.size();
    int dp[n]; //dp[i] represents the length of the longest decreasing subsequence till the ith index
    for(int i=0; i<n; i++)
        dp[i] = 1;;
    
    int i = n-1, j = n-2;

    while(j >= 0){
        while(i > j){
            if(arr[j] > arr[i] && (dp[j] < dp[i]+1))
                dp[j] = dp[i]+1;
            i--;
        }
        j--;
        i = n-1;
    }
    int lid = INT_MIN;
    for(int i=0; i<n; i++)
        lid = max(lid, dp[i]);
    
    return lid;
}

int main(){ 
    vector<int> arr = {5,0,3,2,1,8};
    cout << longestDecreasingSub(arr) << endl;

    return 0;
}   