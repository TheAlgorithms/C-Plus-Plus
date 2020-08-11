/*A cost matrix will be given by the user.
A program needs to be developed to find the minimum cost path from (0,0) position to (m,n) position
i.e from the initial element to the final element in a given array.
The path must be chosen such a way that total cost of traversing from initial position to the final position should be the least.

*/

/* Dynamic Programming implementation of MCP problem */
#include<iostream>

#define row 100
#define col 100


int min(int x, int y, int z);

int minimun_cost_path(int cost[row][col], int m, int n)
{   /*
        Find the minimum cost traced by all possible paths from top left to bottom right in
        a given matrix. 
    */
    

     // Instead of following line, we can use int tc[m+1][n+1] or dynamically allocate memoery to save space. 
     // The following line isused to keep te program simple and make it working on all compilers.
     int dp[R][C];  

     dp[0][0] = cost[0][0];

     /* Initialize first column of total cost(dp) array */
     for (int i = 1; i <= m; i++){
        dp[i][0] = dp[i-1][0] + cost[i][0];
     }

     /* Initialize first row of dp array */
     for (int j = 1; j <= n; j++){
        dp[0][j] = dp[0][j-1] + cost[0][j];
     }

     /* Construct rest of the dp array */
     for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            dp[i][j] = min(dp[i-1][j-1], 
                           dp[i-1][j], 
                           dp[i][j-1]) + cost[i][j];
        }
     }

     return dp[m][n];
}

/* A utility function that returns minimum of 3 integers */
int min(int x, int y, int z)
{
   if (x < y){
      return (x < z)? x : z;
   }
   else{
      return (y < z)? y : z;
   }
}

/* Driver program to test above functions */
int main()
{  
   int cost[row][col] = { {1, 2, 3},
                      {4, 8, 2},
                      {1, 5, 3} };
   std::cout<<minimun_cost_path(cost,2,2);
   return 0;
}
