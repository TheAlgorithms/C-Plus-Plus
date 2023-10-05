/**
 *
 * \file
 * \brief [Depth First Search Algorithm
 * (Depth First Search)](https://en.wikipedia.org/wiki/Depth-first_search)
 *
 * \author [Khalid Abdullah](http://github.com/khalid586)
 *
 * \details
 * Depth First Search also quoted as DFS is a Graph Traversal Algorithm.
 * Time Complexity O(|V| + |E|) where V is number of vertices and E
 * is number of edges in graph.
 *
 * Application of Depth First Search are
 *
 * 1. Finding connected components
 * 2. Finding 2-(edge or vertex)-connected components.
 * 3. Finding 3-(edge or vertex)-connected components.
 * 4. Finding the bridges of a graph.
 * 5. Generating words in order to plot the limit set of a group.
 * 6. Finding strongly connected components.
 *
 * And there are many more...
 *
 * <h4>Working</h4>
 * 1. Mark all vertices as unvisited first
 * 2. start exploring from some starting vertex.
 *
 *      While exploring vertex we mark the vertex as visited
 *      and start exploring the vertices connected to this
 *      vertex in recursive way.
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 1;
int vis[N];  // array for marking the nodes as visited or unvisited
std::vector<int> graph[N];  // graph given by the user

void dfs(int starting_node) {
    cout << starting_node << ' ';
    vis[starting_node] = 1;  // node will be marked as visited

    for (auto child : graph[starting_node]) {
        if (vis[child] == 0) {  // DFS will be applied if it is unvisited
            dfs(child);
        }
    }
}

int main() {
    int node, edges;
    cin >> node >> edges;  // Take input from user [how many nodes and edges are there(can't be more than 1e7)]

    for (int i = 0; i < edges; i++) {
        int x, y;
        cin >> x >> y;  // Two connected nodes
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for (int i = 1; i <= node; i++) {
        if (vis[i] == 0) {  // we will apply dfs on a node if it is unvisited
            dfs(i);
        }
    }

    cout << endl;
}