/**
 * @file binary_search_tree_OOP_approach.cpp
 * @brief An implementation of Binary Search Tree class,
 * including various tree-traversals like 
 * In-Order, Pre-Order, Post-Order, BFT  
 * @author [Dharani Akurathi](https://github.com/Dharni0607)
 */

#include<bits/stdc++.h> 
#include<queue>

/**
 *  node structure [value][left*, right*...]
 */
struct node {
    int value;
    std::shared_ptr<node> left;
    std::shared_ptr<node> right;
};

/**
 * implementation of Binary Search Tree class with basic methods
 */

class BinarySearchTree{
    std::shared_ptr<node> root;

public:
    /**
     * Binary Search Tree - constructor method
     */
    BinarySearchTree(){
        root = nullptr;
    }
    BinarySearchTree(BinarySearchTree const&) = delete;
    BinarySearchTree& operator =(BinarySearchTree const&) = delete;
    ~BinarySearchTree(){
    }
    /**
     * The following fuctions inserts a node with given
     * data into binary search tree 
     * @param data is the value of the node that has to be inserted
     */
    void insert(int data){
        std::shared_ptr<node> newnode = std::shared_ptr<node>(new node);
        newnode->value = data;
        newnode->left = nullptr;
        newnode->right = nullptr;
        if(root == nullptr){
            root = newnode;
            return;
        }
        std::shared_ptr<node> current = root;
        while(true){
            if(current->value > data){
                if(current->left == nullptr)
                {
                    current->left = newnode;
                    return;
                }
                else{
                    current = current->left;
                }
            }
            else{
                if(current->right == nullptr)
                {
                    current->right = newnode;
                    return;
                }
                else{
                    current = current->right;
                }
            }
            
        } 
    }

    std::shared_ptr<node> getRoot(){
        return root;
    }
    
    /**
     * Implementation of Breadth First Traversal
     * Traversal starts at the root node and explores all of the 
     * neighbor nodes at the present depth prior to moving on
     * to the nodes at the next depth level.
     */
    void BFT() {
        std::queue<std::shared_ptr<node>> q;
        q.push(root);
        while(!q.empty()){
            std::shared_ptr<node> current = q.front();
            q.pop();
            std::cout << current->value << " ";
            if(current->left){
                q.push(current->left);
            }
            if(current->right){
                q.push(current->right);
            }
        }
    }

    /**
     * Implementation of Pre-order Traversal
     * Every sub-tree is traversed in the following order :
     * root - left - right
     * @param current is the current root node of the sub-tree
     */
    void preOrder(std::shared_ptr<node> const& current){
        if(current)
        {
            std::cout << current->value << " ";
            preOrder(current->left);
            preOrder(current->right);
        }
    }

    /**
     * Implementation of In-order Traversal
     * Every sub-tree is traversed in the following order :
     * left - root - right
     * @param current is the current root node of the sub-tree
     */
    void inOrder(std::shared_ptr<node> const& current){
        if(current)
        {
            inOrder(current->left);
            std::cout << current->value << " ";
            inOrder(current->right);
        }
    }

    /**
     * Implementation of Post-order Traversal
     * Every sub-tree is traversed in the following order :
     * left - right - root
     * @param current is the current root node of the sub-tree
     */
    void postOrder(std::shared_ptr<node> const& current){
        if(current)
        {
            postOrder(current->left);
            postOrder(current->right);
            std::cout << current->value << " ";
        }
    }

    /**
     * The minValueNodeInRightST function returns the node with minimum value,
     * in the current sub-tree
     * @param node is root node of current sub-tree
     */
    std::shared_ptr<node> minValueNodeInRightST(std::shared_ptr<node> n) 
    { 
        std::shared_ptr<node> current = n; 
        while (current && current->left){
            current = current->left; 
        }
        return current; 
    } 
    
    /**
     * The deleteNode function deletes the node having target as
     * its value from the tree, If such node doesn't exsit in the 
     * tree, then nothing will be deleted.
     * @param current is the root node of current sub-tree
     * @param target is the value of node to be deleted
     */
    std::shared_ptr<node> deleteNode(std::shared_ptr<node> current, int target){
        if(current == nullptr){
            return current;
        }
        /* If current value is greater than target, 
            then exsits in left sub-tree */
        else if(current->value > target){
            current->left = deleteNode(current->left, target);
        } 
        /* If current value is less than target, 
            then exsits in right sub-tree */
        else if(current->value < target){
            current->right = deleteNode(current->right, target);
        }
        /* If current value is the target */
        else{
            std::shared_ptr<node> temp = nullptr;
            if(current->left == nullptr){
                temp = current->right;
                current = temp;
            }
            else if(current->right == nullptr){
                temp = current->left;
                current = temp;
            }
            else{
                std::shared_ptr<node> inorder_successor = minValueNodeInRightST(current->right);
                current->value = inorder_successor->value;
                current->right = deleteNode(current->right, inorder_successor->value);
            }
        }
        return current;
    }
    
    /**
     * To remove the node with given target from the tree
     * @param target is the value of node to be deleted
     */
    void remove(int target){
        root = deleteNode(root, target);
    }
};

int main() {
    std::array<int, 10> arr{{34, 45, 12, 7, 15, 190, 2, 1, 100, 5}};
    BinarySearchTree bst;
    for(int num: arr){
        bst.insert(num);
    }
    std::cout << "\nPre-order Traversal:\n";
    bst.preOrder(bst.getRoot());
    std::cout << "\nIn-order Traversal:\n";
    bst.inOrder(bst.getRoot());
    std::cout << "\nPost-order Traversal:\n";
    bst.postOrder(bst.getRoot());
    std::cout << "\nRemoving node\n";
    bst.remove(34);
    bst.remove(7);
    std::cout << "\nBreadth first Traversal\n";
    bst.BFT();
    return 0;
}
