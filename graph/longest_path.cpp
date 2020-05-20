#include <iostrema>
#include <vector>

std::vector<int> arr[100001]; // a vector to store graph.
int vis[100001]; // an array that maintains that a node is vidited or not.
int maxd = -1;   // maxd is a variable that store the maximum distance.

void dfs(int node, int d) {
    vis[node] = 1;
    if (d > maxd) {
        maxd = d;
    }

    for (int child : arr[node]) // tranversing the all nodes inside this node.
        if (vis[child] == 0)
            dfs(child, d + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b; // n is the number of nodes
    cin >> n;

    // a and b is used to for input an edge between a and b.
    for (int i = 1; i < n; i++)
        cin >> a >> b, arr[a].pb(b), arr[b].pb(a);
    maxd = -1;
    dfs(1, 0);

    for (int i = 1; i < n; i++)
        vis[i] = 0;
    maxd = -1;

    dfs(maxNode, 0);
    std::cout << maxd << "\n";
    return 0;
}
