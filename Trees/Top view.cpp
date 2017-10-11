// C++ program to print top 
// view of binary tree
#include<bits/stdc++.h>
using namespace std;
 
//Structure of binary tree
struct Node
{
    int data;
    struct Node* left, * right;
};
 
// function should print the topView of 
// the binary tree
void topView(struct Node *root)
{
    if (root == NULL)
        return;
 
    unordered_map<int, int> m;
    queue<pair<Node*, int>> q;
 
    // push node and horizontal distance to queue
    q.push(make_pair(root, 0));
    
    while (!q.empty())
    {
        pair<Node*, int> p = q.front();
        Node *n = p.first;
        int val = p.second;
        q.pop();
         
        // if horizontal value is not in the hashmap 
        // that means it is the first value with that
        // horizontal distance so print it and store 
        // this value in hashmap
        if (m.find(val)==m.end())
        {
            m[val] = n->data;
            printf("%d ", n->data);
        }
         
        if (n->left != NULL)
            q.push(make_pair(n->left, val-1));
         
        if (n->right != NULL)
            q.push(make_pair(n->right, val+1));
    }
}
 
// function to create a new node
struct Node* newNode(int key)
{
    struct Node* node = new Node;
    node->data= key;
    node->left = node->right = NULL;
    return node;
}
 
// main function
int main()
{
    /* Create following Binary Tree
             1
           /  \
          2    3
           \
            4
             \
              5
               \
                6*/
                 
    Node *root=newNode(1);
    root->left=newNode(2);
    root->right=newNode(3);
    root->left->right=newNode(4);
    root->left->right->right=newNode(5);
    root->left->right->right->right=newNode(6);
     
    topView(root);
    return 0;
}