// C++ Program to find height of the tree using bottom - up DP.

/*
 * Given a rooted tree with node 1.
 * Task is to find the height of the tree.
 * Example: -
 * 4
 * 1 2
 * 1 3
 * 2 4
 * Height of the tree : - 3
*/

#include<iostream>
#include<vector>

// global declarations
// no of nodes max limit.
const int MAX = 1e5;
// adjacency list
std::vector<int> adj[MAX];
std::vector<bool> visited;
std::vector<int> dp;

void dp_with_dfs(int u) {
    visited[u] = true;
    int child_height = 1;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dp_with_dfs(v);

            // selected maximum subtree height from all child.
            child_height = std::max(child_height, dp[v]+1);
        }
    }
    // assigned the max child height to current visited node.
    dp[u] = child_height;
}

int main() {
    // number of nodes
    int n;
    std::cin >> n;
    int u, v;
    // Tree contains exactly n-1 edges where n denotes the nodes.
    for (int i = 0; i < n-1; i++) {
        std::cin >> u >> v;
        // undirected tree u -> v and v -> u.
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // initialize all nodes as unvisited.
    visited.assign(n+1, false);
    // initialize depth of all nodes to 0.
    dp.assign(n+1, 0);
    // function call which will initialize the height of all nodes.
    dp_with_dfs(1);
    std::cout << "Height of the Tree : " << dp[1] << std::endl;
}

