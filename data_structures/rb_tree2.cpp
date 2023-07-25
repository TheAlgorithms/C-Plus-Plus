/**
 * @file
 * @brief A Red Black Tree Program
 * (https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html)
 * @details
 * A program simulating the Red Black Tree algorithm
 * using helper functions with descriptive function names and annotations.
 * @author [Brennan Allen](https://github.com/brennandoubt)
 * @see rb_tree.cpp
 */

#include <cassert>   /// for assert
#include <cstdlib>   /// for rand_r
#include <iostream>  /// for IO operations
#include <sstream>   /// for creating ostringstreams
#include <string>    /// for creating strings
#include <vector>    /// for creating vectors

using std::cout;
using std::endl;
using std::invalid_argument;
using std::ostringstream;
using std::string;
using std::vector;

// represent node colors as fixed integers
const int COLOR_RED = 0;
const int COLOR_BLACK = 1;
const int COLOR_DOUBLE_BLACK = 2;

/**
 * @brief Node blueprint for red black tree
 * @details
 * Defines the structure of a node's contents in the
 * tree. Each node contains a number representing its color,
 * an integer value, and pointers to its
 * parent and child nodes. Nodes are red by default.
 */
struct rbt_node {
    uint16_t color = COLOR_RED;

    int val = 0;

    rbt_node* parent = nullptr;
    rbt_node* left = nullptr;
    rbt_node* right = nullptr;

    bool treatAsNull = false;
};

/**
 * @brief Red Black Tree data structure blueprint
 * @details
 * Defines a collection of functions and variables
 * used to create a red black tree data structure.
 */
class red_black_tree {
 public:
    /**
     * @brief Constructor for Red Black Tree
     */
    red_black_tree() {
        root = nullptr;
        num_items = 0;
    }

    /**
     * @brief Deconstructor for Red Black Tree
     * @details
     * post_delete() used to
     * free Red Black Tree memory
     */
    ~red_black_tree() { post_delete(root); }

    /**
     * @brief Deletes tree nodes through postorder traversal
     * @param node the node where postorder traversal starts from
     */
    void post_delete(rbt_node* node) {
        // delete left then right (recursively)
        if (node != nullptr) {
            post_delete(node->left);
            post_delete(node->right);
        }
        // delete parent
        delete node;
    }

    /**
     * @brief Makes this tree a copy of another tree
     * @param rbt the Red Black Tree to be copied
     */
    red_black_tree(const red_black_tree& rbt) {
        // re-initialize tree
        this->root = nullptr;
        this->num_items = 0;

        // insert tree nodes in same order as the copied tree
        for (int n : rbt.nodes_order_added) {
            this->insert(n);
        }
    }

    /**
     * @brief Gives size of tree
     * @return num_items number of nodes in tree
     */
    uint64_t size() { return num_items; }

    /**
     * @brief Gives tree data in infix notation
     * @return string representing tree nodes in infix order
     */
    string to_infix_string() const { return to_infix_string(root); }

    /**
     * @brief Gives tree data in prefix notation
     * @return string representing tree nodes in prefix order
     */
    string to_prefix_string() const { return to_prefix_string(root); }

    /**
     * @brief Gives tree data in postfix notation
     * @return string representing tree nodes in postfix order
     */
    string to_postfix_string() const { return to_postfix_string(root); }

    /**
     * @brief inserts a new node into tree
     * @param value integer value stored in the new node
     */
    void insert(int value) {
        // check for duplicate keys
        if (this->contains(value)) {
            throw invalid_argument(
                "insert(): Node is already in tree"
                ", duplicate nodes not allowed.");
        }
        // using 'auto' specifier since type already known from 'new rbt_node'
        auto node_to_insert = new rbt_node();

        node_to_insert->val = value;
        nodes_order_added.push_back(value);

        // set node as the root if tree is empty
        if (root == nullptr) {
            root = node_to_insert;
            root->color = COLOR_BLACK;
        } else {
            rbt_node* curr_node = root;
            rbt_node* curr_parent = nullptr;

            // traverse down tree until a place to insert node is found
            while (curr_node != nullptr) {
                curr_parent = curr_node;

                if (value < curr_node->val) {
                    // go left if value < current node
                    curr_node = curr_node->left;
                } else if (value > curr_node->val) {
                    // go right if value > current node
                    curr_node = curr_node->right;
                }
            }
            // set parent and child pointers for node
            node_to_insert->parent = curr_parent;
            if (value < node_to_insert->parent->val) {
                node_to_insert->parent->left = node_to_insert;
            } else if (value > node_to_insert->parent->val) {
                node_to_insert->parent->right = node_to_insert;
            }
            // maintain conditions for red black tree
            check_tree_conditions(node_to_insert);
        }
        num_items++;
    }

