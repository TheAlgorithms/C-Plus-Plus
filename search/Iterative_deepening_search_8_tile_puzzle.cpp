#include <bits/stdc++.h>
using namespace std;

#define N 3 // for 3 x 3 tile size

class Node {
private:
    vector<vector<int>> state;
    pair<int, int> blankIndex;
    Node *parent;
    int depth;

    pair<int, int> findBlankIndex() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

public:
    Node(const vector<vector<int>> &state, Node *parent, int depth) 
        : state(state), parent(parent), depth(depth) {
        blankIndex = findBlankIndex();
    }

    vector<vector<int>> getState() { return state; }
    pair<int, int> getBlankIndex() { return blankIndex; }
    int getDepth() { return depth; }
};

class Solve8TilePuzzle {
public:
    vector<vector<int>> initialState, goalState;
    set<vector<vector<int>>> visitedList;

    Solve8TilePuzzle(const vector<vector<int>> &initialState, const vector<vector<int>> &goalState)
        : initialState(initialState), goalState(goalState) {}

    bool boundsOK(int i, int j) {
        return (i >= 0 && i < N && j >= 0 && j < N);
    }

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

    void iterativeDeepeningSearch() {
        for (int depth = 0; depth < INT_MAX; depth++) {
            visitedList.clear();
            Node *root = new Node(initialState, nullptr, 0);
            if (dls(root, depth)) return;
        }
    }

    void printSolution(Node *node) {
        cout << "Solution found at depth " << node->getDepth() << endl;
        // Print the path (not implemented here for simplicity)
    }

    bool isSolvable() {
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

void takeUserInput(vector<vector<int>> &initialState) {
    cout << "Enter the initial state of the 8-tile puzzle (0 for blank tile):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initialState[i][j];
        }
    }
}

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
