#include <iostream>
#include <vector>
#include <cmath>
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

Node* insert(Node* root, int val){
    if(root == NULL){
        root = new Node(val);
        return root;
    }

    if(root->data > val){
        root->left = insert(root->left, val);
    }else{
        root->right = insert(root->right, val);
    }
}

Node* buildBST(int arr[], int n){
    Node* root = NULL;

    for(int i=0; i<n; i++){

        root = insert(root, arr[i]);
    }

    return root;
}
void printPath(vector<int> path){
    cout << "Path of Length is :- ";
    for(int i=0; i<path.size(); i++){
        cout  << path[i] << " ";
    }

    cout << endl;
}

void pathOfRoot(Node* root, vector<int>& path){
    if(root == NULL){
        return ;
    }

    path.push_back(root->data);

    if(root->left == NULL && root->right == NULL){
        printPath(path);
        path.pop_back();
        return;
    }

    pathOfRoot(root->left, path);
    pathOfRoot(root->right, path);

    path.pop_back();
}

void rootToLeaf(Node* root){
    vector<int> pth;

    pathOfRoot(root, pth);
}
int main(){
    int arr[9] = {8,5, 3, 1, 4, 6, 10, 11, 14};

    Node *root = buildBST(arr, 9);

    rootToLeaf(root);
}