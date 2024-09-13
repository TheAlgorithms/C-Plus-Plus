#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

std::vector<int> topoSortKahn(int N, const std::vector<std::vector<int> > &adj);

int main() {
    int nodes = 0, edges = 0;
    std::cin >> edges >> nodes;
    if (edges == 0 || nodes == 0) {
        return 0;
    }
    int u = 0, v = 0;

    std::vector<std::vector<int> > graph(nodes);
    // create graph
    // example
    // 6 6
    // 5 0 5 2 2 3 4 0 4 1 1 3

    for (int i = 0; i < edges; i++) {
        std::cin >> u >> v;
        graph[u].push_back(v);
    }

    std::vector<int> topo = topoSortKahn(nodes, graph);
    // topologically sorted nodes
    for (int i = 0; i < nodes; i++) {
        std::cout << topo[i] << " ";
    }
}

std::vector<int> topoSortKahn(int V,
                              const std::vector<std::vector<int> > &adj) {
    std::vector<bool> vis(V + 1, false);
    std::vector<int> deg(V + 1, 0);
    for (int i = 0; i < V; i++) {
        for (int j : adj[i]) {
            deg[j]++;
        }
    }
    std::queue<int> q;
    for (int i = 0; i < V; i++) {
        if (deg[i] == 0) {
            q.push(i);
            vis[i] = true;
        }
    }
    std::vector<int> arr(V + 1, 0);
    int count = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        arr[count++] = cur;
        for (int i : adj[cur]) {
            if (!vis[i]) {
                deg[i]--;
                if (deg[i] == 0) {
                    q.push(i);
                    vis[i] = true;
                }
            }
        }
    }
    return arr;
}
