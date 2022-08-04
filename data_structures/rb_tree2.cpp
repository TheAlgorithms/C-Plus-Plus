#include "rbtree.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <ostream>

using namespace std;

// Helper for deconstructor - delete nodes in post-order
void RedBlackTree::PostDelete(RBTNode* node) {
    // delete left then right (recursively)
    if (node != nullptr) {
        PostDelete(node->left);
        PostDelete(node->right);
    }
    // delete parent
    delete node;
}

/**
 * @brief Constructs a new copy of the Red Black Tree passed
 * to this function.
 * 
 * @param rbt the Red Black Tree to be copied
 */
RedBlackTree::RedBlackTree(const RedBlackTree& rbt) {
    // initialize tree first
    this->root = nullptr;
    this->numItems = 0;

    // insert nodes from passed tree in the same order they were inserted into the original tree
    for (int n : rbt.nodes_order_added) {
        this->Insert(n);
    }
}

/**
 * @brief Inserts new node into tree with the
 * value passed.
 * 
 * @param value value of the new node
 */
void RedBlackTree::Insert(int value) {
    // check for duplicate keys
    if (this->Contains(value)) {
        throw invalid_argument("Insert(): Node is already in tree, duplicate nodes not allowed.");
    }
    RBTNode *node_to_insert = new RBTNode();
    node_to_insert->val = value;
    nodes_order_added.push_back(value);

    // set node as the root if tree is empty
    if (root == nullptr) {
        root = node_to_insert;
        root->color = COLOR_BLACK;
    } else {
        RBTNode *curr_node = root;
        RBTNode *curr_parent = nullptr;

        // traverse down tree until a place to insert node is found
        while (curr_node != nullptr) {
            curr_parent = curr_node;

            // go left if value < current node
            if (value < curr_node->val) {
                curr_node = curr_node->left;
            }
            // go right if value > current node
            else if (value > curr_node->val) {
                curr_node = curr_node->right;
            }
        }
        // set parent and child pointers for node
        node_to_insert->parent = curr_parent;
        if (value < node_to_insert->parent->val) {
            node_to_insert->parent->left = node_to_insert;
        }
        else if (value > node_to_insert->parent->val) {
            node_to_insert->parent->right = node_to_insert;
        }
        // check and fix tree if needed after insertion to maintain RBT conditions
        CheckTreeConditions(node_to_insert);
    }
    numItems++;
}

/**
 * @brief Removes node from tree and checks/fixes tree to maintain RBT
 * conditions.
 * 
 * @param data value of the node to remove
 */
void RedBlackTree::Remove(int data) {
    RBTNode* node_to_delete = Find(data);
    // this variable represents the node that will replace the deleted node
    RBTNode* replacement_node = node_to_delete;

    // node to delete has two children -- update node with its IOS value and remove IOS node
    if (node_to_delete->left != nullptr && node_to_delete->right != nullptr) {
        int ios_val = InOrderSuccessor(node_to_delete)->val;
        Remove(ios_val);
        node_to_delete->val = ios_val;
    }
    else {
        // node to delete has no children -- disconnect node from its parent
        if (node_to_delete->left == nullptr && node_to_delete->right == nullptr) {
            // removing a root with no children
            if (root == node_to_delete) {
                // root replaced with a null pointer to empty tree
                root = nullptr;
                replacement_node = root;
            }
            else {
                // node's location is still needed for fixing tree, so it's only marked as null for now
                node_to_delete->treatAsNull = true;
            }
        }
        // node to delete has one child -- node's child moves up to replace deleted node
        else {
            // removing a root with one child
            if (root == node_to_delete) {
                // root replaced with root's child and root properties are reset
                root = MeToOnlyChildPtr(node_to_delete);
                root->parent = nullptr;
                root->color = COLOR_BLACK;
                replacement_node = root;
            }
            else {
                // setting parent and child pointers for the node's one child
                ParentToMePtr(node_to_delete) = MeToOnlyChildPtr(node_to_delete);
                MeToOnlyChildPtr(node_to_delete)->parent = node_to_delete->parent;
                replacement_node = MeToOnlyChildPtr(node_to_delete);
            }
        }
        // Now check Rotate/Recolor conditions...
        if (root != nullptr) {
            // a replacement node that's red or at the root just needs to be recolored black
            if (replacement_node == root || replacement_node->color == COLOR_RED) {
                replacement_node->color = COLOR_BLACK;
            }
            // deleted node was black and replacement node is black/null, causes double-blackness problem in tree that needs to be fixed
            else if (node_to_delete->color == COLOR_BLACK && (replacement_node->color == COLOR_BLACK || replacement_node->treatAsNull == true)) {
                replacement_node->color = COLOR_DOUBLE_BLACK;
                fix_double_black(replacement_node);
            }
        }
        // if node to delete is a leaf, disconnect it from its parent after treating it as null to fix any double-blackness issues in tree
        if (node_to_delete->treatAsNull == true) {
            ParentToMePtr(node_to_delete) = nullptr;
        }
        // finally delete node's memory and decrement tree size
        delete node_to_delete;
        numItems--;
    }
}

