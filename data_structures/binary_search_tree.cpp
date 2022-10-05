/**
 * \file
 * \brief A simple tree implementation using structured nodes
 *
 * \todo update code to use C++ STL library features and OO structure
 * \warning This program is a poor implementation - C style - and does not
 * utilize any of the C++ STL features.
 */
#include <iostream>
using namespace std;

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

struct node *Insert(node *n, int x) {
	// If the tree is empty or when we reach a null leaf node we add a new node
	if(n == NULL)
	{
		n = (struct node*)malloc(sizeof(struct node));
		n->val = x;
		n->left = NULL;
		n->right = NULL;
	}
	else
	{
		/*since this is a binary search tree we don't have the need to have nodes with the same value on the tree.
		  In this case, when the value we want to add is greater than the root node we call the insert function again
		  pointing to the right node. The same is valid for the left node when the value is samller than the root node.
		  We repeat this until we find a null leaf node to store our new node. */
		if(x > n->val)
		{
			n->right = Insert(n->right, x);
		}
		if(x < n->val)
		{
			n->left = Insert(n->left, x);
		}
	}
	return n;
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
    queue.front = 0;
    queue.rear = 0;
    int value;
    int ch;
    struct node *root = NULL;
    std::cout << "\nEnter the value of root node :";
    std::cin >> value;
    root = Insert(root, value);
    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First";

        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        int x;
        switch (ch) {
        case 1:
            std::cout << "\nEnter the value to be Inserted : ";
            std::cin >> x;
            Insert(root, x);
            break;
        case 2:
            std::cout << "\nEnter the value to be Deleted : ";
            std::cin >> x;
            Remove(root, root, x);
            break;
        case 3:
            BFT(root);
            break;
        case 4:
            Pre(root);
            break;
        case 5:
            In(root);
            break;
        case 6:
            Post(root);
            break;
        }
    } while (ch != 0);

    return 0;
}
