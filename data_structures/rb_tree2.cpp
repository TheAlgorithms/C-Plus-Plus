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

// defining colors
const int COLOR_RED = 0;
const int COLOR_BLACK = 1;
const int COLOR_DOUBLE_BLACK = 2;

/**
 * @brief Node blueprint for red black tree
 * @note
 * Defines the structure of a node's contents in the
 * tree. Each node contains a number representing its color,
 * an integer value, and pointers to its
 * parent and child nodes. Nodes are red by default.
 */
struct RBTNode {
    uint16_t color = COLOR_RED;

    int val = 0;

    RBTNode* parent = nullptr; //
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;

    bool treatAsNull = false;
};

class RedBlackTree {
 public:
    /**
     * @brief Constructor for Red Black Tree
     */
    RedBlackTree() {
        root = nullptr;
        numItems = 0;
    }

    /**
     * @brief Deconstructor for Red Black Tree
     * @note 
     * PostDelete() used to
     * free Red Black Tree memory
     */
    ~RedBlackTree() { PostDelete(root); }

    /**
     * @brief Deletes tree nodes through postorder traversal
     * @param node the node where postorder traversal starts from
     */
    void PostDelete(RBTNode* node) {
        // delete left then right (recursively)
        if (node != nullptr) {
            PostDelete(node->left);
            PostDelete(node->right);
        }
        // delete parent
        delete node;
    }

    /**
     * @brief Makes this tree a copy of another tree
     * @param rbt the Red Black Tree to be copied
     */
    RedBlackTree(const RedBlackTree& rbt) {
        // re-initialize tree
        this->root = nullptr;
        this->numItems = 0;

        // insert tree nodes in same order as the copied tree
        for (int n : rbt.nodes_order_added) {
            this->Insert(n);
        }
    }

    /**
     * @brief Gives size of tree
     * @return numItems number of nodes in tree
     */
    uint64_t Size() { return numItems; }

    /**
     * @brief Gives tree data in infix notation
     * @return string representing tree nodes in infix order
     */
    string ToInfixString() const { return ToInfixString(root); }

    /**
     * @brief Gives tree data in prefix notation
     * @return string representing tree nodes in prefix order
     */
    string ToPrefixString() const { return ToPrefixString(root); }

    /**
     * @brief Gives tree data in postfix notation
     * @return string representing tree nodes in postfix order
     */
    string ToPostfixString() const { return ToPostfixString(root); }

    /**
     * @brief Inserts a new node into tree
     * @param value integer value stored in the new node
     */
    void Insert(int value) {
        // check for duplicate keys
        if (this->Contains(value)) {
            throw invalid_argument(
                "Insert(): Node is already in tree"
                ", duplicate nodes not allowed.");
        }
        // using 'auto' specifier since type already known from 'new RBTNode'
        auto node_to_insert = new RBTNode();

        node_to_insert->val = value;
        nodes_order_added.push_back(value);

        // set node as the root if tree is empty
        if (root == nullptr) {
            root = node_to_insert;
            root->color = COLOR_BLACK;
        } else {
            RBTNode* curr_node = root;
            RBTNode* curr_parent = nullptr;

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
            // check and fix tree if needed after insertion
            // to maintain RBT conditions
            CheckTreeConditions(node_to_insert);
        }
        numItems++;
    }

    /**
     * @brief Removes node from tree and re-balances as needed
     * @note
     * Re-balances tree by checking if
     * red black tree conditions need to be fixed
     * when removing the node. Node colors or pointers
     * may need to change in order to maintain the necessary
     * conditions for a red black tree after removal.
     * @param data integer value of the node to remove
     */
    void Remove(int data) {
        RBTNode* node_to_delete = Find(data);

        // to store the node that will replace the deleted node
        RBTNode* replacement_node = node_to_delete;

        // to check number of children the node to delete has
        unsigned int num_children = get_num_children(node_to_delete);

        // to check if node to delete is also the root node
        bool is_root = (node_to_delete == root);

        if (num_children == 2) {
            int ios_val = InOrderSuccessor(node_to_delete)->val;
            Remove(ios_val);
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
                root = MeToOnlyChildPtr(node_to_delete);
                root->parent = nullptr;
                root->color = COLOR_BLACK;
                replacement_node = root;
            } else {
                // update pointers for node's only child
                ParentToMePtr(node_to_delete) =
                    MeToOnlyChildPtr(node_to_delete);
                MeToOnlyChildPtr(node_to_delete)->parent =
                    node_to_delete->parent;
                replacement_node = MeToOnlyChildPtr(node_to_delete);
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
            ParentToMePtr(node_to_delete) = nullptr;
        }

        delete node_to_delete;
        numItems--;
    }

