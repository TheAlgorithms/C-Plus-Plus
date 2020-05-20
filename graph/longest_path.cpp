#include <iostream>
#include <vector>

std::vector<int> arr[100001]; // a vector to store graph.
int vis[100001]; // an array that maintains that a node is vidited or not.
int maxd = -1;   // maxd is a variable that store the maximum distance.
int maxNode;     // maxNode is a varaibale that store the maximum node.
void dfs(int node, int d) {
    vis[node] = 1;
    if (d > maxd) {
        maxd = d;
        maxNode = node;
    }

    for (int child : arr[node]) // tranversing the all nodes inside this node.
        if (vis[child] == 0)
            dfs(child, d + 1);
}

int main() {

    int n, a, b; // n is the number of nodes
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