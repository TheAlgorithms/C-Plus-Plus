/**
 * @file
 * @brief Iterative version of Preorder, Postorder and preorder traversal of tree,
 *  (https://en.wikipedia.org/wiki/Tree_traversal).
 * @author [Motasim](https://github.com/motasimmakki)
 * @details
 * 
 * ->Iterative Preorder Traversal of a tree<-
 * Create a Stack that will store the Node of Tree.
 * Push the root node into the stack.
 * Save the root into the variabe named as current, and pop and elemnt from the stack.
 * Store the data of current into the result array, and start traversing from it.
 * Push both the child node of the current node into the stack, first right child then left child.
 * Repeat the same set of steps untill the Stack becomes empty.
 * And return the result array as the preorder traversal of a tree.
 * 
 * ->Iterative Postorder Traversal of a tree<-
 * Create a Stack that will store the Node of Tree.
 * Push the root node into the stack.
 * Save the root into the variabe named as current, and pop and elemnt from the stack.
 * Store the data of current into the result array, and start traversing from it.
 * Push both the child node of the current node into the stack, first left child then right child.
 * Repeat the same set of steps untill the Stack becomes empty.
 * Now reverse the result array and then return it to the calling function as a postorder traversal of a tree.
 * 
 * ->Iterative Inorder Traversal of a tree<-
 * Create a Stack that will store the Node of Tree.
 * Push the root node into the stack.
 * Save the root into the variabe named as current.
 * Now iterate and take the current to the extreme left of the tree by traversing only to its left.
 * Pop the elemnt from the stack and assign it to the current.
 * Store the data of current into the result array.
 * Repeat the same set of steps untill the Stack becomes empty or the current becames NULL.
 * And return the result array as the inorder traversal of a tree.
 */
#include<iostream> // For I/O operations.
#include<stdlib.h> // For maloc function.
#include<bits/stdc++.h> // For stack and vector.
using namespace std; // for using namespace std.

// struct that defines the structure of the node of a tree.
struct BinaryTree
{
	int data;
	struct BinaryTree *left;
	struct BinaryTree *right;
}typedef BT;

// createNewNode() function that will allocate the memory for a node and,
// along the data and return the node.
BT * createNewNode(int data){
	BT *node = (BT*) malloc(sizeof(BT));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

// preOrderIterative() function that will perform the preorder traversal iteratively,
// and return the result array that contain the preorder traversal of a tree.
vector<int> preOrderIterative(BT* root){   
    stack<BT*> stack;
    vector<int> result;
    
    stack.push(root);
    
    while(!stack.empty()){
        result.push_back(stack.top()->data);
        BT* current = stack.top();
        stack.pop();
        
        if(current->right)
            stack.push(current->right);
        if(current->left)
            stack.push(current->left);
    }
    
    return result;
}

// postOrderIterative() function that will perform the postorder traversal iteratively,
// and return the result array that contain the postorder traversal of a tree.
vector<int> postOrderIterative(BT* root){   
    stack<BT*> stack;
    vector<int> result;
    
    stack.push(root);
    
    while(!stack.empty()){
        result.push_back(stack.top()->data);
        BT* current = stack.top();
        stack.pop();
        
        if(current->left)
            stack.push(current->left);
        if(current->right)
            stack.push(current->right);
    }

    reverse(result.begin(), result.end());
    
    return result;
}

// inOrderIterative() function that will perform the inorder traversal iteratively,
// and return the result array that contain the inorder traversal of a tree.
vector<int> inOrderIterative(BT* root) {
        stack<BT*> stack;
        vector<int> result;
    
        BT* current = root;
        
        while(!stack.empty() || current){
            while(current){
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

// main() function or the driver function.
// @returns 0 on exit.
int main(){
    // Creating a tree with the following structure,
    /* 
              1
            /   \
           2     3
         /   \
        4     5
    */
    BT *root = createNewNode(1);
	root->left=createNewNode(2);
	root->right=createNewNode(3);
	root->left->left=createNewNode(4);
	root->left->right=createNewNode(5);

    // Calling preOrderIterative() function and passing a root node,
    // and printing its preorder traversal.
    vector<int> result = preOrderIterative(root);
    cout<< "\nPreOrder Traversal Is : "<< endl;
    for(int i = 0; i < result.size(); i++)
        cout<< result[i]<< "  ";
    
    // Calling postOrderIterative() function and passing a root node,
    // and printing its postorder traversal.
    result = postOrderIterative(root);
    cout<< "\nPostOrder Traversal Is : "<< endl;
    for(int i = 0; i < result.size(); i++)
        cout<< result[i]<< "  ";
    
    // Calling inOrderIterative() function and passing a root node,
    // and printing its inorder traversal.
    result = inOrderIterative(root);
    cout<< "\nInOrder Traversal Is : "<< endl;
    for(int i = 0; i < result.size(); i++)
        cout<< result[i]<< "  ";

    // End of main() funtion.
    return 0;
}