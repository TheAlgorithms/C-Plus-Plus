//To find the binomial coefficient mod 10^9+7 using dp
#include <iostream>
#include <math.h>
using namespace std;
typedef long long int lli;

lli nCr(lli n, lli r, lli mod)
{
    if (n < r)
        return 0;

    else if (n == r)
        return 1;

    else
    {
        int dp[n + 1][r + 1]; // dp array
        dp[0][0] = 0;

        for (lli i = 1; i <= n; i++)
        {
            for (lli j = 0; j <= min(r, i); j++)
            {
                if (i == j || j == 0)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    dp[i][j] = (dp[i - 1][j] % mod + dp[i - 1][j - 1] % mod) % mod;
                }
            }
        }

        return dp[n][r];
    }
}

int main()
{
    lli mod = pow(10, 9) + 7;
    lli n, r;
    cout << "Enter the value of n" << endl;
    cin >> n;
    cout << "Enter the value of r" << endl;
    cin >> r;

    cout << "The value of nCr is = " << nCr(n, r, mod) << endl;
    return 0;
}