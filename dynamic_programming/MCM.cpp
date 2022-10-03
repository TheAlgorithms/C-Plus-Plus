/*
https://en.wikipedia.org/wiki/Matrix_chain_multiplication
Matrix chain multiplication (or the matrix chain ordering problem) is an optimization problem concerning the most efficient way to multiply a given sequence of matrices.
The problem is not actually to perform the multiplications, but merely to decide the sequence of the matrix multiplications involved. The problem may be solved using 
dynamic programming.

The matrix multiplication is associative as no matter how the product is parenthesized, the result obtained will remain the same. For example, for four matrices A, B, 
C, and D, we would have:

  ((AB)C)D = ((A(BC))D) = (AB)(CD) = A((BC)D) = A(B(CD))

However, the order in which the product is parenthesized affects the number of simple arithmetic operations needed to compute the product. 
For example, if A is a 10 * 30 matrix, B is a 30 * 5 matrix, and C is a 5 * 60 matrix, then computing (AB)C needs (10*30*5) + (10*5*60) = 1500 + 3000 = 4500 operations 
while computing A(BC) needs (30*5*60) + (10*30*60) = 9000 + 18000 = 27000 operations. Clearly, the first method is more efficient.
*/
/// Time complexity = O(n*n*n)  Space complexity=O(n*n)  where 'n' is the size of the array
#include<iostream>
#include <vector>
#include <climits>
using namespace std;

//Recusrion+Memoization approach
int solve(vector<int>& arr,int i,int j,vector<vector<int>>& memo)
{
    if(i>=j)  //it means single element which does not makes sense as we need minimum 2 elements to represent matrix dimension
        return 0;
    if(memo[i][j]!=-1)
        return memo[i][j];

    int mn=INT_MAX;
    for(int k=i;k<=j-1;k++){
        int steps = arr[i-1]*arr[k]*arr[j] + solve(arr,i,k,memo) + solve(arr,k+1,j,memo);
        mn=min(steps,mn);
    }
    return memo[i][j]=mn;
}
int MCM_memo(vector<int>& arr){
    int n=arr.size();
    vector<vector<int>> memo(n,vector<int>(n,-1));
    //we are gonna use [i-1][i] as matrix dimension
    return solve(arr,1,n-1,memo);
}

//tabulation approach
int MCM_tabl(vector<int>& arr){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int>(n));
    //base case
    for(int i=0;i<n;i++)
        dp[i][i]=0;

    for(int i=n-1;i>=1;i--){
        for(int j=i+1;j<n;j++){  //as j will always be on the right of i
            int mn=INT_MAX;
            for(int k=i;k<j;k++){
                int steps = arr[i-1]*arr[k]*arr[j] + dp[i][k] + dp[k+1][j];
                mn=min(steps,mn);
            }
            dp[i][j]=mn;
        }
    }
    return dp[1][n-1];
}

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];

    //cout<<MCM_memo(arr)<<"\n";
    cout<<"The minimum cost is: "<<MCM_tabl(arr);
  return 0;
}

/*
Test cases:

4
10 20 30 40
The minimum cost is 18000

4
10 30 5 60
The minimum cost is 4500

*/
