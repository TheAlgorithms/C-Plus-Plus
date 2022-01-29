#include <iostream>
#include <queue>
using namespace std;

class node {
 public:
    int val;
    node *left;
    node *right;
};

//Combine this function with a binary tree root to get the sum of right leaves.
void sumOfRightLeaves (node* root) {
    queue <node*> que;
    int sum = 0;

    if (root != nullptr)
    {
        que.push(root);
    }
    while (!que.empty())
    {
        if (que.front()->right != nullptr && que.front()->right->right == nullptr && que.front()->right->left == nullptr)
        {
            sum += que.front()->right->val;
        }
        if (que.front()->left != nullptr)
        {
            que.push(que.front()->left);
        }
        if (que.front()->right != nullptr)
        {
            que.push(que.front()->right);
        }
        que.pop();
    }
    cout << sum;
}

int main () {
    return 0;
}