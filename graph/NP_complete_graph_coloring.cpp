
#include <iostream> 
#include <list> 

// A class that represents an undirected graph 
namespace graph{
    
namespace NP_complete_graph_coloring{
    

class Graph { 
private:    
	int V;   // No. of vertices 
	std::list<int> *adj;  // A dynamic array of adjacency lists 
	
public:

	// Constructor and destructor 
	
	Graph(int V) { this->V = V; adj = new std::list<int>[V]; } 

	// function to add an edge to graph 
	
	void addEdge(int v, int w); 

	// Prints greedy coloring of the vertices 
	
	void greedyColoring(); 
}; 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 
	adj[w].push_back(v);  // Note: the graph is undirected 
} 

// Assigns colors (starting from 0) to all vertices and prints 
// the assignment of colors 

void Graph::greedyColoring() 
{ 
	int result[V]; 

	// Assign the first color to first vertex 
	
	result[0] = 0; 

	// Initialize remaining V-1 vertices as unassigned 
	
	for (int u = 1; u < V; u++){
			result[u] = -1;  // no color is assigned to u 
	}  

	// A temporary array to store the available colors. True 
	// value of available[color] would mean that the color 'color' is 
	// assigned to one of its adjacent vertices 
	
	bool available[V]; 
	for (int color = 0; color < V; color++){
		available[color] = false; 
	}
	// Assign colors to remaining V-1 vertices 
	
	for (int u = 1; u < V; u++){ 
		// Process all adjacent vertices and flag their colors 
		// as unavailable 
		
		std::list<int>::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i){
			if (result[*i] != -1){
					available[result[*i]] = true;
			}
		}			 

		// Find the first available color 
		int color;
		for (color = 0; color < V; color++){
			if (available[color] == false){
					break; 
			}
		}
		
		result[u] = color;  // Assign the found color 

		// Reset the values back to false for the next iteration 
		
		for (i = adj[u].begin(); i != adj[u].end(); ++i){
			if (result[*i] != -1){
					available[result[*i]] = false; 
			}
		}	
	} 

	// print the result 
	
	for (int u = 0; u < V; u++){
			std::cout << "Vertex " << u << " ---> Color "
			<< result[u] << std::endl;
	}		 
} 


}//namespace Graph

}//namespace np complete

//Function to test the above algorithm

static void test() {
    graph::NP_complete_graph_coloring::Graph G1(
        5);  /// creating graph G1 with 5 vertices
        
    /// adding edges to the graphs as per the illustrated example
    G1.addEdge(0, 1); 
	G1.addEdge(0, 2); 
	G1.addEdge(0, 4); 
	G1.addEdge(1, 2); 
	G1.addEdge(1, 3); 
	G1.addEdge(2, 3); 
	G1.addEdge(3, 4); 
    
    std::cout << "Coloring of graph G1 \n"; 
	G1.greedyColoring(); 
    
    graph::NP_complete_graph_coloring::Graph G2(
        4);  /// creating graph G2 with 4 vertices
        
    /// adding edges to the graphs as per the illustrated example
    G2.addEdge(0, 1); 
	G2.addEdge(0, 2); 
	G2.addEdge(0, 3); 
	G2.addEdge(1, 2); 
	G2.addEdge(2, 3); 
	
	std::cout << "\nColoring of graph G2 \n"; 
	G2.greedyColoring(); 

}

int main() 
{ 
	test();  /// Testing
    return 0;
} 

