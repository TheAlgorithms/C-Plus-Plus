#include <iostream>
using namespace std;
#include <map>
#include <stack>
#include <vector>

class node {
 public:
    int data;
    node* left;
    node* right;
    node* parent;
    node(int n) {
        data = n;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};
//normal inorder traversal
void inorder(node* head, vector<int>& out) {
    node* cur = head;
    if (!cur)
        return;
    inorder(cur->left, out);
    out.push_back(cur->data);
    inorder(cur->right, out);
}

//when preorder and inorder vectors are given
node* buildtree2pre(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& inorder, int inStart, int inEnd,
                    map<int, int>& inmp) {
    if (preStart > preEnd || inStart > inEnd)
        return NULL;
    node* root = new node(preorder[preStart]);
    int inroot = inmp[root->data];
    int numsleft = inroot - inStart;
    root->left = buildtree2pre(preorder, preStart + 1, preStart + numsleft,
                               inorder, inStart, inroot - 1, inmp);
    root->right = buildtree2pre(preorder, preStart + numsleft + 1, preEnd,
                                inorder, inroot + 1, inEnd, inmp);
    return root;
}
node* buildtreepre(vector<int>& inorder, vector<int>& preorder) {
    map<int, int> inmp;
    for (int i = 0; i < inorder.size(); i++) {
        inmp[inorder[i]] = i;
    }
    node* root = buildtree2pre(preorder, 0, preorder.size() - 1, inorder, 0,
                               inorder.size() - 1, inmp);
    return root;
}

//when postorder and inorder vectors are given
node* buildtree2post(vector<int>& postorder, int postStart, int postEnd,
                     vector<int>& inorder, int inStart, int inEnd,
                     map<int, int>& inmp) {
    if (postStart > postEnd || inStart > inEnd)
        return NULL;
    node* root = new node(postorder[postEnd]);
    int inroot = inmp[root->data];
    int numsleft = inroot - inStart;
    root->left = buildtree2post(postorder, postStart, postStart + numsleft - 1,
                                inorder, inStart, inroot - 1, inmp);
    root->right = buildtree2post(postorder, postStart + numsleft, postEnd - 1,
                                 inorder, inroot + 1, inEnd, inmp);
    return root;
}
node* buildtreepost(vector<int>& inorder, vector<int>& postorder) {
    map<int, int> inmp;
    for (int i = 0; i < inorder.size(); i++) {
        inmp[inorder[i]] = i;
    }
    node* root = buildtree2post(postorder, 0, postorder.size() - 1, inorder, 0,
                                inorder.size() - 1, inmp);
    return root;
}

int main(){
    vector<int> inorder_seq = {1, 2, 3, 4, 5};
    vector<int> preorder_seq = {3, 2, 1, 4, 5};
    vector<int> postorder_seq = {1, 2, 5, 4, 3};

    cout << "=== Build BST from Preorder & Inorder ===\n";
    node* tree_pre = buildtreepre(inorder_seq, preorder_seq);
    vector<int> out;
    inorder(tree_pre, out);
    cout << "Inorder: ";
    for (auto x : out) cout << x << " ";
    out.clear();
    cout << endl;
    cout << "=== Build BST from Postorder & Inorder ===\n";
    node* tree_post = buildtreepost(inorder_seq, postorder_seq);
    inorder(tree_post, out);
    cout << "Inorder: ";
    for (auto x : out) cout << x << " ";
}