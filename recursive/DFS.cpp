/*
The provided C++ code implements a Tree Search using Depth-First Search (DFS).
The tree is represented by a custom TreeNode structure, where each node holds an
integer value and a list (vector) of its child nodes. The DFS function takes the
root node and a target value as input, recursively traversing the tree by
visiting each node and its children. It checks if the current node's value
matches the target, and if not, proceeds to explore all of its children. If the
target is found at any point, the function returns true; otherwise, it continues
searching the entire tree, returning false if the target is not found.

In the main function, a sample tree is constructed with a root node and its
children. The DFS algorithm is called to search for a specified target value in
the tree, and based on the result, a message is printed indicating whether the
target was found. The code also includes memory management by deallocating the
nodes after the search to prevent memory leaks. This recursive approach is
efficient for exploring trees, particularly when the structure is highly
irregular or when depth-based exploration is prioritized.
 */
#include <iostream>
#include <vector>
using namespace std;

// Tree node structure
struct TreeNode {
    int value;
    vector<TreeNode*> children;

    TreeNode(int val) : value(val) {}
};

// Depth-First Search (DFS) to search the tree
bool dfs(TreeNode* node, int target) {
    if (node == nullptr) {
        return false;
    }

    // Check if the current node is the target
    if (node->value == target) {
        return true;
    }

    // Traverse all children (recursive search)
    for (auto child : node->children) {
        if (dfs(child, target)) {
            return true;
        }
    }

    return false;
}

int main() {
    // Create a sample tree
    TreeNode* root = new TreeNode(1);
    TreeNode* child1 = new TreeNode(2);
    TreeNode* child2 = new TreeNode(3);
    TreeNode* child3 = new TreeNode(4);

    root->children.push_back(child1);
    root->children.push_back(child2);
    child1->children.push_back(child3);

    int target = 4;

    // Search the target in the tree
    if (dfs(root, target)) {
        cout << "Target " << target << " found in the tree." << endl;
    } else {
        cout << "Target " << target << " not found in the tree." << endl;
    }

    // Cleanup dynamically allocated memory
    delete root;
    delete child1;
    delete child2;
    delete child3;

    return 0;
}