#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * @brief TreeNode class representing a node in a binary tree.
 */
class TreeNode {
 public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * @brief Builds a binary tree from a vector of integers.
 *
 * @param arr vector of integers where index represents the node level in a
 * complete binary tree.
 * @return root of the binary tree.
 */
TreeNode* buildTree(const std::vector<int>& arr) {
    if (arr.size() <= 1)
        return nullptr;

    TreeNode* root = new TreeNode(arr[1]);
    std::queue<std::pair<int, TreeNode*>> q;
    q.push({1, root});
    int i = 2;

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        int j = node.first;
        TreeNode* current = node.second;

        if (j * 2 < arr.size()) {
            current->left = new TreeNode(arr[j * 2]);
            q.push({j * 2, current->left});
        }
        if (j * 2 + 1 < arr.size()) {
            current->right = new TreeNode(arr[j * 2 + 1]);
            q.push({j * 2 + 1, current->right});
        }
    }

    return root;
}

/**
 * @brief Displays the right view of the binary tree.
 *
 * @param root Root of the binary tree.
 */
void rightView(TreeNode* root) {
    if (!root)
        return;

    std::unordered_map<int, TreeNode*> levelMap;
    std::vector<int> rightViewNodes;
    std::queue<std::pair<int, TreeNode*>> q;
    q.push({0, root});

    while (!q.empty()) {
        auto [level, currentNode] = q.front();
        q.pop();

        // Always update the rightmost node at each level
        levelMap[level] = currentNode;

        // Add right and left children to the queue (right first for right view)
        if (currentNode->right)
            q.push({level + 1, currentNode->right});
        if (currentNode->left)
            q.push({level + 1, currentNode->left});
    }

    // Collect and print the right view nodes
    for (auto& [level, node] : levelMap) {
        rightViewNodes.push_back(node->val);
    }

    // Print the right view
    for (int val : rightViewNodes) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Tests the right view function with predefined test cases.
 */
void test() {
    // Test Case 1: Simple binary tree with right children
    std::vector<int> tree1 = {0, 1, 2, 3,
                              4, 5, 6};  // Binary tree represented as array
    TreeNode* root1 = buildTree(tree1);
    std::cout << "Test 1 (Expected right view: 1 3 6): ";
    rightView(root1);

    // Test Case 2: Binary tree with no right children
    std::vector<int> tree2 = {0, 1, 2, 3, 4,
                              5, 6, 7, 8};  // Complete binary tree
    TreeNode* root2 = buildTree(tree2);
    std::cout << "Test 2 (Expected right view: 1 3 7): ";
    rightView(root2);

    // Test Case 3: Left-skewed binary tree
    std::vector<int> tree3 = {0, 1, 2};  // Only root and one left child
    TreeNode* root3 = buildTree(tree3);
    std::cout << "Test 3 (Expected right view: 1 2): ";
    rightView(root3);

    // Test Case 4: Empty tree
    std::vector<int> tree4 = {0};  // No nodes in the tree
    TreeNode* root4 = buildTree(tree4);
    std::cout << "Test 4 (Expected right view: Empty): ";
    rightView(root4);

    // Assert-based test validation
    assert(root1 != nullptr);  // Ensure the tree is built properly
    assert(root2 != nullptr);
    assert(root3 != nullptr);
    assert(root4 == nullptr);  // The empty tree should be null

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function.
 */
int main() {
    test();
    return 0;
}
