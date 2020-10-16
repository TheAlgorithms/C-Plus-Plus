#include <iostream>
#include <vector>

constexpr int V = 6;
constexpr int INFINITY = 99999;

std::vector< std::vector< int > >graph {{0, 4, 1, 4, INFINITY, INFINITY},
                   {4, 0, 3, 8, 3, INFINITY},
                   {1, 3, 0, INFINITY, 1, INFINITY},
                   {4, 8, INFINITY, 0, 5, 7},
                   {INFINITY, 3, 1, 5, 0, INFINITY},
                   {INFINITY, INFINITY, INFINITY, 7, INFINITY, 0}};

void findMinimumEdge() {
    for (int i = 0; i < V; i++) {
        int min = INFINITY;
        int minIndex = 0;
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != 0 && graph[i][j] < min) {
                min = graph[i][j];
                minIndex = j;
            }
        }
        std::cout << i << "  -  " << minIndex << "\t" << graph[i][minIndex] << std::endl;
    }
}

int main() {
    findMinimumEdge();
    return 0;
}
