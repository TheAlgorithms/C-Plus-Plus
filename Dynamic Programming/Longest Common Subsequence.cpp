//Longest common subsequence - Dynamic Programming
#include <iostream>
using namespace std;
int lcs(string a, string b){
	int m = a.length(), n = b.length();
	int res[m+1][n+1];
	for (int i = 0; i < m+1; ++i)
	{
		for (int j = 0; j < n+1; ++j)
		{
			if(i==0||j==0)
				res[i][j] = 0;
			else if(a[i-1]==b[j-1])
				res[i][j] = 1 + res[i-1][j-1];
			else
				res[i][j] = max(res[i-1][j], res[i][j-1]);
		}
	}
	return res[m][n];
}
int main(int argc, char const *argv[])
{
	string a,b;
	cin>>a>>b;
	cout<<lcs(a,b);
	return 0;
}