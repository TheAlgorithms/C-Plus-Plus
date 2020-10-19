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

int main() {

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
