/*
 >> Given an undirected and unweightrd graph. This algorithm finds if the graph is bicolorable or not.
 >> Bicolorable graph means we will be able to color all the nodes of the graph only using two colors, 
    and two adjacent nodes should be of different colors.
 >> This algorithm uses bfs traversal and works in O(V+E) time. where V is the number of vertices and E is the 
    number of edges. 
*/
#include<iostream>
#include<queue>
#include<cstring>
#define MAX 1001
#define WHITE 0
#define RED 2
#define BLUE 3
using namespace std;

int nodes, edges, u, v;
vector<int> graph[MAX]; // Adjacency list representation of the graph.
int color[MAX]; // Array used to store color of nodes.
queue<int> q;

// This function returns true if the graph is bicolorable and false otherwise.
bool is_bicolorable(int source) {
    q.push(source);
    color[source] = RED; // Setting a specific color to the source node

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(int i=0; i<graph[cur].size(); i++) {
            int next = graph[cur][i];
            
            if(color[next] == WHITE) {
                // The color of node 'cur' and node 'next' must be different
                if(color[cur] == RED)
                    color[next] = BLUE;
                else 
                    color[next] = RED;
                
                q.push(next);
            }

            // If color of 'cur' and 'next' is same, that means two adjacent nodes have
            // same color. That means the graph is not bicolorable.
            if(color[cur] == color[next]) 
                return false;
        }
    }
    return true;
}

int main() {
    cout << "Total nodes in the graph:\n";
    cin >> nodes;
    cout << "Total edges in the graph:\n";
    cin >> edges;

    cout << "Two nodes which contains an edge between them: \n";
    for(int i=0; i<edges; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); //used for Undirected graph. // comment out this line for directed graph.
    }

    memset(color, WHITE, sizeof color); // Initially color of all nodes is set to white.

    int source = 1;
    bool temp = is_bicolorable(source);

    if(temp)
        cout << "Bicolorable\n";
    else 
        cout << "Not bicolorable\n";

    return 0;
}