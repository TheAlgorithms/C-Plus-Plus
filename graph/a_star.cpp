/**
 *  \addtogroup graph Graph Algorithms
 *  @{
 *  \file
 *  \brief [A* Search Algorithm
 *  (A* SEARCH)](https://en.wikipedia.org/wiki/A*_search_algorithm)
 * implementation
 *
 *  \author [Nirmalya Pal](http://github.com/SpEXterXD)
 *
 *  \details
 *  A* Search is an informed search algorithm that is used to find the shortest
 * path from a start node to a goal node in a graph. It uses a heuristic to
 * improve the efficiency of the search process.
 *
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * A structure to represent a node in the graph.
 */
struct Node {
    int id;        // Unique identifier for the node
    float gCost;   // Cost from the start node to this node
    float hCost;   // Heuristic cost from this node to the goal
    float fCost;   // Total cost (gCost + hCost)
    Node* parent;  // Pointer to the parent node in the path

    Node(int id) : id(id), gCost(0), hCost(0), fCost(0), parent(nullptr) {}
};

/**
 * A comparison operator for the priority queue to order nodes based on fCost.
 */
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->fCost > b->fCost;  // Min-heap based on fCost
    }
};

/**
 * Function to calculate the heuristic cost (Euclidean distance in this case).
 *
 * @param a - current node's position (x1, y1)
 * @param b - target node's position (x2, y2)
 * @return - heuristic cost
 */
float heuristic(int x1, int y1, int x2, int y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

/**
 * The A* search algorithm to find the shortest path in a graph.
 *
 * @param start - starting node's ID
 * @param goal - goal node's ID
 * @param graph - adjacency list of the graph (node ID -> list of (neighbor ID,
 * cost))
 * @param positions - map of node IDs to their (x, y) coordinates for heuristic
 * calculation
 * @return - vector of node IDs representing the shortest path
 */
std::vector<int> aStarSearch(
    int start, int goal,
    const std::unordered_map<int, std::vector<std::pair<int, float>>>& graph,
    const std::unordered_map<int, std::pair<int, int>>& positions) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode>
        openSet;                              // Nodes to be evaluated
    std::unordered_map<int, Node*> allNodes;  // To keep track of all nodes

    // Initialize the start node
    Node* startNode = new Node(start);
    startNode->hCost =
        heuristic(positions.at(start).first, positions.at(start).second,
                  positions.at(goal).first, positions.at(goal).second);
    startNode->fCost = startNode->hCost;  // Initial fCost
    openSet.push(startNode);
    allNodes[start] = startNode;

    while (!openSet.empty()) {
        Node* currentNode =
            openSet.top();  // Get the node with the lowest fCost
        openSet.pop();

        // If we reached the goal, reconstruct the path
        if (currentNode->id == goal) {
            std::vector<int> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode->id);
                currentNode = currentNode->parent;
            }
            std::reverse(path.begin(),
                         path.end());  // Reverse to get path from start to goal
            return path;
        }

        // Explore neighbors
        for (const auto& neighbor : graph.at(currentNode->id)) {
            int neighborID = neighbor.first;
            float cost = neighbor.second;

            // Calculate gCost for the neighbor
            float tentativeGCost = currentNode->gCost + cost;

            // If neighbor is not in the open set or found a better path
            if (allNodes.find(neighborID) == allNodes.end() ||
                tentativeGCost < allNodes[neighborID]->gCost) {
                if (allNodes.find(neighborID) == allNodes.end()) {
                    allNodes[neighborID] = new Node(neighborID);
                }
                Node* neighborNode = allNodes[neighborID];
                neighborNode->gCost = tentativeGCost;
                neighborNode->hCost = heuristic(positions.at(neighborID).first,
                                                positions.at(neighborID).second,
                                                positions.at(goal).first,
                                                positions.at(goal).second);
                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
                neighborNode->parent = currentNode;

                // Add to the open set if not already present
                openSet.push(neighborNode);
            }
        }
    }

    return {};  // Return an empty path if no path found
}

/**
 * Main function to demonstrate the A* search algorithm.
 */
int main() {
    // Example graph representation using an adjacency list
    std::unordered_map<int, std::vector<std::pair<int, float>>> graph = {
        {1, {{2, 1.0}, {3, 4.0}}},
        {2, {{1, 1.0}, {3, 2.0}, {4, 5.0}}},
        {3, {{1, 4.0}, {2, 2.0}, {4, 1.0}}},
        {4, {{2, 5.0}, {3, 1.0}}}};

    // Positions of the nodes for heuristic calculation (x, y coordinates)
    std::unordered_map<int, std::pair<int, int>> positions = {
        {1, {0, 0}}, {2, {1, 1}}, {3, {2, 2}}, {4, {3, 1}}};

    int start = 1;  // Starting node ID
    int goal = 4;   // Goal node ID

    std::vector<int> path = aStarSearch(start, goal, graph, positions);

    // Display the result
    if (!path.empty()) {
        std::cout << "Shortest path from " << start << " to " << goal << ": ";
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path found from " << start << " to " << goal << ".\n";
    }

    return 0;
}
/** @} */
