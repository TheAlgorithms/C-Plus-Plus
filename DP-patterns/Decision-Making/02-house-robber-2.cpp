class Solution
{
    int HouseRobberOne(vector<int> &A, int start, int end)
    {
        if (start > end)
            return 0;
        int robPrev = A[start], doNotRobPrev = 0;
        for (int i = start + 1; i <= end; ++i)
        {
            int robCurr = A[i] + doNotRobPrev;
            int doNotRobCurr = max(robPrev, doNotRobPrev);
            robPrev = robCurr;
            doNotRobPrev = doNotRobCurr;
        }
        return max(robPrev, doNotRobPrev);
    }

public:
    int rob(vector<int> &A)
    {
        if (A.size() == 1)
            return A[0];
        return max(HouseRobberOne(A, 0, A.size() - 2), HouseRobberOne(A, 1, A.size() - 1));
        //         int dp[101][2][2] = {}, n = A.size();
        //         if(n == 1) return A[0];

        //         dp[0][0][0] = 0;
        //         dp[0][1][1] = A[0];

        //         for(int i = 1; i < n; ++i) {
        //             dp[i][1][0] = A[i] + dp[i - 1][0][0];
        //             dp[i][1][1] = A[i] + dp[i - 1][0][1];
        //             dp[i][0][0] = max(dp[i - 1][1][0], dp[i - 1][0][0]);
        //             dp[i][0][1] = max(dp[i - 1][1][1], dp[i - 1][0][1]);
        //         }

        //         return max(max(dp[n - 1][0][0], dp[n - 1][0][1]), dp[n - 1][1][0]);
    }
};