#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e6;
vector<int> g[N], newg[N], rg[N], todo;
int  indeg[N];
vector<int> comp;
int vis[N],vis2[N];
vector<int> gr[N];
int n,m;

void dfs(int k){
	vis[k]=1;
	for(auto it:g[k]){
		if(!vis[it])
			dfs(it);
	}
	todo.push_back(k); // stores vertices in decreasing order of their finishing time
}

void dfs2(int u){
	comp.push_back(u);
	vis2[u]=1;
	for(auto it:rg[u]){
		if(!vis2[it])
			dfs2(it);
	}
}

void sccAddEdge(int from, int to){
	g[from].push_back(to);
	rg[to].push_back(from);
}

void scc(){
	for(int i=1;i<=n;i++){
		if(!vis[i])
			dfs(i);
	}
	reverse(todo.begin(), todo.end());
	for(int i=0;i<todo.size();i++){
		if(!vis2[todo[i]]){
			dfs2(todo[i]);
			for(int j=0;j<comp.size();j++){
				cout<<comp[j]<<" ";
			}
			cout<<"\n";
			comp.clear();
		}
	}
}

int main(){
	cout<<"Enter the number of vertices and the number of directed edges\n";
  	cin>>n>>m;
	int x,y;
	for(int i=0;i<m;i++){
		cin>>x>>y;
		sccAddEdge(x,y);
	}
	scc();

	return 0;
}
