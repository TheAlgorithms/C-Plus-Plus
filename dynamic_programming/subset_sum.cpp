// Subset Sum - Dynamic Programming
//Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.
#include <bits/stdc++.h>
using namespace std;

bool SubsetSum(int arr[], int n, int sum)
{
    bool dp[n+1][sum+1];

    for (int i = 0; i <= n; i++)
      dp[i][0] = true;

    for (int i = 1; i <= sum; i++)
      dp[0][i] = false;
     for (int i = 1; i <= n; i++)
     {
       for (int j = 1; j <= sum; j++)
       {
         if(j<arr[i-1])
         dp[i][j] = dp[i-1][j];
         if (j >= arr[i-1])
           dp[i][j] = dp[i-1][j] || dp[i - 1][j-arr[i-1]];
       }
     }
     return dp[n][sum];
}
int main()
{
  int n;
  cout<<"Enter number of elements in set\n";
  cin>>n;
  cout<<"Enter "<<n<<" elements\n";
  int a[n];
  for(int i=0;i<n;i++) cin>>a[i];
  int sum;
  cout<<"Enter sum of subset\n";
  cin>>sum;
  if (SubsetSum(a, n, sum) == true)
     printf("Found a subset with given sum");
  else
     printf("No subset with given sum");
  return 0;
}