/**
 * @brief Fixes double-blackness issue caused by trying to remove 
 * a node from tree - to ensure each tree path has an equal number
 * of black nodes (one of the properties of Red Black Trees).
 * 
 * @param replacement_node the double-black node
 */
void RedBlackTree::fix_double_black(RBTNode* replacement_node) {
    // sibling not needed if replacement node is at the tree's root
    if (replacement_node == root) {
        replacement_node->color = COLOR_BLACK;
    }
    else {
        // now using sibling for below conditions
        RBTNode* sibling = GetSibling(replacement_node);

        // sibling is black - check sibling's kids
        if (sibling->color == COLOR_BLACK) {
            // at least one red child
            if (has_red_child(sibling)) {
                // rotate/recolor to fix double-blackness
                CheckSiblingConditions(replacement_node, sibling);
            }
            // no red children
            else {
                // shift blackness level up to parent
                sibling->color = COLOR_RED;
                replacement_node->color = COLOR_BLACK;
                replacement_node->parent->color++;
                // blackness shift may make parent double-black so fix if needed
                if (replacement_node->parent->color == COLOR_DOUBLE_BLACK) {
                    fix_double_black(replacement_node->parent);
                }
            }
        }
        // or replacement's sibling is red, rotate to give replacement a black sibling
        else if (sibling->color == COLOR_RED) {
            // recoloring needed for rotation
            sibling->parent->color = COLOR_RED;
            sibling->color = COLOR_BLACK;

            // rotate right for left sibling
            if (ParentToMePtr(sibling) == sibling->parent->left) {
                RotateRight(sibling);
            }
            // rotate left for right sibling
            else if (ParentToMePtr(sibling) == sibling->parent->right) {
                RotateLeft(sibling);
            }
            // try fixing double-blackness again after giving replacement node a black sibling
            fix_double_black(replacement_node);
        }
    }
}

/**
 * @brief Checks if passed node has a red child.
 * 
 * @param n 
 * @return true 
 * @return false 
 */
bool RedBlackTree::has_red_child(RBTNode* n) {
    RBTNode* n_left = n->left;
    RBTNode* n_right = n->right;

    // at least one red child
    return (n_left != nullptr && n_left->color == COLOR_RED) || (n_right != nullptr && n_right->color == COLOR_RED);
}

/**
 * @brief Rotates/recolors tree based on four sibling cases
 * (left left, left right, right right, right left) to 
 * fix double-blackness issue in tree.
 * 
 * *Note: Assumed that the parameters given will be correct for this function's specific
 * use.
 * 
 * @param replacement the double-black node that replaces the node to delete in tree
 * @param sibling the sibling of double-black replacement node
 */
