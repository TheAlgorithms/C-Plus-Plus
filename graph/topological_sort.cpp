#include <algorithm>
#include <iostream>
#include <vector>

int number_of_vertices,
    number_of_edges;  // For number of Vertices (V) and number of edges (E)
std::vector<std::vector<int>> graph;
std::vector<bool> visited;
std::vector<int> topological_order;

void dfs(int v) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }
    topological_order.push_back(v);
}

void topological_sort() {
    visited.assign(number_of_vertices, false);
    topological_order.clear();
    for (int i = 0; i < number_of_vertices; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    reverse(topological_order.begin(), topological_order.end());
}
int main() {
    std::cout
        << "Enter the number of vertices and the number of directed edges\n";
    std::cin >> number_of_vertices >> number_of_edges;
    int x = 0, y = 0;
    graph.resize(number_of_vertices, std::vector<int>());
    for (int i = 0; i < number_of_edges; ++i) {
        std::cin >> x >> y;
        x--, y--;  // to convert 1-indexed to 0-indexed
        graph[x].push_back(y);
    }
    topological_sort();
    std::cout << "Topological Order : \n";
    for (int v : topological_order) {
        std::cout << v + 1
                  << ' ';  // converting zero based indexing back to one based.
    }
    std::cout << '\n';
    return 0;
}
