#include <iostream>
#include <vector>

namespace graph {
void addEdge(std::vector<std::vector<int>> *adj, int u, int v) {
    (*adj)[u].push_back(v);
    (*adj)[v].push_back(u);
}

bool isBipartite(std::vector<std::vector<int>> *adj, int *colour, int *vis,
                 int u, int p) {
    colour[u] = 1 - colour[p];
    vis[u] = 1;
    bool ret = true;
    for (int i = 0; i < (*adj)[u].size(); i++) {
        int v = (*adj)[u][i];
        if (v == p) {
            continue;
        }
        if (vis[v] && colour[v] == colour[u]) {
            return false;
        }
        if (vis[v]) {
            continue;
        }
        ret &= isBipartite(adj, colour, vis, v, u);
    }
    return ret;
}

}  // namespace graph

int main() {
    int vertices, edges;
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<int>> adj(vertices + 1, std::vector<int>());

    for (int a = 0; a < edges; a++) {
        int nodeA, nodeB;
        std::cin >> nodeA >> nodeB;
        graph::addEdge(&adj, nodeA, nodeB);
    }

    int vis[vertices + 1], colour[vertices + 1];
    for (int a = 0; a <= vertices; a++) vis[a] = 0, colour[a] = 0;
    bool isBipartite = true;
    for (int a = 1; a < vertices; a++) {
        if (vis[a] == 0) {
            isBipartite &= graph::isBipartite(&adj, colour, vis, a, 0);
        }
    }
    if (isBipartite) {
        printf("The graph is bipartite!\n");
    } else {
        printf("The graph is not bipartite!\n");
    }
    return 0;
}