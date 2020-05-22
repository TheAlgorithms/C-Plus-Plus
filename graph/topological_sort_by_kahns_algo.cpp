#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>

int *topoSortKahn(int N, std::vector<int> adj[]);

int main() {
    int nodes, edges;
    std::cin >> edges >> nodes;
    if (edges == 0 || nodes == 0)
        return 0;
    int u, v;

    std::vector<int>graph[nodes];
    // create graph
    // example
    // 6 6
    // 5 0 5 2 2 3 4 0 4 1 1 3

    for (int i = 0; i < edges; i++) {
        std::cin >> u >> v;
        graph[u].push_back(v);
    }

    int *topo = topoSortKahn(nodes, graph);
    // topologically sorted nodes
    for (int i = 0; i < nodes; i++) {
        std::cout << topo[i] << " ";
    }
}

int* topoSortKahn(int V, std::vector<int> adj[]) {
    std::vector<bool>vis(V+1, false);
    std::vector<int>deg(V+1, 0);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            deg[adj[i][j]]++;
        }
    }
    std::queue<int>q;
    for (int i = 0; i < V; i++) {
        if (deg[i] == 0) {
            q.push(i);
            vis[i] = true;
        }
    }
    int *arr = new int[V+1];
    memset(arr, 0, V+1);
    int count = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        arr[count] = cur;
        count++;
        for (int i = 0; i < adj[cur].size(); i++) {
            if (!vis[adj[cur][i]]) {
                deg[adj[cur][i]]--;
                if (deg[adj[cur][i]] == 0) {
                    q.push(adj[cur][i]);
                    vis[adj[cur][i]] = true;
                }
            }
        }
    }
    return arr;
}
