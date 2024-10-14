#include <iostream>
#include <vector>
#include <cmath>
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
Node* BuildTree(vector<int> nodes){

    idx++;

    if(nodes[idx] == -1){
        return NULL;
    }

    Node* currNode = new Node(nodes[idx]);
    currNode->left = BuildTree(nodes);
    currNode->right = BuildTree(nodes);

    return currNode;

}

int height(Node* root){

    if(root == NULL){
        return 0;
    }
    
  int ans = height(root->left) + height(root->right) + 1;


    return ans;
}

int main(){

    vector<int> nodes = {1,2,3,-1,-1,5,-1,-1,3,-1,6,-1,-1};

    Node* root = BuildTree(nodes);
    cout << root->data << endl;

    cout << "Height of tree is : " << height(root) << endl;

}