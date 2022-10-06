#include <iostream>
#include <cstring>
using namespace std;

// 2D DP
int main2()
{
    int A[] = {2, 3, 5, 6, 8, 10};
    int n = 6, target = 10;

    // how many subsets of A can sum to target?

    // Method 1 -> let dp[x][y] = number of subsets in first 'x' elements that sum up to 'y'
    // we add 1 more element 'i'
    // if(A[i - 1] <= j)
    // dp[i][j] = dp[i - 1][j] + d[i - 1][j - A[i - 1]];
    // i.e num ways we can make 'j' using first 'i' elements = num ways we can make 'j' using first 'i - 1' elements
    //                                                         +
    //                                                         num ways we can make 'j - A[i - 1]' using first 'i - 1' elements

    int dp[n + 1][target + 1];

    for (int i = 0; i <= n; ++i)
        dp[i][0] = 1;

    for (int i = 1; i <= target; ++i)
        dp[0][i] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= target; ++j)
        {
            if (A[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - A[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[n][target];

    return 0;
}

// Since at each point, we only ned the prev row, and some column <= j
// we can use 1D DP and iterate on it from right to left

int main()
{
    int A[] = {2, 3, 5, 6, 8, 10};
    int n = 6, target = 10;

    // dp[j] = number of ways we can make 'j' using the prev 'i' elements
    int dp[target + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // we can make sum '0' using only the empty subset

    for (int i = 1; i <= n; ++i)
    {
        for (int j = target; j >= 1; --j)
        {
            if (A[i - 1] <= j)
                dp[j] = dp[j] + dp[j - A[i - 1]];
        }
    }

    cout << "using 1D DP : ";
    cout << dp[target];

    return 0;
}
