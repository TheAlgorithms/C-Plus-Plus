//#include<bits/stdc++.h>
#include <iostream>

using namespace std;
// Find the lowest common ancestor using binary lifting in O(nlogn)
// Zero based indexing
// Resource : https://cp-algorithms.com/graph/lca_binary_lifting.html
const int N = 1005;
const int LG = log2(N) + 1;
struct lca
{
    int n;
    vector<int> adj[N]; // Graph
    int up[LG][N]; // build this table
    int level[N]; // get the levels of all of them

    lca(int n_): n(n_)
    {
        memset(up, -1, sizeof(up));
        memset(level, 0, sizeof(level));
        for (int i = 0; i < n - 1; ++i)
	{
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        level[0] = 0;
        dfs(0, -1);
        build();
    }
    void verify()
    {
        for (int i = 0; i < n; ++i)
	{
            cout << i << " : level: " << level[i] << endl;
        }
        cout << endl;
        for (int i = 0; i < LG; ++i)
	{
            cout << "Power:" << i << ": ";
            for (int j = 0; j < n; ++j)
	    {
                cout << up[i][j] << " ";
            }
            cout << endl;
        }
    }

    void build()
    {
        for (int i = 1; i < LG; ++i)
	{
            for (int j = 0; j < n; ++j)
	    {
                if (up[i - 1][j] != -1)
		{
                    up[i][j] = up[i - 1][up[i - 1][j]];
                }
            }
        }
    }

    void dfs(int node, int par)
    {
        up[0][node] = par;
        for (auto i: adj[node])
	{
            if (i != par)
	    {
                level[i] = level[node] + 1;
                dfs(i, node);
            }
        }
    }
    int query(int u, int v)
    {
        u--;
        v--;
        if (level[v] > level[u])
	{
            swap(u, v);
        }
        // u is at the bottom.
        int dist = level[u] - level[v];
        // Go up this much distance
        for (int i = LG - 1; i >= 0; --i)
	{
            if (dist & (1 << i))
	    {
                u = up[i][u];
            }
        }
        if (u == v)
	{
            return u;
        }
        assert(level[u] == level[v]);
        for (int i = LG - 1; i >= 0; --i)
	{
            if (up[i][u] != up[i][v])
	    {
                u = up[i][u];
                v = up[i][v];
            }
        }
        assert(up[0][u] == up[0][v]);
        return up[0][u];
    }
};

int main()
{
    int n; // number of nodes in the tree.
    lca l(n); // will take the input in the format given
    // n-1 edges of the form
    // a b
    // Use verify function to see.
}
