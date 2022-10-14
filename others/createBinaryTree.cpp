#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

class Node {
 public:
    int data;
    Node *left;
    Node *right;
    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *buildTree(Node *root) {
    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    if (data == -1) {
        return NULL;
    }
    cout << "Enter the data to the left of " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter the data to the right of " << data << endl;
    root->right = buildTree(root->right);
    return root;
}

vector<int> reverseLevelOrder(Node *root) {
    queue<Node *> q;
    q.push(root);
    vector<int> ans;
    while (!q.empty()) {
        /* code */
        Node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->right) {
            q.push(temp->right);
        }
        if (temp->left) {
            q.push(temp->left);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void levelOrder(Node *root) {
    queue<Node *> q;

    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if (temp == NULL) {
            // purana level complete traverse ho chuka hai
            cout << endl;
            if (!q.empty()) {
                // queue still has some child
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

void inorder(Node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(Node *root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void buildFromLevelOrder(Node *root) {
    queue<Node *> q;
    int data;
    cout << "Enter data for root " << endl;
    cin >> data;
    root = new Node(data);
    q.push(root);

    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();

        cout << "Enter the left for: " << temp->data << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1) {
            temp->left = new Node(leftData);
            q.push(temp->left);
        }

        cout << "Enter the right for: " << temp->data << endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1) {
            temp->right = new Node(rightData);
            q.push(temp->right);
        }
    }
}
int main() {
    Node *root = NULL;
    buildFromLevelOrder(root);
    levelOrder(root);
    /*
    root = buildTree(root);
        levelOrder(root);
        cout << "\nReversed Level Order is: ";
        reverseLevelOrder(root);
        cout << "\nInorder traversal is: ";
        inorder(root);

        cout << "\nPreorder traversal is: ";
        preorder(root);

        cout << "\nPostorder traversal is: ";
        postorder(root);*/

    return 0;
}