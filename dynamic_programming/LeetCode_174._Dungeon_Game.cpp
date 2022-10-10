class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) { 
        int m = dungeon.size(), n = dungeon[0].size();

        // dp[i][j] means min hp needed at point (i, j) to survive (it cannot be 0 and has to be at least 1 at any point)
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));     // pad matrix with extra row and column for shorter code
        dp[m][n-1] = dp[m-1][n] = 1;

        // since we need min hp when starting out (top left), we fill table from bottom right (princess) to top left (knight)
        for(int i = m-1; i >= 0; i--) {
            for(int j = n-1; j >= 0; j--) {
                // at any cell check cell below and on right
                int need = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
                dp[i][j] = need > 0 ? need : 1;
            }
        }
        return dp[0][0];
    }
};

/*

-2  -3  3           7   5   2   ∞
-5  -10 1   --->    6   11  5   ∞
10  30  -5          1   1   6   1
                    ∞   ∞   1   ∞
*/
