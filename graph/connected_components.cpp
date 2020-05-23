#include <iostream>
#include <vector>

using std::vector;

class graph {
 private:
    vector<vector<int>> adj;
    int connected_components;
    void depth_first_search();
    void explore(int, vector<bool>&);
 public:
    explicit graph(int n): adj(n, vector<int>()) {
      connected_components = 0;
    }
    void addEdge(int, int);
    int getConnectedComponents() {
      depth_first_search();
      return connected_components;
    }
};

void graph::addEdge(int u, int v) {
  adj[u-1].push_back(v-1);
  adj[v-1].push_back(u-1);
}

void graph::depth_first_search() {
  int n = adj.size();
  vector<bool> visited(n, false);

  for (int i = 0 ; i < n ; i++) {
    if (!visited[i]) {
      explore(i, visited);
      connected_components++;
    }
  }
}

void graph::explore(int u, vector<bool> &visited) {
  visited[u] = true;
  for (auto v : adj[u]) {
    if (!visited[v]) {
      explore(v, visited);
    }
  }
}

int main() {
  graph g(4);
  g.addEdge(1, 2);
  g.addEdge(3, 2);
  std::cout << g.getConnectedComponents();
  return 0;
}
