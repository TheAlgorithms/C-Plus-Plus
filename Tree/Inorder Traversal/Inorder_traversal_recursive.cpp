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

/**
* @output
* Create the Following Binary Tree and find Inorder traversal
*
*
*                   1 
*                  /  \
*                 /    \
*                3      5
*               / \    / \ 
*              /   \  /   \
*             7    11 17   NULL(-1)
*
*    InOrder Traversal - 7 3 11 1 17 5
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
void InOrderRecursion(Node *root)
{
    // check if root is not NULL
    if(root)
    {
        // first we have to traverse left subtree
        InOrder(root->left);
      
        // print the data
        cout<<root->data<<" ";
      
        // now we have to traverse right subtree
        InOrder(root->right);
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
    InOrderRecursion(root);
    return 0;
}
