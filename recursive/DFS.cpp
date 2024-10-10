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