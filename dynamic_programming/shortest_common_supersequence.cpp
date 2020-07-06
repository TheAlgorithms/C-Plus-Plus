#include <bits/stdc++.h>
using namespace std;

string lcs(string x, string y, int m, int n) {
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	for (unsigned int i = 1; i <= m; i++) {
		for (unsigned int j = 1; j <= n; j++) {
			if (x[i - 1] == y[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];

			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	string res = "";
	int i = m; int j = n;
	while (i > 0 and j > 0) {
		if (x[i - 1] == y[j - 1]) {
			res = x[i - 1] + res;
			i--;
			j--;
		} else if (dp[i][j - 1] > dp[i - 1][j])
		{	res = y[j - 1] + res;
			j--;
		} else {
			res = x[i - 1] + res;
			i--;
		}
	}
	while (i > 0) {
		res = x[i - 1] + res;
		i--;
	}
	while (j > 0) {
		res = y[j - 1] + res;
		j--;
	}
	return res;
}
string shortestCommonSupersequence(string str1, string str2) {

	return lcs(str1, str2, str1.size(), str2.size());


}

int main() {
	string str1 ;
	string str2 ;
	cin>>str1>>str2;
	string ans = shortestCommonSupersequence(str1, str2);
	cout << ans << endl;


	return 0;
}