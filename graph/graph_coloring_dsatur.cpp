#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>

/**
 * @brief [DSatur graph coloring algorithm]
 * 
 * @author [Magdy Sedra](https://github.com/MSedra)
 *
 * @details
 * Graph Coloring: It is a way to color nodes or edges of a graph so that no adjacent nodes or edges have the same color.
 * Below is an implementation for the DSatur algorithm, which is a heuristic algorithm that finds the chromatic number (the minimum number of colors
 * needed to color the graph) and a valid coloring. It is implemented using red black tree (std::set) for efficiency. 
 * Nodes are traversed in order of:
 * 1) Highest Saturation Degree (number of unique colors in neighborhood).
 * 2) In case of ties, Highest Degree in the uncolored subgraph.
 * 3) In case of ties, Lower node index
 * Saturation of a node: It is the number of distinct colors that its neighbors are colored with.
 * A node picked is colored with the minimum possible color [1, maxDegree+1] and then is removed
 * from the graph by removing its edge from the degrees of its neighbors
 */


 /**
  * @brief [Graph class]
  *
  * @details
  * A class representing a graph.
  */

namespace graphcoloring {

	class Graph {
		std::vector<std::vector<int>> adjList;
		std::vector<int> degrees;
	public:

		Graph(int nodesCount) {
			assert(nodesCount > 0);
			adjList.resize(nodesCount);
			degrees.resize(nodesCount);
		}

		/**
		 * @brief Function returns the number of nodes in the graph
		 *
		 * @return the size of adjacency list which is equivalent to the number of nodes
		 */
		int getNodesCount() const {
			return adjList.size();
		}

		/**
		 * @brief Function adds an edge in the graph
		 *
		 * @param nodeA -> the first node in the edge
		 * @param nodeB -> the second node in the edge
		 */
		void addEdge(int nodeA, int nodeB) {
			int nodesCount = getNodesCount();
			assert(nodeA >= 0 && nodeA < nodesCount);
			assert(nodeB >= 0 && nodeB < nodesCount);
			adjList[nodeA].push_back(nodeB);
			adjList[nodeB].push_back(nodeA);
			++degrees[nodeA];
			++degrees[nodeB];
		}

		/**
		 * @brief Function returns the neighbors of a node
		 *
		 * @param node -> the node whose neighbors are requested
		 *
		 * @return the neighbors vector of the parameter node
		 */
		const std::vector<int>& getNeighbors(int node) const {
			int nodesCount = getNodesCount();
			assert(node >= 0 && node < nodesCount);
			return adjList[node];
		}

		/**
		 * @brief Function returns the degrees vector of the graph such that
		 * degrees[i] is the count of neighbors of node i.
		 *
		 * @return the degrees vector
		 */
		std::vector<int> getDegrees() const {
			return degrees;
		}
	};

	class DSatur {
		std::vector<int> colors;
	public:
		/**
		 * @brief Function runs the DSatur algorithm for a graph by find an optimal vertices coloring
		 * such that no 2 vertices sharing an edge have the same color. The function sets the resulting colors in the colors vector.
		 *
		 * @param graph -> input graph
		 */
		void solve(const Graph& graph) {
			int nodesCount = graph.getNodesCount();
			std::vector<int> degrees = graph.getDegrees();
			int maxDegree = *max_element(degrees.begin(), degrees.end());
			std::vector<std::vector<bool>> neighboringColors(nodesCount, std::vector<bool>(maxDegree + 2));
			std::vector<int> saturation(nodesCount);

			auto cmp = [&](int nodeA, int nodeB) {
				if (saturation[nodeA] != saturation[nodeB])
					return saturation[nodeA] > saturation[nodeB];
				if (degrees[nodeA] != degrees[nodeB])
					return degrees[nodeA] > degrees[nodeB];
				return nodeA < nodeB;
			};
			std::set<int, decltype(cmp)> tree(cmp);

			colors.clear();
			colors.resize(nodesCount, 0);
			for (int i = 0; i < nodesCount; ++i)
				tree.insert(i);

			while (!tree.empty()) {
				int nodeToColor = *tree.begin();
				int color = getValidColor(neighboringColors[nodeToColor], maxDegree);
				colors[nodeToColor] = color;
				for (auto neighbor : graph.getNeighbors(nodeToColor))
					if (!colors[neighbor]) {
						tree.erase(neighbor);
						if (!neighboringColors[neighbor][color]) {
							++saturation[neighbor];
							neighboringColors[neighbor][color] = true;
						}
						--degrees[neighbor];
						tree.insert(neighbor);
					}
				tree.erase(nodeToColor);
			}

		}

		/**
		 * @brief Function gets the minimum color [1, maxDegree+1] such that the number of neighbors
		 * colored with this color = 0
		 *
		 * @param neighborsColors -> neighborsColors[i] is true if there is at least 1 neighbor colored with color i
		 * @param maxDegree -> maximum degree of a node in the graph
		 *
		 * @return the minimum valid color [1, maxDegree+1]
		 */
		int getValidColor(const std::vector<bool>& neighborsColors, const int& maxDegree) const {
			for (int i = 1; i <= maxDegree + 1; ++i)
				if (!neighborsColors[i])
					return i;
		}

		/**
		 * @brief Function returns colors vector resulting from the DSatur algorithm
		 *
		 * @return the colors vector
		 */
		std::vector<int> getColors() const {
			return colors;
		}

		/**
		 * @brief Function returns the Chromatic Number resulting from the DSatur algorithm
		 *
		 * @return the maximum color in the colors vector, which is the Chromatic Number
		 */
		int getChromaticNumber() const {
			return *max_element(colors.begin(), colors.end());
		}
	};
}

static void test() {

	const int V = 4;

	graphcoloring::Graph graph(V);
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(0, 3);
	graph.addEdge(1, 2);
	graph.addEdge(2, 3);

	graphcoloring::DSatur dSatur;
	dSatur.solve(graph);

	std::cout << "Coloring graph with " << dSatur.getChromaticNumber() << " colors." << std::endl;
    const std::vector<int> colors = dSatur.getColors();
	for (int i = 0; i < V; ++i)
		std::cout << "Node " << i << " is colored with " << colors[i] << std::endl;

}

int main() {

	test(); 
	return 0;
}