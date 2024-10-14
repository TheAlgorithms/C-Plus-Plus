#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Node{ 
    public:
    int data;
    Node* left;
    Node* right;


    Node(int data){
        this->data = data;
        left = right = NULL;
    }
};

Node* sortedInorder(vector<int> arr, int st, int ed){

    if(st > ed){
        return NULL;
    }

    int mid = st +  (ed - st)/2;

    Node* currNode = new Node(arr[mid]);
    currNode->left = sortedInorder(arr, st, mid-1);
    currNode->right = sortedInorder(arr, mid+1, ed);

    return currNode;
    
}

void inorder(Node* root, vector<int>&nodes){
    if(root == NULL){
        return;
    }

    inorder(root->left, nodes);
    nodes.push_back(root->data);
    inorder(root->right, nodes);       
}

void preorder(Node* root){
    if(root == NULL){
        return ;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

Node* balanceBST(Node* root){
    
    vector<int> nodes;
    inorder(root, nodes);

    return sortedInorder(nodes, 0, nodes.size() - 1);

}
int main()
{
    // int arr[7] = {3,4,5,6,7,8,9};

    // Node *root = buildBst(arr,7);


    Node* root = new Node(6);
    root->left = new Node(5);
    root->left->left = new Node(4);
    root->left->left->left= new Node(3);


    root->right = new Node(7);
    root->right->right = new Node(8);
    root->right->right->right = new Node(9);


   root = balanceBST(root);
   preorder(root);
     
    return 0;
   
}