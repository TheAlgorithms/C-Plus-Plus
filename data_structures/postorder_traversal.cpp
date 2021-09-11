#include<iostream>
using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
};

Node* create_node(int data){
    Node* temp = new Node;
    temp->val = data;
    temp->left = temp->right = NULL;
    return temp;
}

void insert(int data,Node* root){
    // if the value of the root node is greater than
    // value of data to be inserted then we go in
    // left subtree
    if(root->val > data){
        if(root->left != NULL)
            insert(data,root->left);
        else
            root->left=create_node(data);
    }
    // if the value of the root node is lesser than
    // value of data to be inserted then we go in
    // right subtree
    if(root->val < data){
        if(root->right != NULL)
            insert(data,root->right);
        else
            root->right=create_node(data);
    }
}

void postorder_traversal(Node* root){
    if(root->left!=NULL)
        postorder_traversal(root->left);
    if(root->right!=NULL)
        postorder_traversal(root->right);

    cout<<root->val<<" ";
}

int main(){
    Node* root = create_node(5);
    insert(3,root);
    insert(4,root);
    insert(1,root);
    insert(8,root);
    insert(7,root);

    /* tree looks like
              5
            /   \  
           3     8
          / \    /
         1   4  7
         Postorder Traversal for the following tree looks like:
         -> 1 4 3 7 8 5
    */

    postorder_traversal(root);
    return 0;
}
// Time Complexity O(N)
// Space Complexity O(1)
