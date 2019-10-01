//(Detection of Directed Cycle in a connected component): http://codeforces.com/contest/505/problem/D
vector<int> g[N], newg[N], rg[N], todo;
int comp[N], indeg[N]; 
bool vis[N];
vector<int> gr[N];

void dfs(int k)
{
    vis[k]=1;
    for(auto it:g[k])
    {
        if(!vis[it])
            dfs(it);
    }
    todo.push_back(k);
}

void dfs2(int k, int val)
{
    comp[k]=val;
    for(auto it:rg[k])
    {
        if(comp[it]==-1)
            dfs2(it, val);
    }
}

void sccAddEdge(int from, int to)
{
    g[from].push_back(to);
    rg[to].push_back(from);
}

void scc()
{
    for(int i=1;i<=n;i++)
        comp[i]=-1;

    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
            dfs(i);
    }

    reverse(todo.begin(), todo.end());

    for(auto it:todo)
    {
        if(comp[it]==-1)
        {
            dfs2(it, ++grp);
        }
    }
}