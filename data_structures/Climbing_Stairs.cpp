class Solution {
public:
    int dp[46];
    Solution(){
        memset(dp,-1,sizeof(dp));
    }
    int climbStairs(int n) {
        if(n==0||n==1||n==2) return n;

        if(dp[n]!=-1) return dp[n];
        return dp[n]=climbStairs(n-1)+climbStairs(n-2);
    }
};
