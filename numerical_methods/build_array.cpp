class Solution {
public:
    int dp[51][101][51], pre[51][101][51], mod = 1e9 + 7;
        
    int numOfArrays(int n, int m, int k) {
        for (int j = 0; j<= m; j++) {
            dp[1][j][1] = 1;
            pre[1][j][1] = j;
        }
        
        for (int len = 2; len <= n; len++) {
            for (int mx = 1; mx <= m; mx++) {
                for (int cost = 1; cost <=k; cost++) {
                    
                    dp[len][mx][cost] = (1LL * mx * dp[len-1][mx][cost]) % mod;
                    
                    /* In this second case, we can append the element "mx" to the end of the array. 
                    for (int i = 1; i < mx; i++) dp[len][mx][cost] += ways[len - 1][i][cost - 1];*/
                    dp[len][mx][cost] = (dp[len][mx][cost] + pre[len-1][mx-1][cost-1]) % mod;\
                    
                    pre[len][mx][cost] = (pre[len][mx-1][cost] + dp[len][mx][cost]) % mod;
                }
            }
        }
        return pre[n][m][k];
    }
};
