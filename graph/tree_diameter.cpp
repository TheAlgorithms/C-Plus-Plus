/**
 * \file 
 * \brief  finds the diameter of a tree
 * \details
 *  Tree diameter is the longest path between any 2 nodes in the tree
 * [Tree Diameter](https://en.wikipedia.org/wiki/Treewidth)
 * 
 * @author [Rakshit P](https://github.com/rakki-18)
 */
 
#include<algorithm>
#include<iostream>
#include<vector>

/**
 * \namespace graph
 * \brief Graph algorithms
 */
namespace graph {


/**
 * \brief
 * Adds an undirected edge from vertex u to vertex v.
 * Essentially adds too directed edges to the adjacency list reprsentation
 * of the graph.
 *
 * @param adj Adjacency list representation of graph
 * @param u first vertex
 * @param v second vertex
 *
 */
void add_undirected_edge(std::vector<std::vector<int> > *adj, int u, int v) {
       (*adj)[u].push_back(v);
       (*adj)[v].push_back(u);
}

/**
 * \brief
 * Function finds the longest path starting from the given node
 *
 * @param adj Adjacency list representation of graph
 * @param node the current node from which we have to find the longest path
 * @param parent the parent of the current node
 * @param diameter a pointer that stores the value of the diameter of the tree
 * @returns an integer which is the longest path starting from the node
 *
 */

int longest_path_from_node( const std::vector<std::vector<int> > &adj, int node,int parent, int *diameter)
{
	
	         //  stores the longest path from the node
	         int longest_path = 0;
	         
			// traversing through all the children of the node
			for(auto to :  adj[node])
			{
				// can not include parent as the node's child
				if(to!=parent)
				{
					// current longest path will be the longest path from the child node and the edge from child to node
					int current_path = 1 + longest_path_from_node(adj,to,node,diameter);
					// diameter will be the maximum of the current diameter and the sum of the current path and longest path from the node
					*diameter = std::max(*diameter, current_path + longest_path);
					// updating the longest_path from the node as the maximum of the current_path and the longest path
					longest_path = std::max(longest_path, current_path);
				}
			}
			return longest_path;
}
/**
 * \brief
 * Function finds the diameter of the given tree
 *
 * @param adj Adjacency list representation of graph
 * @param root_node the root node of the given tree
 * @param vertices the number of vertices in the tree
 * @returns an integer which is the diameter of the given tree
 *
 */


int find_diameter( const std::vector<std::vector<int> > &adj, int root_node,int vertices)
{
	   // stores the diameter of the tree
		int *diameter;
		
		// calling the recursive function starting from the root node and "-1" as root node doesn't have a parent
		int var = longest_path_from_node(adj,root_node,-1,diameter);
		
		return (*diameter);
}
}

int main()
{
	        int vertices,edges;
         	std::cout<<" Enter the number of vertices in the tree"<<std::endl;
         	std::cin>>vertices;
             edges = vertices  - 1;       // edges  = vertices - 1 for a tree
         	
            // creating the graph
			std::vector<std::vector<int>> adj(vertices, std::vector<int>());
			std::cout<<"Enter the edges as a pair of vertices"<<std::endl;
			while(edges--)
			{
				
				int x = 0,y = 0;
				std::cin >> x >> y;
				graph::add_undirected_edge(&adj,x,y);
			}
			
			std::cout<<" Tree diameter is "<<graph::find_diameter(adj,0,vertices)<<"\n";
			return 0;
}