    /**
     * @brief removes node from tree and re-balances as needed
     * @details
     * Re-balances tree by checking if
     * red black tree conditions need to be fixed
     * when removing the node. Node colors or pointers
     * may need to change in order to maintain the necessary
     * conditions for a red black tree after removal.
     * @param data integer value of the node to remove
     */
    void remove(int data) {
        rbt_node* node_to_delete = find(data);

        // to store the node that will replace the deleted node
        rbt_node* replacement_node = node_to_delete;

        // to check number of children the node to delete has
        unsigned int num_children = get_num_children(node_to_delete);

        // to check if node to delete is also the root node
        bool is_root = (node_to_delete == root);

        if (num_children == 2) {
            int ios_val = in_order_successor(node_to_delete)->val;
            remove(ios_val);
            node_to_delete->val = ios_val;
            return;
        } else if (num_children == 0) {
            // disconnect node from parent if it has no children

            if (root != node_to_delete) {
                node_to_delete->treatAsNull = true;
            } else {
                root = nullptr;
                replacement_node = root;
            }
        } else if (num_children == 1) {
            // replace node with its only child

            if (is_root) {
                root = me_to_only_child_ptr(node_to_delete);
                root->parent = nullptr;
                root->color = COLOR_BLACK;
                replacement_node = root;
            } else {
                // update pointers for node's only child
                parent_to_me_ptr(node_to_delete) =
                    me_to_only_child_ptr(node_to_delete);
                me_to_only_child_ptr(node_to_delete)->parent =
                    node_to_delete->parent;
                replacement_node = me_to_only_child_ptr(node_to_delete);
            }
        }

        // check rotate/recolor conditions
        if (root != nullptr) {
            if (replacement_node == root ||
                replacement_node->color == COLOR_RED) {
                replacement_node->color = COLOR_BLACK;
            } else if (node_to_delete->color == COLOR_BLACK &&
                       (replacement_node->color == COLOR_BLACK ||
                        replacement_node->treatAsNull)) {
                // fix double-blackness in tree

                replacement_node->color = COLOR_DOUBLE_BLACK;
                fix_double_black(replacement_node);
            }
        }

        // node marked as null if it's a leaf
        if (node_to_delete->treatAsNull) {
            // disconnect node from parent
            parent_to_me_ptr(node_to_delete) = nullptr;
        }

        delete node_to_delete;
        num_items--;
    }

    /**
     * @brief Gives the number of children a node has
     * @param node the tree node to check
     * @return unsigned int the number of children for this node
     */
    unsigned int get_num_children(rbt_node* node) {
        unsigned int num_children = 0;

        if (node->left != nullptr)
            num_children++;
        if (node->right != nullptr)
            num_children++;

        return num_children;
    }

    /**
     * @brief Fixes double-blackness issue in tree
     * @details
     * Double-blackness case can occur when removing a node
     * from the red black tree. Fixing this case ensures each path
     * in the tree will have an equal number of black nodes,
     * a necessary condition for a red black tree.
     * @param replacement_node the double-black node
     */
    void fix_double_black(rbt_node* replacement_node) {
        if (replacement_node == root) {
            replacement_node->color = COLOR_BLACK;
        } else {
            rbt_node* sibling = get_sibling(replacement_node);

            if (sibling->color == COLOR_BLACK) {
                if (has_red_child(sibling)) {
                    check_sibling_conditions(replacement_node, sibling);
                } else {
                    // shift blackness level up to parent
                    sibling->color = COLOR_RED;
                    replacement_node->color = COLOR_BLACK;
                    replacement_node->parent->color++;

                    if (replacement_node->parent->color == COLOR_DOUBLE_BLACK) {
                        fix_double_black(replacement_node->parent);
                    }
                }
            } else if (sibling->color == COLOR_RED) {
                // rotate tree to give replacement node a black sibling

                // recolor before rotation
                sibling->parent->color = COLOR_RED;
                sibling->color = COLOR_BLACK;

                // rotate right for left sibling
                if (parent_to_me_ptr(sibling) == sibling->parent->left) {
                    rotate_right(sibling);
                } else if (parent_to_me_ptr(sibling) == sibling->parent->right) {
                    // rotate left for right sibling
                    rotate_left(sibling);
                }

                // fix again with a black sibling
                fix_double_black(replacement_node);
            }
        }
    }

    /**
     * @brief Checks if a node has a red child
     * @param n the node to check
     * @return true if node has a red child, false otherwise
     */
    bool has_red_child(rbt_node* n) {
        rbt_node* n_left = n->left;
        rbt_node* n_right = n->right;

        return (n_left != nullptr && n_left->color == COLOR_RED) ||
               (n_right != nullptr && n_right->color == COLOR_RED);
    }

    /**
     * @brief Re-balances tree based on the double-black
     * node and its sibling conditions
     * @note
     * Assumed that parameters will be correct for this
     * function's specific use. Tree nodes may be rotated
     * or recolored to fix double-blackness.
     * @param replacement the double-black tree node
     * @param sibling the sibling of the double-black node
     */
    void check_sibling_conditions(rbt_node* replacement, rbt_node* sibling) {
        rbt_node* s_left = sibling->left;
        rbt_node* s_right = sibling->right;

        // check if sibling is the left child of its parent
        if (parent_to_me_ptr(sibling) == sibling->parent->left) {
            // left left: with left or 2 red kids
            if (s_left != nullptr && s_left->color == COLOR_RED) {
                // rotate right once and recolor to fix double-blackness
                rotate_right(sibling);
                shift_colors_left(sibling);
            } else {
                // left right: with 1 red kid on right (only other case)

                // simpler left left case is made from rotating left
                rotate_left(s_right);
                sibling = s_right;
                color_swap(sibling, sibling->left);

                // rotate right and recolor to fix new left left case
                rotate_right(sibling);
                shift_colors_left(sibling);
            }
        } else if (parent_to_me_ptr(sibling) == sibling->parent->right) {
            // sibling is a right child of its parent

            // right right: with right or 2 red kids
            if (s_right != nullptr && s_right->color == COLOR_RED) {
                // rotate left once and recolor
                rotate_left(sibling);
                shift_colors_right(sibling);
            } else {
                // right left: with 1 red kid on left

                // rotate right on child, making a right right rotate case
                rotate_right(s_left);
                sibling = s_left;
                color_swap(sibling, sibling->right);

                // rotate left and recolor to fix new right right case
                rotate_left(sibling);
                shift_colors_right(sibling);
            }
        }
        // color level returns to black
        replacement->color--;
    }

