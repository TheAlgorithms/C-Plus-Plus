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
    printTree(root);

    return 0;
}
