#include<bits/stdc++.h>   // used for queue in the code
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e6;
int n,m;
vector<int> adj[N];   // adjacency list

int main(){
	cout<<"Enter the number of vertices and the number of directed edges\n";
  	cin>>n>>m;
	int x,y;
	vector<int> side(n, -1);  // set which eah edge belongs(0 or 1)
	for(int i=0;i<m;i++){
		cin>>x>>y;
		x--;
		y--;
		adj[x].push_back(y);
		adj[y].push_back(x);    // adds edges
	}
	bool is_bipartite = true;
	queue<int> q;
	for (int st = 0; st < n; ++st){
	    if (side[st] == -1){
	        q.push(st);
	        side[st] = 0;
	        while (!q.empty()) {
	            int v = q.front();
	            q.pop();
	            for (int u : adj[v]) {
	                if (side[u] == -1) {
	                    side[u] = side[v] ^ 1;
	                    q.push(u);
	                } else {
	                    is_bipartite &= side[u] != side[v];   // checks if two adjacent vertices are assigned the same set
	                }
	            }
	        }
	    }
	}

	cout << (is_bipartite ? "YES" : "NO") << endl;

// Test Case1:
// Input:
// 5 3
// 1 4
// 2 4
// 3 5
// Output:
// YES
//
// Test Case2:
// Input:
// 5 5
// 2 4
// 1 4
// 3 5
// 4 5
// 2 5
// Output:
// No
	return 0;
}
