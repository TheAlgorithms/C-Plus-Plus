//inorder traversal algorithm for tree data structure
#include <iostream>
using namespace std;

struct Node{
    int node_data;
    Node* left;
    Node* right;

    /*Constructor to assign the value of data to node_data, left and right pointer to NULL by default */

    Node(int data){
        node_data = data;
        left = right = NULL;
    }
};


/* Inorder traversal is a recursive algorithm which traverse the tree in a specific order. Following is the traversal order.
1. It visits left node of root recursively
2. then visit root Node
3. at last visit right node of root recursively
*/ 

void inorder_traversal(Node* root){
    if(root == NULL){
        return;
    }

    inorder_traversal(root->left);
    cout<<root->node_data<<" -> ";
    inorder_traversal(root->right);
}


int main(){
    // creating a tree
    struct Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    /* Tree:-
                        1
                      /   \
                     2     3
                   /  \   /  \
                  4    5  6   7
    */

   //calling the inorder_traversal function
   inorder_traversal(root);



}