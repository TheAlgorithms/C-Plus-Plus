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


bool checkBST(Node* root, int key)
{
    if(root == NULL){
        return 0;
    }

    if(root->data == key){
        return true;
    }

    if(root->data < key){
        if(checkBST(root->right->data == key)){
            return true;
        }else{
            if(checkBST(root->left->data == key)){
                return true;
            }
        }
    }

    return false;
}


int main()
{
    vector<int>  nodes = {1,2,3,-1,-1,5,-1,-1,3,-1,6,-1,-1};

   Node* root =  buildTree(nodes);
   
   cout << "Roots = " << root->data << endl;

   cout << "Check BST" << checkBST(root, 2) << endl;
}