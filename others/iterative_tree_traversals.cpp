/**
 * @file
 * @brief Iterative version of Preorder, Postorder, and preorder [Traversal of the Tree]
 * (https://en.wikipedia.org/wiki/Tree_traversal)
 * @author [Motasim](https://github.com/motasimmakki)
 * @details
 * 
 * ### Iterative Preorder Traversal of a tree
 * Create a Stack that will store the Node of Tree.
 * Push the root node into the stack.
 * Save the root into the variabe named as current, and pop and elemnt from the stack.
 * Store the data of current into the result array, and start traversing from it.
 * Push both the child node of the current node into the stack, first right child then left child.
 * Repeat the same set of steps untill the Stack becomes empty.
 * And return the result array as the preorder traversal of a tree.
 * 
 * ### Iterative Postorder Traversal of a tree
 * Create a Stack that will store the Node of Tree.
 * Push the root node into the stack.
 * Save the root into the variabe named as current, and pop and elemnt from the stack.
 * Store the data of current into the result array, and start traversing from it.
 * Push both the child node of the current node into the stack, first left child then right child.
 * Repeat the same set of steps untill the Stack becomes empty.
 * Now reverse the result array and then return it to the calling function as a postorder traversal of a tree.
 * 
 * ### Iterative Inorder Traversal of a tree
 * Create a Stack that will store the Node of Tree.
 * Push the root node into the stack.
 * Save the root into the variabe named as current.
 * Now iterate and take the current to the extreme left of the tree by traversing only to its left.
 * Pop the elemnt from the stack and assign it to the current.
 * Store the data of current into the result array.
 * Repeat the same set of steps until the Stack becomes empty or the current becomes NULL.
 * And return the result array as the inorder traversal of a tree.
 */
#include <iostream>   /// for I/O operations
#include <stack>      /// for `stack`
#include <vector>     /// for `vector`
#include <algorithm>  /// for `reverse`
#include <cassert>    /// for `assert`

/**
 * @namespace others
 * @brief Other algorithms
 */
