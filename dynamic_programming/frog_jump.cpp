// Code for memoization of frog jump from 1 to k steps 

#include<bits/stdc++.h>
using namespace std;

const int N=1e5;
vector<int> temp(N,-1);

int solution(int idx,int k,vector<int> height)
{
    if(idx==0)  return 0;
    if(temp[idx]!=-1) return temp[idx];
    int ans=INT_MAX;
    for(int i=0;i<k;i++)
    {
        if(idx-i>=0)
        {
            ans=min(solution(idx-i,k,height)+(height[idx]-height[idx-i]),ans);
        }
    }
    return temp[idx]=ans;
}

// code for tabulation of frog jump

int solution(vector<int> height,int k)
{
    int n=sizeof(height);
    vector<int> dp(n);
    dp[0]=0;
    for(int i=1;i<n;i++)
    {
        int min_step=INT_MAX;
        for(int j=1;j<=k;j++)
        {
            if(i-j>=0)
            min_step=min(min_step,dp[i-j]+abs(height[i]-height[i-j]));
        }
        dp[i]=min_step;
    }

}

int main()
{
    vector<int> height={20,60,50,10,20,90};
    int k;
    cin>>k;
    cout<<solution(6-1,k,height)<<endl;
}