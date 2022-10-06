#include<bits/stdc++.h>
using namespace std;

const int N=1000;
vector<vector<int>> dp(N,vector<int>(N,-1));

int n=2,m=2;
int solution(int i,int j)
{
    if(i==n-1&j==m-1)
    {
        return 1;
    }
    if(dp[i][j]!=-1) return dp[i][j];
    int down=0,right=0;
    if(i+1<n)
    down=solution(i+1,j);
    if(j+1<m)
    right=solution(i,j+1);
    return dp[i][j]=down+right;
}

void tabulation_solution()
{
    vector<vector<int>> ali(N, vector<int>(N,0));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(i==0&&j==0) ali[i][j]=1;
            else
            {
            int left=0,up=0;
            if(j>0) left=ali[i][j-1];
            if(i>0) up=ali[i-1][j];
            ali[i][j]=left+up;
            }
        }
    }
    cout<< ali[n-1][m-1];
}

void space_optimized()
{
    vector<int> any(m,0);
    for(int i=0;i<n;i++)
    {
        vector<int> temp(m,0);
        for(int j=0;j<m;j++)
        {
            if(j==0&&i==0) temp[j]=1;
            else
            {
                int up=0,left=0;
                if(i>0) up=any[j];
                if(j>0) left=temp[j-1];
                temp[j]=up+left;
            }
        }
        any=temp;
    }
    cout<<any[m-1];
}

int main()
{
    cout<<solution(0,0);
    tabulation_solution();
    space_optimized();
}