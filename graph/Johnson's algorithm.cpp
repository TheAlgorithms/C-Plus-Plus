/*
*
*
*
*
*brief-- Johnson's algorithm*
*
*Details-
*finding shortest paths between
*every pair of vertices in a given
*weighted directed Graph and weights may be negative.
*
*
*
*
*---Complexity----
*O(V^2logV + V*E)
*
*
*
*---Application-----
*
*
*
*1.A new vertex is added to the graph, and it is connected by edges of zero weight to all other vertices in the graph.
*2.All edges go through a reweighting process that eliminates negative weight edges.
*3.The added vertex from step 1 is removed and Dijkstra's algorithm is run on every node in the graph.
*
*
*
*
*------Algorithm Idea-----
*
*1. Let the given graph be G.
Add a new vertex s to the graph,
add edges from new vertex to all vertices of G.
Let the modified graph be G’.
*
*
*2.Run Bellman-Ford algorithm on G’ with s as source.
Let the distances calculated by Bellman-Ford be h[0], h[1], .. h[V-1].
If we find a negative weight cycle, then return.
Note that the negative weight cycle cannot be created by new vertex s as there is no edge to s.
All edges are from s.
*
*
*3.Reweight the edges of original graph.
For each edge (u, v), assign the new weight as “original weight + h[u] – h[v]”.
*
*
*4.Remove the added vertex s and run Dijkstra’s algorithm for every vertex.
*
*
*/

/**
*
*
*-----Pseudo Code------
* 1.
    create G` where G`.V = G.V + {s},
        G`.E = G.E + ((s, u) for u in G.V), and
        weight(s, u) = 0 for u in G.V
*
* 2.
    if Bellman-Ford(s) == False
        return "The input graph has a negative weight cycle"
    else:
        for vertex v in G`.V:
            h(v) = distance(s, v) computed by Bellman-Ford
        for edge (u, v) in G`.E:
            weight`(u, v) = weight(u, v) + h(u) - h(v)
*
*
*3.
        D = new matrix of distances initialized to infinity
        for vertex u in G.V:
            run Dijkstra(G, weight`, u) to compute distance`(u, v) for all v in G.V
            for each vertex v in G.V:
                D_(u, v) = distance`(u, v) + h(v) - h(u)
        return D
*
*/



#include<iostream>
#define INF 9999
using namespace std;
int min(int a, int b);

int cost[10][10], adj[10][10]; // declaring two 2-D array

inline int min(int a, int b){
    /**Returns the minimum value*/
   return (a<b)?a:b;
}
main() {
   int vert, edge, i, j, k, c; // declaring variables
   cout << "Enter no of vertices: ";
   cin >> vert;
   cout << "Enter no of edges: ";
   cin >> edge;
   cout << "Enter the EDGE Costs:\n";
   for (k = 1; k <= edge; k++) {
        /**take the input and store it into adj and cost matrix*/
      cin >> i >> j >> c;
      adj[i][j] = cost[i][j] = c;
   }
   for (i = 1; i <= vert; i++)
      for (j = 1; j <= vert; j++) {
         if (adj[i][j] == 0 && i != j)
            adj[i][j] = INF;
   /**if there is no edge, put infinity*/
      }
   for (k = 1; k <= vert; k++)
      for (i = 1; i <= vert; i++)
         for (j = 1; j <= vert; j++)
            adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            /**find minimum path from i to j through k*/
   cout << "Resultant adj matrix\n";
   for (i = 1; i <= vert; i++) {
      for (j = 1; j <= vert; j++) {
            if (adj[i][j] != INF)
               cout << adj[i][j] << " ";
      }
      cout << "\n";
   }
   return 0;
}


/**
-----OUTPUT--------

Enter no of vertices: 3
Enter no of edges: 5
Enter the EDGE Costs:
1 2 8
2 1 12
1 3 22
3 1 6
2 3 4
Resultant adj matrix
0 8 12
10 0 4
6 14 0
*/