    /**
     * @brief Shifts colors of a node and its children to the right
     * @param sibling the node where color shift occurs
     */
    void shift_colors_right(rbt_node* sibling) {
        sibling->right->color = sibling->color;
        sibling->color = sibling->left->color;
        sibling->left->color = COLOR_BLACK;
    }

    /**
     * @brief Shifts colors of a node and its children to the left
     * @note
     * A left color shift is necessary after a right rotation occurs
     * in the red black tree.
     * @param sibling the node where color shift occurs
     */
    void shift_colors_left(rbt_node* sibling) {
        sibling->left->color = sibling->color;
        sibling->color = sibling->right->color;
        sibling->right->color = COLOR_BLACK;
    }

    /**
     * @brief Gives the pointer from a node to its only child
     * @details
     * Assuming node 'n' has only one valid child,
     * this function checks if it's a left or right child and
     * returns the pointer to it from parent node 'n'
     * (ex. returns 'n->left' or 'n->right')
     * @param n the node to get the child pointer for
     * @return rbt_node*& the node's pointer to its only child
     */
    rbt_node*& me_to_only_child_ptr(rbt_node* n) {
        // check node has exactly one non-null child
        if ((n->left == nullptr || n->right == nullptr) &&
            !(n->left == nullptr && n->right == nullptr)) {
            // is left child
            if (n->left != nullptr) {
                return n->left;
            } else if (n->right != nullptr) {
                // is right child

                return n->right;
            }
        }
        // reaches here if passed node is invalid for function
        throw invalid_argument(
            "me_to_only_child_ptr(): Node passed "
            "doesn't have exactly one child.");
    }

    /**
     * @brief Gives the pointer from a node's parent to itself
     * @param n the node pointed to by its parent
     * @return rbt_node*& the parent's pointer to the node
     */
    rbt_node*& parent_to_me_ptr(rbt_node* n) {
        rbt_node* p = n->parent;
        if (p != nullptr) {
            if (p->left == n) {
                return p->left;
            } else if (p->right == n) {
                return p->right;
            }
        }
        throw invalid_argument(
            "parent_to_me_ptr(): Node passed is root"
            " or has invalid parent.");
    }

    /**
     * @brief Re-balances tree after a new node is inserted
     * @details
     * Tree nodes may be rotated or recolored to
     * maintain necessary conditions for red black tree.
     * @param node checks tree starting from this node (assumed
     * to be the node just inserted into tree) up to the root
     */
    void check_tree_conditions(rbt_node* node) {
        if (node == root || node == nullptr) {
            if (node == root) {
                root->color = COLOR_BLACK;
            }
        } else if (node->parent->color == COLOR_RED) {
            rbt_node* parent_sibling = this->get_sibling(node->parent);

            if (parent_sibling == nullptr ||
                parent_sibling->color == COLOR_BLACK) {
                conditional_rotate(node);
            } else if (parent_sibling->color == COLOR_RED) {
                rbt_node* grandparent = node->parent->parent;

                // push blackness down from grandparent node
                grandparent->color = COLOR_RED;
                grandparent->left->color = COLOR_BLACK;
                grandparent->right->color = COLOR_BLACK;

                // recursively check tree conditions after recolor
                check_tree_conditions(grandparent);
            }
        }
    }

    /**
     * @brief Rotates tree nodes left
     * @note
     * Rotation should occur with respect to the parent node
     * in a grandparent-parent-child tree case.
     * @param node the parent node where rotation occurs
     */
    void rotate_left(rbt_node* node) {
        rbt_node* great_grandparent = node->parent->parent;
        rbt_node* grandparent = node->parent;

        node->parent = great_grandparent;
        if (great_grandparent != nullptr) {
            if (node->val <= great_grandparent->val) {
                great_grandparent->left = node;
            } else if (node->val > great_grandparent->val) {
                great_grandparent->right = node;
            }
        } else {
            // parent becomes root if there's no great grandparent node
            this->root = node;
        }

        rbt_node* parent_left = node->left;

        grandparent->parent = node;
        node->left = grandparent;

        if (parent_left != nullptr) {
            parent_left->parent = grandparent;
        }
        grandparent->right = parent_left;
    }

    /**
     * @brief Rotates tree nodes right
     * @note
     * Rotation should occur with respect to the parent node
     * in a grandparent-parent-child tree case.
     * @param node the parent node where rotation occurs
     */
    void rotate_right(rbt_node* node) {
        rbt_node* great_grandparent = node->parent->parent;
        rbt_node* grandparent = node->parent;

        node->parent = great_grandparent;
        if (great_grandparent != nullptr) {
            if (node->val <= great_grandparent->val) {
                great_grandparent->left = node;
            } else if (node->val > great_grandparent->val) {
                great_grandparent->right = node;
            }
        } else {
            // parent becomes the root if there's no great grandparent node
            this->root = node;
        }

        rbt_node* parent_right = node->right;

        grandparent->parent = node;
        node->right = grandparent;

        if (parent_right != nullptr) {
            parent_right->parent = grandparent;
        }
        grandparent->left = parent_right;
    }

