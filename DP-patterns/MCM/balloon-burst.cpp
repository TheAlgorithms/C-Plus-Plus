class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();
        int dp[n][n];
        memset(dp, 0, sizeof(dp));

        for (int g = 0; g < n; ++g)
        {
            for (int l = 0, r = g; r < n; ++l, ++r)
            {

                for (int k = l; k <= r; ++k)
                {
                    int left = k == l ? 0 : dp[l][k - 1];
                    int right = k == r ? 0 : dp[k + 1][r];
                    int val = nums[k];

                    if (l > 0)
                        val *= nums[l - 1];
                    if (r < n - 1)
                        val *= nums[r + 1];

                    dp[l][r] = max(dp[l][r], left + val + right);
                }
            }
        }

        return dp[0][n - 1];
    }
};