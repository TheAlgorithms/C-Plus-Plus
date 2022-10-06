class Solution
{
public:
    int rob(vector<int> &A)
    {
        // 0 -> not robbed
        // 1 -> robbed
        // dp[0][j] -> max amount if we rob current house
        // dp[1][j] -> max amount if we don't rob current house
        int robPrev = A[0], doNotRobPrev = 0;

        for (int i = 1; i < A.size(); ++i)
        {
            // dp[1][i] = A[i] + dp[0][i - 1];
            // dp[0][i] = max(dp[1][i - 1], dp[0][i - 1]);
            int robCurr = A[i] + doNotRobPrev;
            int doNotRobCurr = max(robPrev, doNotRobPrev);

            // for next iteration
            robPrev = robCurr;
            doNotRobPrev = doNotRobCurr;
        }

        return max(robPrev, doNotRobPrev);
    }
};