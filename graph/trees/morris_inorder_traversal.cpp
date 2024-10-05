#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
    Node(int x, Node *left, Node *right) : data(x), left(left), right(right) {}
};

vector<int> morrisTraversal(Node *root)
{
    vector<int> ans;
    Node *cur = root;
    while (cur != NULL)
    {
        if (cur->left == NULL)
        {
            ans.push_back(cur->data);
            cur = cur->right;
        }
        else
        {
            Node *prev = cur->left;
            while (prev->right && prev->right != cur)
            {
                prev = prev->right;
            }
            if (prev->right == NULL)
            {
                prev->right = cur;

                cur = cur->left;
            }
            else
            {
                prev->right = NULL;
                ans.push_back(cur->data);
                cur = cur->right;
            }
        }
    }
    return ans;
}

int main(){
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    vector<int> ans = morrisTraversal(root);
    for(auto it:ans){
        cout<<it<<" ";
    }
    return 0;
}