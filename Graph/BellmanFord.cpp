#include<bits/stdc++.h> 
#include "./includes/graph.hpp"
#include "./includes/aux.hpp"

using namespace std; 

bool bellman_ford(Graph graph, int src) {

    cout << "Running Bellman Ford from source: " << src << endl;

    vector<int> dist(graph.num_v, INT_MAX);
    vector<int> parent(graph.num_v, -1);

    dist[src] = 0;
    parent[src] = src;

    // for each vertex
    for (int i = 1; i < graph.num_v; i++) {

        // iterate for all edges
        for (int j = 0; j < graph.num_v; j++) {
            list<pair<int,int>>::iterator k;
            for(k = graph.adjLists[j].begin(); k != graph.adjLists[j].end(); ++k) {
                int u = j;
                int v = k->first;
                int w = k->second;

                if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    parent[v] = u;
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    // iterate for all edges
    for (int j = 0; j < graph.num_v; j++) {
        list<pair<int,int>>::iterator k;
        for(k = graph.adjLists[j].begin(); k != graph.adjLists[j].end(); ++k) {
            int u = j;
            int v = k->first;
            int w = k->second;

            if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {

                cout << "Graph contains negative cycle \n \n";
                return false; // negative cycle is detected
            }
        }
    }

    cout << "to \t dist" << endl;
    for (int i = 0; i < graph.num_v; ++i) 
        cout << i << "\t " << dist[i] << endl;

    cout << endl << "vertex \t parent" << endl;
    for (int i = 0; i < graph.num_v; ++i)
        cout << i << "\t " << parent[i] << endl;
    return true;

}

int main(int argc, char *argv[]) {
    
    ifstream file;
    if(!getFile(argc, argv, file)) {
        exit(0);
    }

    Graph graph = create_graph(file);

    bellman_ford(graph, 0);

    return 0;
}