#include<bits/stdc++.h>
using namespace std;
bool comparebox(vector<int>v1, vector<int>v2){
    return v1[2]<v2[2];
}
bool canPlace(vector<int> v1,vector<int> v2){
    if(v1[0]>v2[0] and v1[1]>v2[1] and v1[2]>v2[2])
        return true;
    return false;
}

int box_stacking_problem(vector<vector<int>> arr){
    int n=arr.size();
    vector<int> dp(n,0);
    sort(arr.begin(),arr.end(),comparebox);
    //cout<<arr[6][2];
    for(int i=0;i<n;i++){
        dp[i]=arr[i][2];
    }
    int max_height=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(canPlace(arr[i],arr[j])){
                int current_height=arr[i][2];
                if(dp[j]+current_height>dp[i]){
                    dp[i]=dp[j]+current_height;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<dp[i]<<" ";
        max_height=max(dp[i],max_height);
    }
    cout<<endl;
    return max_height;
}
int main(){
    vector<vector<int>> arr={
            {2,1,2},
            {3,2,3},
            {2,2,8},
            {2,3,4},
            {2,2,1},
            {4,4,5},
    };
    cout<<box_stacking_problem(arr);
}
