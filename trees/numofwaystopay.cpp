#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <climits>
#include <bits/stdc++.h>
using namespace std;

int minways(int m, vector<int> denoms)
{
    vector<int> dp(m+1,INT_MAX);
    dp[0]=0;

    for(int i=1;i<=m;i++)
    {
       // dp[i]=INT_MAX;

        for(int c : denoms )
        {
            if(i-c>=0 and dp[i-c]!=INT_MAX)
            dp[i] = min(dp[i],dp[i-c] +1);
        }
    }
    return dp[m] ==INT_MAX? -1: dp[m];
}


int main()
{ vector<int> denmos = {1,5,7,10};
int m ;
cout<<"Enter"<<endl;
cin>>m;
cout<<minways(m,denmos)<<endl;

    return 0;
}