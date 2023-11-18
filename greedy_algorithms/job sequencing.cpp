// 由于代码过长，这里只给出了部分代码，完整代码请参考相关教程或书籍。
#include<bits/stdc++.h>
using namespace std;

void addEdge(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
}

void topologicalSortUtil(int v, bool visited[], stack<int>& Stack, vector<int> adj[]) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size(); i++)
        if (!visited[adj[v][i]])
            topologicalSortUtil(adj[v][i], visited, Stack, adj);

    Stack.push(v);
}

void topologicalSort(vector<int> adj[], int V) {
    stack<int> Stack;
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack, adj);

    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

int main() {
    // 请根据实际情况添加边和顶点
    return 0;
}
