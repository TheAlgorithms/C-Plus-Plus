class Solution {
public:
    int maxx;
    int dp[201][201];
    bool vis[201][201];
    
    void dfs(vector<vector<int>>& matrix,int i,int j)
    {
        vis[i][j] = 1;
        
        int r[4] = {0,1,-1,0};
        int c[4] = {1,0,0,-1};
        
        for(int k = 0;k<4;k++)
        {
            int row = i + r[k];
            int col = j + c[k];
            
            if(row >=0 && row < matrix.size() && col >= 0 && col<matrix[i].size())
            {
                
                
                if(matrix[i][j] < matrix[row][col])
                {
                    if(!vis[row][col])
                    {
                        dfs(matrix, row,col);
                    }
                    
                    // cout<< i<<" "<<j<<" "<<row<<" "<<col<<endl;
                    dp[i][j] = max(dp[i][j], 1+dp[row][col]);
                    // cout<< "DP : "<<i<<""<<j<<" "<<dp[i][j]<<endl; 
                }  
            }
        }        
    }
    
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
              for(int i = 0;i<matrix.size();i++)
        {
            for(int j = 0;j<matrix[i].size();j++)
            {
             dp[i][j] = 1;
                vis[i][j] = 0;
            }
        }  
        
        
        
        maxx = 1;
        for(int i = 0;i<matrix.size();i++)
        {
            for(int j = 0;j<matrix[i].size();j++)
            {
                if(!vis[i][j])
                {dfs(matrix,i,j);}
            }
        }
        
        for(int i = 0;i<matrix.size();i++)
        {
            for(int j = 0;j<matrix[i].size();j++)
            {
                // cout<<dp[i][j]<<" ";
                maxx = max(maxx,dp[i][j]);
            }
            // cout<<endl;
        }
        
        
        return maxx;
        
    }
};
