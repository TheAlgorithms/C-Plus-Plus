/*
Problem Description:
Euler tour is defined as a way of traversing tree such that each vertex is added
to the tour when we visit it (either moving down from parent vertex or returning
from child vertex). We start from root and reach back to root after visiting all
vertices. It requires exactly 2*n-1 vertices to store Euler tour.

Test Case :
input:
4
1 2
2 3
2 4

output:
1 2 3 2 4 2 1
*/

#include <iostream>
#include <vector>
using namespace std;

const int N = 1000;
vector<int> adj[N+1];
vector<int>vis(N+1,0);

//stores Euler Tour
vector<int>eulerTour(2 * N);
//dfs implementation to generate euler tour
void eulerTree(int u, int &id) {
    vis[u] = 1;
    eulerTour[id++] = u;
    for (auto it : adj[u]) {
        if (!vis[it]) {
            eulerTree(it, id);
            eulerTour[id++] = u;
        }
    }
}

void solve(int root, int n) {
    int id = 0;
    eulerTree(root, id);
    for (int i = 0; i < (2 * n - 1); i++) 
        cout << eulerTour[i] << " ";
}

int main() {
    int n,u,v;
    cin >> n;
    for (int i = 1; i < n; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve(1, n);
    return 0;
}