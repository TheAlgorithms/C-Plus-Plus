/*
Edmonds-Karp Max Flow Algorithm. Works in O(V * E ^ 2) worst case.
This implementation only supports one edge per node-pair in the residual network.
*/
#include <algorithm>    // fill, min
#include <cstring>      // memset
#include <vector>
#include <limits>       // numeric_limits
#include <queue>

using namespace std;

// T is the capacity datatype
template<typename T>
struct EdmondsKarp {
    static const int NODES = ;  // <- insert value
    static const T INF = numeric_limits<T>::max();

    T cap[NODES][NODES];
    vector<int> adj[NODES];
    int p[NODES];

    void init() {
        fill(adj, adj + NODES, vector<int>());
    }

    void addEdge(int u, int v, T c) {
        adj[u].push_back(v);
        cap[u][v] = c;

        adj[v].push_back(u);
        cap[v][u] = 0;
    }

    bool bfs(int s, int t) {
        memset(p, -1, sizeof p);
        bitset<NODES> visit;
        queue<int> q;

        visit[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto v : adj[u]) {
                if (!visit[v] && cap[u][v] > ( T )0) {
                    p[v] = u;
                    visit[v] = true;
                    q.push(v);
                }
            }
        }

        return visit[t];
    }

    T maxflow(int s, int t) {
        T mf = 0;
        while (bfs(s, t)) {
            T f = INF;
            for (int u = t; u != s; u = p[u])
                f = min(f, cap[p[u]][u]);
            if (f == ( T )0)
                break;
            for (int u = t; u != s; u = p[u]) {
                cap[p[u]][u] -= f;
                cap[u][p[u]] += f;
            }
            mf += f;
        }
        return mf;
    }
};

// Sample usage:

/*
int main() {
    EdmondsKarp<int> mf;
    mf.init();

    // ...
    mf.addEdge(..., ...);

    s = // source
    t = // sink
    result = mf.maxflow(s, t);

    return 0;
}
*/