    /**
     * @brief Gives the number of children a node has
     * @param node the tree node to check
     * @return unsigned int the number of children for this node
     */
    unsigned int get_num_children(RBTNode* node) {
        unsigned int num_children = 0;
        
        if (node->left != nullptr)
            num_children++;
        if (node->right != nullptr)
            num_children++;

        return num_children;
    }

    /**
     * @brief Fixes double-blackness issue in tree
     * 
     * @note
     * Double-blackness case can occur when removing a node
     * from the red black tree. Fixing this case ensures each path
     * in the tree will have an equal number of black nodes,
     * a necessary condition for a red black tree.
     *
     * @param replacement_node the double-black node
     */
    void fix_double_black(RBTNode* replacement_node) {
        // sibling not needed if replacement node is at the tree's root
        if (replacement_node == root) {
            replacement_node->color = COLOR_BLACK;
        } else {
            // now using sibling for below conditions
            RBTNode* sibling = GetSibling(replacement_node);

            // sibling is black - check sibling's kids
            if (sibling->color == COLOR_BLACK) {
                // at least one red child
                if (has_red_child(sibling)) {
                    // rotate/recolor to fix double-blackness
                    CheckSiblingConditions(replacement_node, sibling);
                } else {
                    // no red children

                    // shift blackness level up to parent
                    sibling->color = COLOR_RED;
                    replacement_node->color = COLOR_BLACK;
                    replacement_node->parent->color++;
                    // blackness shift may make parent double-black,
                    // so fix if needed
                    if (replacement_node->parent->color == COLOR_DOUBLE_BLACK) {
                        fix_double_black(replacement_node->parent);
                    }
                }
            } else if (sibling->color == COLOR_RED) {
                // or replacement's sibling is red,
                // rotate to give replacement a black sibling

                // recoloring needed for rotation
                sibling->parent->color = COLOR_RED;
                sibling->color = COLOR_BLACK;

                // rotate right for left sibling
                if (ParentToMePtr(sibling) == sibling->parent->left) {
                    RotateRight(sibling);
                } else if (ParentToMePtr(sibling) == sibling->parent->right) {
                    // rotate left for right sibling
                    RotateLeft(sibling);
                }
                // try fixing double-blackness again after
                // giving replacement node a black sibling
                fix_double_black(replacement_node);
            }
        }
    }

