class Solution
{
    bool flag = false;
    int n, side;

    void solve(vector<int> &m, int idx, int curr, int mask)
    {
        // if all elements used
        if (mask == ((1 << n) - 1))
        {
            flag = true;
            return;
        }

        // completed a side
        if (curr == side)
        {
            // select new starting point
            for (int i = 0; i < n; ++i)
            {
                if ((mask & (1 << i)) == 0)
                {
                    // unused element
                    solve(m, i + 1, m[i], mask | (1 << i));
                    return;
                }
            }
        }

        // when side is not yet completed
        for (int j = idx; j < n; ++j)
        {
            if ((mask & (1 << j)) == 0 && curr + m[j] <= side)
            {
                // unused element
                solve(m, j + 1, curr + m[j], mask | (1 << j));
                if (flag == true)
                    return;
            }
        }
    }

public:
    bool makesquare(vector<int> &m)
    {
        long sum = accumulate(m.begin(), m.end(), 0l);
        if (sum % 4)
            return false;
        side = sum / 4;
        n = m.size();

        if (side < *max_element(m.begin(), m.end()))
            return false;

        solve(m, 1, m[0], 1);

        return flag;
    }
};