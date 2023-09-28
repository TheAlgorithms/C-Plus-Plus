/**
 * @file
 * @brief Implementation to [inorder traversal of tree]
 * (https://www.geeksforgeeks.org/count-set-bits-in-an-integer/) in an
 * integer.
 *
 * @details
 * We are given an integer number. We need to calculate the number of set bits
 * in it.
 *
 * A binary tree consists of n nodes. We have to traverse in the Left side node, root node and then right node
 * Complexity Analysis
 * Worst Case Time Complexity: O(n)
 * Space complexity: O(n)
 * @author [Suraj Patil](https://github.com/SURAJPATIL6088)
 */

#include <iostream>  /// for io operations
using namespace std;

/**
 * @class Node
 * @brief Tree Traversals
 */
class Node
{

    public:
      int data;
      Node *left;
      Node *right;

    // parametrized contructor for assign the value
    Node(int x)
    {
        this->data = x;
        // initially left will points to the NULL
        this->left = NULL;
        // initially right will points to the NULL
        this->right = NULL;
    }
};

/**
 * @brief Function to create the tree from given nodes
 *
 * @param root node.
 */
Node *CreateTree(Node *root)
{
    // take the input from the user
    int data;
    cout<<"Enter the Data in Root Node : ";
    cin>>data;

    // add the input
    root = new Node(data);
    // if the input is -1 then it is the
    if(data == -1)
    {
        return NULL;
    }

    // get the data for left part
    cout<<"Enter the Data for Insert in Left : "<<data<<endl;
    root->left = CreateTree(root->left);
    
    // get the data for right part
    cout<<"Enter the Data for Insert in Right : "<<data<<endl;
    root->right = CreateTree(root->right);

    // return the root of the binary tree
    return root;
}
/**
 * @brief Function that perfoms inorder traversal on tree
 *
 * @param it takes the root node of the binary tree.
 * @param it traverse in these order - Left_Node -> Root_Node -> Right_Node
 */

void InOrder(Node *root)
{
    // Stack follows the LIFO (Last In First Out) Principle
    stack<Node *>s;
    Node *ptr = root;
    
    // boundary condition to check the given pointer that pointing to the node or stack is empty or not
  while(ptr != NULL || s.empty() == false)
    {
        // reach the left node of the ptr node
        while(ptr != NULL)
        {
            // place the pointer for traversing in left subtree
            s.push(ptr);
            // move the pointer to the left
            ptr = ptr->left;
        }

        // get the top of the stack
        ptr = s.top();
        // don't forget to pop element from the stack when we take top element
        s.pop();
        // print the data
        cout<<ptr->data<<" ";
        
        // we have visited the node and its left subtree
        // now we have visit right subtree
        ptr = ptr->right;
    }
}

/** Main function */
int main()
{
    // create the new node for the tree creation
    Node *root = NULL;

    // create the tree
    root = CreateTree(root);

    // make a function call with the root node
    InOrder(root);
    return 0;
}
