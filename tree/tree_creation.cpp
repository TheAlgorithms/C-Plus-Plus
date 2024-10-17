#include <cassert>  // for assert()
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

// Utility function to collect the in-order traversal in a vector (for testing)
void collectInOrder(TreeNode* root, std::vector<int>& output) {
    if (!root)
        return;
    collectInOrder(root->left, output);
    output.push_back(root->val);
    collectInOrder(root->right, output);
}

// Tests for binary tree building and traversal
void test() {
    // Test Case 1: Simple binary tree
    std::vector<int> tree1 = {0, 1, 2, 3, 4, 5, 6};  // 1-based index array
    TreeNode* root1 = buildTree(tree1);
    std::vector<int> expectedInOrder1 = {4, 2, 5, 1,
                                         6, 3};  // Expected in-order traversal
    std::vector<int> actualInOrder1;
    collectInOrder(root1, actualInOrder1);
    assert(actualInOrder1 ==
           expectedInOrder1);  // Assert in-order traversal matches expected

    // Test Case 2: Tree with only one node
    std::vector<int> tree2 = {0, 1};  // Only root
    TreeNode* root2 = buildTree(tree2);
    std::vector<int> expectedInOrder2 = {1};
    std::vector<int> actualInOrder2;
    collectInOrder(root2, actualInOrder2);
    assert(actualInOrder2 == expectedInOrder2);  // Assert single node

    // Test Case 3: Empty tree (no nodes)
    std::vector<int> tree3 = {0};  // No valid nodes
    TreeNode* root3 = buildTree(tree3);
    std::vector<int> actualInOrder3;
    collectInOrder(root3, actualInOrder3);
    assert(actualInOrder3.empty());  // Assert in-order traversal is empty

    // Test Case 4: Left-skewed tree
    std::vector<int> tree4 = {0, 1, 2};  // Only left child
    TreeNode* root4 = buildTree(tree4);
    std::vector<int> expectedInOrder4 = {
        2, 1};  // In-order should visit left child first
    std::vector<int> actualInOrder4;
    collectInOrder(root4, actualInOrder4);
    assert(actualInOrder4 == expectedInOrder4);

    // Test Case 5: Right-skewed tree
    std::vector<int> tree5 = {0, 1, 0, 2};  // Only right child
    TreeNode* root5 = buildTree(tree5);
    std::vector<int> expectedInOrder5 = {
        1, 2};  // In-order should visit root and then right child
    std::vector<int> actualInOrder5;
    collectInOrder(root5, actualInOrder5);
    assert(actualInOrder5 == expectedInOrder5);

    std::cout << "All tests passed!\n";
}

int main() {
    test();  // Run test cases
    return 0;
}
