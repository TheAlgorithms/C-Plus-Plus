/**
 * \file
 * \brief A simple tree implementation using structured nodes
 * \Object Oriented approach
 */

#include<bits/stdc++.h> 
#include<queue>
using namespace std;

struct node {
    int value;
    node *left;
    node *right;
};

class BinarySearchTree{
    node *root;

public:
    BinarySearchTree(){
        root = NULL;
    }

    void insert(int data){
        node *newnode = new node;
        newnode->value = data;
        newnode->left = NULL;
        newnode->right = NULL;
        if(root == NULL){
            root = newnode;
            return;
        }
        node *current = root;
        while(true){
            if(current->value > data){
                if(current->left == NULL)
                {
                    current->left = newnode;
                    return;
                }
                else
                    current = current->left;
            }
            else{
                if(current->right == NULL)
                {
                    current->right = newnode;
                    return;
                }
                else
                    current = current->right;
            }
            
        } 
    }

    node *getRoot(){
        return root;
    }
    
    void BFT() {
        queue<node*> q;
        q.push(root);
        while(!q.empty()){
            node *current = q.front();
            q.pop();
            cout << current->value << " ";
            if(current->left)
                q.push(current->left);
            if(current->right)
                q.push(current->right);
        }
    }

    void preOrder(node *current){
        if(current)
        {
            cout << current->value << " ";
            preOrder(current->left);
            preOrder(current->right);
        }
    }

    void inOrder(node *current){
        if(current)
        {
            inOrder(current->left);
            cout << current->value << " ";
            inOrder(current->right);
        }
    }

    void postOrder(node *current){
        if(current)
        {
            postOrder(current->left);
            postOrder(current->right);
            cout << current->value << " ";
        }
    }

    node *minValueNodeInRightST(node *node) 
    { 
        struct node *current = node; 
        while (current && current->left) 
            current = current->left;       
        return current; 
    } 
    
    node *deleteNode(node *current, int target){
        if(current == NULL)
            return current;

        else if(current->value > target){
            current->left = deleteNode(current->left, target);
        } 
        
        else if(current->value < target){
            current->right = deleteNode(current->right, target);
        }
        
        else{
            if(current->value > target){
                current = current->left;
            } 
            else if(current->value < target){
                current = current->right;
            }
            else{
                node *temp;
                if(current->left == NULL){
                    temp = current->right;
                    free(current);
                    current = current->right;
                }
                else if(current->right == NULL){
                    temp = current->left;
                    free(current);
                    current = current->left;
                }
                else{
                    node *inorder_successor = minValueNodeInRightST(current->right);
                    current->value = inorder_successor->value;
                    current->right = deleteNode(current->right, inorder_successor->value);
                }
            }
        }
        return current;
    }
    
    void remove(int target){
        root = deleteNode(root, target);
    }
};

int main() {
    int value;
    int ch;
    
    BinarySearchTree BST;
    cout << "\nEnter the value of root node :";
    cin >> value;
    BST.insert(value);

    do {
        cout << "\n0. Exit/Stop"
                  << "\n1. Insert a node"
                  << "\n2. Delete a node"
                  << "\n3. Breadth First Traversal"
                  << "\n4. Preorder Traversal"
                  << "\n5. Inorder Traversal"
                  << "\n6. Postorder Traversal";

        cout << "\nEnter Your Choice : ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "\nEnter the value to be Inserted : ";
            cin >> value;
            BST.insert(value);
            break;
        case 2:
            cout << "\nEnter the value to be Deleted : ";
            cin >> value;
            BST.remove(value);
            break;
        case 3:
            BST.BFT();
            break;
        case 4:
            BST.preOrder(BST.getRoot());
            break;
        case 5:
            BST.inOrder(BST.getRoot());
            break;
        case 6:
            BST.postOrder(BST.getRoot());
            break;
        }
    } while (ch != 0);

    return 0;
}
