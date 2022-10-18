#include <iostream>
#include <list>
#include <queue>
using namespace std;

class node {
 public:
    int val;
    node *left;
    node *right;
    node(int val) {
        this->val = val;
        left = NULL;
        right = NULL;
    }
    ~node() {
        delete left;
        delete right;
    }
};

node *takeInputLevelWise() {
    cout << "Enter Root Data: ";
    int rootData;
    cin >> rootData;
    if (rootData == -1)
        return NULL;

    node *root = new node(rootData);
    queue<node *> pendingNodes;
    pendingNodes.push(root);

    while (pendingNodes.size()) {
        node *front = pendingNodes.front();
        pendingNodes.pop();

        cout << "Enter Left of " << front->val << ": ";
        int leftData;
        cin >> leftData;
        if (leftData != -1) {
            node *leftChild = new node(leftData);
            pendingNodes.push(leftChild);
            front->left = leftChild;
        }

        cout << "Enter Right of " << front->val << ": ";
        int rightData;
        cin >> rightData;
        if (rightData != -1) {
            node *rightChild = new node(rightData);
            front->right = rightChild;
            pendingNodes.push(rightChild);
        }
    }

    return root;
}

void CreateTree(node *curr, node *n, int x, char pos) {
    if (n != NULL) {
        char ch;
        cout << "\nLeft or Right of " << n->val << " : ";
        cin >> ch;
        if (ch == 'l')
            CreateTree(n, n->left, x, ch);
        else if (ch == 'r')
            CreateTree(n, n->right, x, ch);
    } else {
        node *t = new node(x);
        if (pos == 'l') {
            curr->left = t;
        } else if (pos == 'r') {
            curr->right = t;
        }
    }
}

void LevelorderTraversal(node *root) {
    if (root == NULL)
        return;

    queue<node *> pendingNodes;
    pendingNodes.push(root);

    while (pendingNodes.size()) {
        node *front = pendingNodes.front();
        pendingNodes.pop();

        cout << front->val << ": ";
        if (front->left != NULL) {
            cout << "L" << front->left->val;
            pendingNodes.push(front->left);
        }
        if (front->right != NULL) {
            cout << " R" << front->right->val;
            pendingNodes.push(front->right);
        }
        cout << endl;
    }
}

void BFT(node *n) {
    list<node *> queue;

    queue.push_back(n);

    while (!queue.empty()) {
        n = queue.front();
        cout << n->val << "  ";
        queue.pop_front();

        if (n->left != NULL)
            queue.push_back(n->left);
        if (n->right != NULL)
            queue.push_back(n->right);
    }
}

void Pre(node *n) {
    if (n != NULL) {
        cout << n->val << "  ";
        Pre(n->left);
        Pre(n->right);
    }
}

void In(node *n) {
    if (n != NULL) {
        In(n->left);
        cout << n->val << "  ";
        In(n->right);
    }
}

void Post(node *n) {
    if (n != NULL) {
        Post(n->left);
        Post(n->right);
        cout << n->val << "  ";
    }
}

int main() {
    int value;
    int ch;
    node *root;

    do {
        cout << "\n1. Insert";
        cout << "\n2. Insert level-wise order";
        cout << "\n3. levelorder Traversal";
        cout << "\n4. Breadth First";
        cout << "\n5. Preorder Depth First";
        cout << "\n6. Inorder Depth First";
        cout << "\n7. Postorder Depth First";

        cout << "\nEnter Your Choice : ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "\nEnter the value of root node :";
                cin >> value;
                root = new node(value);
                int x;
                char pos;
                cout << "\nEnter the value to be Inserted : ";
                cin >> x;
                cout << "\nLeft or Right of Root : ";
                cin >> pos;
                if (pos == 'l')
                    CreateTree(root, root->left, x, pos);
                else if (pos == 'r')
                    CreateTree(root, root->right, x, pos);
                break;
            case 2:
                root = takeInputLevelWise();
                break;
            case 3:
                LevelorderTraversal(root);
                break;
            case 4:
                BFT(root);
                break;
            case 5:
                Pre(root);
                break;
            case 6:
                In(root);
                break;
            case 7:
                Post(root);
                break;
        }
    } while (ch != 0);
}
