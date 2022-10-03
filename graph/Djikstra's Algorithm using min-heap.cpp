#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

const int inf = 1e9;


//Time Complexity O(Elog(V))
void djikstra(vector<vpii>& graph, int src, int v){
    vector<int> dist(v+1, inf);         //dist[i] will hold the shortest distance from src to i

    priority_queue<pii,vpii,greater<pii> > pq;

    vector<int> vis(v+1,0);
	pq.push({0,src});
	dist[src]=0;
	while(!pq.empty()){
		pii top = pq.top();
		pq.pop();
		int u = top.second;
        if(vis[u]) continue;
        vis[u] = 1;
		for(auto x: graph[u]){
			int v = x.first, w = x.second;
			if(dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				pq.push(pii(dist[v],v));
			}
		}
	}

    cout<<"vertex distance_from_src"<<endl;
    for(int i=1; i<=v; i++) cout<<i<<" "<<dist[i]<<endl;
}



int main(){
    int v,e;    //v = no. of vertices, e = no. of edges
    cin>>v>>e;

    vector<vpii> graph(v+1);

    for(int i=0; i<e; i++){
        int x,y,w;            //x and y are connected vertices and z is weight on that edge
        cin>>x>>y>>w;
        graph[x].push_back({y,w});
        graph[y].push_back({x,w});
    }

    int src;
    cin>>src;

    djikstra(graph, src, v);
}
