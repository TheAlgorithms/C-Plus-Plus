const int N = 1e5 + 10;
//REMEMBER TO CALL initDSU()
int dsu[N], sz[N];
void initDSU(int n) {for(int i = 0; i <= n; i++) sz[i] = 1, dsu[i] = i;}
int findp(int u) {if(dsu[u] == u) return u; return dsu[u] = findp(dsu[u]);}
bool merge(int u, int v){
	u = findp(u); v = findp(v);
	if(u == v) return false;
	if(sz[u] < sz[v]) swap(u, v);
	dsu[v] = u; sz[u] += sz[v];
	return true;
}