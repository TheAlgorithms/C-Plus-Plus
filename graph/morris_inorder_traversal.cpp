/*
Morris Traversal is an algorithm to traverse a binary tree without using extra space (like a stack or recursion). It achieves O(1) space complexity by temporarily modifying the tree structure to create links (threads) to predecessors. During traversal, each node's predecessor in its left subtree is linked to the current node, allowing the algorithm to return to the current node after visiting its left child. Once visited, these links are removed, ensuring the original tree structure is restored. This allows for efficient, space-optimized in-order traversal.
*/

#include <vector>
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    // Default constructor
    Node() : data(0), left(nullptr), right(nullptr) {}

    // Constructor to initialize with data
    Node(int x) : data(x), left(nullptr), right(nullptr) {}

    // Constructor to initialize with data, left, and right pointers
    Node(int x, Node *left, Node *right) : data(x), left(left), right(right) {}
};

// Function to perform Morris Traversal
vector<int> morrisTraversal(Node *root)
{
    vector<int> ans;  // Vector to store the in-order traversal result
    Node *cur = root; // Start with the root node
    while (cur != NULL)
    {
        // If there is no left child, visit the current node and move to the right child
        if (cur->left == NULL)
        {
            ans.push_back(cur->data); // Add current node's data to the result
            cur = cur->right;         // Move to the right child
        }
        else
        {
            // Find the rightmost node in the left subtree (in-order predecessor)
            Node *prev = cur->left;
            while (prev->right && prev->right != cur)
            {
                prev = prev->right; // Traverse to the rightmost node
            }

            // If the right pointer of the predecessor is null, create a temporary link to the current node
            if (prev->right == NULL)
            {
                prev->right = cur; // Create a thread (temporary link) to the current node
                cur = cur->left;   // Move to the left child
            }
            // If the right pointer of the predecessor points to the current node, it means we need to break the link
            else
            {
                prev->right = NULL;        // Remove the temporary link
                ans.push_back(cur->data);  // Add current node's data to the result
                cur = cur->right;          // Move to the right child
            }
        }
    }
    return ans; // Return the in-order traversal result
}

int main() {
    // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    // Performing Morris Traversal
    vector<int> ans = morrisTraversal(root);
    
    // Printing the result of in-order traversal
    for(auto it : ans) {
        cout << it << " ";
    }

    return 0;
}
