#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <cassert>
#include <limits>

constexpr int WHITE = 0;
constexpr int GREY = 1;
constexpr int BLACK = 2;
constexpr int64_t INF = std::numeric_limits<int16_t>::max();

namespace graph {

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
std::vector<size_t> dfs(const std::vector<std::vector<size_t> > &graph, size_t start) {
    std::vector<size_t> checked(graph.size(), WHITE), traversed_path;

    checked[start] = GREY;
    std::stack<size_t> stack;
    stack.push(start);
    while (!stack.empty()) {
        int act = stack.top();
        stack.pop();

        if (checked[act] == GREY) {
            traversed_path.push_back(act + 1);
            for (auto it : graph[act]) {
                stack.push(it);
                if (checked[it] != BLACK) {
                    checked[it] = GREY;
                }
            }
            checked[act] = BLACK;  // nodo controllato
        }
    }
    return traversed_path;
}
}

void tests() {
	size_t start_pos;

	/// Test 1
	std::cout << "Case 1: " << std::endl;
	start_pos = 1;
	std::vector<std::vector<size_t> > g1(3, std::vector<size_t>());

	graph::addEdge(&g1, 1, 2);
	graph::addEdge(&g1, 2, 3);
	graph::addEdge(&g1, 3, 1);

	std::vector<size_t> expected1 {1, 2, 3}; /// for the above sample data, this is the expected output
	assert(graph::dfs(g1, start_pos - 1) == expected1);
	std::cout << "Passed" << std::endl;

	/// Test 2
	std::cout << "Case 2: " << std::endl;
	start_pos = 1;
	std::vector<std::vector<size_t> > g2(4, std::vector<size_t>());

	graph::addEdge(&g2, 1, 2);
	graph::addEdge(&g2, 1, 3);
	graph::addEdge(&g2, 2, 4);
	graph::addEdge(&g2, 4, 1);

	std::vector<size_t> expected2 {1, 3, 2, 4}; /// for the above sample data, this is the expected output
	assert(graph::dfs(g2, start_pos - 1) == expected2);
	std::cout << "Passed" << std::endl;

	/// Test 3
	std::cout << "Case 3: " << std::endl;
	start_pos = 2;
	std::vector<std::vector<size_t> > g3(4, std::vector<size_t>());

	graph::addEdge(&g3, 1, 2);
	graph::addEdge(&g3, 1, 3);
	graph::addEdge(&g3, 2, 4);
	graph::addEdge(&g3, 4, 1);

	std::vector<size_t> expected3 {2, 4, 1, 3}; /// for the above sample data, this is the expected output
	assert(graph::dfs(g3, start_pos - 1) == expected3);
	std::cout << "Passed" << std::endl;

}

int main() {
    tests();
    
    size_t vertices = 0, edges = 0, start_pos = 1;
	std::vector<size_t> traversal;

    std::cout << "Enter the Vertices : ";
	std::cin >> vertices;
	std::cout << "Enter the Edges : ";
	std::cin >> edges;

    std::vector<std::vector<size_t> > adj(vertices, std::vector<size_t>());
    std::cout << "Enter the vertices which have edges between them : " << std::endl;

	while (edges--) {
		size_t u = 0, v = 0;
		std::cin >> u >> v;
		graph::addEdge(&adj, u, v);
	}

    std::cout << "Enter the starting vertex [1,n]: " << std::endl;
	std::cin >> start_pos;
	start_pos -= 1;
	traversal = graph::dfs(adj, start_pos);

    for (auto x : traversal) {
		std::cout << x << ' ';
	}

    return 0;
}
