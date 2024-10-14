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


Node* removeLeafNodes(Node* root, int target) {
        if(root == NULL){
            return NULL;
        }

        Node* left = removeLeafNodes(root->left, target);
        Node* right = removeLeafNodes(root->right, target);

        if(left == NULL && right == NULL && root->data == target){
            return NULL;
        }

        root->left = left;
        root->right = right;
        return root;
}

void printInOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

int main() {
    vector<int> nodes = {1, 2, -1, -1, 3, 2, -1, 2, -1, -1, 4, -1, -1};
    
    Node* root = buildTree(nodes);
    cout << "Tree before removing leaf nodes:\n";
    printInOrder(root);
    cout << endl;

    Node* ans = removeLeafNodes(root, 2);

    cout << "Tree after removing leaf nodes with target 2:\n";
    printInOrder(ans);
    cout << endl;

    return 0;
}