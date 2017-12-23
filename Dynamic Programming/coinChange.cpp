//Coin Change problem - Dynamic Programming
//For a given sum, find out in how many ways the sum can be made
//by using infinite supply of N coins of different values.
#include<bits/stdc++.h>
using namespace std;
int coinCount( int S[], int m, int n )
{
    int x, y;
    int dp[n+1][m];

    for (int i=0; i<m; i++) dp[0][i] = 1;

    for (int i = 1; i < n+1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            x = (i-S[j] >= 0)? dp[i - S[j]][j]: 0;
            y = (j >= 1)? dp[i][j-1]: 0;
            dp[i][j] = x + y;
        }
    }
    return dp[n][m-1];
}
int main()
{
    int n,sum;
    cout<<"Enter the total sum value\n";
    cin>>sum;
    cout<<"Enter number of coins\n";
    cin>>n;
    int a[n];
    cout<<"Enter values of "<<n<<" coins seperated by space(eg : 1 2 3)\n";
    for(int i=0;i<n;i++) cin>>a[i];
    printf(" %d ", coinCount(a, sum, n));
    return 0;
}
