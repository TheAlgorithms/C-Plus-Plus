/**
 * @file strongly_connected_components.cpp
 * @author Kia Pousti
 * @brief Tarjan’s Algorithm to find Strongly Connected Components (SCC) in a directed graph
 * @date 2025-07-29
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std;

class TarjanSCC {
private:
    int V, time;
    vector<vector<int> > adj;
    vector<int> disc, low;
    vector<bool> inStack;
    stack<int> stk;
    vector<vector<int> > components;

    void dfs(int u) {
        disc[u] = low[u] = time++;
        stk.push(u);
        inStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (disc[u] == low[u]) {
            vector<int> scc;
            int v;
            do {
                v = stk.top(); stk.pop();
                inStack[v] = false;
                scc.push_back(v);
            } while (u != v);
            components.push_back(scc);
        }
    }

public:
    TarjanSCC(int V) : V(V), time(0), adj(V), disc(V, -1), low(V, -1), inStack(V, false) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    vector<vector<int> > getSCCs() {
        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1)
                dfs(i);
        }
        return components;
    }
};

int main() {
    TarjanSCC g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    auto sccs = g.getSCCs();

    // Assert the expected number of SCCs
    assert(sccs.size() == 3);

    // Print SCCs
    cout << "Strongly Connected Components:\n";
    for (const auto& scc : sccs) {
        for (int node : scc)
            cout << node << " ";
        cout << "\n";
    }

    return 0;
}
