/*
    statement => min operations to reach target!

    let dp[i] be the min number of operations to reach 'i' characters on screen
    
    how can we reach 'i'
    find factor of 'i', say j
    dp[i] = min(dp[i], dp[j] + i / j)
    
    i / j gives us the operations to reach i from j   
   
    we just have to return dp[target]
*/

class Solution
{
public:
    int minSteps(int n)
    {
        int dp[n + 1];
        dp[1] = 0;

        for (int i = 2; i <= n; ++i)
        {

            // find largest factor of i
            for (int j = i / 2; j >= 1; --j)
            {
                if (i % j == 0)
                {
                    dp[i] = dp[j] + i / j;
                    break;
                }
            }
        }

        return dp[n];
    }
};