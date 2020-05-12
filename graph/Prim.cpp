// C++ program to implement Prim's Algorithm
#include <iostream>
#include <vector>
#include <queue>

const int MAX = 1e4 + 5;
typedef std:: pair<int, int> PII;

bool marked[MAX];
std:: vector <PII> adj[MAX];

int prim(int x) {
    // priority queue to maintain edges with respect to weights
    std:: priority_queue<PII, std:: vector<PII>, std:: greater<PII> > Q;
    int y;
    int minimumCost = 0;
    PII p;

    Q.push(std:: make_pair(0, x));
    while (!Q.empty()) {
        // Select the edge with minimum weight
        p = Q.top();
        Q.pop();
        x = p.second;
        // Checking for cycle
        if (marked[x] == true)
            continue;
        minimumCost += p.first;
        marked[x] = true;
        for (int i = 0; i < adj[x].size(); ++i) {
            y = adj[x][i].second;
            if (marked[y] == false)
                Q.push(adj[x][i]);
        }
    }
    return minimumCost;
}

int main() {
    int nodes, edges, x, y;
    int weight, minimumCost;

    std:: cin >> nodes >> edges;  // number of nodes & edges in graph
    if (nodes == 0 || edges == 0)
        return 0;

    // Edges with their nodes & weight
    for (int i = 0; i < edges; ++i) {
        std::cin >> x >> y >> weight;
        adj[x].push_back(std:: make_pair(weight, y));
        adj[y].push_back(std:: make_pair(weight, x));
    }

    // Selecting 1 as the starting node
    minimumCost = prim(1);
    std:: cout << minimumCost << std:: endl;
    return 0;
}
