// TOP DOWN APPROACH
class Solution
{
    int val[14][14], n;
    int dp[14][(1 << 14) - 1];

    int solve(int c, int mask)
    {
        if (c == n)
            return 0;

        if (dp[c][mask] != -1)
            return dp[c][mask];

        int ans = INT_MAX / 2;
        for (int i = 0; i < n; ++i)
        {
            if ((mask & (1 << i)) == 0)
            {
                ans = min(ans, val[c][i] + solve(c + 1, mask | (1 << i)));
            }
        }

        return dp[c][mask] = ans;
    }

public:
    int minimumXORSum(vector<int> &nums1, vector<int> &nums2)
    {
        this->n = nums1.size();
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                val[i][j] = nums1[i] ^ nums2[j];
            }
        }

        return solve(0, 0);
    }
};

// 2D BOTTOM UP APPROACH
class Solution
{
    int count_set_bits(int a)
    {
        int cnt = 0;
        while (a)
        {
            cnt++;
            a = (a & (a - 1));
        }
        return cnt;
    }

public:
    int minimumXORSum(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        int dp[14][16384] = {[0 ... 13][0 ... 16383] = INT_MAX};

        for (int i = 0; i < n; ++i)
        {
            dp[0][1 << i] = (nums1[0] ^ nums2[i]);
        }

        for (int i = 1; i < n; ++i)
        {
            for (int mask = 0; mask < (1 << n); ++mask)
            {
                if (count_set_bits(mask) == i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        if ((mask & (1 << j)) == 0)
                        {
                            dp[i][mask | (1 << j)] = min(dp[i][mask | (1 << j)], (nums1[i] ^ nums2[j]) + dp[i - 1][mask]);
                        }
                    }
                }
            }
        }

        return dp[n - 1][(1 << n) - 1];
    }
};

// 1D BOTTOM UP APPROACH
class Solution
{
    int count_set_bits(int a)
    {
        int cnt = 0;
        while (a)
        {
            cnt++;
            a = (a & (a - 1));
        }
        return cnt;
    }

public:
    int minimumXORSum(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        int dp[16384] = {[0 ... 16383] = INT_MAX};

        for (int i = 0; i < n; ++i)
        {
            dp[1 << i] = (nums1[0] ^ nums2[i]);
        }

        // let dp[i][mask] = minimum xor sum of first 'i' elements of nums1 using a subset of nums2 denoted by mask

        for (int i = 1; i < n; ++i)
        {
            for (int mask = 0; mask < (1 << n); ++mask)
            {
                if (count_set_bits(mask) == i)
                {
                    for (int j = n - 1; j >= 0; --j)
                    {
                        if ((mask & (1 << j)) == 0)
                        {
                            dp[mask | (1 << j)] = min(dp[mask | (1 << j)], (nums1[i] ^ nums2[j]) + dp[mask]);
                        }
                    }
                }
            }
        }

        // minimum xor sum of of all elements of nums1 with all elements of nums2
        return dp[(1 << n) - 1];
    }
};