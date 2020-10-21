#include<iostream> 
using namespace std;
  
//declaration for new bst node  
struct bstnode 
{ 
int data; 
struct bstnode *left, *right; 
}; 
  
// create a new BST node 
struct bstnode *newNode(int key) 
{ 
struct bstnode *temp =  new struct bstnode(); 
temp->data = key; 
temp->left = temp->right = NULL; 
return temp; 
} 
   
// perform inorder traversal of BST 
void inorder(struct bstnode *root) 
{ 
if (root != NULL) 
    { 
inorder(root->left); 
cout<<root->data<<" "; 
inorder(root->right); 
    } 
} 
   
/* insert a new node in BST with given key  */
struct bstnode* insert(struct bstnode* node, int key) 
{ 
    //tree is empty;return a new node
if (node == NULL) return newNode(key); 
   
    //if tree is not empty find the proper place to insert new node
if (key < node->data) 
node->left  = insert(node->left, key); 
else
node->right = insert(node->right, key); 
   
    //return the node pointer
return node; 
} 
//returns the node with minimum value
struct bstnode * minValueNode(struct bstnode* node) 
{ 
struct bstnode* current = node; 
   
    //search the leftmost tree
while (current && current->left != NULL) 
current = current->left; 
   
return current; 
} 
  //function to delete the node with given key and rearrange the root
struct bstnode* deleteNode(struct bstnode* root, int key) 
{ 
    // empty tree 
if (root == NULL) return root; 
   
    // search the tree and if key < root, go for lefmost tree 
if (key < root->data) 
root->left = deleteNode(root->left, key); 
   
    // if key > root, go for rightmost tree 
else if (key > root->data) 
root->right = deleteNode(root->right, key); 
   
    // key is same as root
else
    { 
        // node with only one child or no child 
if (root->left == NULL) 
        { 
struct bstnode *temp = root->right; 
delete(root); 
return temp; 
        } 
else if (root->right == NULL) 
        { 
struct bstnode *temp = root->left; 
delete(root); 
return temp; 
        } 
   
     // node with both children; get successor and then delete the node
struct bstnode* temp = minValueNode(root->right); 
   
        // Copy the inorder successor's content to this node 
root->data = temp->data; 
         
       // Delete the inorder successor 
root->right = deleteNode(root->right, temp->data); 
    } 
    return root; 
}   
// main program
int main() 
{ 
    /* Let us create following BST 
              40 
             /  \ 
           30   60 
                    \ 
                   65 
                      \
                     70*/
struct bstnode *root = NULL; 
root = insert(root, 40); 
root = insert(root, 30); 
root = insert(root, 60); 
root = insert(root, 65); 
root = insert(root, 70); 
 
cout<<"Binary Search Tree created (Inorder traversal):"<<endl; 
inorder(root); 
   
cout<<"\nDelete node 40\n"; 
root = deleteNode(root, 40); 
cout<<"Inorder traversal for the modified Binary Search Tree:"<<endl; 
inorder(root); 
   
return 0; 
}
