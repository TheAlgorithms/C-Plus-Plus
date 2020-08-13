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
 * 	Example - Here is a graph with 5 vertices and is bipartite
 *
 *		1   4
 *	   / \ / \
 *	  2   3   5
 *
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
    inline graph(int size) : adj(size, vector<int>()) { n=size; side.resize(size,-1); }

    void addEdge(int, int);     /// function to add edges to our graph

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
	bool check = true;
	queue<int> q;
	for (int current_edge = 0; current_edge < n; ++current_edge)
	{
		if(side[current_edge]==-1){
			q.push(current_edge);
			side[current_edge] = 0;
			while(q.size()){
				int current = q.front();
				q.pop();
				for(auto neighbour : adj[current]){
					if(side[neighbour]==-1){
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
	graph g(5);				/// creating a graph with 5 vertices
	/// adding edges to the graph as per the illustrated example
	g.addEdge(1,2);
	g.addEdge(1,3);
	g.addEdge(3,4);
	g.addEdge(4,5);

	/// checking whether the graph is bipartite or not
	if(g.is_bipartite()){
		std::cout<<"The given graph is a bipartite graph\n";
	} 
	else{
		std::cout<<"The given graph is not a bipartite graph\n";
	}
	return 0;
}
