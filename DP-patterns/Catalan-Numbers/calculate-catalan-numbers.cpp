#include <iostream>
#include <cstring>
using namespace std;

// Formula
// Cn = C0Cn-1 + C1Cn-2 + C2Cn-3 + ..... + Cn-2C1 + Cn-1C0

// OR
// Cn = 2nCn / (n + 1)

/*

C0 = 1, C1 = 1;
now,

C2 = C0C1 + C1C0
   = 1*1 + 1*1 = 2
and,

C3 = C0C2 + C1C1 + C2C0
   = 1*2 + 1*1 + 2*1
   = 5

and so on

*/

// ##########################################################################
//    METHOD 1 => RECURSIVE DP
//    O(N^2)
// ##########################################################################

int catalan(int n, int dp[])
{
    if (n == 0 || n == 1)
        return dp[n] = 1;

    if (dp[n] != -1)
        return dp[n];

    int ans = 0;
    for (int i = 0, j = n - 1; i < n; ++i, --j)
    {
        ans += catalan(i, dp) * catalan(j, dp);
    }
    return dp[n] = ans;
}

int main1()
{
    int n;
    cin >> n;

    int dp[n + 1];
    memset(dp, -1, sizeof(dp));
    catalan(n, dp);

    for (int i = 0; i <= n; ++i)
    {
        cout << dp[i] << " ";
    }
    return 0;
}

// ##########################################################################
//    METHOD 2 => ITERATIVE DP
//    O(N^2)
// ##########################################################################

int main2()
{
    int n;
    cin >> n;

    int dp[n + 1];
    dp[0] = dp[1] = 1;

    cout << dp[0] << " " << dp[1] << " ";

    for (int i = 2; i <= n; ++i)
    {
        dp[i] = 0;
        for (int j = 0; j < i; ++j)
            dp[i] += dp[j] * dp[i - j - 1];

        cout << dp[i] << " ";
    }
    return 0;
}

// ##########################################################################
//    METHOD 3 => BINOMIAL COEFFICIENT
//    only gives us the nth catalan number
//    O(N) time
//    O(1) space
// ##########################################################################

long long nCr(int n, int r)
{
    long long ans = 1;

    for (int i = 1; i <= r; ++i)
    {
        ans *= (n + 1 - i);
        ans /= i;
    }

    return ans;
}

int main()
{
    int n;
    cin >> n;

    cout << (long long)nCr(2 * n, n) / (n + 1);
    return 0;
}

// #########################################################################