    /**
     * @brief Rotates tree based on a node and its parent
     * and grandparent positions
     * @details
     * Rotation Conditions
     * 1) left left: Rotate right, Recolor
     * 2) left right: Rotate left then right, Recolor
     * 3) right left: Rotate right then left, Recolor
     * 4) right right: Rotate left, Recolor
     * @param node the tree node where rotation occurs
     */
    void conditional_rotate(rbt_node* node) {
        rbt_node* parent_left = node->parent->left;
        rbt_node* parent_right = node->parent->right;
        rbt_node* grandparent_left = node->parent->parent->left;
        rbt_node* grandparent_right = node->parent->parent->right;

        // ... left
        if (parent_left == node) {
            // left left
            if (grandparent_left == node->parent) {
                // rotate right on parent
                rotate_right(node->parent);
                color_swap(node->parent, node->parent->right);
            }
            // right left
            if (grandparent_right == node->parent) {
                rotate_right(node);
                rotate_left(node);
                color_swap(node, node->left);
            }
        }
        // ... right
        if (parent_right == node) {
            // right right
            if (grandparent_right == node->parent) {
                rotate_left(node->parent);
                color_swap(node->parent, node->parent->left);
            }
            // left right
            if (grandparent_left == node->parent) {
                rotate_left(node);
                rotate_right(node);
                color_swap(node, node->right);
            }
        }
    }

    /**
     * @brief Swaps the colors of two tree nodes
     * @note
     * Assumed that nodes will always be original parent
     * and grandparent nodes of a rotated subtree.
     * @param parent the rotated parent node
     * @param grandparent the rotated grandparent node
     */
    void color_swap(rbt_node* parent, rbt_node* grandparent) {
        uint16_t gp_color = grandparent->color;
        grandparent->color = parent->color;
        parent->color = gp_color;
    }

    /**
     * @brief Gives a node's in-order successor (IOS)
     * @note
     * This function is used in remove().
     * @param node the node to get the IOS of
     * @return rbt_node* the IOS node
     */
    rbt_node* in_order_successor(rbt_node* node) {
        // begin traversal at the passed node
        rbt_node* trav = node;

        // go right once
        if (trav->right != nullptr) {
            trav = trav->right;

            // go left until at leftmost node
            while (trav->left != nullptr) {
                trav = trav->left;
            }
        }

        return trav;
    }

    /**
     * @brief Checks if a node with a given value is in the tree
     * @param value the value to check for
     * @return true if the tree contains a node with this value
     * @return false otherwise
     */
    bool contains(int value) {
        if (root != nullptr) {
            rbt_node* trav = root;

            while (trav != nullptr) {
                // node with the same value found in tree
                if (trav->val == value) {
                    return true;
                } else if (value < trav->val) {
                    // use binary search to efficiently traverse tree
                    trav = trav->left;
                } else if (value > trav->val) {
                    trav = trav->right;
                }
            }
        }

        // node not in tree or tree is empty
        return false;
    }

    /**
     * @brief finds a node in the tree with a specified value.
     * @note
     * This function is the same as contains()
     * except it returns the node found or throws
     * an exception.
     * @param value the value of the node to search for
     * @return rbt_node* the node with this value
     */
    rbt_node* find(int value) {
        if (root != nullptr) {
            rbt_node* trav = root;
            while (trav != nullptr) {
                if (trav->val == value) {
                    return trav;
                } else if (value < trav->val) {
                    trav = trav->left;
                } else if (value > trav->val) {
                    trav = trav->right;
                }
            }
        }
        // reaches here if node not found in tree
        throw invalid_argument("Node not in tree.");
    }

    /**
     * @brief Gives the minimum node value in tree.
     * @return int the lowest value in the tree
     */
    int get_min() {
        // minimum value node will be at left end of the tree
        rbt_node* trav = root;
        while (trav->left != nullptr) {
            trav = trav->left;
        }
        return trav->val;
    }

    /**
     * @brief Gives the maximum node value in tree
     * @return int the highest value in the tree
     */
    int get_max() {
        // maximum value node will be at right end of the tree
        rbt_node* trav = root;
        while (trav->right != nullptr) {
            trav = trav->right;
        }
        return trav->val;
    }

    /**
     * @brief Gives the sibling of a node if one exists
     * @param node the node to get the sibling of
     * @return rbt_node*& the sibling of the passed node
     */
    rbt_node*& get_sibling(rbt_node* node) {
        if (node == root) {
            throw invalid_argument("Root has no sibling.");
        }
        // check which parent's child is NOT the passed node
        if (node->parent->left != node) {
            return node->parent->left;
        } else if (node->parent->right != node) {
            return node->parent->right;
        } else {
            // no sibling
            throw invalid_argument("Invalid node passed.");
        }
    }

 private:
    uint64_t num_items;              /// number of nodes in tree
    rbt_node* root;                  /// top node of tree
    vector<int> nodes_order_added;  /// for copy constructor

    /**
     * @brief Creates an infix string of tree
     * @param node the top node where the string begins
     * recursively generating down the tree
     * @return string representing tree in infix notation
     */
    string to_infix_string(struct rbt_node* node) const {
        ostringstream nodeOSS;

        if (node != nullptr) {
            // print left (recursion)
            nodeOSS << to_infix_string(node->left);

            // print node's color and value
            nodeOSS << " ";
            if (node->color == COLOR_BLACK) {
                nodeOSS << 'B';
            } else {
                nodeOSS << 'R';
            }
            nodeOSS << node->val << " ";

            // print right (recursion)
            nodeOSS << to_infix_string(node->right);
        }
        // return string once null node reached (base case)
        return nodeOSS.str();
    }

