/**
 *  @file is_graph_bipartite
 *
 *	@brief Algorithm to check whether a graph is bipartite
 *
 *	@details
 *	A graph is a collection of nodes also called vertices and these vertices
 *	are connected by edges.A bipartite graph is a graph whose vertices can be
 * 	divided into two disjoint and independent sets U and V such that every edge 
 *	connects a vertex in U to one in V. 	
 *	(https://en.wikipedia.org/wiki/Bipartite_graph)
 *	The given Algorithm will determine whether the given graph is bipartite or not
 *
 *
 * 	Example - Here is a graph g1 with 5 vertices and is bipartite
 *
 *		1   4
 *	   / \ / \
 *	  2   3   5
 *	
 *	Example - Here is a graph G2 with 3 vertices and is not bipartite
 *
 *		1 --- 2
 *		 \   /
 *		   3
 *
 *	
 *	@author [Akshat Vaya](https://github.com/AkVaya)
 *		
 */
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

const int nax = 5e5 + 1;
/**
 * Class for representing graph as an adjacency list.
 */
class graph {
 	private: 
 		int n;						/// size of the graph

    	vector<vector <int> > adj;	/// adj stores the graph as an adjacency list

    	vector<int> side;			///stores the side of the vertex

 	public:
    /**
     * @brief Constructor that initializes the graph on creation
     */
    graph(int size = nax){
    	n = size;
    	adj.resize(n);
    	side.resize(n,-1);
    }

    void addEdge(int u, int v);     /// function to add edges to our graph

	bool is_bipartite();    	/// function to check whether the graph is bipartite or not

};
/**
 * @brief Function that add an edge between two nodes or vertices of graph
 *
 * @param u is a node or vertex of graph
 * @param v is a node or vertex of graph
 */
void graph::addEdge(int u, int v) {
    adj[u-1].push_back(v-1);
    adj[v-1].push_back(u-1);
}
/**
 *	@brief function that checks whether the graph is bipartite or not
 */
bool graph::is_bipartite(){
	n = adj.size();
	side.resize(n,-1);
	bool check = true;
	queue<int> q;
	for (int current_edge = 0; current_edge < n; ++current_edge)
	{
		if(side[current_edge] == -1){
			q.push(current_edge);
			side[current_edge] = 0;
			while(q.size()){
				int current = q.front();
				q.pop();
				for(auto neighbour : adj[current]){
					if(side[neighbour] == -1){
						side[neighbour] = (1 ^ side[current]);
						q.push(neighbour);
					}
					else{
						check &= (side[neighbour] != side[current]);
					}
				}
			}
		}
	}
	return check;
}
/**
 * main funtion
 */
int main(){
	graph G1(5);	/// creating graph G1 with 5 vertices
	/// adding edges to the graphs as per the illustrated example
	G1.addEdge(1,2);
	G1.addEdge(1,3);
	G1.addEdge(3,4);
	G1.addEdge(4,5);

	graph G2(3);	/// creating graph G2 with 3 vertices
	/// adding edges to the graphs as per the illustrated example
	G2.addEdge(1,2);
	G2.addEdge(1,3);
	G2.addEdge(2,3);
	/// checking whether the graphs are bipartite or not
	if(G1.is_bipartite()){
		std::cout<<"The given graph G1 is a bipartite graph\n";
	} 
	else{
		std::cout<<"The given graph G1 is not a bipartite graph\n";
	}
	if(G2.is_bipartite()){
		std::cout<<"The given graph G2 is a bipartite graph\n";
	} 
	else{
		std::cout<<"The given graph G2 is not a bipartite graph\n";
	}
	return 0;
}