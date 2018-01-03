//Longest Palindromic Subsequence - Dynamic Programming
//Given a sequence, find the length of the longest palindromic subsequence present in it.

#include<bits/stdc++.h>
using namespace std;

int lps(string str)
{
   int n = str.length();
   int i, j, cl;
   int dp[n][n];

   for (i = 0; i < n; i++)
      dp[i][i] = 1;

    for (cl=2; cl<=n; cl++)
    {
        for (i=0; i<n-cl+1; i++)
        {
            j = i+cl-1;
            if (str[i] == str[j] && cl == 2)
               dp[i][j] = 2;
            else if (str[i] == str[j])
               dp[i][j] = dp[i+1][j-1] + 2;
            else
               dp[i][j] = max(dp[i][j-1], dp[i+1][j]);
        }
    }

    return dp[0][n-1];
}

int main()
{
    string s;
    cout<<"Enter a string\n";
    cin>>s;
    cout<<"The lnegth of the Longest Palindromic Subsequence is "<<lps(s)<<endl;
    return 0;
}
