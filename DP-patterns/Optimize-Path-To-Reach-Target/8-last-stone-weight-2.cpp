/*
    let's imagine that, we have to divide given elements into two groups
    +ve group and -ve group
    
    let groups be s1 and s2
    we know s1 + s2 = sum ----------- (1)
    
    let's assume, s1 >= s2
    therefore, s1 - s2 = x -------------(2)
    
    according to the question, we have to minimise x
    
    from eq 1 and 2,
    sum - 2s2 = x
    
    since, we have to minimise x,
    let's maximise s2
    
    what will be the range of s2?
    => [0, sum/2] (as it's less than or equal to s1)
    
    how will be find the largest sum possible by some subset of array that is <= sum/2
    
    Our final answer = s1 - s2
                     = sum - 2s2
    
    let dp[i][j] = true (if there is any subset in 'i' numbers, that sum up to j)
                   false (otherwise)
    
    we have to find
    max element possible in dp[n][0......sum/2]    

*/

class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size();
        int total_sum = accumulate(stones.begin(), stones.end(), 0);
        int sum = total_sum / 2;

        bool dp[n + 1][sum + 1];

        // if number of elements = 0
        // it is not possible to form any subset using '0' numbers that sum up to j
        for (int i = 0; i <= sum; ++i)
            dp[0][i] = false;

        // if required sum = 0
        // empty subset is always possible
        for (int i = 0; i <= n; ++i)
            dp[i][0] = true;

        // general case
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= sum; ++j)
            {
                if (stones[i - 1] <= j)
                {
                    dp[i][j] = dp[i - 1][j - stones[i - 1]] || dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // find max element possible in last row of dp
        // it means, that using n numbers the largest subset formed can have the following sums
        int s2 = 0;
        for (int i = sum; i >= 0; --i)
        {
            if (dp[n][i])
            {
                s2 = i;
                break;
            }
        }

        int s1 = total_sum - s2;

        return s1 - s2;
    }
};

// SPACE OPTIMIZED 1D DP SOLUTION
class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size();
        int total_sum = accumulate(stones.begin(), stones.end(), 0);
        int sum = total_sum / 2;

        bool dp[sum + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = true;

        // general case
        for (int i = 1; i <= n; ++i)
            for (int j = sum; j >= 0; --j)
                if (stones[i - 1] <= j)
                    dp[j] = dp[j - stones[i - 1]] || dp[j];

        // find max element possible in last row of dp
        // it means, that using n numbers the largest subset formed can have the following sums
        int s2 = 0;
        for (int i = sum; i >= 0; --i)
        {
            if (dp[i])
            {
                s2 = i;
                break;
            }
        }

        int s1 = total_sum - s2;

        return s1 - s2;
    }
};

// BITMASK SOLUTION
class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {
        int tot_sum = accumulate(stones.begin(), stones.end(), 0);
        int sum = tot_sum / 2;
        bitset<3001> b(1);

        for (auto &i : stones)
            b |= (b << i);

        int i;
        for (i = sum; i >= 1; --i)
        {
            if (b[i])
                break;
        }

        return tot_sum - 2 * i;
    }
};
