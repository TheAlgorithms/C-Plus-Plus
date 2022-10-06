class Solution
{
public:
    int minCost(int N, vector<int> &cuts)
    {
        cuts.push_back(0);
        cuts.push_back(N);
        sort(cuts.begin(), cuts.end());
        int n = cuts.size();

        int dp[n][n];
        memset(dp, 0, sizeof(dp));

        for (int g = 2; g < n; ++g)
        {
            for (int l = 0, r = g; r < n; ++l, ++r)
            {
                if (g == 2)
                {
                    dp[l][r] = cuts[r] - cuts[l];
                }
                else
                {
                    dp[l][r] = INT_MAX;
                    for (int k = l + 1; k < r; ++k)
                    {
                        dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r]);
                    }
                    dp[l][r] += cuts[r] - cuts[l];
                }
            }
        }

        return dp[0][n - 1];
    }
};