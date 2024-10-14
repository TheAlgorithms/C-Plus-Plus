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
        left = right = nullptr;
    }
};

Node* insertBST(Node* root, int val){
    if(root == NULL){
        root = new Node(val);
        return root;
    }

    if(root->data > val){
        root->left = insertBST(root->left, val);
    }else{
        root->right = insertBST(root->right, val);
    }

    return root;
}

Node* buildBST(int arr[], int n){
    Node* root = nullptr;

    for(int i=0; i<n; i++){
        root = insertBST(root, arr[i]);
    }


    return root;
}

void inorder(Node* root){
    if(root == NULL){
        return ;
    }


    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right); 
}


bool search(Node* root, int val){
    if(root == NULL){
        return false;
    }

    if(root->data == val){
        return true;
    }else if(root->data > val){
        return search(root->left, val);
    }else{
        return search(root->right, val);
    }


}

int main()
{
    int arr[6] = {5, 1, 3, 4, 2, 7};

    Node *root = buildBST(arr, 6);
 
    inorder(root);
    cout << endl;
    // cout << search(root, 10) << endl;
    
    return 0;
}