    /**
     * @brief Creates a prefix string of tree
     * @param node the top node where string
     * begins recursively generating down the tree
     * @return string representing tree in prefix notation
     */
    string to_prefix_string(struct rbt_node* node) const {
        ostringstream nodeOSS;
        if (node != nullptr) {
            // print node's color and value
            nodeOSS << " ";
            if (node->color == COLOR_BLACK) {
                nodeOSS << 'B';
            } else {
                nodeOSS << 'R';
            }
            nodeOSS << node->val << " ";

            // print left then right (recursively)
            nodeOSS << to_prefix_string(node->left);
            nodeOSS << to_prefix_string(node->right);
        }
        return nodeOSS.str();
    }

    /**
     * @brief Creates a postfix string of tree
     * @param node the top node where string
     * begins recursively generating down the tree
     * @return string representing tree in postfix notation
     */
    string to_postfix_string(struct rbt_node* node) const {
        ostringstream nodeOSS;
        if (node != nullptr) {
            // print left then right (recursively)
            nodeOSS << to_postfix_string(node->left);
            nodeOSS << to_postfix_string(node->right);

            // print node's color and value
            nodeOSS << " ";
            if (node->color == COLOR_BLACK) {
                nodeOSS << 'B';
            } else {
                nodeOSS << 'R';
            }
            nodeOSS << node->val << " ";
        }
        return nodeOSS.str();
    }
};

/**
 * @brief self-test by calling constructor
 * @return void
 */
