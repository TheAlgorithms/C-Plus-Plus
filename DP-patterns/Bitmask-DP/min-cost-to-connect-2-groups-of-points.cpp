/*
Concept!
Since we have to connect atleast 1 element of group one to atleast 1 element of group 2 and vice versa
and it's given that number of elements in group 1 <= number of elements in group 2

Idea
Let's connect all elements of group1 to some subset of elements in group2
such that cost of connecting all elements in group 1 to group 2 is minimum

After this, some elements in group2 may remain unconnected, now we will connect them to min cost edges

*/

class Solution
{
    int sz1, sz2;

    int min_cost[13] = {[0 ... 12] = INT_MAX};
    int dp[13][1 << 12];

    int solve(int i, int mask, vector<vector<int>> &cost)
    {
        // 13th state is when all group 1 elements are exhausted but not group2 elements
        if (dp[i][mask] != -1)
            return dp[i][mask];

        int c = i >= sz1 ? 0 : INT_MAX;

        if (i >= sz1)
        {

            // connecting remaining unconnected elements in group 2
            for (int j = 0; j < sz2; ++j)
                if ((mask & (1 << j)) == 0) // if jth element in group2 isn't connected
                    c += min_cost[j];
        }
        else
        {

            // we have all options of elements in group2 for each element in group1
            for (int j = 0; j < sz2; ++j)
                c = min(c, cost[i][j] + solve(i + 1, mask | (1 << j), cost));
        }

        return dp[i][mask] = c;
    }

public:
    int connectTwoGroups(vector<vector<int>> &cost)
    {
        sz1 = cost.size(), sz2 = cost[0].size();
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i < sz2; ++i)
        {
            for (int j = 0; j < sz1; ++j)
            {
                min_cost[i] = min(min_cost[i], cost[j][i]);
            }
        }

        return solve(0, 0, cost);
    }
};