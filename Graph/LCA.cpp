int tim=0;
int parent[LG][N];
int tin[N], tout[N], level[N];

void dfs(int k, int par, int lvl)
{
	tin[k]=++tim;
	parent[0][k]=par;
	level[k]=lvl;
	for(auto it:g[k])
	{
		if(it==par)
			continue;
		dfs(it, k, lvl+1);
	}
	tout[k]=tim;
}

int walk(int u, int h)
{
	for(int i=LG-1;i>=0;i--)
	{
		if((h>>i) & 1)
			u = parent[i][u];
	}
	return u;
}

void precompute()
{
	for(int i=1;i<LG;i++)
		for(int j=1;j<=n;j++)
			if(parent[i-1][j])
				parent[i][j]=parent[i-1][parent[i-1][j]];
}

int LCA(int u, int v)
{
	if(level[u]<level[v])
		swap(u,v);
	int diff=level[u]-level[v];
	for(int i=LG-1;i>=0;i--)
	{
		if((1<<i) & diff)
		{
			u=parent[i][u];
		}
	}
	if(u==v)
		return u;
	for(int i=LG-1;i>=0;i--)
	{
		if(parent[i][u] && parent[i][u]!=parent[i][v])
		{
			u=parent[i][u];
			v=parent[i][v];
		}
	}
	return parent[0][u];
}

int dist(int u, int v)
{
	return level[u] + level[v] - 2 * level[LCA(u, v)];
}