namespace others {
/**
 * @namespace iterative_tree_traversals
 * @brief Functions for [Traversal of the Tree](https://en.wikipedia.org/wiki/Tree_traversal) algorithm
 */
namespace iterative_tree_traversals {
/**
 * @brief defines the structure of a node of the tree.
 */
struct Node{
    int data = 0;       ///< The value/key of the node.
    struct Node *left;  ///< struct pointer to left subtree.
    struct Node *right; ///< struct pointer to right subtree.
};

/**
 * @brief defines the functions associated with the binary tree.
 */
class BinaryTree {
    public:
        Node *createNewNode(int);                    ///< function that will create new node for insertion.
        std::vector<int> preOrderIterative(Node *);  ///< function that takes root of the tree as an argument, and returns its preorder traversal.
        std::vector<int> postOrderIterative(Node *); ///< function that takes root of the tree as an argument, and returns its postorder traversal.
        std::vector<int> inOrderIterative(Node *);   ///< function that takes root of the tree as an argument, and returns its inorder traversal.
};

/**
 * @brief will allocate the memory for a node and, along the data and return the node.
 * @param data 
 * @return pointer to the newly created node with assigned data. 
 */
Node *  BinaryTree::createNewNode(int data) {
    Node *node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

/**
 * @brief preOrderIterative() function that will perform the preorder traversal iteratively,
 * and return the result array that contain the preorder traversal of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the preorder traversal of a tree
 */
std::vector<int> BinaryTree::preOrderIterative(Node *root) {   
    std::stack<Node *> stack; ///< is used to find and traverse the child nodes.
    std::vector<int> result;  ///< list of values, sorted in pre-order.
    
    stack.push(root);
    
    while(!stack.empty()) {
        result.push_back(stack.top()->data);
        Node *current = stack.top();
        stack.pop();
        
        if(current->right) {
            stack.push(current->right);
        }
        if(current->left) {
            stack.push(current->left);
        }
    }
    
    return result;
}

/**
 * @brief postOrderIterative() function that will perform the postorder traversal iteratively,
 * and return the result array that contain the postorder traversal of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the postorder traversal of a tree
 */
std::vector<int> BinaryTree::postOrderIterative(Node *root) {   
    std::stack<Node *> stack; ///< is used to find and traverse the child nodes.
    std::vector<int> result;  ///< List of values, sorted in post-order.
    
    stack.push(root);
    
    while(!stack.empty()) {
        result.push_back(stack.top()->data);
        Node *current = stack.top();
        stack.pop();
        
        if(current->left) {
            stack.push(current->left);
        }
        if(current->right) {
            stack.push(current->right);
        }
    }

    reverse(result.begin(), result.end());
    
    return result;
}

/**
 * @brief inOrderIterative() function that will perform the inorder traversal iteratively,
 * and return the result array that contain the inorder traversal of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the inorder traversal of a tree
 */
std::vector<int> BinaryTree::inOrderIterative(Node *root) {
    std::stack<Node *> stack; ///< is used to find and traverse the child nodes.
    std::vector<int> result;  ///< List of values, sorted in in-order.

    Node *current = root;
    
    while(!stack.empty() || current) {
        while(current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();    
        result.push_back(current->data);   
        current = current->right;
    }   
    return result;
}
}  //  namespace iterative_tree_traversals
}  //  namespace others

/**
 * @brief Test the computed preorder with the actual preorder.
 * @param binaryTree instance of BinaryTree class
 * @param root head/root node of a tree
 */
static void test1(others::iterative_tree_traversals::BinaryTree binaryTree, others::iterative_tree_traversals::Node *root){
    std::vector<int> actual_result{1, 2, 4, 5, 3};
    std::vector<int> result; ///< result stores the preorder traversal if the binary tree

    // Calling preOrderIterative() function by passing a root node,
    // and storing the preorder traversal in result.
    result = binaryTree.preOrderIterative(root); 

    // Self-testing the result using assert.
    for(int i = 0; i < result.size(); i++)
        assert(actual_result[i] == result[i]);

    // Printing the result storing preorder.
    std::cout<< "\nPreOrder Traversal Is : "<< std::endl;
    for(auto i: result) {
        std::cout<< i<< "  ";
    }
}

/**
 * @brief Test the computed postorder with the actual postorder
 * @param binaryTree instance of BinaryTree class
 * @param root head/root node of a tree
 */
static void test2(others::iterative_tree_traversals::BinaryTree binaryTree, others::iterative_tree_traversals::Node *root){
    std::vector<int> actual_result{4, 5, 2, 3, 1};
    std::vector<int> result; ///< result stores the postorder traversal if the binary tree.

    // Calling postOrderIterative() function by passing a root node,
    // and storing the postorder traversal in result.
    result = binaryTree.postOrderIterative(root);

    // Self-testing the result using `assert`
    for(int i = 0; i < result.size(); i++)
        assert(actual_result[i] == result[i]);

    // Printing the result storing postorder.
    std::cout<< "\nPostOrder Traversal Is : "<< std::endl;
    for(auto i: result) {
        std::cout<< i<< "  ";
    }
}

/**
 * @brief Test the computed inorder with the actual inorder.
 * @param binaryTree instance of BinaryTree class
 * @param root head/root node of a tree
 */
static void test3(others::iterative_tree_traversals::BinaryTree binaryTree, others::iterative_tree_traversals::Node *root){
    std::vector<int> actual_result{4, 2, 5, 1, 3};
    std::vector<int> result; ///< result stores the inorder traversal if the binary tree.

    // Calling inOrderIterative() function by passing a root node,
    // and storing the inorder traversal in result.
    result = binaryTree.inOrderIterative(root);

    // Self-testing the result using `assert`
    for(int i = 0; i < result.size(); i++)
        assert(actual_result[i] == result[i]);

    // Printing the result storing inorder.
    std::cout<< "\nInOrder Traversal Is : "<< std::endl;
    for(auto i: result) {
        std::cout<< i<< "  ";
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Creating a tree with the following structure,
    /* 
              1
            /   \
           2     3
         /   \
        4     5
    */

    others::iterative_tree_traversals::BinaryTree binaryTree; ///< instace of BinaryTree, used to access its members functions.
    others::iterative_tree_traversals::Node *root = binaryTree.createNewNode(1);
    root->left = binaryTree.createNewNode(2);
    root->right = binaryTree.createNewNode(3);
    root->left->left = binaryTree.createNewNode(4);
    root->left->right = binaryTree.createNewNode(5);

    
    test1(binaryTree, root);  // run preorder-iterative test
    std::cout<< "\nPre-order test Passed!"<< std::endl;

    test2(binaryTree, root);  // run postorder-iterative test
    std::cout<< "\nPost-order test Passed!"<< std::endl;

    test3(binaryTree, root);  // run inorder-iterative test
    std::cout<< "\nIn-order test Passed!"<< std::endl;

    return 0;
}
