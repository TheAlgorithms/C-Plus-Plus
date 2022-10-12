#include <bits/stdc++.h>
using namespace std;

public:
    //we use depth-first search to detect cycle in this undirected graph
    bool dfs(int v, vector<bool>&visitedArray, vector<int> adj[], int parent){
        visitedArray[v]=true;
        for (auto it: adj[v]){
            if (visitedArray[it]==false){ // if we visit an already visited node
                if (dfs(it, visitedArray, adj, v)){
                    return true;
                }
            }
            else if (it != parent){ //if the already visited node is not the parent of this current node, then there is a cycle
                return true;
            }
        }
        return false;
    }
  // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>visitedArray(V, false);
        for (int i=0; i<V; ++i){
            if (visitedArray[i]==false){
                if (dfs(i, visitedArray, adj, -1)){
                    return true;
                }
            }
        }
        return false;
    }
};


int main(){
	int tc;
	cin >> tc;
	while (tc--){
    //V - number of vertices
    //E - number of edges
		int V,E;
		cin >> V >> E;
		vector<int> adj[V]; // adjacency list
		for (int i=0; i<E; ++i){
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		Solution obj;
		bool ans=obj.isCycle(V, adj);
		if (ans)
			cout << "Cycle is detected" << endl;
		else
			cout << "No cycle is detected" << endl;
	}
	return 0;
}
