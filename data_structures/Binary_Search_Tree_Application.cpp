// This is Full Binary Search Tree with Insertion, Deletion, Search and inorder_Traversal of tree with user interaction (kind of application)
// As well as the time complexity of each function

#include <iostream>
using namespace std;
#define ll long long
#define endl "\n"
//---------- Ayush Rudani ----------//

class Node
{
public:
    int data;
    Node *left, *right;
    Node(int data = 0) { this->data = data, this->left = this->right = NULL; }
};

class BinarySearchTree
{
    int total_node;

public:
    Node *root;

    BinarySearchTree()
    {
        this->root = NULL;
    }
    Node *insertElementInBST(Node *, int);
    Node *deleteElementInBST(Node *, int);
    void inOrderTraversal(Node *);
    bool searchElementInBST(Node *, int);
};

//-------------------------------------------------------------------------------
// INSERT ELEMENT IN BST

// FIRST METHOD (iterative method)
// Time Complexity :- O(height)
// Auxiliary space Complexity :- O(1)

Node *BinarySearchTree::insertElementInBST(Node *root, int ele)
{
    if (root == NULL)
    {
        Node *new_node = new Node(ele);
        if (NULL == new_node)
        {
            cout << "New node not created successfully\n";
            return root;
        }
        root = new_node;
        total_node++;
        return root;
    }
    Node *current = NULL;
    current = root;
    while (current != NULL)
    {
        if (current->data > ele)
        {
            if (current->left == NULL)
                break;
            else
                current = current->left;
        }
        else
        {
            if (current->right == NULL)
                break;
            else
                current = current->right;
        }
    }
    Node *new_node = new Node(ele);
    if (NULL == new_node)
    {
        cout << "New node not created successfully\n";
        return root;
    }

    if (current->data > ele)
        current->left = new_node;

    else
        current->right = new_node;

    total_node++;
    return root;
}

// SECOND METHOD (recursive method)
// Time Complexity :- O(height)
// Auxiliary space Complexity :- O(height)
/*
Node *BinarySearchTree::insertElementInBST(Node *root,int ele){
    if(root == NULL){
        Node *new_node = new Node(ele);
        if(NULL == new_node){
            cout<<"New node not created successfully\n";
            return root;
        }
        return new_node;
    }
    if(root->data > ele){
        root->left = insertElementInBST(root->left,ele);
    }else f(root->data < ele){
        root->right = insertElementInBST(root->right,ele);
    }
    return root;
}
*/

//-------------------------------------------------------------------------------
// DELETE ELEMENT IN BST

// FIRST METHOD (recursive method)
// Time Complexity :- O(height)
// Auxiliary space Complexity :- O(height)

Node *findCloestGreaterSuccessor(Node *r_right)
{
    r_right = r_right->right;
    while ((r_right != NULL) && (r_right->left != NULL))
        r_right = r_right->left;
    return r_right;
}
Node *BinarySearchTree::deleteElementInBST(Node *root, int ele)
{
    if (root == NULL)
        return root;

    if (root->data > ele)
        root->left = deleteElementInBST(root->left, ele);

    else if (root->data < ele)
        root->right = deleteElementInBST(root->right, ele);

    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            Node *successor = findCloestGreaterSuccessor(root);
            root->data = successor->data;
            root->right = deleteElementInBST(root->right, successor->data);
        }
    }
    return root;
}

//-------------------------------------------------------------------------------

// INORDER TRAVERSAL IN BST (LEFT ROOT RIGHT)

// Recursive Solution for INORDER TRAVERSAL
void BinarySearchTree::inOrderTraversal(Node *root)
{
    if (root == NULL)
        return;
    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}

// Iterative Solution for inOrderTraversal
/*
void BinarySearchTree::inOrderTraversal(Node *root){
    stack<Node *> address;
    while((root != NULL) || (!address.empty())){
        if(root != NULL){
            address.push(root);
            root = root->left;
        }else{
            Node *temp = address.top();
            address.pop();
            cout<<temp->data<<" ";
            root = temp->right;
        }
    }
}
*/

//-------------------------------------------------------------------------------

// SEARCH ELEMENT IN BST

// FIRST METHOD (iterative method)
// Time Complexity :- O(height)
// Auxiliary space Complexity :- O(1)

bool BinarySearchTree::searchElementInBST(Node *root, int ele)
{
    while (root != NULL)
    {
        if (root->data == ele)
            return true;

        else if (root->data > ele)
            root = root->left;

        else
            root = root->right;
    }
    return false;
}

// SECOND METHOD (recursive method)
// Time Complexity :- O(height)
// Auxiliary space Complexity :- O(height)
/*
bool BinarySearchTree::searchElementInBST(Node *root,int ele){
    if(root == NULL)
        return false;
    if(root->data == ele)
        return true;
    if(root->data > ele){
        return searchElementInBST(root->left,ele);
    }else{
        return searchElementInBST(root->right,ele);
    }
}
*/

//-------------------------------------------------------------------------------

int main()
{
    ios_base ::sync_with_stdio(false);

    BinarySearchTree b1;
    while (true)
    {
        cout << endl;
        cout << "=> Enter 0 for EXIT" << endl;
        cout << "=> Enter 1 for insert element in BST" << endl;
        cout << "=> Enter 2 for search element in BST" << endl;
        cout << "=> Enter 3 for inorder traversal of BST" << endl;
        int operation;
        cout << "\nEnter your choice: ";
        cin >> operation;
        if (operation == 0)
        {
            cout << endl
                 << "Pressed :- " << operation << endl;
            return 0;
        }
        else if (operation == 1)
        {
            cout << endl
                 << "Pressed :- " << operation << endl;
            int x;
            cout << "Enter element :- ";
            cin >> x;
            b1.root = b1.insertElementInBST(b1.root, x);
            cout << endl;
        }
        else if (operation == 2)
        {
            cout << endl
                 << "Pressed :- " << operation << endl;
            int x;
            cout << "Enter Searching element :- ";
            cin >> x;
            if (b1.searchElementInBST(b1.root, x))
            {
                cout << x << " is present in BST" << endl;
            }
            else
            {
                cout << x << " is not present in BST" << endl;
            }
            cout << endl;
        }
        else if (operation == 3)
        {
            cout << endl
                 << "Pressed :- " << operation << endl;
            cout << "INORDER TRAVERSAL OF BST" << endl;
            b1.inOrderTraversal(b1.root);
            cout << endl;
        }
        else
        {
            cout << "INVALID OPERATION" << endl;
        }
    }
    return 0;
}