#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 43, C = 20;
 
int n, m, dp[1 << C];
ll G[MAX];
 
int maxClique()
{
	for(int i = 1; i < (1 << max(0, n - C)); i++)
	{
		int x = i;
		for(int j = 0; j < max(0, n - C); j++)
			if((i >> j) & 1)
				x &= G[j + C] >> C;
		if(x == i) dp[i] = __builtin_popcount(i);
	}
	for(int i = 1; i < (1 << max(0, n - C)); i++)
		for(int j = 0; j < max(0, n - C); j++)
			if((i >> j) & 1)
				dp[i] = max(dp[i], dp[i ^ (1 << j)]);
	int ans = 0;
	for(int i = 0; i < (1 << min(C, n)); i++){
		int x = i, y = (1 << max(0, n - C)) - 1;
		for(int j = 0; j < min(C, n); j++)
			if((i >> j) & 1)
				x &= G[j], y &= G[j] >> C;
		if(x == i)
		    ans = max(ans, __builtin_popcount(i) + dp[y]);
	}
	return ans;
}
 
int main()
{
    cin >> n >> m;
    while(m--)
    {
        int u, v; 
        cin >> u >> v; u--; v--; 
        G[u] |= (1LL << v);
        G[v] |= (1LL << u);
    }
    for(int i = 0; i < n; i++)
        G[i] |= (1LL << i);
    cout << maxClique() << '\n';
 
	return 0;
}
