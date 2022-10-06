#include <iostream>
#include <cstring>
using namespace std;
// Problem - https://docs.google.com/document/d/1zuw8hBXHsiTYTH8u986fQhn8TWfpOk9BQBIRH3lo_W8/edit
/*

SAMPLE INPUT
9 2 7 8
6 4 3 7
5 8 1 8
7 6 9 4

SAMPLE OUTPUT
13

*/

int cost[4][4], n = 4;
int dp[4][(1 << 4) - 1];

int solve(int i, int mask)
{
    // all rows taken
    if (i == n)
        return 0;

    if (dp[i][mask] != -1)
        return dp[i][mask];

    int c = INT_MAX;
    // we can choose all remaining options of jobs
    for (int j = 0; j < n; ++j)
    {

        // job is not chosen by any other worker
        if ((mask & (1 << j)) == 0)
        {
            c = min(c, cost[i][j] + solve(i + 1, mask | (1 << j)));
        }
    }

    return dp[i][mask] = c;
}

int main()
{
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> cost[i][j];

    // we start with the 0th worker, ans since all jobs are available initial mask = 0
    cout << "ANS : " << solve(0, 0) << "\n";
    return 0;
}