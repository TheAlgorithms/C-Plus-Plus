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

bool twoSumBST(Node* root1, Node* root2, int x){
    if(root1 == NULL && root2 == NULL){
        return false;
    }

    if()
}

int main()
{
    int arr[7] = {5, 2, 3, 4, 6, 7, 8};
    int arr1[7] = {10 , 3, 6, 8, 11, 15, 18};

    Node *root1 = buildBST(arr, 7);
    Node *root2 = buildBST(arr1, 7);
 
    cout << twoSumBST(root1, root2, 16) << endl;
    
    return 0;
}