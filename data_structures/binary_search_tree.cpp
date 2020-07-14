/**
 * \file
 * \brief A simple tree implementation using structured nodes
 */
#include <algorithm>  // test code
#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

/**
 * @namespace data_structure
 * @brief Implementations of various data structures
 */
namespace data_structure {
/**
 * @namespace data_structure::BST
 * @brief Implementation of Binary Search Tree data structure
 */
namespace BST {
/** An struct node type.
 *  Define a element for tree insert/remove operation
 */
struct node {
    int val{};                   /**< int value of a node struct*/
    std::shared_ptr<node> left;  /**< left subtree pointer */
    std::shared_ptr<node> right; /**< right subtree pointer */
};

/** insert a node to tree
 * with greater value to right subtree, smaller value node to left subtree
 * \param[in] n root node of a tree
 * \param[in] x a node with value to be insert
 */
void Insert(node* n, int x) {
    if (x < n->val) {
        if (n->left == nullptr) {
            n->left = std::shared_ptr<node>(new node);
            n->left->val = x;
            n->left->left = nullptr;
            n->left->right = nullptr;
        } else {
            Insert(n->left.get(), x);
        }
    } else {
        if (n->right == nullptr) {
            n->right = std::shared_ptr<node>(new node);
            n->right->val = x;
            n->right->left = nullptr;
            n->right->right = nullptr;
        } else {
            Insert(n->right.get(), x);
        }
    }
}

/** find max node value of a left subtree
 * \param[in] n the root node pointer of subtree
 * \return the max node int value
 */
int findMaxInLeftST(node* n) {
    while (n->right != nullptr) {
        n = n->right.get();
    }
    return n->val;
}

/** remove a node from tree
 *  travesal a tree and find a node ,then delete it.
 * \param[in] p parent node of start node
 * \param[in] n start node to search a node with value x
 * \param[in] x the int value of a node
 */
void Remove(const std::shared_ptr<node>& p, const std::shared_ptr<node>& n,
            int x) {
    if (n->val == x) {
        if (n->right == nullptr && n->left == nullptr) {
            if (x > p->val) {
                p->right = nullptr;
            } else {
                p->left = nullptr;
            }
            n.reset();
            //   delete n;
        } else if (n->right == nullptr) {
            if (x > p->val) {
                p->right = n->left;
            } else {
                p->left = n->left;
            }
            n.reset();
            //   delete n;
        } else if (n->left == nullptr) {
            if (x > p->val) {
                p->right = n->right;
            } else {
                p->left = n->right;
            }
            n.reset();
            //   delete n;
        } else {
            int y = findMaxInLeftST(n->left.get());
            n->val = y;
            Remove(n, n->left, y);
        }
    } else if (x < n->val) {
        Remove(n, n->left, x);
    } else {
        Remove(n, n->right, x);
    }
}

/** free memory of all tree nodes.
 * \param[in] n the root node pointer of a tree
 */
void FreeTreeNodes(const std::shared_ptr<node>& root) {
    if (root != nullptr) {
        FreeTreeNodes(std::move(root->left));
        FreeTreeNodes(std::move(root->right));
        std::cout << root->val << "  ";
        root.reset();
        // delete root; // finaly delete root node
    }
}

/** Breadth First Search a Tree as a Graph with queue structure
 * and begin with node pointer n
 * \param[in] n node pointer of a tree
 */
void BFT(node* n) {
    std::queue<node*> queue;
    if (n != nullptr) {
        queue.push(n);
    }

    node* temp = nullptr;
    while (!queue.empty()) {
        temp = queue.front();
        queue.pop();
        std::cout << temp->val << "  ";
        if (temp->left) {
            queue.push(temp->left.get());
        }
        if (temp->right) {
            queue.push(temp->right.get());
        }
    }
}

/** traverse a tree with Pre order
 * and print the node value
 * \param[in] n the root node pointer of a tree
 */
void Pre(node* n) {
    if (n != nullptr) {
        std::cout << n->val << "  ";
        Pre(n->left.get());
        Pre(n->right.get());
    }
}

/** traverse a tree with In order
 * and print the node value
 * \param[in] n the root node pointer of a tree
 */
void In(node* n) {
    if (n != nullptr) {
        In(n->left.get());
        std::cout << n->val << "  ";
        In(n->right.get());
    }
}

/** traverse a tree with Post order
 * and print the node value
 * \param[in] n the root node pointer of a tree
 */
void Post(node* n) {
    if (n != nullptr) {
        Post(n->left.get());
        Post(n->right.get());
        std::cout << n->val << "  ";
    }
}

/** test traverse a tree with Post order
 * and save the traverse node to an array.
 * \param[in] n the node pointer of a tree to start traverse
 * \param[out] arr the output array that save the traversed tree nodes pointers
 */
void testInOrderTraverse(node* n, std::vector<int>* arr) {
    if (n != nullptr) {
        testInOrderTraverse(n->left.get(), arr);
        std::cout << n->val << "  ";
        arr->push_back(n->val);
        testInOrderTraverse(n->right.get(), arr);
    }
}
}  // namespace BST

}  // namespace data_structure

