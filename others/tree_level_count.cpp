/**
 * @file
 * @brief Finding level count of tree using a queue
 * @details
 * Create a queue storing the root of the tree.
 * Enters while loop that loops until the queue is empty.
 * Then enters for loop that loops current size of queue which
 * holds the nodes in the same level.
 * Checks if current node has left or right child and
 * if child exists, adds the child to the queue.
 * Once for loop is over, it increases level count since the
 * next iteration of the queue will be the next level in the tree.
 * When queue is empty, the tree has been fully traversed and the 
 * level count is displayed.
 * @author [Francisco](https://github.com/FSanchez-UF)
 */

#include <iostream>
#include <string>
#include <queue>
using namespace std;

class TreeNode {
public:
    string Name, ID;
    TreeNode* left, *right;
    TreeNode* root = NULL;
        
    //constructors
    TreeNode() : ID("00000000"), Name("John Smith"), left(nullptr), right(nullptr) {}
    TreeNode(string x, string name) : ID(x), Name(name), left(nullptr), right(nullptr) {}
    TreeNode(string x, string name, TreeNode *left, TreeNode *right) : ID(x), Name(name), left(left), right(right) {}

    //functions accessible from main
    void Insert(string name, string ID); // inserts node in tree
    void printLevelCount(); //prints number of levels in tree

    //helper functions that actually executes command
private:  
    TreeNode* helperInsert(string name, string ID, TreeNode* root);
    void helperLevelCount(TreeNode* root);
};

void TreeNode::Insert(string name, string ID) {
    this->root = helperInsert(name, ID, this->root);
}

TreeNode* TreeNode::helperInsert(string name, string numID, TreeNode* root) {
    //inserts node in tree
    if (root == NULL) {
        cout << "successful" << endl;
        return new TreeNode(numID, name);
    }

    //inserts node data to right if data greater than parent node
    else if (stoi(numID) > stoi(root->ID)) {
        root->right = helperInsert(name, numID, root->right);
    }

    //inserts node data to left if data is less than parent node
    else {
        root->left = helperInsert(name, numID, root->left);
    }
    return root;
}

void TreeNode::printLevelCount() {
    helperLevelCount(this->root);
}

void TreeNode::helperLevelCount(TreeNode* root) {
    int tempSize, level = 0;
    TreeNode* currentNode;
    queue<TreeNode*> traversing;

    //tree doesn't have node, prints 0
    if (root == NULL) {
        cout << level << endl;
        return;
    }

    traversing.push(root);
    
    //iterates through tree using queue to find lowest leaf node
    while (!traversing.empty()) {
        tempSize = traversing.size();
        
        // iterates through current level of tree
        for (int i = 0; i < tempSize; i++) {
            currentNode = traversing.front();
            
            // if node has child, adds child to queue
            if (currentNode->left != NULL)
                traversing.push(currentNode->left);
            
            if (currentNode->right != NULL)
                traversing.push(currentNode->right);

            traversing.pop();
        }
        level++;
    }
    cout << level << endl;
}

int main() {
    TreeNode Tree;

    // adds nodes with data in tree
    Tree.Insert("Chad Nicholson", "65401058");
    Tree.Insert("Merle Selby", "85962566");
    Tree.Insert("Fox Stacy", "39893505");
    Tree.Insert("Sanford Joseph", "47475877");
    Tree.Insert("Patience Jeffery", "53941549");
    Tree.Insert("Sheenagh Graves", "67157203");
    Tree.Insert("Beau Wyndham", "19784866");
    Tree.Insert("Lottie Marsden", "42596112");
    Tree.Insert("Lottie Marsden", "57684687");
    Tree.Insert("Georgie Stamp", "95299448");
    Tree.Insert("Adaline Smith", "20669516");
    Tree.Insert("Arlen Goffe", "44554326");

    // prints the level count of tree
    Tree.printLevelCount();

    return 0;
}