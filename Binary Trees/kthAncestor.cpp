#include <vector>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;


class Node {
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

int kthAncestor(Node* root, int node, int k)
{
    if(root == NULL){
        return -1;
    }

    if(root->data == node){
        return 0;
    }

    int leftnode = kthAncestor(root->left, node, k);
    int rightnode = kthAncestor(root->right, node, k);

    int vaildVal = leftnode == -1 ? rightnode : leftnode;
    if(vaildVal + 1 == k){
        cout << "Kth Ancestor = " << root->data << endl;
    }

    return vaildVal + 1;
}
int main(){

    vector<int> nodes = {1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};

    Node* root = buildTree(nodes);
    cout << root->data << endl;

    kthAncestor(root, 6, 1); 

    return 0; 
} 