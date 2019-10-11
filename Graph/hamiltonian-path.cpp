//A Hamiltonian path, is a path in an undirected or directed graph that visits each vertex exactly once.
 
#include<bits/stdc++.h>
using namespace std;
 
bool path(int x, int V, vector < vector <int> > adj, unordered_set <int> &s){
    if(s.size() == V) return true;
    for(int i = 0; i < adj[x].size(); i++){
        if(s.find(adj[x][i]) == s.end()){
            s.insert(adj[x][i]);
            bool hamiltonian = path(adj[x][i], V, adj, s);
            if(hamiltonian) return true;
            s.erase(adj[x][i]);
        }
    }
    return false;
}
 
int main()
 {
	//code
	int t;
	cin>>t;
	while(t--){
	    int V, E;
	    cin>>V>>E;
	    vector < vector <int> > adj(V);
	    for(int i = 0; i < E; i++){
	        int u, v;
	        cin>>u>>v;
	        u--;
	        v--;
	        adj[u].push_back(v);
	        adj[v].push_back(u);
	    }
	    bool hamiltonian = false;
	    for(int i = 0; i < V; i++){
	        unordered_set <int> s;
	        s.insert(i);
	        hamiltonian = path(i, V, adj, s);
	        if(hamiltonian) break;
	    }
	    if(hamiltonian) cout<<1<<endl;
	    else cout<<0<<endl;
	}
	return 0;
}
