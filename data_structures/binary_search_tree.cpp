/**
 * \file
 * \brief A simple tree implementation using structured nodes
 */
#include <iostream>
#include <list>

struct node {
    int val;
    node *left;
    node *right;
};
node *root;

void insert(node *n, int x) {
    if (x < n->val) {
        if (n->left == NULL) {
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->left = temp;
        } else {
            insert(n->left, x);
        }
    } else if (x > n->val) {
        if (n->right == NULL) {
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->right = temp;
        } else {
            insert(n->right, x);
        }
    }
}

int findMaxInLeftST(node* n) {
    while (n->right != NULL) {
        n = n->right;
    }
    return n->val;
}
void remove(node* p, node* n, int x) {
    if (n->val == x) {
        if (n->left == NULL && n->right == NULL) {
            if (x > p->val) {
                p->right = NULL;
            } else {
                p->left = NULL;
            }
        } else if (n->right == NULL) {
            if (x > p->val) {
                p->right = n->left;
            } else {
                p->left = n->left;
            }

        } else if (n->left == NULL) {
            if (x > p->val) {
                p->right = n->right;
            } else {
                p->left = n->right;
            }
        } else {
            int y = findMaxInLeftST(n->left);
            n->val = y;
            remove(n, n->left, x);
        }
    } else if (n->val > x) {
        remove(n, n->left, x);
    } else {
        remove(n, n->right, x);
    }
}

void BFT(node *n) {
    std::list<node* > queue;

    queue.push_back(n);

    while (!queue.empty()) {
        n = queue.front();
        std::cout << n->val << "  ";
        queue.pop_front();

        if (n->left != NULL) {
            queue.push_back(n->left);
        }
        if (n->right != NULL) {
            queue.push_back(n->right);
        }
    }
}

void Pre(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        Pre(n->left);
        Pre(n->right);
    }
}

void In(node *n) {
    if (n != NULL) {
        In(n->left);
        std::cout << n->val << "  ";
        In(n->right);
    }
}

void Post(node *n) {
    if (n != NULL) {
        Post(n->left);
        Post(n->right);
        std::cout << n->val << "  ";
    }
}

int main() {
    int value;
    int ch;
    node* root= new node();
    std::cout << "\nEnter the Root node Value: ";
    std::cin >> value;
    root->val = value;
    root->left = NULL;
    root->right = NULL;
    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First Traverse"
                  << "\n4. Pre-Order"
                  << "\n5. In-Order"
                  << "\n6. Post-Order"
                  << "\n7. Exit"
                  << "\nEnter the Choice: ";
        std::cin >> ch;

        switch (ch) {
        case 1:
            int x;
            std::cout << "\nEnter the value to Insert:";
            std::cin >> x;
            insert(root, x);
            break;
        case 2:
            int del;
            std::cout << "\nEnter the value to be deleted:";
            std::cin >> del;
            remove(root, root, del);
            break;
        case 3:
            std::cout << "\nBreadth First Traverse:";
            BFT(root);
            break;
        case 4:
            std::cout << "\nPre-Order Traversal:";
            Pre(root);
            break;
        case 5:
            std::cout << "\nIn-Order Traversal:";
            In(root);
            break;
        case 6:
            std::cout << "\nPost-Order Traversal:";
            Post(root);
            break;
        case 7:
            exit(0);
        default:
            std::cout << "\nInvalid Choice!!";
        }
    } while (ch != 7);

    return 0;
}
