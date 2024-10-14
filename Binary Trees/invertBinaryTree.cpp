#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

static int idx = -1;

Node* buildTree(vector<int> nodes){

    idx++;

    if(nodes[idx] == -1){
        return NULL;
    }

    Node* currNode = new Node(nodes[idx]);
    currNode->left = buildTree(nodes);
    currNode->right = buildTree(nodes);

    return currNode;
}


Node* invertTree(Node* root){
    if(root == NULL){
        return root;
    }

    Node* left = invertTree(root->left);
    Node* right = invertTree(root->right);

    root->left = right;
    root->right = left;
    return root;
}


int main(){

    vector<int> nodes = {1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};

    Node* root = buildTree(nodes);

    cout << invertTree(root) << endl;
}