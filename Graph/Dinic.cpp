// Dinic's algorithm to find max flow in a graph.
struct edge{
	int from, to;
	ll capacity, flow = 0;
	edge(int from, int to, ll cap) : from(from) , to(to), capacity(cap) {}
	void print(){
		cout<<"("<<from<<"->"<<to<<") capacity:"<<capacity<<" Flow:"<<flow<<endl;
	}
};

struct Dinic{
	const ll INF = 1e18;
	vector<edge> edges;				// stores the edges
	vector<vector<int>> adj;  // stores the id
	int n,m = 0; // Number of nodes ( including s and t), edges
	int source, sink;
	vector<int> level, ptr;
	queue<int> q;

	Dinic(int n, int s, int t) : n(n), source(s), sink(t){
		adj.resize(n);
		level.resize(n);
		ptr.resize(n);
	}

	void add_edge(int from, int to, ll cap){
		edges.emplace_back(from,to,cap); // Front
		edges.emplace_back(to,from,0); // Residual edge
		adj[from].push_back(m);
		adj[to].push_back(m+1);
		m += 2;
	}

	bool bfs(){
		while(!q.empty()){
			int from = q.front(); q.pop();
			for( auto id : adj[from] ){
				if( edges[id].capacity - edges[id].flow < 1 ) continue; // Dont have Cap
				if( level[edges[id].to] != -1 ) continue; // Already visited
				level[edges[id].to] = level[from] + 1;
				q.push(edges[id].to);
			}
		}
		return level[sink] != -1 ; // Was it possible to reach the sink
	}

	ll dfs(int from, ll pushed){
		if( pushed == 0 ) return 0;
		if( from == sink ) return pushed;

		for(auto& cid = ptr[from]; cid < (int)adj[from].size(); cid++ ){
			int id = adj[from][cid];
			int to = edges[id].to;
			if( (level[from] + 1 != level[to]) || (edges[id].capacity - edges[id].flow < 1) ) continue;
			ll get = dfs(to, min(pushed, edges[id].capacity - edges[id].flow) );
			if( get == 0 ) continue;
			edges[id].flow += get;
			edges[id^1].flow -= get;
			return get;
		}
		return 0;
	}

	ll flow(){
		ll f = 0;
		int iter = 0;
		while(true){
			fill(level.begin(), level.end(), -1);
			level[source] = 0;
			q.push(source);
			if( ! bfs() ){ break; }
			fill(ptr.begin(), ptr.end(), 0);
			while(ll pushed= dfs(source, INF)){
				f += pushed;
			}
		}
		return f;
	}
};

// see this soultion to understand how to use this: https://codeforces.com/problemset/submission/727/52666039
