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

std::vector<std::vector<int>>graph;
int tree_diameter;
int number_of_vertices, number_of_edges;
int longest_path_from_node(int u, int parent)
{
	    int longest_path = 0  ;
	    for(int to : graph[u])
	    {
			if(to  != parent)
			{
				int current_path = 1 + longest_path_from_node(to,u);
				tree_diameter = std::max(tree_diameter,  current_path + longest_path) ;
				longest_path = std::max(longest_path , current_path);
			}
		}
		return longest_path;
}

int main()
{
         	std::cout<<" Enter the number of vertices in the tree"<<std::endl;
         	std::cin>>number_of_vertices;
         	number_of_edges = number_of_vertices  - 1;       // edges  = vertices - 1 for a tree
         	 int x = 0, y = 0;
			graph.resize(number_of_vertices, std::vector<int>());
			for (int i = 0; i < number_of_edges; ++i) 
			{
				std::cin >> x >> y;
				x--, y--;  // to convert 1-indexed to 0-indexed
				graph[x].push_back(y);
				graph[y].push_back(x);
			}
			longest_path_from_node(0,-1);
			std::cout<<" Tree diameter is "<<tree_diameter<<"\n";
			return 0;
}
