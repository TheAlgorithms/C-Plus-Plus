#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

// defining colors
#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2 // for remove()

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct RBTNode {
    // nodes are red by default, null/root/red's child nodes are recolored to black
    unsigned short int color = COLOR_RED;
    // has int value to represent node itself
    int val;

    // has a parent and left/right child nodes
    RBTNode* parent = nullptr;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;

    bool treatAsNull = false;
};

class RedBlackTree {
    // implement these methods in cpp file
    public:
         // Constructor - Initializes new Red Black Tree
        RedBlackTree() { 
            root = nullptr;
            numItems = 0;
        };

        // Deconstructor - calls helper PostDelete to free Red Black Tree memory
        ~RedBlackTree() { PostDelete(root); };

        // Copy constructor - Creates copy of passed Red Black Tree reference
        RedBlackTree(const RedBlackTree& rbt);

        // Removes node while maintaining RBT conditions
        void Remove(int data);

        // Inserts new unique node with value 'n' into tree
        void Insert(int n);

        // Checks if node with value 'n' is in tree
        bool Contains(int n);

        // Min node's value in tree
        int GetMin();

        // Max node's value in tree
        int GetMax();

        // Number of nodes in tree
        int Size() { return numItems; };

        // Tree in infix notation
        string ToInfixString() const { return ToInfixString(root); };

        // Tree in prefix notation
        string ToPrefixString() const { return ToPrefixString(root); };

        // Tree in postfix notation
        string ToPostfixString() const { return ToPostfixString(root); };

    private:
        // ToInfixString (private impl) -- print left, print root, print right
        string ToInfixString(struct RBTNode* node) const;
        // ToPrefixString (private impl) -- prints node, then left, then right
        string ToPrefixString(struct RBTNode* node) const;
        // ToPostfixString (private impl) -- prints left, then right, then node
        string ToPostfixString(struct RBTNode* node) const;

        // counts nodes in tree, initialized to 0
        unsigned long long int numItems;
        // root pointer
        RBTNode *root;

        // ALL ADDIITIONAL METHODS/HELPERS ADDED BELOW...

        // stores node's values in exact order nodes were added to tree (used for copy constructor)
        vector<int> nodes_order_added;

        // similar to postfix string impl, recursively deletes left, then right, then parent
        void PostDelete(RBTNode* node);

        // helpers for rotating/recoloring subtree
        void RotateRight(RBTNode* node);
        void RotateLeft(RBTNode* node);
        void ColorSwap(RBTNode* node, RBTNode* node2);
        // rotates tree based on given Red Black Tree conditions
        void ConditionalRotate(RBTNode* node);

        // rotates and recolors tree as needed after inserting a new node into tree
        void CheckTreeConditions(RBTNode* node);

        // finds node with given value in tree
        RBTNode* Find(int value);
        // gets in-order successor of passed node
        RBTNode* InOrderSuccessor(RBTNode* node);

        // gets sibling of passed node
        RBTNode*& GetSibling(RBTNode* node);

        /**
         * @brief Assuming node 'n' has only one valid child, check if it's a left/right child and
         * return the pointer to it from parent node 'n' (ex. returns 'n->left' or 'n->right')
         * 
         * @param n the node to get the child pointer for
         * @return RBTNode*& the pointer from parent 'n' to its one non-null child
         */
        RBTNode*& MeToOnlyChildPtr(RBTNode* n);

        /**
         * @brief Finds whether node 'n' is a left or right child
         * from its parent node.
         * 
         * @param n the node to check whether its left or right
         * @return RBTNode*& the parent pointer to 'n' (will point on either left or right side of parent node to get 'n')
         */
        RBTNode*& ParentToMePtr(RBTNode* n);

        // helper for fixing double-blackness when removing
        void fix_double_black(RBTNode* n);

        // checking sibling rotate conditions after remove
        void CheckSiblingConditions(RBTNode* node, RBTNode* sibling);

        // color shift following left rotate
        void ShiftColorsRight(RBTNode* node);
        // color shift following right rotate
        void ShiftColorsLeft(RBTNode* node);

        // checks if node has a red child
        bool has_red_child(RBTNode* node);
};

#endif