void simple_constructor_test() {
    cout << "Testing Simple Constructor... " << endl;
    red_black_tree rbt = red_black_tree();

    assert(rbt.to_infix_string() == "");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief simple insert of a value into tree
 * @return void
 */
void insert_first_node_test() {
    cout << "Testing insert One Node..." << endl;

    red_black_tree rbt = red_black_tree();
    rbt.insert(30);

    assert(rbt.to_prefix_string() == " B30 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting two values into tree
 * @return void
 */
void insert_second_node_test() {
    cout << "Testing insert Second Node..." << endl;
    red_black_tree* rbt = new red_black_tree();
    rbt->insert(30);
    rbt->insert(15);

    assert(rbt->to_prefix_string() == " B30  R15 ");
    delete rbt;

    rbt = new red_black_tree();
    rbt->insert(30);
    rbt->insert(45);

    assert(rbt->to_prefix_string() == " B30  R45 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting three nodes into tree
 * (and making rotations occur)
 * @return void
 */
void insert_third_node_test() {
    cout << "Testing insert Third Node..." << endl;

    red_black_tree* rbt = new red_black_tree();
    rbt->insert(30);
    rbt->insert(15);
    rbt->insert(10);  // Left Left

    // rotate right once
    assert(rbt->to_prefix_string() == " B15  R10  R30 ");
    delete rbt;

    rbt = new red_black_tree();
    rbt->insert(30);
    rbt->insert(15);
    rbt->insert(25);  // Left Right

    // rotate once right on parent then once left on grandparent
    assert(rbt->to_prefix_string() == " B25  R15  R30 ");
    delete rbt;

    rbt = new red_black_tree();
    rbt->insert(30);
    rbt->insert(15);
    rbt->insert(45);  // Easy case

    // nodes on either side and parent is black, so no rotation or recolor
    assert(rbt->to_prefix_string() == " B30  R15  R45 ");
    delete rbt;

    rbt = new red_black_tree();
    rbt->insert(75);
    rbt->insert(215);
    rbt->insert(130);  // Right Left

    assert(rbt->to_prefix_string() == " B130  R75  R215 ");
    delete rbt;

    rbt = new red_black_tree();
    rbt->insert(648);
    rbt->insert(735);
    rbt->insert(9442);  // Right Right

    assert(rbt->to_prefix_string() == " B735  R648  R9442 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting four values into tree
 * @return void
 */
void insert_fourth_node_test() {
    cout << "Testing insert Fourth Node..." << endl;

    red_black_tree rbt = red_black_tree();

    rbt.insert(13);
    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(9);

    assert(rbt.to_prefix_string() == " B7  B3  B13  R9 ");

    red_black_tree rbt2 = red_black_tree();

    rbt2.insert(34);
    rbt2.insert(76);
    rbt2.insert(21984);
    rbt2.insert(2);

    assert(rbt2.to_prefix_string() == " B76  B34  R2  B21984 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting five nodes into tree
 * @return void
 */
void insert_fifth_node_test() {
    cout << "Testing insert Fifth Node..." << endl;
    red_black_tree* rbt = new red_black_tree();
    rbt->insert(30);
    rbt->insert(15);
    rbt->insert(45);
    rbt->insert(10);
    rbt->insert(25);

    assert(rbt->to_prefix_string() == " B30  B15  R10  R25  B45 ");
    delete rbt;

    red_black_tree rbt2 = red_black_tree();
    rbt2.insert(783);
    rbt2.insert(91);
    rbt2.insert(31);
    rbt2.insert(11);
    rbt2.insert(-87);

    assert(rbt2.to_prefix_string() == " B91  B11  R-87  R31  B783 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if string functions
 * return correct values
 * @return void
 */
void to_strings_test() {
    cout << "Testing ToString Methods..." << endl;

    red_black_tree rbt = red_black_tree();
    rbt.insert(12);
    rbt.insert(11);
    rbt.insert(15);
    rbt.insert(5);
    rbt.insert(13);
    rbt.insert(7);

    assert(rbt.to_prefix_string() == " B12  B7  R5  R11  B15  R13 ");
    assert(rbt.to_infix_string() == " R5  B7  R11  B12  R13  B15 ");
    assert(rbt.to_postfix_string() == " R5  R11  B7  R13  B15  B12 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing with inserts into tree
 * using different values
 * @return void
 */
void random_inserts_test() {
    cout << "Testing Random insert Stuff..." << endl;
    cout << "\t This test passes if it doesn't crash and valgrind"
            " reports no issues"
         << endl;
    red_black_tree* rbt = new red_black_tree();
    rbt->insert(15);
    rbt->insert(13);
    rbt->insert(20);
    rbt->insert(12);
    cout << endl;

    delete rbt;

    rbt = new red_black_tree();

    rbt->insert(12);
    rbt->insert(11);
    rbt->insert(15);
    rbt->insert(5);
    rbt->insert(13);
    rbt->insert(7);
    delete rbt;

    rbt = new red_black_tree();

    rbt->insert(12);
    rbt->insert(10);
    rbt->insert(8);
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing copy constructor by
 * copying a tree
 * @return void
 */
void copy_constructor_test() {
    cout << "Testing Copy Constructor..." << endl;

    red_black_tree rbt1 = red_black_tree();
    rbt1.insert(11);
    rbt1.insert(23);
    rbt1.insert(9);
    rbt1.insert(52);
    rbt1.insert(31);
    rbt1.insert(4);

    assert(rbt1.to_prefix_string() == " B11  B9  R4  B31  R23  R52 ");

    red_black_tree rbt2 = red_black_tree(rbt1);

    assert(rbt2.to_prefix_string() == rbt1.to_prefix_string());

    rbt1.insert(200);
    assert(rbt2.to_prefix_string() != rbt1.to_prefix_string());

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if contains() function correctly
 * determines if a value is in the tree
 * @return void
 */
void contains_test() {
    cout << "Testing contains..." << endl;
    red_black_tree* rbt = new red_black_tree();
    rbt->insert(40);
    rbt->insert(22);
    rbt->insert(15);
    rbt->insert(31);
    rbt->insert(55);
    rbt->insert(12);
    rbt->insert(17);
    rbt->insert(29);
    rbt->insert(34);

    assert(rbt->contains(34));
    delete rbt;

    red_black_tree rbt2 = red_black_tree();
    rbt2.insert(1);
    rbt2.insert(27);
    rbt2.insert(99);
    rbt2.insert(19);

    assert(rbt2.contains(1) && rbt2.contains(99));

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing get_min(), get_max() functions
 * have correct outputs
 * @return void
 */
void get_min_max_test() {
    cout << "Testing Get Minimum and Get Maximum..." << endl;

    red_black_tree rbt = red_black_tree();

    rbt.insert(34);
    rbt.insert(76);
    rbt.insert(21984);
    rbt.insert(2);

    assert(rbt.get_max() == 21984 && rbt.get_min() == 2);

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of copy constructor
 * @return void
 */
void copy_constructor_test2() {
    cout << "Testing Copy Constructor..." << endl;

    red_black_tree rbt1 = red_black_tree();
    rbt1.insert(11);
    rbt1.insert(23);
    rbt1.insert(9);
    rbt1.insert(52);
    rbt1.insert(31);
    rbt1.insert(4);

    assert(rbt1.to_prefix_string() == " B11  B9  R4  B31  R23  R52 ");

    red_black_tree rbt2 = red_black_tree(rbt1);

    assert(rbt1.size() == rbt2.size());
    assert(rbt2.to_prefix_string() == rbt1.to_prefix_string());

    rbt1.insert(200);
    assert(rbt2.to_prefix_string() != rbt1.to_prefix_string());

    red_black_tree rbt3 = red_black_tree();
    cout << rbt3.to_prefix_string() << endl;
    rbt3.insert(12);
    rbt3.insert(10);
    rbt3.insert(0);
    rbt3.insert(11);
    rbt3.insert(3);
    rbt3.insert(9);
    rbt3.insert(2);
    rbt3.insert(7);
    rbt3.insert(1);
    rbt3.insert(4);
    rbt3.insert(6);
    rbt3.insert(8);
    rbt3.insert(37);
    rbt3.insert(5);
    rbt3.insert(72);
    rbt3.insert(55);
    rbt3.insert(90);
    rbt3.insert(92);
    rbt3.insert(20);
    rbt3.insert(13);

    rbt3.insert(57);

    rbt3.insert(30);
    rbt3.insert(64);

    // left rotate on root
    rbt3.insert(69);

    rbt3.insert(50);
    rbt3.insert(67);
    rbt3.insert(99);
    rbt3.insert(89);
    rbt3.insert(33);

    assert(
        rbt3.to_prefix_string() ==
        " B12  R7  B3  B1  R0  R2  B5  R4  R6"
        "  B10  B9  R8  B11  R55  B20  B13  R37  B30  R33  B50  B69  R64  B57"
        "  B67  R90  B72  R89  B92  R99 ");

    red_black_tree rbt4 = red_black_tree(rbt3);

    string s3 = rbt3.to_prefix_string();
    string s4 = rbt4.to_prefix_string();

    assert(rbt3.size() == rbt4.size());
    assert(s3 == s4);

    rbt3.insert(200);
    assert(rbt3.to_prefix_string() != rbt4.to_prefix_string());

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if tree properly
 * balances out when inserting values
 * @return void
 */
void test_insert_with_recursive_fix_up() {
    cout << "Testing Recursive FixUp..." << endl;

    red_black_tree* rbt = new red_black_tree();
    rbt->insert(400);
    rbt->insert(800);
    rbt->insert(200);
    rbt->insert(600);
    rbt->insert(150);
    rbt->insert(900);
    rbt->insert(300);
    rbt->insert(100);
    rbt->insert(175);
    rbt->insert(160);

    assert(rbt->to_prefix_string() ==
           " B200  R150  B100  B175  "
           "R160  R400  B300  B800  R600  R900 ");

    rbt->insert(185);
    rbt->insert(180);  // does a recursive fix-up

    assert(rbt->to_prefix_string() ==
           " B200  B150  B100  R175  B160  "
           "B185  R180  B400  B300  B800  R600  R900 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief Prints and evaluates test outputs
 * @param desc brief description of this test
 * @param rbt red black tree used for this test
 * @param exp_ans correct output for this test
 */
void print_test_line(string desc, const red_black_tree* rbt, string exp_ans) {
    cout << desc << ": " << rbt->to_prefix_string() << endl;
    assert(rbt->to_prefix_string() == exp_ans);
}

/**
 * @brief testing removing values from tree
 * (removing a root node with one child)
 * @return void
 */
void remove_test1() {
    cout << "Testing removing root (with one child)..." << endl;

    red_black_tree rbt = red_black_tree();
    rbt.insert(10);
    rbt.insert(459);

    cout << "size: " << rbt.size() << endl;
    assert(rbt.size() == 2);

    cout << "rbt: " << rbt.to_prefix_string() << endl;
    assert(rbt.to_prefix_string() == " B10  R459 ");

    // remove root with one right child
    rbt.remove(10);

    cout << "rbt: " << rbt.to_prefix_string() << endl;
    assert(rbt.to_prefix_string() == " B459 ");

    // remove root with no children (empties tree)
    rbt.remove(459);

    cout << "rbt: " << rbt.to_prefix_string() << endl;
    assert(rbt.to_prefix_string() == "");
    assert(rbt.size() == 0);

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of removing values
 * from tree (removing a leaf node)
 * @return void
 */
void remove_test2() {
    cout << "Testing removing leaf..." << endl;

    red_black_tree rbt = red_black_tree();
    rbt.insert(10);
    rbt.insert(459);

    cout << "rbt: " << rbt.to_prefix_string() << endl;

    // Removing leaf
    rbt.remove(459);

    cout << "rbt: " << rbt.to_prefix_string() << endl;

    // Removing last node/root (empties tree again)
    rbt.remove(10);

    cout << "rbt: " << rbt.to_prefix_string() << endl;
    assert(rbt.to_prefix_string() == "");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of removing values
 * from tree (removing node with two children)
 * @return void
 */
void remove_test3() {
    cout << "Testing removing node with two children..." << endl;

    red_black_tree* rbt = new red_black_tree();
    rbt->insert(14);
    rbt->insert(10);
    rbt->insert(459);  // B14 R10 R459 -- node 14 with two children 10 and 459

    print_test_line("tree", rbt, " B14  R10  R459 ");

    // remove 14 (has two children)
    rbt->remove(14);
    print_test_line("removing 14", rbt, " B459  R10 ");

    rbt->remove(459);
    print_test_line("removing 459", rbt, " B10 ");

    rbt->remove(10);
    print_test_line("removing 10", rbt, "");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of removing values
 * from tree (removing from a larger tree)
 * @return void
 */
void remove_test4() {
    cout << "Removing from larger tree "
            "(recursive call with IOS or IOP test)..."
         << endl;

    red_black_tree* rbt = new red_black_tree();

    rbt->insert(94);
    rbt->insert(18);
    rbt->insert(3);
    rbt->insert(22);
    rbt->insert(0);
    rbt->insert(537);
    rbt->insert(308);
    rbt->insert(23);
    rbt->insert(24);
    rbt->insert(21);
    rbt->insert(25);

    print_test_line("tree", rbt,
                  " B23  R18  B3  R0  B22  R21  R94"
                  "  B24  R25  B537  R308 ");

    rbt->remove(23);

    print_test_line("removing 23", rbt,
                  " B24  R18  B3  R0  B22  R21"
                  "  R94  B25  B537  R308 ");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if tree properly
 * rotates after inserting certain values
 * @return void
 */
void remove_rotate_case_test() {
    cout << "Testing removing that requires double-black fix..." << endl;

    red_black_tree* rbt = new red_black_tree();

    rbt->insert(9);
    rbt->insert(11);
    rbt->insert(5);
    rbt->insert(14);
    rbt->insert(4);
    rbt->insert(6);
    rbt->insert(7);

    print_test_line("tree", rbt, " B9  R5  B4  B6  R7  B11  R14 ");

    // RIGHT RIGHT CASE (rotate left on black sibling)
    rbt->remove(4);

    print_test_line("right right remove", rbt, " B9  R6  B5  B7  B11  R14 ");

    red_black_tree rbt2 = red_black_tree();

    rbt2.insert(9);
    rbt2.insert(11);
    rbt2.insert(5);
    rbt2.insert(14);
    rbt2.insert(4);
    rbt2.insert(7);
    rbt2.insert(6);

    cout << "tree2: " << rbt2.to_prefix_string() << endl;
    assert(rbt2.to_prefix_string() == " B9  R5  B4  B7  R6  B11  R14 ");

    // RIGHT LEFT CASE (black sibling 7 is right child with one left red child)
    rbt2.remove(4);

    cout << "right left remove: " << rbt2.to_prefix_string() << endl;
    assert(rbt2.to_prefix_string() == " B9  R6  B5  B7  B11  R14 ");

    rbt2.insert(4);  // makes left left case when removing 7
    assert(rbt2.to_prefix_string() == " B9  R6  B5  R4  B7  B11  R14 ");

    // LEFT LEFT CASE (black sibling 5 is left child with one left red child)
    rbt2.remove(7);
    assert(rbt2.to_prefix_string() == " B9  R5  B4  B6  B11  R14 ");

    delete rbt;
    rbt = new red_black_tree();

    // inserting nodes into tree from an array
    int fill_tree_vec[12] = {9, 11, 5, 14, 4, 6, 7, 3, 2, 17, 1, 8};
    for (int val : fill_tree_vec) {
        rbt->insert(val);
    }
    cout << "tree3: " << rbt->to_prefix_string() << endl;
    assert(rbt->to_prefix_string() ==
           " B5  R3  B2  R1  B4  R9  B7"
           "  R6  R8  B14  R11  R17 ");

    rbt->remove(1);  // simple remove on red leaf
    assert(rbt->to_prefix_string() ==
           " B5  R3  B2  B4  R9  B7  R6"
           "  R8  B14  R11  R17 ");

    rbt->insert(0);
    assert(rbt->to_prefix_string() ==
           " B5  R3  B2  R0  B4  R9  B7"
           "  R6  R8  B14  R11  R17 ");

    rbt->insert(1);
    assert(rbt->to_prefix_string() ==
           " B5  R3  B1  R0  R2  B4  R9"
           "  B7  R6  R8  B14  R11  R17 ");

    rbt->remove(0);  // another simple red leaf remove
    assert(rbt->to_prefix_string() ==
           " B5  R3  B1  R2  B4  R9  B7"
           "  R6  R8  B14  R11  R17 ");

    // LEFT RIGHT CASE (black sibling 1 is a left child with one right
    // red child)
    rbt->remove(4);
    cout << "left right remove: " << rbt->to_prefix_string() << endl;
    assert(rbt->to_prefix_string() ==
           " B5  R2  B1  B3  R9  B7  R6"
           "  R8  B14  R11  R17 ");

    // removing 3 (recursive fix double black case)
    rbt->remove(3);
    print_test_line("recursive double-black fix (removing 3)", rbt,
                  " B5  B2  R1  R9  B7  R6  R8  B14  R11  R17 ");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing removing a value with a "red sibling"
 * from tree
 * @return void
 */
void remove_red_sibling_case_test() {
    cout << "Testing remove that requires double-black fix with red "
            "sibling case..."
         << endl;

    red_black_tree rbt = red_black_tree();

    int fill_tree_vec[6] = {11, 9, 7, 5, 8, 6};
    for (int val : fill_tree_vec) {
        rbt.insert(val);
    }
    cout << "tree: " << rbt.to_prefix_string() << endl;
    assert(rbt.to_prefix_string() == " B9  R7  B5  R6  B8  B11 ");

    rbt.remove(11);  // 11 is black leaf with red sibling 7
    cout << "removing 11: " << rbt.to_prefix_string() << endl;
    assert(rbt.to_prefix_string() == " B7  B5  R6  B9  R8 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing memory management as values are
 * removed from tree
 * @return void
 */
void large_random_remove_memory_test() {
    cout << "Giant remove Test..." << endl;

    red_black_tree* giant_rbt = new red_black_tree();

    vector<int> random_numbers;  // to store inserted numbers

    while (giant_rbt->size() != 711) {
        int random_num = rand();
        if (!giant_rbt->contains(random_num)) {
            random_numbers.push_back(random_num);
            giant_rbt->insert(random_num);
        }
    }
    // getting numbers to remove, starting from end of vector
    size_t idx = random_numbers.size() - 1;

    // then removing the numbers until tree is empty
    // (checking for memory issues/exceptions)
    while (giant_rbt->size() != 0) {
        giant_rbt->remove(random_numbers[idx--]);
    }

    delete giant_rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief more testing of removing certain nodes from
 * a tree
 * @return void
 */
void larger_comprehensive_remove_test() {
    cout << "Testing many removes from larger tree..." << endl;

    red_black_tree* rbt = new red_black_tree();

    int fill_tree_vec[19] = {40, 97, 12, 43,   33,   87,   99,  439, 8762, 3,
                             7,  1,  2,  9999, 8888, 2345, 111, 687, 0};

    for (int val : fill_tree_vec) {
        rbt->insert(val);
    }

    cout << "tree: " << rbt->to_prefix_string() << endl;
    assert(rbt->to_prefix_string() ==
           " B87  B12  R3  B1  R0  R2  B7  R40  B33"
           "  B43  B439  R99  B97  B111  R8762  B2345  R687  B9999  R8888 ");

    rbt->remove(87);  // removing root
    cout << "removing 87: " << rbt->to_prefix_string() << endl;
    assert(rbt->to_prefix_string() ==
           " B97  B12  R3  B1  R0  R2  B7  R40  B33"
           "  B43  B439  B99  R111  R8762  B2345  R687  B9999  R8888 ");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief self-test implementation
 */
void tests() {
    simple_constructor_test();

    insert_first_node_test();

    insert_second_node_test();
    insert_third_node_test();
    insert_fourth_node_test();
    insert_fifth_node_test();

    to_strings_test();
    random_inserts_test();
    copy_constructor_test();

    contains_test();
    get_min_max_test();

    copy_constructor_test2();
    test_insert_with_recursive_fix_up();

    remove_test1();
    remove_test2();
    remove_test3();
    remove_test4();
    remove_rotate_case_test();
    remove_red_sibling_case_test();
    large_random_remove_memory_test();
    larger_comprehensive_remove_test();

    cout << "All tests passed!" << endl;
}

/**
 * @brief main function to run tests
 * @return 0 with successful exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