    /**
     * @brief Checks if a node has a red child
     * @param n the node to check
     * @returns true if node has a red child, false otherwise
     */
    bool has_red_child(RBTNode* n) {
        RBTNode* n_left = n->left;
        RBTNode* n_right = n->right;

        // at least one red child
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
    void CheckSiblingConditions(RBTNode* replacement, RBTNode* sibling) {
        RBTNode* s_left = sibling->left;
        RBTNode* s_right = sibling->right;

        // check if sibling is the left child of its parent
        if (ParentToMePtr(sibling) == sibling->parent->left) {
            // left left: with left or 2 red kids
            if (s_left != nullptr && s_left->color == COLOR_RED) {
                // rotate right once and recolor to fix double-blackness
                RotateRight(sibling);
                ShiftColorsLeft(sibling);
            } else {
                // left right: with 1 red kid on right (only other case)

                // simpler left left case is made from rotating left
                RotateLeft(s_right);
                sibling = s_right;
                ColorSwap(sibling, sibling->left);

                // rotate right and recolor to fix new left left case
                RotateRight(sibling);
                ShiftColorsLeft(sibling);
            }
        } else if (ParentToMePtr(sibling) == sibling->parent->right) {
            // sibling is a right child of its parent

            // right right: with right or 2 red kids
            if (s_right != nullptr && s_right->color == COLOR_RED) {
                // rotate left once and recolor
                RotateLeft(sibling);
                ShiftColorsRight(sibling);
            } else {
                // right left: with 1 red kid on left (only other case)

                // rotate right on child, making a right right rotate case
                RotateRight(s_left);
                sibling = s_left;
                ColorSwap(sibling, sibling->right);

                // rotate left and recolor to fix new right right case
                RotateLeft(sibling);
                ShiftColorsRight(sibling);
            }
        }
        // replacement node's blackness level goes down to black again
        replacement->color--;
    }

    /**
     * @brief Shifts colors of a node and its children to the right
     * @param sibling the node where color shift occurs
     */
    void ShiftColorsRight(RBTNode* sibling) {
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
    void ShiftColorsLeft(RBTNode* sibling) {
        sibling->left->color = sibling->color;
        sibling->color = sibling->right->color;
        sibling->right->color = COLOR_BLACK;
    }

    /**
     * @brief Gives the pointer from a node to its only child
     * @note
     * Assuming node 'n' has only one valid child,
     * this function checks if it's a left or right child and
     * returns the pointer to it from parent node 'n'
     * (ex. returns 'n->left' or 'n->right')
     * @param n the node to get the child pointer for
     * @return RBTNode*& the node's pointer to its only child
     */
    RBTNode*& MeToOnlyChildPtr(RBTNode* n) {
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
            "MeToOnlyChildPtr(): Node passed "
            "doesn't have exactly one child.");
    }

    /**
     * @brief Gives the pointer from a node's parent to itself
     * @param n the node pointed to by its parent
     * @return RBTNode*& the parent's pointer to the node
     */
    RBTNode*& ParentToMePtr(RBTNode* n) {
        RBTNode* p = n->parent;
        if (p != nullptr) {
            if (p->left == n) {
                return p->left;
            } else if (p->right == n) {
                return p->right;
            }
        }
        throw invalid_argument(
            "ParentToMePtr(): Node passed is root"
            " or has invalid parent.");
    }

    /**
     * @brief Re-balances tree after a new node is inserted
     * @note
     * Tree nodes may be rotated or recolored to
     * maintain necessary conditions for red black tree.
     * @param node checks tree starting from this node (assumed
     * to be the node just inserted into tree) up to the root
     */
    void CheckTreeConditions(RBTNode* node) {
        // to make sure program doesn't skip over root to its
        // parent's nullptr (when skipping over to grandparent)
        if (node == root || node == nullptr) {
            if (node == root) {
                root->color = COLOR_BLACK;
            }
        } else if (node->parent->color == COLOR_RED) {
            // 1) if inserted node's parent = red (indicates
            // 3rd node was inserted in tree), check parent sibling

            RBTNode* parent_sibling = this->GetSibling(node->parent);

            // a) if parent sibling = black/null, rotate and recolor
            if (parent_sibling == nullptr ||
                parent_sibling->color == COLOR_BLACK) {
                ConditionalRotate(node);
            } else if (parent_sibling->color == COLOR_RED) {
                // b) if parent sibling = red, Recolor by
                // "pushing blackness down from grandparent"

                // parent of inserted node
                RBTNode* gp = node->parent->parent;

                // recolor grandparent red
                gp->color = COLOR_RED;

                // recolor grandparent children black
                gp->left->color = COLOR_BLACK;
                gp->right->color = COLOR_BLACK;

                // recursively check tree conditions after recoloring
                CheckTreeConditions(gp);
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
    void RotateLeft(RBTNode* node) {
        RBTNode* great_grandparent = node->parent->parent;
        RBTNode* grandparent = node->parent;

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

        RBTNode* parent_left = node->left;

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
    void RotateRight(RBTNode* node) {
        RBTNode* great_grandparent = node->parent->parent;
        RBTNode* grandparent = node->parent;

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

        RBTNode* parent_right = node->right;

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
     * @note
     * Rotation Conditions
     * 1) left left: Rotate right, Recolor
     * 2) left right: Rotate left then right, Recolor
     * 3) right left: Rotate right then left, Recolor
     * 4) right right: Rotate left, Recolor
     * @param node the tree node where rotation occurs
     */
    void ConditionalRotate(RBTNode* node) {
        RBTNode* parent_left = node->parent->left;
        RBTNode* parent_right = node->parent->right;
        RBTNode* grandparent_left = node->parent->parent->left;
        RBTNode* grandparent_right = node->parent->parent->right;

        // ... left
        if (parent_left == node) {
            // left left
            if (grandparent_left == node->parent) {
                // rotate right on parent
                RotateRight(node->parent);
                ColorSwap(node->parent, node->parent->right);
            }
            // right left
            if (grandparent_right == node->parent) {
                RotateRight(node);
                RotateLeft(node);
                ColorSwap(node, node->left);
            }
        }
        // ... right
        if (parent_right == node) {
            // right right
            if (grandparent_right == node->parent) {
                RotateLeft(node->parent);
                ColorSwap(node->parent, node->parent->left);
            }
            // left right
            if (grandparent_left == node->parent) {
                RotateLeft(node);
                RotateRight(node);
                ColorSwap(node, node->right);
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
    void ColorSwap(RBTNode* parent, RBTNode* grandparent) {
        uint16_t gp_color = grandparent->color;
        grandparent->color = parent->color;
        parent->color = gp_color;
    }

    /**
     * @brief Gives a node's in-order successor (IOS)
     * @note
     * This function is used in Remove().
     * @param node the node to get the IOS of
     * @return RBTNode* the IOS node
     */
    RBTNode* InOrderSuccessor(RBTNode* node) {
        // begin traversal at the given node
        RBTNode* trav = node;

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
     * @return true if the tree contains a node with this value, false otherwise
     */
    bool Contains(int value) {
        if (root != nullptr) {

            RBTNode* trav = root;

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
     * @brief Finds a node in the tree with a specified value.
     * @note
     * This function is the same as Contains() 
     * except it returns the node found or throws
     * an exception.
     * @param value the value of the node to search for
     * @return RBTNode* the node with this value
     */
    RBTNode* Find(int value) {
        if (root != nullptr) {
            RBTNode* trav = root;
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
    int GetMin() {
        // minimum value node will be at left end of the tree
        RBTNode* trav = root;
        while (trav->left != nullptr) {
            trav = trav->left;
        }
        return trav->val;
    }

    /**
     * @brief Gives the maximum node value in tree
     * @return int the highest value in the tree
     */
    int GetMax() {
        // rightmost node in tree
        RBTNode* trav = root;
        while (trav->right != nullptr) {
            trav = trav->right;
        }
        return trav->val;
    }

    /**
     * @brief Gives the sibling of a node if one exists
     * @param node the node to get the sibling of
     * @return RBTNode*& the sibling of the passed node
     */
    RBTNode*& GetSibling(RBTNode* node) {
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
    uint64_t numItems;
    RBTNode* root;
    vector<int> nodes_order_added;

    /**
     * @brief Creates an infix string of tree
     * @param node the top node where the string begins
     * recursively generating down the tree
     * @return string representing tree in infix notation
     */
    string ToInfixString(struct RBTNode* node) const {
        ostringstream nodeOSS;

        if (node != nullptr) {
            // print left (recursion)
            nodeOSS << ToInfixString(node->left);

            // print node's color and value
            nodeOSS << " ";
            if (node->color == COLOR_BLACK) {
                nodeOSS << 'B';
            } else {
                nodeOSS << 'R';
            }
            nodeOSS << node->val << " ";

            // print right (recursion)
            nodeOSS << ToInfixString(node->right);
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
    string ToPrefixString(struct RBTNode* node) const {
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
            nodeOSS << ToPrefixString(node->left);
            nodeOSS << ToPrefixString(node->right);
        }
        return nodeOSS.str();
    }

    /**
     * @brief Creates a postfix string of tree
     * @param node the top node where string
     * begins recursively generating down the tree
     * @return string representing tree in postfix notation
     */
    string ToPostfixString(struct RBTNode* node) const {
        ostringstream nodeOSS;
        if (node != nullptr) {
            // print left then right (recursively)
            nodeOSS << ToPostfixString(node->left);
            nodeOSS << ToPostfixString(node->right);

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
 * @returns void
 */
void TestSimpleConstructor() {
    cout << "Testing Simple Constructor... " << endl;
    RedBlackTree rbt = RedBlackTree();
    // cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
    assert(rbt.ToInfixString() == "");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief simple insert of a value into tree
 * @returns void
 */
void TestInsertFirstNode() {
    cout << "Testing Insert One Node..." << endl;
    RedBlackTree rbt = RedBlackTree();
    rbt.Insert(30);
    // cout << "rbt: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == " B30 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting two values into tree
 * @returns void
 */
void TestInsertSecondNode() {
    cout << "Testing Insert Second Node..." << endl;
    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(30);  // leak here
    rbt->Insert(15);
    // cout << "rbt: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() == " B30  R15 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(45);
    // cout << "rbt: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() == " B30  R45 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting three nodes into tree
 * (and making rotations occur)
 * @returns void
 */
void TestInsertThirdNode() {
    cout << "Testing Insert Third Node..." << endl;
    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(10);  // Left Left

    // ROTATE RIGHT ONCE
    assert(rbt->ToPrefixString() == " B15  R10  R30 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(25);  // Left right

    // ROTATE ONCE RIGHT ON PARENT THEN ONCE LEFT ON GRANDPARENT
    assert(rbt->ToPrefixString() == " B25  R15  R30 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(45);  // Easy case

    // NODES ON EITHER SIDE AND PARENT IS BLACK, SO NO ROTATION OR RECOLOR
    assert(rbt->ToPrefixString() == " B30  R15  R45 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(75);
    rbt->Insert(215);
    rbt->Insert(130);  // Right left

    assert(rbt->ToPrefixString() == " B130  R75  R215 ");
    delete rbt;

    rbt = new RedBlackTree();
    rbt->Insert(648);
    rbt->Insert(735);
    rbt->Insert(9442);  // Right right

    assert(rbt->ToPrefixString() == " B735  R648  R9442 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting four values into tree
 * @returns void
 */
void TestInsertFourthNode() {
    cout << "Testing Insert Fourth Node..." << endl;

    RedBlackTree rbt = RedBlackTree();

    rbt.Insert(13);
    rbt.Insert(7);
    rbt.Insert(3);
    rbt.Insert(9);

    assert(rbt.ToPrefixString() == " B7  B3  B13  R9 ");

    RedBlackTree rbt2 = RedBlackTree();

    rbt2.Insert(34);
    rbt2.Insert(76);
    rbt2.Insert(21984);
    rbt2.Insert(2);

    assert(rbt2.ToPrefixString() == " B76  B34  R2  B21984 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief test inserting five nodes into tree
 * @returns void
 */
void TestInsertFifthNode() {
    cout << "Testing Insert Fifth Node..." << endl;
    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(45);
    rbt->Insert(10);
    rbt->Insert(25);

    assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
    delete rbt;

    RedBlackTree rbt2 = RedBlackTree();
    rbt2.Insert(783);
    rbt2.Insert(91);
    rbt2.Insert(31);
    rbt2.Insert(11);
    rbt2.Insert(-87);

    assert(rbt2.ToPrefixString() == " B91  B11  R-87  R31  B783 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if string functions
 * return correct values
 * @returns void
 */
void TestToStrings() {
    cout << "Testing ToString Methods..." << endl;

    RedBlackTree rbt = RedBlackTree();
    rbt.Insert(12);
    rbt.Insert(11);
    rbt.Insert(15);
    rbt.Insert(5);
    rbt.Insert(13);
    rbt.Insert(7);

    assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
    assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
    assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing with inserts into tree
 * using different values
 * @returns void
 */
void TestInsertRandomTests() {
    cout << "Testing Random Insert Stuff..." << endl;
    cout << "\t This test passes if it doesn't crash and valgrind"
            " reports no issues"
         << endl;
    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(15);
    rbt->Insert(13);
    rbt->Insert(20);
    rbt->Insert(12);
    cout << endl;

    delete rbt;

    rbt = new RedBlackTree();

    rbt->Insert(12);
    rbt->Insert(11);
    rbt->Insert(15);
    rbt->Insert(5);
    rbt->Insert(13);
    rbt->Insert(7);
    delete rbt;

    rbt = new RedBlackTree();

    rbt->Insert(12);
    rbt->Insert(10);
    rbt->Insert(8);
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing copy constructor by
 * copying a tree
 * @returns void
 */
void TestCopyConstructor() {
    cout << "Testing Copy Constructor..." << endl;

    RedBlackTree rbt1 = RedBlackTree();
    rbt1.Insert(11);
    rbt1.Insert(23);
    rbt1.Insert(9);
    rbt1.Insert(52);
    rbt1.Insert(31);
    rbt1.Insert(4);

    assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

    RedBlackTree rbt2 = RedBlackTree(rbt1);

    assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

    rbt1.Insert(200);
    assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if Contains() function correctly
 * determines if a value is in the tree
 * @returns void
 */
void TestContains() {
    cout << "Testing Contains..." << endl;
    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(40);
    rbt->Insert(22);
    rbt->Insert(15);
    rbt->Insert(31);
    rbt->Insert(55);
    rbt->Insert(12);
    rbt->Insert(17);
    rbt->Insert(29);
    rbt->Insert(34);

    assert(rbt->Contains(34));
    delete rbt;

    RedBlackTree rbt2 = RedBlackTree();
    rbt2.Insert(1);
    rbt2.Insert(27);
    rbt2.Insert(99);
    rbt2.Insert(19);

    assert(rbt2.Contains(1) && rbt2.Contains(99));

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing GetMin(), GetMax() functions return
 * correct outputs
 * @returns void
 */
void TestGetMinimumMaximum() {
    cout << "Testing Get Minimum and Get Maximum..." << endl;

    RedBlackTree rbt = RedBlackTree();

    rbt.Insert(34);
    rbt.Insert(76);
    rbt.Insert(21984);
    rbt.Insert(2);

    assert(rbt.GetMax() == 21984 && rbt.GetMin() == 2);

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of copy constructor
 * @returns void
 */
void TestCopyConstructor2() {
    cout << "Testing Copy Constructor..." << endl;

    RedBlackTree rbt1 = RedBlackTree();
    rbt1.Insert(11);
    rbt1.Insert(23);
    rbt1.Insert(9);
    rbt1.Insert(52);
    rbt1.Insert(31);
    rbt1.Insert(4);

    assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

    RedBlackTree rbt2 = RedBlackTree(rbt1);

    assert(rbt1.Size() == rbt2.Size());
    assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

    rbt1.Insert(200);
    assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

    RedBlackTree rbt3 = RedBlackTree();
    cout << rbt3.ToPrefixString() << endl;
    rbt3.Insert(12);
    rbt3.Insert(10);
    rbt3.Insert(0);
    rbt3.Insert(11);
    rbt3.Insert(3);
    rbt3.Insert(9);
    rbt3.Insert(2);
    rbt3.Insert(7);
    rbt3.Insert(1);
    rbt3.Insert(4);
    rbt3.Insert(6);
    rbt3.Insert(8);
    rbt3.Insert(37);
    rbt3.Insert(5);
    rbt3.Insert(72);
    rbt3.Insert(55);
    rbt3.Insert(90);
    rbt3.Insert(92);
    rbt3.Insert(20);
    rbt3.Insert(13);

    // (good here for whole tree) should have B7
    // root, B3 root left, R12 root right here
    rbt3.Insert(57);

    rbt3.Insert(30);
    rbt3.Insert(64);

    // **where left rotate on root occurs
    // (root = B12, root left = R7, root right = R55)
    rbt3.Insert(69);

    rbt3.Insert(50);
    rbt3.Insert(67);
    rbt3.Insert(99);
    rbt3.Insert(89);
    rbt3.Insert(33);

    assert(
        rbt3.ToPrefixString() ==
        " B12  R7  B3  B1  R0  R2  B5  R4  R6"
        "  B10  B9  R8  B11  R55  B20  B13  R37  B30  R33  B50  B69  R64  B57"
        "  B67  R90  B72  R89  B92  R99 ");

    RedBlackTree rbt4 = RedBlackTree(rbt3);

    string s3 = rbt3.ToPrefixString();
    // cout << "s3: " << s3 << endl;
    string s4 = rbt4.ToPrefixString();
    // cout << "s4: " << s4 << endl;
    assert(rbt3.Size() == rbt4.Size());
    assert(s3 == s4);

    rbt3.Insert(200);
    assert(rbt3.ToPrefixString() != rbt4.ToPrefixString());

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if tree properly
 * balances out when inserting values
 * @returns void
 */
void TestInsertWithRecursiveFixUp() {
    cout << "Testing Recursive FixUp..." << endl;

    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(400);
    rbt->Insert(800);
    rbt->Insert(200);
    rbt->Insert(600);
    rbt->Insert(150);
    rbt->Insert(900);
    rbt->Insert(300);
    rbt->Insert(100);  // visualization and prefix looks good up to here
    rbt->Insert(175);  // also looks good here
    rbt->Insert(160);  // does some weird stuff!

    assert(rbt->ToPrefixString() ==
           " B200  R150  B100  B175  "
           "R160  R400  B300  B800  R600  R900 ");

    rbt->Insert(185);
    rbt->Insert(180);  // does a recursive fix-up

    assert(rbt->ToPrefixString() ==
           " B200  B150  B100  R175  B160  "
           "B185  R180  B400  B300  B800  R600  R900 ");
    delete rbt;

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief helper for the test functions
 * in printing/evaluating their outputs
 *
 * @param desc brief description of this test
 * @param rbt red black tree used for this test
 * @param exp_ans correct output for this test (to compare
 * with actual output)
 */
void PrintTestLine(string desc, const RedBlackTree* rbt, string exp_ans) {
    cout << desc << ": " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() == exp_ans);
}

/**
 * @brief testing removing values from tree
 * (removing a root node with one child)
 * @returns void
 */
void RemoveTest1() {
    cout << "Testing removing root (with one child)..." << endl;

    RedBlackTree rbt = RedBlackTree();
    rbt.Insert(10);
    rbt.Insert(459);

    cout << "Size: " << rbt.Size() << endl;
    assert(rbt.Size() == 2);

    cout << "rbt: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == " B10  R459 ");

    // remove root with one right child
    rbt.Remove(10);

    cout << "rbt: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == " B459 ");

    // remove root with no children (empties tree)
    rbt.Remove(459);

    cout << "rbt: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == "");
    assert(rbt.Size() == 0);

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of removing values
 * from tree (removing a leaf node)
 * @returns void
 */
void RemoveTest2() {
    cout << "Testing removing leaf..." << endl;

    RedBlackTree rbt = RedBlackTree();
    rbt.Insert(10);
    rbt.Insert(459);

    cout << "rbt: " << rbt.ToPrefixString() << endl;

    // Removing leaf
    rbt.Remove(459);

    cout << "rbt: " << rbt.ToPrefixString() << endl;

    // Removing last node/root (empties tree again)
    rbt.Remove(10);

    cout << "rbt: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == "");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of removing values
 * from tree (removing node with two children)
 * @returns void
 */
void RemoveTest3() {
    cout << "Testing removing node with two children..." << endl;

    RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(14);
    rbt->Insert(10);
    rbt->Insert(459);  // B14 R10 R459 -- node 14 with two children 10 and 459

    PrintTestLine("tree", rbt, " B14  R10  R459 ");

    // Remove 14 (has two children)
    rbt->Remove(14);
    PrintTestLine("removing 14", rbt, " B459  R10 ");

    rbt->Remove(459);
    PrintTestLine("removing 459", rbt, " B10 ");

    rbt->Remove(10);
    PrintTestLine("removing 10", rbt, "");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief additional testing of removing values
 * from tree (removing from a larger tree)
 * @returns void
 */
void RemoveTest4() {
    cout << "Removing from larger tree "
            "(recursive call with IOS or IOP test)..."
         << endl;

    RedBlackTree* rbt = new RedBlackTree();

    rbt->Insert(94);
    rbt->Insert(18);
    rbt->Insert(3);
    rbt->Insert(22);
    rbt->Insert(0);
    rbt->Insert(537);
    rbt->Insert(308);
    rbt->Insert(23);
    rbt->Insert(24);
    rbt->Insert(21);
    rbt->Insert(25);

    PrintTestLine("tree", rbt,
                  " B23  R18  B3  R0  B22  R21  R94"
                  "  B24  R25  B537  R308 ");

    rbt->Remove(23);

    PrintTestLine("removing 23", rbt,
                  " B24  R18  B3  R0  B22  R21"
                  "  R94  B25  B537  R308 ");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing if tree properly
 * rotates after inserting certain values
 * @returns void
 */
void RemoveTestRotateCase() {
    cout << "Testing removing that requires double-black fix..." << endl;

    RedBlackTree* rbt = new RedBlackTree();

    rbt->Insert(9);
    rbt->Insert(11);
    rbt->Insert(5);
    rbt->Insert(14);
    rbt->Insert(4);
    rbt->Insert(6);
    rbt->Insert(7);

    PrintTestLine("tree", rbt, " B9  R5  B4  B6  R7  B11  R14 ");

    // RIGHT RIGHT CASE -- rotate left on black sibling
    rbt->Remove(4);

    PrintTestLine("right right remove", rbt, " B9  R6  B5  B7  B11  R14 ");

    RedBlackTree rbt2 = RedBlackTree();

    rbt2.Insert(9);
    rbt2.Insert(11);
    rbt2.Insert(5);
    rbt2.Insert(14);
    rbt2.Insert(4);
    rbt2.Insert(7);
    rbt2.Insert(6);

    cout << "tree2: " << rbt2.ToPrefixString() << endl;
    assert(rbt2.ToPrefixString() == " B9  R5  B4  B7  R6  B11  R14 ");

    // RIGHT LEFT CASE (black sibling 7 is right child with one left red child)
    rbt2.Remove(4);

    cout << "right left remove: " << rbt2.ToPrefixString() << endl;
    assert(rbt2.ToPrefixString() == " B9  R6  B5  B7  B11  R14 ");

    rbt2.Insert(4);  // makes left left case when removing 7
    assert(rbt2.ToPrefixString() == " B9  R6  B5  R4  B7  B11  R14 ");

    // LEFT LEFT CASE (black sibling 5 is left child with one left red child)
    rbt2.Remove(7);
    assert(rbt2.ToPrefixString() == " B9  R5  B4  B6  B11  R14 ");

    // deconstruct red black tree and construct a new, empty tree again from
    // same variable
    delete rbt;
    rbt = new RedBlackTree();

    // inserting nodes into tree from an array
    int fill_tree_vec[12] = {9, 11, 5, 14, 4, 6, 7, 3, 2, 17, 1, 8};
    for (int val : fill_tree_vec) {
        rbt->Insert(val);
    }
    cout << "tree3: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() ==
           " B5  R3  B2  R1  B4  R9  B7"
           "  R6  R8  B14  R11  R17 ");

    rbt->Remove(1);  // simple remove on red leaf
    assert(rbt->ToPrefixString() ==
           " B5  R3  B2  B4  R9  B7  R6"
           "  R8  B14  R11  R17 ");

    rbt->Insert(0);
    assert(rbt->ToPrefixString() ==
           " B5  R3  B2  R0  B4  R9  B7"
           "  R6  R8  B14  R11  R17 ");

    rbt->Insert(1);
    assert(rbt->ToPrefixString() ==
           " B5  R3  B1  R0  R2  B4  R9"
           "  B7  R6  R8  B14  R11  R17 ");

    rbt->Remove(0);  // another simple red leaf remove
    assert(rbt->ToPrefixString() ==
           " B5  R3  B1  R2  B4  R9  B7"
           "  R6  R8  B14  R11  R17 ");

    // LEFT RIGHT CASE (black sibling 1 is a left child with one right
    // red child)
    rbt->Remove(4);
    cout << "left right remove: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() ==
           " B5  R2  B1  B3  R9  B7  R6"
           "  R8  B14  R11  R17 ");

    // removing 3 (recursive fix double black case)
    rbt->Remove(3);
    PrintTestLine("recursive double-black fix (removing 3)", rbt,
                  " B5  B2  R1  R9  B7  R6  R8  B14  R11  R17 ");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing removing a value with a "red sibling"
 * from tree
 * @returns void
 */
void RemoveTestRedSiblingCase() {
    cout << "Testing remove that requires double-black fix with red "
            "sibling case..."
         << endl;

    RedBlackTree rbt = RedBlackTree();

    int fill_tree_vec[6] = {11, 9, 7, 5, 8, 6};
    for (int val : fill_tree_vec) {
        rbt.Insert(val);
    }
    cout << "tree: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == " B9  R7  B5  R6  B8  B11 ");

    rbt.Remove(11);  // 11 is black leaf with red sibling 7
    cout << "removing 11: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == " B7  B5  R6  B9  R8 ");

    cout << "PASSED!" << endl << endl;
}

/**
 * @brief testing memory management as values are
 * removed from tree
 * @returns void
 */
void LargeRandomRemoveMemoryTest() {
    cout << "Giant Remove Test..." << endl;

    RedBlackTree* giant_rbt = new RedBlackTree();

    vector<int> random_numbers;  // to store inserted numbers
    unsigned int seed = time(NULL);

    while (giant_rbt->Size() != 711) {
        int random_num = rand_r(&seed);
        if (!giant_rbt->Contains(random_num)) {
            random_numbers.push_back(random_num);
            giant_rbt->Insert(random_num);
        }
    }
    // getting numbers to remove, starting from end of vector
    size_t idx = random_numbers.size() - 1;

    // then removing the numbers until tree is empty
    // (checking for memory issues/exceptions)
    while (giant_rbt->Size() != 0) {
        giant_rbt->Remove(random_numbers[idx--]);
    }

    delete giant_rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief more testing of removing certain nodes from
 * a tree
 * @returns void
 */
void LargerComprehensiveRemoveTest() {
    cout << "Testing many removes from larger tree..." << endl;

    RedBlackTree* rbt = new RedBlackTree();

    int fill_tree_vec[19] = {40, 97, 12, 43,   33,   87,   99,  439, 8762, 3,
                             7,  1,  2,  9999, 8888, 2345, 111, 687, 0};

    for (int val : fill_tree_vec) {
        rbt->Insert(val);
    }

    cout << "tree: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() ==
           " B87  B12  R3  B1  R0  R2  B7  R40  B33"
           "  B43  B439  R99  B97  B111  R8762  B2345  R687  B9999  R8888 ");

    rbt->Remove(87);  // removing root
    cout << "removing 87: " << rbt->ToPrefixString() << endl;
    assert(rbt->ToPrefixString() ==
           " B97  B12  R3  B1  R0  R2  B7  R40  B33"
           "  B43  B439  B99  R111  R8762  B2345  R687  B9999  R8888 ");

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

/**
 * @brief main function where all test functions are
 * called
 * @returns void
 */
int main() {
    TestSimpleConstructor();

    TestInsertFirstNode();

    TestInsertSecondNode();
    TestInsertThirdNode();
    TestInsertFourthNode();
    TestInsertFifthNode();

    TestToStrings();
    TestInsertRandomTests();
    TestCopyConstructor();

    TestContains();
    TestGetMinimumMaximum();

    TestCopyConstructor2();
    TestInsertWithRecursiveFixUp();

    RemoveTest1();
    RemoveTest2();
    RemoveTest3();
    RemoveTest4();
    RemoveTestRotateCase();
    RemoveTestRedSiblingCase();
    LargeRandomRemoveMemoryTest();
    LargerComprehensiveRemoveTest();

    cout << "ALL TESTS PASSED!!" << endl;
    return 0;
}
