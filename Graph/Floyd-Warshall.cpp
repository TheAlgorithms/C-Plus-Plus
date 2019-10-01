/*
The floyd-warshall algorithm calculates a minimum distance between all vertex pairs in a single run.
The bidimensional array that maintains the distance between all pairs is initialized with the weight of the edges between nodes, and infinity when there is no edge between two vertices.
the distance from one node to itself is zero
The complexity for this is O(V³)
So it's more efficient than running the dijkstra algorithm V times
*/


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

using ii = pair<int, int>;


typedef struct edge_{
    int nodeA,nodeB,weight;
}edge;


const int MAX { 210 }, oo { 1000000010 };
int dist[MAX][MAX], pred[MAX][MAX];
vector<ii> adj[MAX];

void floyd_warshall(int N)
{
    for (int u = 1; u <= N; ++u)
        for (int v = 1; v <= N; ++v)
            dist[u][v] = oo;

    for (int u = 1; u <= N; ++u)
    {
        dist[u][u] = 0;
        pred[u][u] = u;
    }

    for (int u = 1; u <= N; ++u)
        for (const auto& [v, w] : adj[u]) {
            dist[u][v] = w;
            pred[u][v] = u;
        }

    for (int k = 1; k <= N; ++k)
    {
        for (int u = 1; u <= N; ++u)
        {
            for (int v = 1; v <= N; ++v)
            {
                if (dist[u][v] > dist[u][k] + dist[k][v])
                {
                    dist[u][v] = dist[u][k] + dist[k][v];
                    pred[u][v] = pred[k][v];
                }
            }
        }
    }
}

int main() {
    vector<edge> edges { edge{(1, 2, 9)}, edge{(1, 3, 7)}, edge{(1, 4, 4)}, 
        edge{(1, 5, 2)}, edge{(2, 3, 1)}, edge{(2, 6, 3)}, edge{(3, 4, 2)},
        edge{(4, 5, 1)}, edge{(5, 6, 11)} };

    int N = 6;

    for (auto& [u, v, w] : edges) {
        adj[u].push_back(ii(v, w));
        adj[v].push_back(ii(u, w));
    }

    floyd_warshall(N);

    for (int u = 1; u <= N; ++u)
    {
        for (int v = 1; v <= N; ++v)
        {
            vector<int> path;
            auto p = v;

            while (p != u) {
                path.push_back(p);
                p = pred[u][p];
            } 

            path.push_back(u);
            reverse(path.begin(), path.end());

            cout << "dist[" << u << "][" << v << "] = " << dist[u][v] 
                << '\n';

            for (size_t i = 0; i < path.size(); ++i)
                cout << path[i] << (i + 1 == path.size() ? "\n" : " -> ");
        }
    }

    return 0;
} 