// TODO : O(N) SPACE SOLUTION
// SUFFIX STRATEGY O(N^2)
// BOTTOM UP STRATEGY O(N^3)
class Solution
{
public:
    int minCut(string s)
    {
        int n = s.size();

        // gap strategy to store all palindromes
        bool check[n][n];
        memset(check, 0, sizeof(check));

        for (int g = 0; g < n; ++g)
        {
            for (int l = 0, r = g; r < n; ++l, ++r)
            {
                if (g == 0)
                    check[l][r] = true;
                else if (g == 1)
                    check[l][r] = s[l] == s[r];
                else
                    check[l][r] = s[l] == s[r] && check[l + 1][r - 1];
            }
        }

        // suffix approach
        // O(n^2)
        int cuts[n];
        cuts[0] = 0;

        for (int r = 1; r < n; ++r)
        {
            if (check[0][r] == 1)
                cuts[r] = 0;
            else
            {
                cuts[r] = INT_MAX;
                for (int l = r; l > 0; --l)
                {
                    if (check[l][r] == 1)
                    {
                        cuts[r] = min(cuts[r], 1 + cuts[l - 1]);
                    }
                }
            }
        }

        return cuts[n - 1];

        // bottom up approach
        // O(n^3)

        int cuts[n][n];
        memset(cuts, 0, sizeof(cuts));

        for (int g = 1; g < n; ++g)
        {
            for (int l = 0, r = g; r < n; ++l, ++r)
            {
                if (check[l][r] == 1)
                    continue;

                cuts[l][r] = INT_MAX;
                for (int k = l; k < r; ++k)
                {
                    cuts[l][r] = min(cuts[l][r], cuts[l][k] + cuts[k + 1][r] + 1);
                }
            }
        }

        return cuts[0][n - 1];
    }
};

// TOP DOWN
// EXTREMELY SLOW
class Solution
{
    int dp[2001][2001] = {[0 ... 2000][0 ... 2000] = -1};
    bool check[2001][2001] = {};
    int solve(int l, int r)
    {
        if (l >= r)
            return 0;

        if (dp[l][r] != -1)
            return dp[l][r];

        if (check[l][r] == 1)
            return 0;

        int ans = INT_MAX;

        for (int k = l; k < r; ++k)
        {
            ans = min(ans, solve(l, k) + solve(k + 1, r) + 1);
        }

        return dp[l][r] = ans;
    }

public:
    int minCut(string s)
    {
        int n = s.size();

        // gap strategy to store all palindromes
        for (int g = 0; g < n; ++g)
        {
            for (int l = 0, r = g; r < n; ++l, ++r)
            {
                if (g == 0)
                    check[l][r] = true;
                else if (g == 1)
                    check[l][r] = s[l] == s[r];
                else
                    check[l][r] = s[l] == s[r] && check[l + 1][r - 1];
            }
        }

        return solve(0, n - 1);
    }
};