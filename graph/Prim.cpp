// C++ program to implement Prim's Algorithm
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int MAX = 1e4 + 5;
typedef pair<int, int> PII;

bool marked[MAX];
vector <PII> adj[MAX];

int prim(int x) {
    // priority queue to maintain edges with respect to weights
    priority_queue<PII, vector<PII>, greater<PII> > Q;
    int y;
    int minimumCost = 0;
    PII p;

    Q.push(make_pair(0, x));
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
        
        for (int i = 0;i < adj[x].size();++i) {
            y = adj[x][i].second;
            if (marked[y] == false)
                Q.push(adj[x][i]);
        }
    }
    return minimumCost;
}

int main()
{
    int nodes, edges, x, y;
    int weight, minimumCost;

    cin >> nodes >> edges;  // number of nodes & edges in graph

    // Edges with their nodes & weight
    for (int i = 0;i < edges;++i) {
        cin >> x >> y >> weight;
        adj[x].push_back(make_pair(weight, y));
        adj[y].push_back(make_pair(weight, x));
    }

    // Selecting 1 as the starting node
    minimumCost = prim(1);
    cout << minimumCost << endl;
    
    return 0;
}
