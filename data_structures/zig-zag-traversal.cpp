#include <iostream>
#include <queue>
#include <stack>
using namespace std;
/*
*  Author: Whitnie Ojie, github URL: github.com/whitojie
*  Tutorial on How to Perform Zig-Zag Level Order Traversal of a Binary Tree:
* 
 * Given a binary tree, the task is to find the zigzag level order traversal of the tree.
 * In zig-zag traversal starting from the first level go from left to right for odd-numbered
 * levels and right to left for even-numbered levels.
 *
*/


// Definition of a tree node
struct Node {
    int data; // The value stored in the node
    Node* left; // Pointer to the left child
    Node* right; // Pointer to the right child

    // Constructor to create a new node with a given value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to perform zig-zag traversal
void zigzagTraversal(Node* root) {
    // If the tree is empty, return immediately
    if (!root) { 
        return;
    }

    stack<Node*> currentLevel, nextLevel; // Two stacks to store nodes at the current and next levels
    bool leftToRight = true; // Boolean flag to track traversal direction

    currentLevel.push(root); // Start with the root node in the currentLevel stack

    while (!currentLevel.empty()) { // Continue until all nodes are processed
        Node* node = currentLevel.top(); // Get the top node from the current stack
        currentLevel.pop(); // Remove it from the stack

        if (node) {
            cout << node->data << " "; // Print the current node's value

            // If traversing from left to right, push left child first, then right child
            if (leftToRight) {
                if (node->left) {
                    nextLevel.push(node->left); // Push left child if exists
                }
                if (node->right){ 
                    nextLevel.push(node->right); // Push right child if exists
                }
            }
            // If traversing from right to left, push right child first, then left child
            else {
                if (node->right) {
                    nextLevel.push(node->right);
                }
                if (node->left) {
                    nextLevel.push(node->left); 
                }
            }
        }

        // If all nodes of the current level have been processed
        if (currentLevel.empty()) {
            leftToRight = !leftToRight; // Reverse the traversal direction for the next level
            swap(currentLevel, nextLevel); // Move nodes from nextLevel to currentLevel
        }
    }
}

// Helper function to create a sample binary tree
Node* createSampleTree() {
    // Manually creating a simple binary tree:
    //        1
    //       / \
    //      2   3
    //     / \ / \
    //    4  5 6  7
    Node* root = new Node(1); 
    root->left = new Node(2); 
    root->right = new Node(3); 
    root->left->left = new Node(4); 
    root->left->right = new Node(5); 
    root->right->left = new Node(6); 
    root->right->right = new Node(7); 
    return root; // Return the root of the tree
}

int main() {
    Node* root = createSampleTree(); // Create the binary tree
    cout << "Zig-Zag Traversal: ";
    zigzagTraversal(root); // Perform zig-zag traversal
    return 0;
}
