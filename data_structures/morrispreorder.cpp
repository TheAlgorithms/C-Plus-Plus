#include <iostream>
#include <queue>

/**************************
    @author mkhuzaima
    (changed to morrisInorder by @shrutisheoran )
**************************/

using namespace std;

struct Btree {
    int data;
    struct Btree *left;   // Pointer to left subtree
    struct Btree *right;  // Pointer to right subtree
};

void insert(Btree **root, int d) {
    Btree *nn = new Btree();  // Creating new node
    nn->data = d;
    nn->left = NULL;
    nn->right = NULL;
    if (*root == NULL) {
        *root = nn;
        return;
    } else {
        queue<Btree *> q;
        // Adding root node to queue
        q.push(*root);
        while (!q.empty()) {
            Btree *node = q.front();
            // Removing parent node from queue
            q.pop();
            if (node->left)
                // Adding left child of removed node to queue
                q.push(node->left);
            else {
                // Adding new node if no left child is present
                node->left = nn;
                return;
            }
            if (node->right)
                // Adding right child of removed node to queue
                q.push(node->right);
            else {
                // Adding new node if no right child is present
                node->right = nn;
                return;
            }
        }
    }
}

void morrisPreorder(Btree *root) {
    Btree *curr = root;
    Btree *temp;
    while (curr) {
        if (curr->left == NULL) {
            cout << curr->data << " ";
            // If left of current node is NULL then curr is shifted to right
            curr = curr->right;
        } else {
            // Left of current node is stored in temp
            temp = curr->left;
            // find right most element of left subtree
            while (temp->right && temp->right != curr) temp = temp->right;
            // If extreme right is null it is made to point to current node
            // (will be used for backtracking)
            if (temp->right == NULL) {
                // print before going to left subtree
                cout << curr->data << " ";

                temp->right = curr;
                // current node is made to point its left subtree
                curr = curr->left;
            }
            // If extreme right already points to current node it it set to
            // null
            else if (temp->right == curr) {
                temp->right = NULL;
                // current node is made to point its right subtree
                curr = curr->right;
            }
        }
    }
}

int main() {
    // Testing morrisInorder funtion
    Btree *root = NULL;
    int i;
    for (i = 1; i <= 7; i++) insert(&root, i);
    cout << "Morris Preorder: ";
    morrisPreorder(root);
    return 0;
}
