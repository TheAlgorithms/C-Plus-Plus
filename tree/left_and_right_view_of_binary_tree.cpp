#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

class TreeNode {
 public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // Default constructor
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Constructor with value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Builds a binary tree from a given array (1-based index, complete binary tree)
TreeNode* buildTree(const std::vector<int>& arr) {
    if (arr.size() <= 1)
        return nullptr;  // Return if array is empty or has no valid root

    TreeNode* root = new TreeNode(arr[1]);
    std::queue<std::pair<int, TreeNode*>> q;
    q.push({1, root});

    for (int i = 2; !q.empty(); ++i) {
        auto [index, currentNode] = q.front();
        q.pop();

        // Add left child if exists
        if (index * 2 < arr.size()) {
            currentNode->left = new TreeNode(arr[index * 2]);
            q.push({index * 2, currentNode->left});
        }
        // Add right child if exists
        if (index * 2 + 1 < arr.size()) {
            currentNode->right = new TreeNode(arr[index * 2 + 1]);
            q.push({index * 2 + 1, currentNode->right});
        }
    }

    return root;
}

// Displays the left view of the binary tree
void leftView(TreeNode* root) {
    if (!root)
        return;

    std::unordered_map<int, TreeNode*> levelMap;
    std::vector<int> leftViewNodes;
    std::queue<std::pair<int, TreeNode*>> q;
    q.push({0, root});

    while (!q.empty()) {
        auto [level, currentNode] = q.front();
        q.pop();

        // Add node to left view if it's the first node of the level
        if (levelMap.find(level) == levelMap.end()) {
            leftViewNodes.push_back(currentNode->val);
            levelMap[level] = currentNode;
        }

        // Add left and right children to the queue
        if (currentNode->left)
            q.push({level + 1, currentNode->left});
        if (currentNode->right)
            q.push({level + 1, currentNode->right});
    }

    // Print the left view
    for (int val : leftViewNodes) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Displays the right view of the binary tree
void rightView(TreeNode* root) {
    if (!root)
        return;

    std::unordered_map<int, TreeNode*> levelMap;
    std::vector<int> leftViewNodes;
    std::queue<std::pair<int, TreeNode*>> q;
    q.push({0, root});

    while (!q.empty()) {
        auto [level, currentNode] = q.front();
        q.pop();

        // Add node to left view if it's the first node of the level
        if (levelMap.find(level) == levelMap.end()) {
            leftViewNodes.push_back(currentNode->val);
        }
        levelMap[level] = currentNode;

        // Add left and right children to the queue
        if (currentNode->left)
            q.push({level + 1, currentNode->left});
        if (currentNode->right)
            q.push({level + 1, currentNode->right});
    }

    // Print the left view
    for (int val : leftViewNodes) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// In-order traversal of the binary tree
void printTree(TreeNode* root) {
    if (!root)
        return;
    printTree(root->left);
    std::cout << root->val << " ";
    printTree(root->right);
}

int main() {
    std::cout << "Enter tree array (to stop, enter -999): ";
    std::vector<int> arr;
    arr.push_back(0);  // Placeholder for 1-based indexing
    int input;

    // Input array elements
    while (std::cin >> input && input != -999) {
        arr.push_back(input);
    }

    TreeNode* root = buildTree(arr);

    // Uncomment this line to print the tree level-wise
    // levelOrder(root);

    // Display the left view of the tree
    leftView(root);

    return 0;
}
