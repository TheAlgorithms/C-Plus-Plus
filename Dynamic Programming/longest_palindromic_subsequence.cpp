/*
	Longest Palindromic SubSequence
	1. Reverse the string and find the LCS of both the strings.
	2. Use the basic DP subtructure
*/
// solution by @pruvi007

#include<bits/stdc++.h>
using namespace std;

// to memoize the recurrence relation
map<pair<int,int>,int> m;
int pal(string s,int i,int j)
{
	if(i>j)
		return 0;
	if(i==j)
		return 1;
	if(s[i] == s[j])
		return 2 + pal(s,i+1,j-1);
	return max(pal(s,i+1,j),pal(s,i,j-1));
}

int palT(string s)
{
	int n = s.length();
	int dp[n+1][n+1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j)
				dp[i][j] = 1;
			if(i>j)
				dp[i][j] = 0;
		}
	}
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<n-i;j++)
		{
			if(s[j] == s[j+i])
				dp[j][j+i] = 2 + dp[j+1][j+i-1];
			else dp[j][j+i] = max(dp[j][j+i-1],dp[j+1][j+i]);
		}
	}
	return dp[0][n-1];
}

int main()
{
	string s;
	cin >> s;
	int n = s.length();
	int ans = pal(s,0,n-1);
	cout << ans << endl;
	ans = palT(s);
	cout << ans << endl;

}