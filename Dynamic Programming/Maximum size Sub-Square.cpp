/*
Given a n*m matrix which contains only 0s and 1s, find out the size of maximum square sub-matrix with all 0s.
*/


#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

//helper function
int findMaxSquareWithAllZeros(int** arr, int row, int col){

    int dp[row][col];
    int result = 1;
    memset(dp,0,sizeof(dp));
    //sub squares ending on first row/column will always be of size 1 if the corresponding element value is 0
    for(int i=0;i<row;i++)
        dp[i][0] = arr[i][0] ^ 1;
    for(int j=0;j<col;j++)
        dp[0][j] = arr[0][j] ^ 1;
    /*sub square ending at arr[i][j] could either be

     extension of the sub square ending at a[i-1][j]
                    OR
     extension of the sub square ending at a[i-1][j-1]
                    OR
     extension of the sub square ending at a[i][j-1]

     depending upon which sub square is the smallest
    */
    for(int i = 1; i < row; i++)
        for(int j = 1; j < col; j++)
            if(arr[i-1][j-1] == 0){
                dp[i][j] = min(dp[i-1][j],min(dp[i-1][j-1],dp[i][j-1])) + 1;
                result = max(dp[i][j],result);
            }
    return result;
}

int main()
 {
  // int **arr is a double pointer as 2D array is allocateed dynamically
  int **arr,n,m,i,j;
  cin>>n>>m;
  arr=new int*[n];
  for(i=0;i<n;i++)
      {
       arr[i]=new int[m];
      }
  for(i=0;i<n;i++)
     {
      for(j=0;j<m;j++)
	    {
	     cin>>arr[i][j];
	    }
     }
  cout << findMaxSquareWithAllZeros(arr,n,m) << endl;
  //preventing memory leak [v. important.. never forget (: ]
  delete arr;
  return 0;
}


