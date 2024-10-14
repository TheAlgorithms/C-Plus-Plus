#include <iostream>
#include <malloc.h>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

Node *inseret(Node *root, int val)
{
    if (root == NULL)
    {
        root = new Node(val);
        return root;
    }

    if (val < root->data)
    {
        root->left = inseret(root->left, val);
    }
    else
    {
        root->right = inseret(root->right, val);
    }

    return root;
}

Node *buildBST(int arr[], int n)
{
    Node *root = NULL;

    for (int i = 0; i < n; i++)
    {
        root = inseret(root, arr[i]);
    }   

    return root;
}

void inorder(Node *root)
{

    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main()
{
    int arr[6] = {5, 1, 3, 4, 2, 7};

    Node *root = buildBST(arr, 6);
    // Node* root = searchBST(arr, 6, 3);
    // Node* root = binarySerachBST(arr, 6,3);
    // cout << search(root, 10) << endl;
    inorder(root);
    cout << endl;
    return 0;
}
