#include<bits/stdc++.h>
using namespace std;

int dp[102][102];
int obs[102][102];
int solve(int i,int j,int m,int n){
    if(i > m || j > n) return 0;
    if(obs[i][j] == 1) return 0;
    if(i == m and j == n){
        return 1;
    }
    if(dp[i][j] != -1) return dp[i][j];
    return  dp[i][j] = solve(i+1,j,m,n) + solve(i,j+1,m,n);
}

int uniquePaths(int m, int n) {
    memset(dp,-1,sizeof(dp));
    return solve(1,1,m,n);
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
{
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(obstacleGrid[i][j] == 1)
                obs[i+1][j+1] = 1;
        }
    }

    return uniquePaths(m,n);
}
void makegrid(int A, int B,vector<vector<int>>& grid)
{
    int c=A/2;
    grid[c][c]=1;
    for(int i=c-B;i<=c+B;i++)
    {
        for(int j=c-B;j<=c+B;j++)
        {
            grid[i][j]=1;
        }
    }
    return;
}
int main(){
int A, B;
cout<<"enter"<<endl;
cin >> A >> B;
vector<vector<int>>grid(A,vector<int>(A,0));
makegrid(A,B,grid);
cout << uniquePathsWithObstacles(grid);
return 0;
}