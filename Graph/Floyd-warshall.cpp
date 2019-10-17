#include <iostream>
#include <vector>
#include <sstream>
 
void print(std::vector<std::vector<double>> dist, std::vector<std::vector<int>> next) {
  std::cout << "(pair, dist, path)" << std::endl;
  const auto size = std::size(next);
  for (auto i = 0; i < size; ++i) {
    for (auto j = 0; j < size; ++j) {
      if (i != j) {
        auto u = i + 1;
        auto v = j + 1;
        std::cout << "(" << u << " -> " << v << ", " << dist[i][j]
          << ", ";
        std::stringstream path;
        path << u;
        do {
          u = next[u - 1][v - 1];
          path << " -> " << u;
        } while (u != v);
        std::cout << path.str() << ")" << std::endl;
      }
    }
  }
}
 
void solve(std::vector<std::vector<int>> w_s, const int num_vertices) {
  std::vector<std::vector<double>> dist(num_vertices);
  for (auto& dim : dist) {
    for (auto i = 0; i < num_vertices; ++i) {
      dim.push_back(INT_MAX);
    }
  }
  for (auto& w : w_s) {
    dist[w[0] - 1][w[1] - 1] = w[2];
  }
  std::vector<std::vector<int>> next(num_vertices);
  for (auto i = 0; i < num_vertices; ++i) {
    for (auto j = 0; j < num_vertices; ++j) {
      next[i].push_back(0);
    }
    for (auto j = 0; j < num_vertices; ++j) {
      if (i != j) {
        next[i][j] = j + 1;
      }
    }
  }
  for (auto k = 0; k < num_vertices; ++k) {
    for (auto i = 0; i < num_vertices; ++i) {
      for (auto j = 0; j < num_vertices; ++j) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
  print(dist, next);
}
 
int main() {
  std::vector<std::vector<int>> w = {
    { 1, 3, -2 },
    { 2, 1, 4 },
    { 2, 3, 3 },
    { 3, 4, 2 },
    { 4, 2, -1 },
  };
  int num_vertices = 4;
  solve(w, num_vertices);
  std::cin.ignore();
  std::cin.get();
  return 0;
}
