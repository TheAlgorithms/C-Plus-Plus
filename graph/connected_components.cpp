/*
 >> Given an undirected and unweighted graph. 
 >> This algorithm finds all the connected components in the graph, i.e, several groups of vertices such that
    within a group each vertex can be reached from another and no path exists between different groups.
 >> The algorithm works in O(V+E) time. Where V is the number of vertices(nodes) and E is the number of edges.
*/

#include<iostream>
#include<cstring>
#include<vector>
#define MAX 1001
using namespace std;

int nodes, edges, u, v;
vector<int> graph[MAX];
bool visited[MAX]; // Checks a node is visited or not.
vector<int> conctdComp; // Stores the nodes connected together (connected components).

void dfs(int source) {
    visited[source] = true;
    conctdComp.push_back(source);
    for(int i=0; i<graph[source].size(); i++) {
        int nod = graph[source][i];
        if(!visited[nod])
            dfs(nod);
    }
}

void PRINT_COMPONENTS() {
    cout << "Component: ";
    for(int j=0; j<conctdComp.size(); j++) 
        cout << conctdComp[j] << " ";
    cout << endl;
}

void find_connected_components() {
    memset(visited, false, sizeof visited); // Initially all nodes are unvisited

    // Run dfs on one node and find all its connected components(nodes) and they are all now visited.
    // Then we will find the first unvisited node of the remaining nodes and run dfs on it. 
    // As a result we will find its connected components.
    // This process continues untill all nodes are visited. 
    for(int i=1; i<=nodes; i++) {
        if(!visited[i]) {
            conctdComp.clear(); // Clear previously stored components(nodes).
            dfs(i);
            PRINT_COMPONENTS();
        }
    }
}

int main() {
    cout << "Total number of nodes:\n";
    cin >> nodes;
    cout << "Total number of edges:\n";
    cin >> edges;

    cout << "Two nodes which contains an edge between them:\n";
    for(int i=0; i<edges; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // For undirected graph.
    }

    find_connected_components();

    return 0;
}


/* ///Sample test cases & outputs///

    Sample input 1:
        Total number of nodes:
        4
        Total number of edges:
        4
        Two nodes which contains an edge between them:
        1 2
        3 4
        1 1
        4 4
    Sample output 1:
        component: 1 2
        component: 3 4


    Sample input 2:
        Total number of nodes:
        8
        Total number of edges:
        7
        Two nodes which contains an edge between them:
        1 2
        1 4
        2 3
        2 4
        4 5
        6 7
        8 8
    Sample output 2:
        Component: 1 2 3 4 5
        Component: 6 7
        Component: 8         
*/