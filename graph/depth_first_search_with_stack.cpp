/**
 *
 * @file
 * @brief [Depth First Search Algorithm using Stack
 * (Depth First Search Algorithm)](https://en.wikipedia.org/wiki/Depth-first_search)
 *
 * @author [Ayaan Khan](http://github.com/ayaankhan98)
 * @author [Saurav Uppoor](https://github.com/sauravUppoor)
 *
 * @details
 * Depth First Search also quoted as DFS is a Graph Traversal Algorithm.
 * Time Complexity O(|V| + |E|) where V is number of vertices and E
 * is number of edges in graph.
 *
 * Application of Depth First Search are
 *
 * 1. Finding connected components
 * 2. Finding 2-(edge or vertex)-connected components.
 * 3. Finding 3-(edge or vertex)-connected components.
 * 4. Finding the bridges of a graph.
 * 5. Generating words in order to plot the limit set of a group.
 * 6. Finding strongly connected components.
 *
 * <h4>Working</h4>
 * 1. Mark all vertices as unvisited (colour it WHITE).
 * 2. Push starting vertex into the stack and colour it GREY.
 * 3. Once a node is popped out of the stack and is coloured GREY, we colour it BLACK.
 * 4. Push all its neighbours which are not coloured BLACK.
 * 5. Repeat steps 4 and 5 until the stack is empty.
 */

#include <iostream> 	 /// for IO operations
#include <stack>    	 /// header for std::stack
#include <vector>   	 /// header for std::vector
#include <cassert>  	 /// header for preprocessor macro assert() 
#include <limits>   	 /// header for limits of integral types

constexpr int WHITE = 0; /// indicates the node hasn't been explored
constexpr int GREY = 1;	 /// indicates node is in stack waiting to be explored
constexpr int BLACK = 2; /// indicates node has already been explored
constexpr int64_t INF = std::numeric_limits<int16_t>::max();


/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {
/**
 * @namespace depth_first_search
 * @brief Functions for [Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search) algorithm
 */
namespace depth_first_search {
/**
 * @brief
 * Adds and edge between two vertices of graph say u and v in this
 * case.
 *
 * @param adj Adjacency list representation of graph
 * @param u first vertex
 * @param v second vertex
 *
 */
void addEdge(std::vector<std::vector<size_t>> *adj, size_t u, size_t v) {
	/*
	*
	* Here we are considering undirected graph that's the
	* reason we are adding v to the adjacency list representation of u
	* and also adding u to the adjacency list representation of v
	*
	*/
	(*adj)[u - 1].push_back(v - 1);
}

/**
 *
 * @brief
 * Explores the given vertex, exploring a vertex means traversing
 * over all the vertices which are connected to the vertex that is
 * currently being explored and push it onto the stack.
 *
 * @param adj graph
 * @param start starting vertex for DFS
 * @return vector with nodes stored in the order of DFS traversal
 *
 */
std::vector<size_t> dfs(const std::vector<std::vector<size_t> > &graph, size_t start) {
    /// checked[i] stores the status of each node
    std::vector<size_t> checked(graph.size(), WHITE), traversed_path;

    checked[start] = GREY;
    std::stack<size_t> stack;
    stack.push(start);

    /// while stack is not empty we keep exploring the node on top of stack
    while (!stack.empty()) {
        int act = stack.top();
        stack.pop();

        if (checked[act] == GREY) {
            /// push the node to the final result vector
            traversed_path.push_back(act + 1);

            /// exploring the neighbours of the current node
            for (auto it : graph[act]) {
                stack.push(it);
                if (checked[it] != BLACK) {
                    checked[it] = GREY;
                }
            }
            checked[act] = BLACK;  /// Node has been explored
        }
    }
    return traversed_path;
}
}  // namespace depth_first_search
}  // namespace graph

/**
 * Self-test implementations
 * @returns none
 */
static void tests() {
	size_t start_pos;

	/// Test 1
	std::cout << "Case 1: " << std::endl;
	start_pos = 1;
	std::vector<std::vector<size_t> > g1(3, std::vector<size_t>());

	graph::depth_first_search::addEdge(&g1, 1, 2);
	graph::depth_first_search::addEdge(&g1, 2, 3);
	graph::depth_first_search::addEdge(&g1, 3, 1);

	std::vector<size_t> expected1 {1, 2, 3}; /// for the above sample data, this is the expected output
	assert(graph::depth_first_search::dfs(g1, start_pos - 1) == expected1);
	std::cout << "Passed" << std::endl;

	/// Test 2
	std::cout << "Case 2: " << std::endl;
	start_pos = 1;
	std::vector<std::vector<size_t> > g2(4, std::vector<size_t>());

	graph::depth_first_search::addEdge(&g2, 1, 2);
	graph::depth_first_search::addEdge(&g2, 1, 3);
	graph::depth_first_search::addEdge(&g2, 2, 4);
	graph::depth_first_search::addEdge(&g2, 4, 1);

	std::vector<size_t> expected2 {1, 3, 2, 4}; /// for the above sample data, this is the expected output
	assert(graph::depth_first_search::dfs(g2, start_pos - 1) == expected2);
	std::cout << "Passed" << std::endl;

	/// Test 3
	std::cout << "Case 3: " << std::endl;
	start_pos = 2;
	std::vector<std::vector<size_t> > g3(4, std::vector<size_t>());

	graph::depth_first_search::addEdge(&g3, 1, 2);
	graph::depth_first_search::addEdge(&g3, 1, 3);
	graph::depth_first_search::addEdge(&g3, 2, 4);
	graph::depth_first_search::addEdge(&g3, 4, 1);

	std::vector<size_t> expected3 {2, 4, 1, 3}; /// for the above sample data, this is the expected output
	assert(graph::depth_first_search::dfs(g3, start_pos - 1) == expected3);
	std::cout << "Passed" << std::endl;

}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // execute the tests

    size_t vertices = 0, edges = 0, start_pos = 1;
	std::vector<size_t> traversal;

    std::cout << "Enter the Vertices : ";
	std::cin >> vertices;
	std::cout << "Enter the Edges : ";
	std::cin >> edges;

    /// creating a graph
    std::vector<std::vector<size_t> > adj(vertices, std::vector<size_t>());

    /// taking input for the edges
    std::cout << "Enter the vertices which have edges between them : " << std::endl;
	while (edges--) {
		size_t u = 0, v = 0;
		std::cin >> u >> v;
		graph::depth_first_search::addEdge(&adj, u, v);
	}

    /// taking input for the starting position
    std::cout << "Enter the starting vertex [1,n]: " << std::endl;
	std::cin >> start_pos;
	start_pos -= 1;
	traversal = graph::depth_first_search::dfs(adj, start_pos);

    /// Printing the order of traversal
    for (auto x : traversal) {
		std::cout << x << ' ';
	}

    return 0;
}