/** test function.
 * auto build a binary tree with special nodes.
 * test the tree Insert() and Remove() function and out test result.
 */
void test_tree() {
    std::shared_ptr<data_structure::BST::node> root(
        new data_structure::BST::node);
    root->val = 4;
    root->left = nullptr;
    root->right = nullptr;
    // test Insert()
    data_structure::BST::Insert(root.get(), 2);
    data_structure::BST::Insert(root.get(), 1);
    data_structure::BST::Insert(root.get(), 3);
    data_structure::BST::Insert(root.get(), 6);
    data_structure::BST::Insert(root.get(), 5);
    data_structure::BST::Insert(root.get(), 7);
    std::cout
        << "after Insert() ,the expected output should be : 1, 2, 3, 4, 5, 6 ,7"
        << std::endl;
    // test code
    std::vector<int> arr;
    testInOrderTraverse(root.get(), &arr);
    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Test Insert() function Passed\n========================\n";

    // test Remove()
    // node* temp = root.get();
    // Remove(std::move(root), std::move(root), 2);
    data_structure::BST::Remove(root, root, 2);
    std::cout << "\n after Remove() node 2 , the expected output should be : "
                 "1, 3, 4, 5, 6, 7"
              << std::endl;
    arr.clear();
    data_structure::BST::testInOrderTraverse(root.get(), &arr);
    for (int i = 0; i < 6; i++) {
        assert(arr[i] != 2);
    }
    std::cout << "Test Remove(2) Passed\n========================\n";
}

/** main test function with commands.
 * build and test a binary search tree according to user input commands.
 */
int main() {
    // test tree
    test_tree();
    int value = 0;
    int ch = 0;
    std::shared_ptr<data_structure::BST::node> root(
        new data_structure::BST::node);
    std::cout << "\nEnter the value of root node :";
    std::cin >> value;
    root->val = value;
    root->left = nullptr;
    root->right = nullptr;

    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First";

        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        int x = 0;
        switch (ch) {
        case 1:
            std::cout << "\nEnter the value to be Inserted : ";
            std::cin >> x;
            data_structure::BST::Insert(root.get(), x);
            break;
        case 2:
            std::cout << "\nEnter the value to be Deleted : ";
            std::cin >> x;
            data_structure::BST::Remove(root, root, x);
            break;
        case 3:
            data_structure::BST::BFT(root.get());
            break;
        case 4:
            data_structure::BST::Pre(root.get());
            break;
        case 5:
            data_structure::BST::In(root.get());
            break;
        case 6:
            data_structure::BST::Post(root.get());
            break;
        }
    } while (ch != 0);

    return 0;
}
