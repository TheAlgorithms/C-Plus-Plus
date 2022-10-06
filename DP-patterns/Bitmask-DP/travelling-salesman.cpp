// N cities, start at 1, find min distance to travel all other cities once and then come back to 1
// dp[i][j] denotes the min distance to travel remaining cities from 'i'th city
// where 'j' is the subset of cities already visited.

// we start from city 1
int solve(int i, int mask)
{
    // all cities are covered
    if (mask == (1 << n) - 1)
    {
        return distance[i][0];
    }

    if (dp[i][mask] != -1)
        return dp[i][mask];

    int ans = INT_MAX;
    // we have n-1 options
    for (int j = 0; j < n; ++j)
    {
        // check if city is unvisited
        if ((mask & (1 << j)) == 0)
        {
            ans = min(ans, distance[i][j] + solve(j, mask | (1 << j)));
        }
    }

    return dp[i][mask] = ans;
}

int main()
{
    int ans = solve(0, 1);
    return 0;
}