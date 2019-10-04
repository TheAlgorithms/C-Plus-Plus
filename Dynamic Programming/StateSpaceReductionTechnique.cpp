#include <bits/stdc++.h>
using namespace std;

// state space reduction can be used to reduce memory used in program
// used in code that calculate dp[i][j] from dp[i-1][k]
// dp[N][N] to dp[2][N]
// reduce memory from N to 2

const int N = 1e6;

int n,dp[N][N],ss[2][N];

int main()
{
    // normal version of dp using N*N space
    for(int i = 1;i <= n;i++) 
    {
        for(int j = 1;j <= n;j++)
        {
            
            // calculate dp[i][j] from dp[i-1][k] for some k
        } 
    }

    // state space reduction version of dp using 2*N space
    int cur = 1,prev = 0;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            // use cur instead of i
            // use prev instead of i-1
            // calculate dp[cur][j] from dp[prev][k] for some k
        }
        //swap cur and prev to change prev to be i and cur to get value for i+1
        swap(cur,prev);
    }

    // these two version get exactly the same value but state space reduction use a lot less memory
}
