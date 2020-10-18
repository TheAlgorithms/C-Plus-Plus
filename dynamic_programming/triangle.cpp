/*Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

*/

class Solution {
public:
     
    int minimumTotal(vector<vector<int>>& tri) {
       
        int i,j,n=tri.size();
        vector<int> dp(n,0);
        for(i=n-1;i>=0;i--)
        for(j=0;j<=i;j++)
        {
         
            if(i+1<n)
            {
                dp[j]=min(dp[j],dp[j+1]);
            }
            dp[j]+=tri[i][j];
        }
        return dp[0];
    }
};
