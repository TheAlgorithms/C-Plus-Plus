/**
 * Articulation Point in a Graph is a point
 * that if we remove that then our graph is divided into more
 * than one component.
 * In other words, it is a point that if we remove it
 * then the graph becomes disconnected.
 *
 * This algorithm is based on DFS and it is similar
 * to finding bridges in a graph.
 *
 * Where is this concept used?
 * 1. In network design, to find critical nodes in a network.
 * 2. In social networks, to find influential people.
 * 3. In transportation, to find critical junctions in a road network.
 * 4. In software engineering, to find critical modules in a software system.
 */

#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> dist, low;
vector<bool> visited;
set<int> articulationPoints;
int timer;
void dfs(int u, int parent);

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    dist.resize(n);
    low.resize(n);
    visited.resize(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    timer = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
    cout << "Articulation Points:" << endl;
    for (auto x : articulationPoints) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

void dfs(int u, int parent) {
    visited[u] = true;
    dist[u] = low[u] = timer++;
    int children = 0;
    for (int v : adj[u]) {
        if (v == parent)  // if v is parent of u then ignore it
            continue;
        if (visited[v]) {  // if v is already visited then it is a back edge
            // back edge
            low[u] = min(low[u], dist[v]);
        } else {  // else it is a tree edge
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // this is articulation point in case of non root node
            if (low[v] >= dist[u] && parent != -1) {
                articulationPoints.insert(u);
            }
            children++;
        }
    }
    // root case
    if (parent == -1 && children > 1) {
        articulationPoints.insert(u);
    }
}