/**
 * @file
 * @brief Tree Sort Algorithm 
 * More about it: https://en.wikipedia.org/wiki/Tree_sort
 * @details
 * Tree sort algorithm is a stable sorting algorithm that uses the property of how a BST stores data.
 * Tree sort performs an inorder traversal on a BST to get the sorted order of elements.
 * Worst case time-complexity of tree_sort is O(N*log(N)), given that the tree is balanced.
 * To ensure that we use a balanced BST, we are using left-leaning Red-Black BST implementation of BST
 * ensuring that our tree stays balanced all the time.
 * Best case, Average case, the Worst case time complexity for tree_sort: N*log(N)
 * Space complexity: O(n)
 * @author [Puneet Tripathi](https://github.com/PuneetTri)
 */

#include<iostream>  // For standard I/O
#include<cassert> // For assert
#include<time.h> // For shuffling array using srand(time(NULL))

// For the nodes of Binary Search Tree
struct node {
    int data;
    node *left;
    node *right;
    bool RED; // Color of parent link
};

// Utility function to easily create new nodes
node *getNode(int data, bool RED) {
    node *temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->RED = RED;

    return temp;
}

// Utility function to check if node has red link or not
bool isRed(node *root) {
    if(root == NULL) return false;
    return root->RED;
}

// Rotate a right leaning subtree to left orientation
node *rotateLeft(node *root) {
    node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    temp->RED = root->RED;
    root->RED = true;

    return temp;
}

// Rotate a left leaning subtree to right orientation
node *rotateRight(node *root) {
    node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    temp->RED = root->RED;
    root->RED = true;

    return temp;
}

// Flip colors of children in case both have red links, change parent's link to red
void flipColors(node *root) {
    root->RED = true;
    root->left->RED = false;
    root->right->RED = false;
}

node *insert(int val, node *root) {
    if(root == NULL) return getNode(val, true);

    // Check if the provided value should be inserted in the left or right subtree
    if(val <= root->data) root->left = insert(val, root->left);
    if(val > root->data) root->right = insert(val, root->right);

    /* Check if any of the red link subtrees are leaning in the wrong direction
    *  This is a left-leaning Red-Black BST, so all red-links should be left-leaning, by definition.
    *  For more information about it; refer to Wikipedia link at top
    */ 
    if(isRed(root->right) && !isRed(root->left)) root = rotateLeft(root);
    if(isRed(root->left) && !isRed(root->left->left)) root = rotateRight(root);
    if(isRed(root->left) && isRed(root->right)) flipColors(root);

    return root;
}

// Inorder traversal funcition of BST
void inorder(node *root, int arr[], int &index) {
    if(root == NULL) return;

    inorder(root->left, arr, index);
    arr[index++] = root->data; // Replacing unsorted elements, with the sorted elements
    inorder(root->right, arr, index);
}


void tree_sort(int arr[], int size) {
    node *root = NULL; // Root pointer for our BST

    // Inserting all the elements of the array into BST
    for(int i=0; i<size; i++){
        root = insert(arr[i], root); // Insertion in a BST is O(log(N))
    }

    int index = 0; // Index value will be passed to help inorder function to replace elements in a sorted order
    inorder(root, arr, index); // Time complexity: O(N)
  
    // As we are inserting N elements into BST, our time complexity becomes O(N*log(N))
    // We then also perform a inorder traversal, this brings our time complexity to: O(N+N*log(N)) -> O(N*log(N))
}

// Utility function to check if array is sorted
bool isSorted(int arr[], int size) {
    for(int i=0; i<size-1; i++) {
        if(arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

// Utility function to shuffle array randomly
void shuffle(int arr[], int n) {
    srand(time(NULL));
    
    for(int i=0; i<n; i++) {
        int rnd = rand() % (n-i);
        int temp = arr[i];
        arr[i] = arr[rnd];
        arr[rnd] = temp;
    }
}

static void test(int t) {
    /* Following tests would check for multiple cases that array
    *  is sorted correctly or not 
    */
    for(int i=1; i<=t; i++) {
        int arr[i]; // Create array size of i, to test array of multiple sizes

        // Add default array values
        for(int j=0; j<i; j++) {
            arr[j] = j+1;
        }

        shuffle(arr, i); // Shuffle the array, so there is no bias in results

        // Print before and after of all test cases
        std::cout << "Test-case: #" << i << std::endl;
        std::cout << "Before sorting:" << std::endl;
        for(int k=0; k<i; k++) std::cout << arr[k] << " ";
        std::cout << std::endl;
        std::cout << std::endl; // For better spacing between test cases

        tree_sort(arr, i); // Sort the array using tree_sort
        
        std::cout << "After sorting:" << std::endl;
        for(int k=0; k<i; k++) std::cout << arr[k] << " ";
        std::cout << std::endl;
        std::cout << std::endl; // For better spacing between test cases
        assert(isSorted(arr,i) == true); // TC #i 
    }
}

int main() {
    test(100); // Run multiple testcases to test our algorithm
}
