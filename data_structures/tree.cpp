#include <iostream>
#include <list>

struct node {
    int val;
    node *left;
    node *right;
};

void CreateTree(node *curr, node *n, int x, char pos) {
    if (n != nullptr) {
        char ch;
        std::cout << "\nLeft or Right of " << n->val << " : ";
        std::cin >> ch;
        if (ch == 'l') {
            CreateTree(n, n->left, x, ch);
        } else if (ch == 'r') {
            CreateTree(n, n->right, x, ch);
}
    } else {
        node *t = new node;
        t->val = x;
        t->left = nullptr;
        t->right = nullptr;
        if (pos == 'l') {
            curr->left = t;
        } else if (pos == 'r') {
            curr->right = t;
        }
    }
}

void BFT(node *n) {
    std::list<node *> queue;

    queue.push_back(n);

    while (!queue.empty()) {
        n = queue.front();
        std::cout << n->val << "  ";
        queue.pop_front();

        if (n->left != nullptr) {
            queue.push_back(n->left);
}
        if (n->right != nullptr) {
            queue.push_back(n->right);
}
    }
}

void Pre(node *n) {
    if (n != nullptr) {
        std::cout << n->val << "  ";
        Pre(n->left);
        Pre(n->right);
    }
}

void In(node *n) {
    if (n != nullptr) {
        In(n->left);
        std::cout << n->val << "  ";
        In(n->right);
    }
}

void Post(node *n) {
    if (n != nullptr) {
        Post(n->left);
        Post(n->right);
        std::cout << n->val << "  ";
    }
}

int main() {
    int value;
    int ch;
    node *root = new node;
    std::cout << "\nEnter the value of root node :";
    std::cin >> value;
    root->val = value;
    root->left = nullptr;
    root->right = nullptr;
    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Breadth First";
        std::cout << "\n3. Preorder Depth First";
        std::cout << "\n4. Inorder Depth First";
        std::cout << "\n5. Postorder Depth First";

        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        switch (ch) {
        case 1:
            int x;
            char pos;
            std::cout << "\nEnter the value to be Inserted : ";
            std::cin >> x;
            std::cout << "\nLeft or Right of Root : ";
            std::cin >> pos;
            if (pos == 'l') {
                CreateTree(root, root->left, x, pos);
            } else if (pos == 'r') {
                CreateTree(root, root->right, x, pos);
            }
            break;
        case 2:
            BFT(root);
            break;
        case 3:
            Pre(root);
            break;
        case 4:
            In(root);
            break;
        case 5:
            Post(root);
            break;
        }
    } while (ch != 0);
}
