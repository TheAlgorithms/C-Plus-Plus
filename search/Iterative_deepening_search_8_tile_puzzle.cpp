#include <bits/stdc++.h>
using namespace std;

#define N 3 // Define the size of the tile puzzle (3x3)

/**
 * @class Node
 * @brief Represents a state in the 8-tile puzzle.
 */
class Node {
private:
    vector<vector<int>> state;        ///< Current state of the puzzle
    pair<int, int> blankIndex;        ///< Index of the blank tile (0)
    Node *parent;                     ///< Parent node for tracing back the solution
    int depth;                        ///< Depth of the current node in the search tree

    /**
     * @brief Finds the index of the blank tile in the current state.
     * @return Pair of indices (row, column) of the blank tile.
     */
    pair<int, int> findBlankIndex() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1}; // Should not reach here if the state is valid
    }

public:
    /**
     * @brief Constructor for Node class.
     * @param state Initial state of the node.
     * @param parent Pointer to the parent node.
     * @param depth Depth of the node.
     */
    Node(const vector<vector<int>> &state, Node *parent, int depth) 
        : state(state), parent(parent), depth(depth) {
        blankIndex = findBlankIndex();
    }

    vector<vector<int>> getState() const { return state; }
    pair<int, int> getBlankIndex() const { return blankIndex; }
    int getDepth() const { return depth; }
};

/**
 * @class Solve8TilePuzzle
 * @brief Solves the 8-tile puzzle using iterative deepening search.
 */
class Solve8TilePuzzle {
public:
    vector<vector<int>> initialState, goalState; ///< Initial and goal states
    set<vector<vector<int>>> visitedList;        ///< Set to track visited states

    /**
     * @brief Constructor for Solve8TilePuzzle class.
     * @param initialState Initial state of the puzzle.
     * @param goalState Goal state of the puzzle.
     */
    Solve8TilePuzzle(const vector<vector<int>> &initialState, const vector<vector<int>> &goalState)
        : initialState(initialState), goalState(goalState) {}

    bool boundsOK(int i, int j) const {
        return (i >= 0 && i < N && j >= 0 && j < N);
    }

    /**
     * @brief Performs depth-limited search.
     * @param currNode Current node being explored.
     * @param depthLimit Maximum depth to explore.
     * @return True if goal state is found, false otherwise.
     */
    bool dls(Node *currNode, int depthLimit) {
        if (currNode->getDepth() > depthLimit) return false;
        visitedList.insert(currNode->getState());

        if (currNode->getState() == goalState) {
            printSolution(currNode);
            return true;
        }

        const vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (const auto &dir : dirs) {
            int newI = currNode->getBlankIndex().first + dir[0];
            int newJ = currNode->getBlankIndex().second + dir[1];

            if (!boundsOK(newI, newJ)) continue;

            vector<vector<int>> newState = currNode->getState();
            swap(newState[currNode->getBlankIndex().first][currNode->getBlankIndex().second], newState[newI][newJ]);
            Node *newNode = new Node(newState, currNode, currNode->getDepth() + 1);

            if (visitedList.find(newNode->getState()) == visitedList.end()) {
                if (dls(newNode, depthLimit)) return true;
            }
        }
        return false;
    }

    /**
     * @brief Initiates the iterative deepening search to solve the puzzle.
     */
    void iterativeDeepeningSearch() {
        for (int depth = 0; depth < INT_MAX; depth++) {
            visitedList.clear();
            Node *root = new Node(initialState, nullptr, 0);
            if (dls(root, depth)) return;
        }
    }

    /**
     * @brief Prints the solution path.
     * @param node The node at which the solution is found.
     */
    void printSolution(Node *node) {
        cout << "Solution found at depth " << node->getDepth() << endl;
        // Trace back to print the solution path if necessary
    }

    /**
     * @brief Checks if the puzzle is solvable based on inversions.
     * @return True if solvable, false otherwise.
     */
    bool isSolvable() const {
        int inversions = 0;
        for (int i = 0; i < N * N; i++) {
            for (int j = i + 1; j < N * N; j++) {
                if (initialState[i / N][i % N] && initialState[j / N][j % N] &&
                    initialState[i / N][i % N] > initialState[j / N][j % N]) {
                    inversions++;
                }
            }
        }
        return (inversions % 2 == 0);
    }
};

/**
 * @brief Takes user input for the initial state of the puzzle.
 * @param initialState Reference to the 2D vector where the input will be stored.
 */
void takeUserInput(vector<vector<int>> &initialState) {
    cout << "Enter the initial state of the 8-tile puzzle (0 for blank tile):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initialState[i][j];
        }
    }
}

/**
 * @brief Main function to run the 8-tile puzzle solver.
 */
int main() {
    vector<vector<int>> initialState(N, vector<int>(N, 0));
    vector<vector<int>> goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    takeUserInput(initialState);

    Solve8TilePuzzle solvePuzzle(initialState, goalState);
    if (solvePuzzle.isSolvable()) {
        solvePuzzle.iterativeDeepeningSearch();
    } else {
        cout << "\nNot Solvable" << endl;
    }

    return 0;
}
