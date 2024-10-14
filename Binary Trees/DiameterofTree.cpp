#include <iostream>
#include <vector>
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

Node* buildTree(vector<int>& nodes, int& idx){
    if(idx >= nodes.size() || nodes[idx] == -1){
        idx++;
        return NULL;
    }

    Node* currNode = new Node(nodes[idx]);
    idx++;
    currNode->left = buildTree(nodes, idx);
    currNode->right = buildTree(nodes, idx);

    return currNode;
}

 

int main() {
    vector<int> nodes = {1,2,3,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    int idx = 0;
    Node* root = buildTree(nodes, idx);

    cout << "Your tree Diameter is : " << diameter(root) << endl;

    return 0;
}
