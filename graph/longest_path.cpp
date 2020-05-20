#include <iostream>
#include <vector>
// a vector to store graph.

std::vector<int> arr[100001];
// an array that maintains that a node is vidited or not.
int vis[100001];
// maxd is a variable that store the maximum distance.
int maxd = -1;
// maxNode is a varaibale that store the maximum node.
int maxNode;
void dfs(int node, int d) {
    vis[node] = 1;
    if (d > maxd) {
        maxd = d;
        maxNode = node;
    }
    // tranversing the all nodes inside this node.
    for (int child : arr[node])
        if (vis[child] == 0)
            dfs(child, d + 1);
}

int main() {
    // n is the number of nodes
    int n, a, b;
    std::cin >> n;

    // a and b is used to for input an edge between a and b.
    for (int i = 1; i < n; i++) {

        std::cin >> a >> b;
        arr[a].push_back(b);
        arr[b].push_back(a);
    }
    maxd = -1;
    dfs(1, 0);
    for (int i = 1; i < n; i++) {
        vis[i] = 0;
    }
    maxd = -1;
    dfs(maxNode, 0);
    std::cout << maxd << "\n";
    return 0;
}
