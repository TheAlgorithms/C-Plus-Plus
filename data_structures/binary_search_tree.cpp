/**
 * \file
 * \brief A simple tree implementation using structured nodes
 *
 * \todo update code to use C++ STL library features and OO structure
 * \warning This program is a poor implementation - C style - and does not
 * utilize any of the C++ STL features.
 */
#include <iostream>
#include <memory>
#include <vector>
#include <queue>

// Node structure representing each element in the binary tree
struct Node {
    int val;
    std::unique_ptr<Node> left;   // Using unique_ptr for automatic memory management
    std::unique_ptr<Node> right;

    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    std::unique_ptr<Node> root; // Root of the binary tree

    // Insert a value into the tree
    void insert(int x) {
        if (!root) {
            root = std::make_unique<Node>(x); // Create root if it doesn't exist
        } else {
            insertHelper(root.get(), x); // Helper function for recursive insertion
        }
    }

    // Remove a value from the tree
    void remove(int x) {
        removeHelper(root, x); // Helper function to manage removal
    }

    // Breadth-first traversal of the tree
    void breadthFirstTraversal() const {
        if (!root) return;
        std::queue<Node*> q; // Using STL queue for level-order traversal
        q.push(root.get());
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->val << "  "; // Print the current node's value
            if (current->left) q.push(current->left.get());
            if (current->right) q.push(current->right.get());
        }
    }

    // Preorder traversal
    void preOrderTraversal() const {
        preOrderHelper(root.get());
    }

    // Inorder traversal
    void inOrderTraversal() const {
        inOrderHelper(root.get());
    }

    // Postorder traversal
    void postOrderTraversal() const {
        postOrderHelper(root.get());
    }

private:
    // Helper function for insertion
    void insertHelper(Node* node, int x) {
        if (x < node->val) {
            if (!node->left) {
                node->left = std::make_unique<Node>(x); // Create left child if it doesn't exist
            } else {
                insertHelper(node->left.get(), x); // Recur to the left
            }
        } else {
            if (!node->right) {
                node->right = std::make_unique<Node>(x); // Create right child if it doesn't exist
            } else {
                insertHelper(node->right.get(), x); // Recur to the right
            }
        }
    }

    // Helper function to find the maximum value in the left subtree
    Node* findMaxInLeft(Node* node) {
        while (node->right) {
            node = node->right.get();
        }
        return node;
    }

    // Helper function for removing a node
    Node* removeHelper(std::unique_ptr<Node>& node, int x) {
        if (!node) return nullptr; // Base case: node not found

        if (x < node->val) {
            node->left = removeHelper(node->left, x); // Recur left
        } else if (x > node->val) {
            node->right = removeHelper(node->right, x); // Recur right
        } else {
            // Node found: handle three cases
            if (!node->left) {
                return std::move(node->right); // No left child
            } else if (!node->right) {
                return std::move(node->left); // No right child
            } else {
                // Node with two children: replace with max value from left subtree
                int maxVal = findMaxInLeft(node->left.get())->val;
                node->val = maxVal; // Replace value
                node->left = removeHelper(node->left, maxVal); // Remove the max value
            }
        }
        return std::move(node); // Return updated node
    }

    // Preorder traversal helper
    void preOrderHelper(Node* node) const {
        if (node) {
            std::cout << node->val << "  "; // Visit node
            preOrderHelper(node->left.get()); // Recur left
            preOrderHelper(node->right.get()); // Recur right
        }
    }

    // Inorder traversal helper
    void inOrderHelper(Node* node) const {
        if (node) {
            inOrderHelper(node->left.get()); // Recur left
            std::cout << node->val << "  "; // Visit node
            inOrderHelper(node->right.get()); // Recur right
        }
    }

    // Postorder traversal helper
    void postOrderHelper(Node* node) const {
        if (node) {
            postOrderHelper(node->left.get()); // Recur left
            postOrderHelper(node->right.get()); // Recur right
            std::cout << node->val << "  "; // Visit node
        }
    }
};

int main() {
    BinaryTree tree;
    int value;
    std::cout << "\nEnter the value of root node: ";
    std::cin >> value;
    tree.insert(value); // Insert the root value

    int choice;
    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First"
                  << "\n0. Exit"
                  << "\nEnter Your Choice: ";
        std::cin >> choice;

        int x;
        switch (choice) {
        case 1:
            std::cout << "\nEnter the value to be Inserted: ";
            std::cin >> x;
            tree.insert(x); // Insert value
            break;
        case 2:
            std::cout << "\nEnter the value to be Deleted: ";
            std::cin >> x;
            tree.remove(x); // Remove value
            break;
        case 3:
            tree.breadthFirstTraversal(); // Perform breadth-first traversal
            break;
        case 4:
            tree.preOrderTraversal(); // Perform preorder traversal
            break;
        case 5:
            tree.inOrderTraversal(); // Perform inorder traversal
            break;
        case 6:
            tree.postOrderTraversal(); // Perform postorder traversal
            break;
        }
    } while (choice != 0); // Exit loop on choice 0

    return 0;
}
