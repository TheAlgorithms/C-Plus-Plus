#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

int count(Node* root){

    if(root == NULL){
        return 0;
    }

    int leftcount = count(root->left);
    int rightcount = count(root->right);

    return leftcount + rightcount + 1;
}

int main()
{
    vector<int> nodes = {1,2,3,-1,-1,5,-1,-1,3,-1,6,-1,-1};

    Node* root = buildTree(nodes);

    cout << " Count 1 : " << count(root) << endl;

    // create yours nodes 
    Node* root2 = new Node(5);
    root2->left = new Node(3);
    root2->right = new Node(2);

    cout << " Count 2 : " << count(root2) << endl;
}