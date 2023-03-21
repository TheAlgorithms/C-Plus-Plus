/**
 * @file
 * @brief [Inorder Tree Traveral](https://www.javatpoint.com/inorder-traversal)
 * @author [Chaitanya Giri](https://github.com/Chaitanya134)
 */

#include <iostream>  /// for IO operations
#include <cassert>   /// for assert
#include <queue>     /// for storing node in level order traversal
#include <sstream>   /// for converting expected output to a string

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
        std::queue<Node*> q;
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
        std::cout << node->data << " ";      // print the current node's data
        inorderTraversal(node->right);  // recursively traverse current node's right subtree
    }
};

/**
* @brief [Self-tests for inorder tree traversal]
* @returns void
*/
void test() {
    BinaryTree tree;    // create a tree
    Node *root = NULL;  // root node

    /* without any nodes (including root) */
    std::stringstream expected_output;
    expected_output << "";

    // Redirect cout to a stringstream buffer
    std::stringstream actual_output;
    std::streambuf* old = std::cout.rdbuf(actual_output.rdbuf());
    tree.inorderTraversal(root);
    std::cout.rdbuf(old);  // restore cout

    assert(actual_output.str() == expected_output.str());

    /* with only a root node */
    tree.insertNode(root, 8);

    expected_output << "8 ";

    old = std::cout.rdbuf(actual_output.rdbuf());
    tree.inorderTraversal(root);
    std::cout.rdbuf(old);

    assert(actual_output.str() == expected_output.str());

    /* perfect binary tree */
    tree.insertNode(root, 3);
    tree.insertNode(root, 10);
    tree.insertNode(root, 1);
    tree.insertNode(root, 6);
    tree.insertNode(root, 5);
    tree.insertNode(root, 2);

    expected_output << "1 3 6 8 5 10 2 ";
    old = std::cout.rdbuf(actual_output.rdbuf());
    tree.inorderTraversal(root);
    std::cout.rdbuf(old);

    assert(actual_output.str() == expected_output.str());
    expected_output.clear();
    actual_output.clear();

    /* complete binary tree */
    tree.insertNode(root, 14);
    tree.insertNode(root, 4);
    tree.insertNode(root, 7);
    tree.insertNode(root, 13);

    expected_output << "14 1 4 3 7 6 13 8 5 10 2 ";
    old = std::cout.rdbuf(actual_output.rdbuf());
    tree.inorderTraversal(root);
    std::cout.rdbuf(old);

    assert(actual_output.str() == expected_output.str());
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing inorder traversal
    test();

    BinaryTree tree;    // create a tree
    Node *root = NULL;  // root node
    
    for(int i = 0; i < 15; i++) tree.insertNode(root, i);
    std::cout << "Inorder Traversal: ";
    tree.inorderTraversal(root);

    return 0;
}
