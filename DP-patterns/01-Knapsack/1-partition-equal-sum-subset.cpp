// 2D DP
class Solution
{
public:
    int equalPartition(int n, int arr[])
    {
        int sum = accumulate(arr, arr + n, 0);
        if (sum & 1)
            return 0;

        sum >>= 1;
        bool dp[n + 1][sum + 1];
        // dp[i][j] => true if we can make 'j' using any subset of the first 'i' elements in arr

        // we cannot make any sum when there are 0 elements in array
        for (int i = 0; i <= sum; ++i)
            dp[0][i] = false;

        // sum = 0, empty subset is always possible
        for (int i = 0; i <= n; ++i)
            dp[i][0] = true;

        // main
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= sum; ++j)
            {
                if (arr[i - 1] <= j)
                    dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        return dp[n][sum];
    }
};

/*
    dp[i][j] = true if there is any subset of the first 'i' elements that sum up to j

    dp[i][j] = dp[i - 1][j] (if we can make 'j' using 'i-1' elements we can obviously make it using 'i' elements)
                ||
               dp[i - 1][j - arr[i - 1]] (if we can make 'j - arr[i - 1]' using 'i - 1' elements,
                                          we can add arr[i - 1] to make it arr[j] using ith element) 


    SPACE OPTIMIZATION
    At each 'i' stage we only care about 'i - 1' stage and some 'j' <= current 'j'
    So instead of a 2d array, we can use a 1D array

    dp[j] = true if we can make j using a subset of all elements
    so now we just have to check if we can make dp[sum] true
*/

// 1D DP
class Solution
{
public:
    int equalPartition(int n, int arr[])
    {
        int sum = accumulate(arr, arr + n, 0);
        if (sum & 1)
            return 0;

        sum >>= 1;
        bool dp[sum + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = true;

        for (int i = 0; i < n; ++i)
        {
            for (int j = sum; j >= 1; --j)
            {
                if (arr[i] <= j)
                {
                    dp[j] = dp[j] || dp[j - arr[i]];
                }
            }
        }

        return dp[sum];
    }
};

// Since we just have to return whether it is possible to make a number or not, we can use bitmasks
// bitmask<MAX SUM> sum(1)
// sum[k] represents if we can make sum 'k' using prev 'i' elements

// BITS SOLUTION!
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1)
            return false;

        sum >>= 1;

        const int MAX_NUM = 100;
        const int MAX_SIZE = 200;
        bitset<MAX_SIZE * MAX_NUM + 1> bits(1);

        for (int &i : nums)
        {
            bits = bits | bits << i;
        }

        return bits[sum];
    }
};
