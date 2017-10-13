#include<iostream>
#include<limits.h>

using namespace std;

//Wrapper class for storing a graph
class Graph{
	public:
	int vertexNum;
	int** edges;

	//Constructs a graph with V vertices and E edges
	Graph(int V){
		this->vertexNum = V;
		this->edges =(int**) malloc(V * sizeof(int*));
		for(int i=0; i<V; i++)
			this->edges[i] = (int*) calloc(V, sizeof(int));
		
	}

	//Adds the given edge to the graph 
	void addEdge(int src, int dst, int weight){
		this->edges[src][dst] = weight;
	}
	

};
//Utility function to find minimum distance vertex in mdist
int minDistance(int mdist[], bool vset[], int V){
	int minVal = INT_MAX, minInd;
	for(int i=0; i<V;i++)
		if(vset[i] == false && mdist[i] < minVal){
		minVal = mdist[i];
		minInd = i;
		}
			
	return minInd;
}

//Utility function to print distances
void print(int dist[], int V){
	cout<<"\nVertex  Distance"<<endl;
	for(int i = 0; i < V; i++){
		if( dist[i] != INT_MAX)
			cout<<i<<"\t"<<dist[i]<<endl;
		else
			cout<<i<<"\tINF"<<endl;
	}
}

//The main function that finds the shortest path from given source
//to all other vertices using Dijkstra's Algorithm.It doesn't work on negative
//weights
void Dijkstra(Graph graph, int src){
	int V = graph.vertexNum;
	int mdist[V]; //Stores updated distances to vertex
	bool vset[V]; // vset[i] is true if the vertex i included
			 // in the shortest path tree

	//Initialise mdist and vset. Set distance of source as zero
	for(int i=0; i<V; i++)
		mdist[i] = INT_MAX, vset[i] = false;
	
	mdist[src] = 0;
	
	//iterate to find shortest path
	for(int count = 0; count<V-1; count++){
		int u = minDistance(mdist,vset,V);
		
		vset[u] = true;
		
		for(int v=0; v<V; v++){
			if(!vset[v] && graph.edges[u][v] && mdist[u] + graph.edges[u][v] < mdist[v])
				mdist[v] = mdist[u] + graph.edges[u][v];
				
		}
	}

	print(mdist, V);
	
	return;
}

//Driver Function
int main(){
	int V,E,gsrc;
	int src,dst,weight;
	cout<<"Enter number of vertices: ";
	cin>>V;
	cout<<"Enter number of edges: ";
	cin>>E;
	Graph G(V);
	for(int i=0; i<E; i++){
		cout<<"\nEdge "<<i+1<<"\nEnter source: ";
		cin>>src;
		cout<<"Enter destination: ";
		cin>>dst;
		cout<<"Enter weight: ";
		cin>>weight;
		G.addEdge(src, dst, weight);
	}
	cout<<"\nEnter source:";
	cin>>gsrc;
	Dijkstra(G,gsrc);

	return 0;
}
