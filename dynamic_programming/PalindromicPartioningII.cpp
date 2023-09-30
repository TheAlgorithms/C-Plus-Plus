#include<bits/stdc++.h>
using namespace std;
int solve(string s){
    int n=s.length();
    if(n==0) return 0;
    int a[n][n];
    for(int i=n-1;i>=0;i--){
        for(int j=i;j<n;j++){
            if(i==j){ 
                a[i][j]=1;
            }
            else if(j==i+1){
                if(s[i]==s[j]) a[i][j]=1;
                else a[i][j]=0;
            }
            else{
                if(s[i]==s[j]) a[i][j]=a[i+1][j-1];
                else a[i][j]=0;
            }
        }
    }
    int dp[n];
    dp[0]=0;
    for(int i=1;i<n;i++){
        dp[i]=INT_MAX;
        for(int j=i;j>=0;j--){
            if(a[j][i]==1 and j!=0){
                dp[i]=min(dp[i],1+dp[j-1]);
            }
            if(a[j][i]==1 and j==0){
                dp[i]=0;
            }
        }
    }
    return dp[n-1];
}
int main(){
    string s;
    cin>>s;
    cout<<solve(s);
}