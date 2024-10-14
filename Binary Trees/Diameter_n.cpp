#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
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

// (diameter,height)
pair<int, int> diam(Node* root){ // o(n)  
    
    if(root == NULL){
        return make_pair(0,0);
    }
    
      // (diamerter, height )
    pair<int, int> leftHt = diam(root->left); // (LD LH)
    pair<int, int> rightHt = diam(root->right); // (RD, RH)

    int currDiam = leftHt.second + rightHt.second + 1;
    int finaldiam = max(currDiam, max(leftHt.first, rightHt.first));

    int finalHt = max(leftHt.second,rightHt.second) + 1;

    return make_pair(finaldiam, finalHt);

}

int main() {
    vector<int> nodes = {1,2,3,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    int idx = 0;
    Node* root = buildTree(nodes, idx);

    cout << "Your tree Diameter is : " << diam(root).first << endl;

    return 0;
}
