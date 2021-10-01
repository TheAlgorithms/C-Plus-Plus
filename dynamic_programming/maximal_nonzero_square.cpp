// Compute the maximal area of a square region having '1' character

/*
Examples :

1) Consider the following grid :
    [["1","0","1","0","0"],
     ["1","0","1","1","1"],
     ["1","1","1","1","1"],
     ["1","0","0","1","0"]]

The largest non-zero square has a side 2 & there are 2 such square marked below with a X
    [["1","0","1","0","0"],              [["1","0","1","0","0"],
     ["1","0","X","X","1"],               ["1","0","1","X","X"],
     ["1","1","X","X","1"],               ["1","1","1","X","X"],
     ["1","0","0","1","0"]]               ["1","0","0","1","0"]]   

Therefore, the area of the largest such square is 2*2 = 4 units

2) Consider the following grid :
        [["0","1"],
         ["1","0"]] 

The largest non-zero square has a side 1 & there are 2 such squares marked below with a X
        [["0","X"],             [["0","1"],
         ["1","0"]]              ["X","0"]] 
    
Therefore, the area of the largest such square is 1*1 = 1 unit
*/

#include<iostream>
#include<cmath>

int main(){
    // The grid dimensions are m x n
    int m,n;
    std::cin>>m>>n;

    // Taking the grid as input
    char grid[m][n];    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            std::cin>>grid[i][j];
        }
    }

    int max_square[m+1][n+1];   // max_square[i][j] respresents the side of the largest square with bottom right corner at (i,j) [1-based indexing]

    // Initialize max_square[i][j] to 0 when either i or j is 0 (as it can only contain degenerate squares)
    for(int i=0;i<=m;i++){
        max_square[i][0] = 0;
    }
    for(int j=0;j<=n;j++){
        max_square[0][j] = 0;
    }

    /* 
    Dynamic programming transition :
    DP[i][j] =  1 + min(DP[i-1,j-1],DP[i-1][j],DP[i][j-1])                if grid[i][j] = 1 [1 based indexing (the actual arra for grid follows 0-based indexng)]
                0                                                         if grid[i][j] = 0 [1 based indexing (the actual arra for grid follows 0-based indexng)]

    Explanation :
    Case 1: If grid[i][j] = 0, there is no square with bottom right corner at (i,j) i.e. DP[i][j] = 0
    Case 2:If grid[i][j] = 0, the largest square will have a side less than 1+D[i-1][j-1],1+D[i-1][j],1+D[i][j-1]
    & to get the largest square it must be equal to min of these 3 quantities
    */
    
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(grid[i-1][j-1]=='1'){
                max_square[i][j] = 1+std::min(max_square[i-1][j-1],std::min(max_square[i-1][j],max_square[i][j-1]));
            }
            else{
                max_square[i][j] = 0;
            }
        }
    }
    // Finally, to get the largest square globally we take the max sqaure with bottom right corner at every possible position i.e. max over the DP table
    int global_max_square = 0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            global_max_square = std::max(global_max_square,max_square[i][j]);
        }
    }
    std::cout<<global_max_square*global_max_square<<'\n';
}