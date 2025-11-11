/**
 * @file cycle_check_undirected_dsu.cpp
 * @brief Detect cycle in an undirected graph using Disjoint Set Union (Union–Find).
 *
 * @details
 * This implementation uses the Union–Find (Disjoint Set Union) data structure
 * with path compression and union by rank for near-constant-time cycle detection.
 * For each edge (u, v):
 *   - If u and v belong to the same set, a cycle exists.
 *   - Otherwise, merge their sets.
 *
 * @complexity
 * - Time:  O(E α(V)), where α(V) is inverse Ackermann function (~constant)
 * - Space: O(V)
 *
 * @example
 * Input graph:
 *   0--1
 *   | /
 *   2
 * has a cycle.
 *
*/

#include <iostream>
#include <vector>
#include <unordered_set>

class DisjointSet {
 private:
    std::vector<int> parent, rank;

 public:
    explicit DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry)
            return false;  // cycle detected

        if (rank[rx] < rank[ry])
            parent[rx] = ry;
        else if (rank[rx] > rank[ry])
            parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
        return true;
    }
};

/**
 * @brief Detect if an undirected graph contains a cycle.
 * Avoids counting duplicated edges (v,u) and (u,v) twice.
 */
bool hasCycle(int V, const std::vector<std::pair<int, int>>& edges) {
    DisjointSet dsu(V);
    std::unordered_set<std::string> seen;

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        if (u == v)
            return true;  // self-loop is a cycle

        // Skip duplicate reversed edges
        std::string key1 = std::to_string(u) + "-" + std::to_string(v);
        std::string key2 = std::to_string(v) + "-" + std::to_string(u);
        if (seen.count(key1) || seen.count(key2))
            continue;
        seen.insert(key1);

        if (!dsu.unite(u, v))
            return true;  // cycle found
    }
    return false;
}

int main() {
    // Test 1: cyclic triangle
    {
        int V = 3;
        std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {0, 2}};
        std::cout << "Test 1 (triangle): " << (hasCycle(V, edges) ? "Cycle\n" : "No cycle\n");
    }

    // Test 2: simple chain
    {
        int V = 4;
        std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 3}};
        std::cout << "Test 2 (chain): " << (hasCycle(V, edges) ? "Cycle\n" : "No cycle\n");
    }

    // Test 3: disconnected with one cycle
    {
        int V = 6;
        std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {4, 5}};
        std::cout << "Test 3 (disconnected): " << (hasCycle(V, edges) ? "Cycle\n" : "No cycle\n");
    }

    // Test 4: self-loop
    {
        int V = 3;
        std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 2}};
        std::cout << "Test 4 (self-loop): " << (hasCycle(V, edges) ? "Cycle\n" : "No cycle\n");
    }

    return 0;
}
