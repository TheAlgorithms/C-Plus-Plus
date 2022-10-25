class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        for(int i=0;i<matrix[0].size();i++)
        {
          
            for(int j=0;j<matrix.size();j++ )
            {
                if(i>0 && j>0 && matrix[i][j]!=matrix[i-1][j-1]){
                return false;
            }
               
            }
        }
        return true;
    }
};
