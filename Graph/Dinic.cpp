/*
Dinic's Max Flow Algorithm. Works in O(V ^ 2 * E) worst case.
- If the graph has unit capcities then O(V * E) worst case.
- If the graph is bipartite then O(E * sqrt(V)) (i.e. Hopcroft-Karp)
*/
#include <algorithm> // fill, min
#include <cstring>   // memset
#include <vector>
#include <limits>    // numeric_limits
#include <queue>

using namespace std;

// Only need to specify NODES, EDGES
// They denote the # of nodes, edges
// of the residual network (edges are
// counted twice because they are
// biderectional.

// T is data type of capacities
template<typename T>
struct Dinic {
    static const int NODES;     // <- insert value
    static const int EDGES;     // <- insert value
    static const int INF = numeric_limits<T>::max();

    vector<int> adj[NODES];
    int level[NODES], st[NODES];
    int to[EDGES], ed_cnt;
    T cap[EDGES];

    void init() {
        fill(adj, adj + NODES, vector<int>());
        ed_cnt = 0;
    }

    void addEdge(int u, int v, T c) {
        adj[u].push_back(ed_cnt);
        to[ed_cnt] = v;
        cap[ed_cnt] = c;
        ed_cnt++;

        adj[v].push_back(ed_cnt);
        to[ed_cnt] = u;
        cap[ed_cnt] = 0;
        ed_cnt++;
    }

    bool bfs(int s, int t) {
        memset(level, -1, sizeof level);
        queue<int> q;

        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == t) break;

            for (auto e : adj[u]) {
                int v = to[e];
                if (cap[e] > ( T )0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        return level[t] != -1;
    }

    T dfs(int u, const int t, T f) {
        if (u == t) return f;
        for (; st[u] < (int)adj[u].size(); st[u]++) {
            int e = adj[u][st[u]];
            int v = to[e];
            if (cap[e] <= ( T )0 || level[v] != level[u] + 1)
                continue;
            T ret = dfs(v, t, min(f, cap[e]));
            if (ret != ( T )0) {
                cap[e] -= ret;
                cap[e ^ 1] += ret;
                return ret;
            }
        }
        return ( T )0;
    }

    T maxflow(int s, int t) {
        T mf = 0;
        while (bfs(s, t)) {
            memset(st, 0, sizeof st);
            T f;
            while ((f = dfs(s, t, INF)) != ( T )0) {
                mf += f;
            }
        }
        return mf;
    }
};

// Sample usage:

/*
int main() {
    Dinic<int> mf;
    mf.init();

    // ...
    mf.addEdge(..., ...);

    s = // source
    t = // sink
    result = mf.maxflow(s, t);

    return 0;
}
*/

