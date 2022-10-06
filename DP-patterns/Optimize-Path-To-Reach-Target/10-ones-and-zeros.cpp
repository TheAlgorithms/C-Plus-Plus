// SPACE OPTIMIZED 2D DP
class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        // pre process strings
        int sz = strs.size();
        int zeros, ones;
        int mp[sz][2];
        memset(mp, 0, sizeof(mp));

        for (int i = 0; i < sz; ++i)
        {
            for (auto &c : strs[i])
                if (c == '0')
                    mp[i][0]++;
                else
                    mp[i][1]++;
        }

        // dp
        int dp[m + 1][n + 1];
        memset(dp, 0, sizeof(dp));

        // num of elements
        for (int s = 1; s <= sz; ++s)
            for (int i = m; i >= 0; --i)
                for (int j = n; j >= 0; --j)
                {
                    zeros = mp[s - 1][0];
                    ones = mp[s - 1][1];
                    if (zeros <= i && ones <= j)
                    {
                        dp[i][j] = max(1 + dp[i - zeros][j - ones], dp[i][j]);
                    }
                }

        return dp[m][n];
    }
};

// 3D DP
class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        // pre process strings
        int sz = strs.size();
        int zeros, ones;
        int mp[sz][2];
        memset(mp, 0, sizeof(mp));

        for (int i = 0; i < sz; ++i)
        {
            for (auto &c : strs[i])
                if (c == '0')
                    mp[i][0]++;
                else
                    mp[i][1]++;
        }

        // dp
        int dp[sz + 1][m + 1][n + 1];
        memset(dp, 0, sizeof(dp));

        // num of elements
        for (int s = 1; s <= sz; ++s)
        {
            for (int i = 0; i <= m; ++i)
            {
                for (int j = 0; j <= n; ++j)
                {
                    zeros = mp[s - 1][0];
                    ones = mp[s - 1][1];
                    if (zeros <= i && ones <= j)
                    {
                        dp[s][i][j] = max(1 + dp[s - 1][i - zeros][j - ones], dp[s - 1][i][j]);
                    }
                    else
                    {
                        dp[s][i][j] = dp[s - 1][i][j];
                    }
                }
            }
        }

        return dp[sz][m][n];
    }
};