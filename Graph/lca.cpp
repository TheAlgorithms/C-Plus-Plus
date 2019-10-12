const int N = 1e5 + 10, K = 18;
int par[N][K], h[N] = {0}; vector<int> graph[N];

void init(int n) {
	for(int i = 0; i < n + 5; i++) 
		for(int j = 0; j < K; j++) par[i][j] = -1;
}

void dfs(int v, int p = -1) {
	par[v][0] = p;
	if(p != -1) h[v] = h[p] + 1;
		
	for(int i = 1; i < K; i++) 
		if(par[v][i-1] != -1) 
			par[v][i] = par[par[v][i-1]][i-1];

	for(int i: graph[v]) if(i != p) dfs(i, v); 
}

int lca(int v, int u) {
	if(h[v] < h[u]) swap(v, u);
	
	for(int i = K-1; i >= 0; i--) 
		if(par[v][i] + 1 and h[par[v][i]] >= h[u]) 
			v = par[v][i];
	if(v == u) return u;
	
	for(int i = K-1; i >= 0; i--) {
		if(par[v][i] != par[u][i]) {
			v = par[v][i]; u = par[u][i];
	} } return par[v][0]; }