class Solution
{
    bool flag;
    int group, n;

    void solve(vector<int> &A, int idx, int curr, int mask)
    {
        // all elements are taken
        if (mask == (1 << n) - 1)
        {
            flag = true;
            return;
        }

        // if curr groupsize == required groupsize, create new group
        if (curr == group)
        {
            for (int i = 0; i < n; ++i)
                if ((mask & (1 << i)) == 0)
                {
                    solve(A, i + 1, A[i], mask | (1 << i));
                    return;
                }
        }

        // continue previous group
        for (int i = idx; i < n; ++i)
        {
            if ((mask & (1 << i)) == 0 && curr + A[i] <= group)
            {
                solve(A, i + 1, curr + A[i], mask | (1 << i));
                if (flag == true)
                    return;
            }
        }
    }

public:
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k)
            return false;
        group = sum / k;
        n = nums.size();

        if (group < *max_element(nums.begin(), nums.end()))
            return false;

        solve(nums, 1, nums[0], 1);
        return flag;
    }
};