#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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
        left = right = NULL;
    }
};

static int idx = -1;

Node *buildTree(vector<int> nodes)
{

    idx++;

    if (nodes[idx] == -1)
    {
        return NULL;
    }

    Node *currNode = new Node(nodes[idx]);
    currNode->left = buildTree(nodes);
    currNode->right = buildTree(nodes);

    return currNode;
}
void prorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->data << " ";
    prorder(root->left);
    prorder(root->right);
}

int transformSum(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftOld = transformSum(root->left);
    int rightOld = transformSum(root->right);

    int currOld = root->data;
    root->data = leftOld + rightOld;

    if (root->left != NULL)
    {
        root->data += root->left->data;
    }

    if (root->right != NULL)
    {
        root->data += root->right->data;
    }

    return currOld;
}

int main()
{

    vector<int> nodes = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};

    Node *root = buildTree(nodes);
    cout << root->data << endl;

    transformSum(root);
    prorder(root);
}