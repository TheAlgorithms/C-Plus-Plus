// LC : 1799

// TIME COMPLEXITY
// 2^(2n) * (2n)^2
class Solution
{
    int dp[8][(1 << 14) - 1], n;

    int solve(int op, int mask, vector<int> &nums)
    {
        if (op > n)
            return 0;

        if (dp[op][mask] != -1)
            return dp[op][mask];

        int ans = 0;

        for (int i = 0; i < 2 * n; ++i)
        {
            if ((mask & (1 << i)) == 0)
            {
                for (int j = i + 1; j < 2 * n; ++j)
                {
                    if ((mask & (1 << j)) == 0)
                    {
                        int new_mask = (mask | (1 << i) | (1 << j));
                        ans = max(ans, op * gcd(nums[i], nums[j]) + solve(op + 1, new_mask, nums));
                    }
                }
            }
        }

        return dp[op][mask] = ans;
    }

public:
    int maxScore(vector<int> &nums)
    {
        n = nums.size() / 2;
        memset(dp, -1, sizeof(dp));
        return solve(1, 0, nums);
    }
};