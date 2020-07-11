/**
 * \file
 * \brief A simple tree implementation using structured nodes
 *
 * \todo update code to use C++ STL library features and OO structure
 * \warning This program is a poor implementation - C style - and does not
 * utilize any of the C++ STL features.
 */
#include <algorithm>  // test code
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
/** An struct node type.
 *  Define a element for tree insert/remove operation
 */
struct node {
    int val;     /**< int value of a node struct*/
    node *left;  /**< left subtree pointer */
    node *right; /**< right subtree pointer */
};

/** insert a node to tree
 * with greater value to right subtree, smaller value node to left subtree
 * \param[in] n root node of a tree
 * \param[in] x a node with value to be insert
 */
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

/** find max node value of a left subtree
 * \param[in] n the root node pointer of subtree
 * \return the max node int value
 */
int findMaxInLeftST(node *n) {
    while (n->right != NULL) {
        n = n->right;
    }
    return n->val;
}

/** remove a node from tree
 *  travesal a tree and find a node ,then delete it.
 * \param[in] p parent node of start node
 * \param[in] n start node to search a node with value x
 * \param[in] x the int value of a node
 */
void Remove(node *p, node *n, int x) {
    if (n->val == x) {
        if (n->right == NULL && n->left == NULL) {
            if (x > p->val) {
                p->right = NULL;
            } else {
                p->left = NULL;
            }
            delete n;
        } else if (n->right == NULL) {
            if (x > p->val) {
                p->right = n->left;
            } else {
                p->left = n->left;
            }
            delete n;
        } else if (n->left == NULL) {
            if (x > p->val) {
                p->right = n->right;
            } else {
                p->left = n->right;
            }
            delete n;
        } else {
            int y = findMaxInLeftST(n->left);
            n->val = y;
            Remove(n, n->left, y);
        }
    } else if (x < n->val) {
        Remove(n, n->left, x);
    } else {
        Remove(n, n->right, x);
    }
}

/** Breath First Search a Tree as a Graph with queue structure
 * and begin with node pointer n
 * \param[in] n node pointer of a tree
 */
void BFT(node *n) {
    std::queue<node *> queue;
    if (n != NULL) {
        queue.push(n);
    }

    node *temp = NULL;
    while (!queue.empty()) {
        temp = queue.front();
        queue.pop();
        std::cout << temp->val << "  ";
        if (temp->left)
            queue.push(temp->left);
        if (temp->right)
            queue.push(temp->right);
    }
}

/** traverse a tree with Pre order
 * and print the node value
 * \param[in] n the root node pointer of a tree
 */
void Pre(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        Pre(n->left);
        Pre(n->right);
    }
}

/** traverse a tree with In order
 * and print the node value
 * \param[in] n the root node pointer of a tree
 */
void In(node *n) {
    if (n != NULL) {
        In(n->left);
        std::cout << n->val << "  ";
        In(n->right);
    }
}

/** traverse a tree with Post order
 * and print the node value
 * \param[in] n the root node pointer of a tree
 */
void Post(node *n) {
    if (n != NULL) {
        Post(n->left);
        Post(n->right);
        std::cout << n->val << "  ";
    }
}

/** test traverse a tree with Post order
 * and save the traverse node to an array.
 * \param[in] n the node pointer of a tree to start traverse
 * \param[out] arr the output array that save the traversed tree nodes pointers
 */
void testInOrderTraverse(node *n, std::vector<int> *arr) {
    if (n != NULL) {
        testInOrderTraverse(n->left, arr);
        std::cout << n->val << "  ";
        arr->push_back(n->val);
        testInOrderTraverse(n->right, arr);
    }
}

/** test function.
 * auto build a binary tree with special nodes.
 * test the tree Insert() and Remove() function and out test result.
 */
void test_tree() {
    node *root = new node;
    root->val = 4;
    root->left = NULL;
    root->right = NULL;
    // test Insert()
    Insert(root, 2);
    Insert(root, 1);
    Insert(root, 3);
    Insert(root, 6);
    Insert(root, 5);
    Insert(root, 7);
    std::cout
        << "after Insert() ,the expected output should be : 1, 2, 3, 4, 5, 6 ,7"
        << std::endl;
    // test code
    std::vector<int> arr;
    testInOrderTraverse(root, &arr);
    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Test Insert() function Passed\n========================\n";

    // test Remove()
    Remove(root, root, 2);
    std::cout << "\n after Remove() node 2 , the expected output should be : "
                 "1, 3, 4, 5, 6, 7"
              << std::endl;
    arr.clear();
    testInOrderTraverse(root, &arr);
    for (int i = 0; i < 6; i++) {
        assert(arr[i] != 2);
    }
    std::cout << "Test Remove(2) Passed\n========================\n";

    // free memory
    Remove(root, root, 1);
    Remove(root, root, 3);
    Remove(root, root, 6);
    Remove(root, root, 5);
    Remove(root, root, 7);
    Remove(root, root, 4);  // remove root node
}

/** main test function with commands.
 * build and test a binary search tree according to user input commands.
 */
int main() {
    // test tree
    test_tree();
    int value;
    int ch;
    node *root = new node;
    std::cout << "\nEnter the value of root node :";
    std::cin >> value;
    root->val = value;
    root->left = NULL;
    root->right = NULL;

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
