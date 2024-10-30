#include <iostream>
#include <queue>
using namespace std;

// class to create Binary Tree
class node {
 public:
    int data;
    node* left;
    node* right;

    node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

// Create Binary Tree
node* buildTree(node* root) {
    cout << "Enter the data : " << endl;
    int data;
    cin >> data;
    root = new node(data);

    if (data == -1) {
        return NULL;
    }

    cout << "Enter the data for inserting in left " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter the data for inserting in right" << data << endl;
    root->right = buildTree(root->right);

    return root;
}

// morris traversal inorder
void MorrisTraversal(node* root) {
    node *curr, *prev;

    if (root == NULL) {
        return;
    }

    curr = root;
    while (curr != NULL) {
        if (curr->left == NULL) {
            cout << curr->data << " ";
            curr = curr->right;
        } else {
            prev = curr->left;
            while (prev->right != NULL && prev->right != curr) {
                prev = prev->right;
            }

            if (prev->right == NULL) {
                prev->right = curr;
                curr = curr->left;
            } else {
                prev->right = NULL;
                cout << curr->data << " ";
                curr = curr->right;
            }
        }
    }
}

int main() {
    node* root = NULL;
    root = buildTree(root);

    cout << "Printing the Inorder : " << endl;
    MorrisTraversal(root);
    // 1 2 4 -1 -1 5 -1 -1 3 -1 -1

    // 1 2 6 -1 -1 7 -1 -1 3 8 -1 -1 9 -1 -1

    /*
                    1
                 /     \
                2        3
              / \       / \
            6    7     8    9


            postorder = 6 7 2 8 9 3 1
            preorder = 1 2 6 7 3 8 9
            inorder = 6 2 7 1 8 3 9
    */

    return 0;
}
