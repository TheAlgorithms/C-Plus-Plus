int dp[101][1024];
// dp[i][mask]
// i => shirt id
// mask => denotes a subset of people out of 10 people, 2^10 [0000000000 to 1111111111]

int solve(int shirt_id, int mask)
{

    // if all people have shirts
    if (mask == (1 << n) - 1)
        return 1;

    // all shirts have exhausted
    if (shirt_id == 101)
        return 0;

    // if we have solve this sub problem in some other branch
    if (dp[shirt_id][mask] != -1)
        return dp[shirt_id][mask];

    int ans = 0;

    // don't give this shirt to anyone
    ans += solve(shirt_id + 1, mask);

    // give this shirt to eligible people
    // i.e if a person has this shirt in their collection and currently don't have any shirt alloted to them
    for (int i = 0; i < n; ++i)
    {
        if ((mask & (1 << i)) == 0 && person[i][shirt_id] == 1)
        {
            ans += solve(shirt_id + 1, mask | (1 << i));
        }
    }

    return dp[shirt_id][mask] = ans;
}