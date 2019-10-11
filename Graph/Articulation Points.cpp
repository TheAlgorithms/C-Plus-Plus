const int N = 1e5 + 5;

int n;
int timer;
int tin[N], low[N];
bool vis[N], isArticulation[N];
vector<int> g[N];

void dfs(int u, int par)
{
	vis[u] = 1;
	tin[u] = low[u] = ++timer;
	int children = 0;
	for(auto &it:g[u])
	{
		if(it == par)
			continue;
		if(vis[it])
			low[u] = min(low[u], tin[it]);
		else
		{
			dfs(it, u);
			low[u] = min(low[u], low[it]);
			if(low[it] >= tin[u] && par != -1)
				isArticulation[u] = 1;
			children++;
		}
	}
	if(par == -1 && children > 1)
		isArticulation[u] = 1;
}

void articulationPoints()
{
	timer = 0;
	memset(vis, 0, sizeof(vis));
	memset(isArticulation, 0, sizeof(isArticulation));
	memset(tin, -1, sizeof(tin));
	memset(low, -1, sizeof(low));
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
			dfs(i, -1);
	}
}
