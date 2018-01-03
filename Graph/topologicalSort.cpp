#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int vis[100001],n,m,a,b;
vector <int> adj[100001],toporder;

void dfs(int v) {
	vis[v] = 1;
	for(int i = 0;i < adj[v].size();i++) {
		int x = adj[v][i];
		if(!vis[x]) {
			dfs(x);
		}
	}
	toporder.push_back(v); // reverse this vector for topological order
}

int main() {

	cin>>n>>m;
	for(int i = 1;i <= m;i++) {
		scanf("%d%d",&a,&b);
		adj[a].push_back(b);
	}
	for(int i = 1;i <= n ;i++) {		
		if(!vis[i]) {
			dfs(i);
		}
	}
	reverse(toporder.begin(),toporder.end());
	for(int i = 0;i < toporder.size();i++)
		printf("%d\n",toporder[i] );
}
