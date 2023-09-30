#include<bits/stdc++.h>
using namespace std;
int solve(string s){
    int n=s.size();
    if(n==0) return 0;
    vector<int>dp(n,0);
    int res=0;
    if(s[0]=='(' and s[1]==')') dp[1]=2;
    for(int i=2;i<s.size();i++){
        if(s[i]==')'){
            if(s[i-1]=='('){
                dp[i]=dp[i-2]+2;
            }
            else{
                if(s[i-dp[i-1]-1]=='(' and i-dp[i-1]>0){
                    dp[i]=dp[i-1]+((i-dp[i-1])>=2?dp[i-dp[i-1]-2]:0)+2;
                }
            }
        }
    }
    return *max_element(dp.begin(),dp.end());
}
int main(){
    string s;
    cin>>s;
    cout<<solve(s);
    return 0;
}