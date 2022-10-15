#include <iostream>
#include <limits>
#include <string>

struct node {
    int val;
    node *left;
    node *right;
};

struct Queue {
    node *t[100];
    int front;
    int rear;
};

Queue queue;

void enqueue(node *n) { queue.t[queue.rear++] = n; }

node *dequeue() { return (queue.t[queue.front++]); }

void Insert(node *n, int x) {
    if (x < n->val) {
        if (n->left == NULL) {
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->left = temp;
        } else {
            Insert(n->left, x);
        }
    } else {
        if (n->right == NULL) {
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->right = temp;
        } else {
            Insert(n->right, x);
        }
    }
}

int findMaxInLeftST(node *n) {
    while (n->right != NULL) {
        n = n->right;
    }
    return n->val;
}

void Remove(node *p, node *n, int x) {
    if (n->val == x) {
        if (n->right == NULL && n->left == NULL) {
            if (x < p->val) {
                p->right = NULL;
            } else {
                p->left = NULL;
            }
        } else if (n->right == NULL) {
            if (x < p->val) {
                p->right = n->left;
            } else {
                p->left = n->left;
            }
        } else if (n->left == NULL) {
            if (x < p->val) {
                p->right = n->right;
            } else {
                p->left = n->right;
            }
        } else {
            int y = findMaxInLeftST(n->left);
            n->val = y;
            Remove(n, n->right, y);
        }
    } else if (x < n->val) {
        Remove(n, n->left, x);
    } else {
        Remove(n, n->right, x);
    }
}

void BFT(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        enqueue(n->left);
        enqueue(n->right);
        BFT(dequeue());
    }
    std::cout << "\n\n";
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

int ReadInt() {
    int var;

    while (true) {
        std::cin >> var;
        if (!std::cin.good()) {
            std::cout << "Option invalid\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else
            break;
    }

    return var;
}

int main() {
    queue.front = 0;
    queue.rear = 0;
    int value;
    int ch;
    node *root = new node;
    std::cout << "\nEnter the value of root node :";
    value = ReadInt();
    root->val = value;
    root->left = NULL;
    root->right = NULL;
    do {
        system("cls");
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First";

        std::cout << "\nEnter Your Choice : ";
        // std::cin >> ch;
        do {
            ch = ReadInt();

            if (ch <= 0 || ch > 6) {
                std::cout << "Option invalid\n";
            }
        } while (ch <= 0 || ch > 6);

        int x;

        switch (ch) {
            case 1:
                std::cout << "\nEnter the value to be Inserted : ";
                x = ReadInt();
                Insert(root, x);
                break;
            case 2:
                std::cout << "\nEnter the value to be Deleted : ";
                x = ReadInt();
                Remove(root, root, x);
                break;
            case 3:
                BFT(root);
                system("pause");
                break;
            case 4:
                Pre(root);
                system("pause");
                break;
            case 5:
                In(root);
                system("pause");
                break;
            case 6:
                Post(root);
                system("pause");
                break;
        }

    } while (ch != 0);

    return 0;
}
