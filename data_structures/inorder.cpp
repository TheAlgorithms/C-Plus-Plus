/**
 * @file
 * @brief [Inorder Tree Traveral](https://www.javatpoint.com/inorder-traversal)
 * @author [Chaitanya Giri](https://github.com/Chaitanya134)
 */

#include <iostream>  /// for IO operations
#include <cassert>   /// for assert
#include <queue>     /// for storing node in level order traversal
using namespace std;

class Node {
public:
    int data;    // data stored in this node
    Node *left;  // pointer to the left node
    Node *right; // pointer to the right node
};

class BinaryTree {
public:
    /**
    * @brief insert a node in the tree using level order traversal
    * @param root root node of the tree
    * @param val value to be inserted
    * @returns void
    */
    void insertNode(Node* &root, int val) {
        // create a new node
        Node *newNode = new Node;
        newNode->data = val;
        newNode->left = NULL;
        newNode->right = NULL;

        if (root == NULL) {
            // point root to the new node if root is NULL
            root = newNode;
            return;
        }

        // queue for level order traversal
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node *node = q.front();
            q.pop();

            if (node->left) {
                // add to left child to queue
                q.push(node->left);
            } else {
                // add new node to the left if no left child is present
                node->left = newNode;
                return;
            }

            if (node->right) {
                // add right child to queue
                q.push(node->right);
            } else {
                // add new node to the right if no right child is present
                node->right = newNode;
                return;
            }
        }
    }

    /**
    * @brief [Algorithm implementation for inorder tree traversal]
    * @param node node from which inorder traversal will start
    * @returns void
    */
    void inorderTraversal(Node *node) {
        if (node == NULL) return;       // stop traversal if node is NULL

        inorderTraversal(node->left);   // recursively traverse current node's left subtree
        cout << node->data << " ";      // print the current node's data
        inorderTraversal(node->right);  // recursively traverse current node's right subtree
    }
};

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing inorder traversal
    BinaryTree tree;  // create a tree
    Node *root = NULL; // root node
    
    for(int i = 0; i < 15; i++) tree.insertNode(root, i);
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(root);

    return 0;
}