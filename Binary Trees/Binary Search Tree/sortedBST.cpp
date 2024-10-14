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

Node* buildBSTFromSorted(int arr[], int st, int end){

    if(st > end){
        return NULL;
    }
    
    int mid = st + (end - st)/2;
    Node* curr = new Node(arr[mid]);

    curr->left = buildBSTFromSorted(arr, st, mid-1);
    curr->right = buildBSTFromSorted(arr, mid + 1, end);

    return curr;
}


void preorder(Node* root){
    if(root == nullptr){
        return ;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
int main()
{
    int arr[7] = {3,4,5,6,7,8,9};

    Node *root = buildBSTFromSorted(arr, 0, 6);

    preorder(root);
   
}