void RedBlackTree::CheckSiblingConditions(RBTNode* replacement, RBTNode* sibling) {
    // need variables to check sibling's children individually
    RBTNode* s_left = sibling->left;
    RBTNode* s_right = sibling->right;

    // left sibling
    if (ParentToMePtr(sibling) == sibling->parent->left) {
        // left left: with left or 2 red kids
        if (s_left != nullptr && s_left->color == COLOR_RED) {
            // rotate right once and recolor to fix double-blackness
            RotateRight(sibling);
            ShiftColorsLeft(sibling);
        }
        // left right: with 1 red kid on right (only other case)
        else {
            // simpler left left case is made from rotating left
            RotateLeft(s_right);
            sibling = s_right;
            ColorSwap(sibling, sibling->left);

            // rotate right and recolor to fix new left left case
            RotateRight(sibling);
            ShiftColorsLeft(sibling);
        }
    }
    // right sibling
    else if (ParentToMePtr(sibling) == sibling->parent->right) {
        // right right: with right or 2 red kids
        if (s_right != nullptr && s_right->color == COLOR_RED) {
            // rotate left once and recolor
            RotateLeft(sibling);
            ShiftColorsRight(sibling);
        }
        // right left: with 1 red kid on left (only other case)
        else {
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

// shift node colors in this rotated subtree to the right (left to parent to right) - after left rotate
void RedBlackTree::ShiftColorsRight(RBTNode* sibling) {
    sibling->right->color = sibling->color;
    sibling->color = sibling->left->color;
    sibling->left->color = COLOR_BLACK;
}
// shift node colors in rotated subtree to the left (right to parent to left) - after right rotate
void RedBlackTree::ShiftColorsLeft(RBTNode* sibling) {
    sibling->left->color = sibling->color;
    sibling->color = sibling->right->color;
    sibling->right->color = COLOR_BLACK;
}

/**
 * @brief Assuming node 'n' has only one valid child, check if it's a left/right child and
 * return the pointer to it from parent node 'n' (ex. returns 'n->left' or 'n->right')
 * 
 * @param n the node to get the child pointer for
 * @return RBTNode*& the pointer from parent 'n' to its one non-null child
 */
RBTNode*& RedBlackTree::MeToOnlyChildPtr(RBTNode* n) {
    // check node has exactly one non-null child
    if ((n->left == nullptr || n->right == nullptr) && !(n->left == nullptr && n->right == nullptr)) {
        // is left child
        if (n->left != nullptr) {
            return n->left;
        }
        // is right child
        else if (n->right != nullptr) {
            return n->right;
        }
    }
    // reaches here if passed node is invalid for function
    throw invalid_argument("MeToOnlyChildPtr(): Node passed doesn't have exactly one child.");
}

/**
 * @brief Finds whether node 'n' is a left or right child
 * from its parent node.
 * 
 * @param n the node to check whether its left or right
 * @return RBTNode*& the parent pointer to 'n' (will point on either left or right side of parent node to get 'n')
 */
RBTNode*& RedBlackTree::ParentToMePtr(RBTNode* n) {
    RBTNode* p = n->parent;
    if (p != nullptr) {
        if (p->left == n) {
            return p->left;
        }
        else if (p->right == n) {
            return p->right;
        }
    }
    throw invalid_argument("ParentToMePtr(): Node passed is root or has invalid parent.");
}

/**
 * @brief Checks and "fixes" tree after a new node is inserted to maintain
 * Red Black Tree conditions (will Rotate and Recolor nodes as needed)
 * 
 * @param node checks tree starting from this node (assumed to be the node just inserted into tree) up to the root
 */
void RedBlackTree::CheckTreeConditions(RBTNode* node) {
    // to make sure program doesn't skip over root to its parent's nullptr (when skipping over to grandparent)
    if (node == root || node == nullptr) {
        if (node == root) {
            root->color = COLOR_BLACK;
        }
    }
    // 1) if inserted node's parent = red (indicates 3rd node was inserted in tree), check parent sibling
    else if (node->parent->color == COLOR_RED) {
        RBTNode *parent_sibling = this->GetSibling(node->parent);

        // a) if parent sibling = black/null, rotate and recolor
        if (parent_sibling == nullptr || parent_sibling->color == COLOR_BLACK) {
            ConditionalRotate(node);
        }
        // b) if parent sibling = red, Recolor by "pushing blackness down from grandparent"
        else if (parent_sibling->color == COLOR_RED) {
            // parent of inserted node
            RBTNode *gp = node->parent->parent;

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


// Rotate left w/ respect to parent node (in a grandparent, parent, child tree case)
void RedBlackTree::RotateLeft(RBTNode *node) {
    // to connect rotated subtree to rest of tree
    RBTNode *great_grandparent = node->parent->parent;
    RBTNode *grandparent = node->parent;

    // 1: change top node that will connect rotated subtree with rest of tree
    node->parent = great_grandparent; // set new parent of rotated subtree to connect to rest of tree (great grandparent of original node)
    if (great_grandparent != nullptr) {
        // now check if great_grandparent is < or > node to set its child pointer for node
        if (node->val <= great_grandparent->val) {
            great_grandparent->left = node;
        } else if (node->val > great_grandparent->val) {
            great_grandparent->right = node;
        }
    } else {
        // parent will be new root if no great grandparent node in tree
        this->root = node;
    }

    // 2: store parent's original right child pointer, will be moved to grandparent's left after rotation to complete "hop over"
    RBTNode *parent_left = node->left;

    // 3: parent's left now points to grandparent (also setting parent pointer)
    grandparent->parent = node;
    node->left = grandparent;

    // 4: override grandparent's right with its left (or parent's original left) (also check if nullptr in case parent pointer needs to be set)
    if (parent_left != nullptr) {
        parent_left->parent = grandparent;
    }
    grandparent->right = parent_left;
}

// Rotate right w/ respect to parent (in a grandparent, parent, child tree case)
void RedBlackTree::RotateRight(RBTNode *node) {
    // stores *original* locations of memory for these pointers?
    RBTNode *great_grandparent = node->parent->parent;
    RBTNode *grandparent = node->parent;

    // 1: change top node that will connect rotated subtree with rest of tree
    node->parent = great_grandparent; // set new parent of rotated subtree to connect to rest of tree (great grandparent of original node)
    if (great_grandparent != nullptr) {
        // now check if great_grandparent is < or > node to set its child pointer for node
        if (node->val <= great_grandparent->val) {
            great_grandparent->left = node;
        } else if (node->val > great_grandparent->val) {
            great_grandparent->right = node;
        }
    } else {
        // parent will be new root if no great grandparent node in tree
        this->root = node;
    }

    // 2: store parent's original right child pointer, will be moved to grandparent's left after rotation to complete "hop over"
    RBTNode *parent_right = node->right;

    // 3: parent's right now points to grandparent (also setting parent pointer)
    grandparent->parent = node;
    node->right = grandparent;

    // 4: override grandparent's left with its right (or parent's original right) (also check if nullptr in case parent pointer needs to be set)
    if (parent_right != nullptr) {
        parent_right->parent = grandparent;
    }
    grandparent->left = parent_right;
}

/**
 * @brief Rotates tree/subtree based on specified conditions and positions of nodes
 * (red parent, null/black parent sibling)
 * 
 * 1) left left: Rotate right, Recolor
 * 2) left right: Rotate left then right, Recolor
 * 3) right left: Rotate right then left, Recolor
 * 4) right right: Rotate left, Recolor
 * 
 * @param node 
 */
void RedBlackTree::ConditionalRotate(RBTNode* node) {
    // pointer variables for checking tree cases
    RBTNode *parent_left = node->parent->left;
    RBTNode *parent_right = node->parent->right;
    RBTNode *grandparent_left = node->parent->parent->left;
    RBTNode *grandparent_right = node->parent->parent->right;
    
    // ... left
    if (parent_left == node) {
        // left left
        if (grandparent_left == node->parent) {
            // rotate right once on parent
            RotateRight(node->parent);
            ColorSwap(node->parent, node->parent->right);
        }
        // right left
        if (grandparent_right == node->parent) {
            // rotate right then left, then color swap with original child/node and grandparent
            RotateRight(node);
            RotateLeft(node);
            ColorSwap(node, node->left);
        }
    }
    // ... right
    if (parent_right == node) {
        // right right
        if (grandparent_right == node->parent) {
            // rotate left once on parent, color swap with original parent and original grandparent of node
            RotateLeft(node->parent);
            ColorSwap(node->parent, node->parent->left);
        }
        // left right
        if (grandparent_left == node->parent) {
            // rotate left then right, color swap with new parent resulting from left rotate (also original child/node) and original grandparent/new parent of node after left rotate
            RotateLeft(node);
            RotateRight(node);
            ColorSwap(node, node->right);
        }
    }
}

/**
 * @brief Swaps colors of the two nodes passed
 * to this function (assuming nodes will always be original parent and grandparent nodes
 * of a rotated subtree).
 * 
 * @param parent the parent node
 * @param grandparent the grandparent node
 */
void RedBlackTree::ColorSwap(RBTNode* parent, RBTNode* grandparent) {
    unsigned short int gp_color = grandparent->color;
    grandparent->color = parent->color;
    parent->color = gp_color;
}

/**
 * @brief Returns the in-order successor (IOS) of the passed
 * node, used in remove() method.
 * 
 * @param node the node to get the IOS of
 * @return RBTNode* the IOS node
 */
RBTNode* RedBlackTree::InOrderSuccessor(RBTNode* node) {
    // starting from node passed
    RBTNode* trav = node;

    // try going right once
    if (trav->right != nullptr) {
        trav = trav->right;

        // then go left until at leftmost node
        while (trav->left != nullptr) {
            trav = trav->left;
        }
    }
    return trav;
}

/**
 * @brief Checks if a node with the passed integer value is in the Red Black
 * Tree.
 * 
 * @param value the value to check for
 * @return true if the tree contains a node with this value
 * @return false otherwise
 */
bool RedBlackTree::Contains(int value) {
    // tree not empty
    if (root != nullptr) {
        // traversing through tree to find node
        RBTNode *trav = root;
        while (trav != nullptr) {
            // node with passed value found
            if (trav->val == value) {
                return true;
            }
            // binary search: value < tree value, go left
            else if (value < trav->val) {
                trav = trav->left;
            }
            // value > tree value, go right
            else if (value > trav->val) {
                trav = trav->right;
            }
        }
    }
    // node not in tree or tree empty
    return false;
}

/**
 * @brief Traverses down the tree until/if a node with the passed
 * integer value is found. Same as the Contains() method except this
 * one returns the node found or throws an exception if not found. 
 * 
 * @param value the value of the node to search for
 * @return RBTNode* the node with this value
 */
RBTNode* RedBlackTree::Find(int value) {
    // tree not empty
    if (root != nullptr) {
        // traversing through tree to find node
        RBTNode *trav = root;
        while (trav != nullptr) {
            // node with passed value found
            if (trav->val == value) {
                return trav;
            }
            // binary search: value < tree value, go left
            else if (value < trav->val) {
                trav = trav->left;
            }
            // value > tree value, go right
            else if (value > trav->val) {
                trav = trav->right;
            }
        }
    }
    // reaches here if node not in tree
    throw invalid_argument("Node not in tree.");
}

/**
 * @brief Finds the node with the minimum value in tree.
 * 
 * @return int the minimum value in the tree
 */
int RedBlackTree::GetMin() {
    // tree is balanced, so go left from root until at leftmost node in tree
    RBTNode *trav = root;
    while (trav->left != nullptr) {
        trav = trav->left;
    }
    return trav->val;
}

/**
 * @brief Returns mode with the maximum value in tree.
 * 
 * @return int the maximum value in the tree
 */
int RedBlackTree::GetMax() {
    // rightmost node in tree
    RBTNode *trav = root;
    while (trav->right != nullptr) {
        trav = trav->right;
    }
    return trav->val;
}


/**
 * @brief Checks for and returns sibling of passed node.
 * 
 * @param node 
 * @return RBTNode*& 
 */
RBTNode*& RedBlackTree::GetSibling(RBTNode *node) {
    if (node == root) {
        throw invalid_argument("Root has no sibling.");
    }
    // check which parent's child is NOT the passed node
    if (node->parent->left != node) {
        return node->parent->left;
    }
    else if (node->parent->right != node) {
        return node->parent->right;
    }
    else {
        // no sibling
        throw invalid_argument("Invalid node passed.");
    }
}

// ToInfixString (private impl) -- print left, print root, print right
string RedBlackTree::ToInfixString(struct RBTNode* node) const {
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

// ToPrefixString (private impl) -- prints node, then left, then right
string RedBlackTree::ToPrefixString(struct RBTNode* node) const {
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
 * @brief ToPostfixString (private impl) -- prints left, then right, then node
 * 
 * @param node 
 * @return string 
 */
string RedBlackTree::ToPostfixString(struct RBTNode* node) const {
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

