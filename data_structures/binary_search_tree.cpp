/**
 * \file
 * \brief A simple tree implementation using structured nodes
 *
 * \todo update code to use C++ STL library features and OO structure
 * \warning This program is a poor implementation - C style - and does not
 * utilize any of the C++ STL features.
 */
#include <iostream>

struct node {
    int val;
    node *left;
    node *right;
};

struct Queue {
    node *t[100];
    int front;
    int rear;
};

Queue queue;

void enqueue(node *n) { queue.t[queue.rear++] = n; }

node *dequeue() { return (queue.t[queue.front++]); }

void Insert(node *n, int x) {
    if (x < n->val) {
        if (n->left == NULL) {
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->left = temp;
        } else {
            Insert(n->left, x);
        }
    } else {
        if (n->right == NULL) {
            node *temp = new node;
            temp->val = x;
            temp->left = NULL;
            temp->right = NULL;
            n->right = temp;
        } else {
            Insert(n->right, x);
        }
    }
}

int findMaxInLeftST(node *n) {
    while (n->right != NULL) {
        n = n->right;
    }
    return n->val;
}

void Remove(node *p, node *n, int x) {
    if (n->val == x) {
        if (n->right == NULL && n->left == NULL) {
            if (x < p->val) {
                p->right = NULL;
            } else {
                p->left = NULL;
            }
        } else if (n->right == NULL) {
            if (x < p->val) {
                p->right = n->left;
            } else {
                p->left = n->left;
            }
        } else if (n->left == NULL) {
            if (x < p->val) {
                p->right = n->right;
            } else {
                p->left = n->right;
            }
        } else {
            int y = findMaxInLeftST(n->left);
            n->val = y;
            Remove(n, n->right, y);
        }
    } else if (x < n->val) {
        Remove(n, n->left, x);
    } else {
        Remove(n, n->right, x);
    }
}

void BFT(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        enqueue(n->left);
        enqueue(n->right);
        BFT(dequeue());
    }
}

void Pre(node *n) {
    if (n != NULL) {
        std::cout << n->val << "  ";
        Pre(n->left);
        Pre(n->right);
    }
}

void In(node *n) {
    if (n != NULL) {
        In(n->left);
        std::cout << n->val << "  ";
        In(n->right);
    }
}

void Post(node *n) {
    if (n != NULL) {
        Post(n->left);
        Post(n->right);
        std::cout << n->val << "  ";
    }
}

int main() {
    queue.front = 0;
    queue.rear = 0;
    int value;
    int ch;
    node *root = new node;
    std::cout << "\nEnter the value of root node :";
    std::cin >> value;
    root->val = value;
    root->left = NULL;
    root->right = NULL;
    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First";

        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        int x;
        switch (ch) {
        case 1:
            std::cout << "\nEnter the value to be Inserted : ";
            std::cin >> x;
            Insert(root, x);
            break;
        case 2:
            std::cout << "\nEnter the value to be Deleted : ";
            std::cin >> x;
            Remove(root, root, x);
            break;
        case 3:
            BFT(root);
            break;
        case 4:
            Pre(root);
            break;
        case 5:
            In(root);
            break;
        case 6:
            Post(root);
            break;
        }
    } while (ch != 0);

    return 0;
}


/*Binary Search Tree which supports the following operations:
(i) Insert an element x
(ii) Delete an element x
(iii) Search for an element x in the BST and change its value to y and then place the node with
value y at its appropriate position in the BST
(iv) Display the elements of the BST in preorder, inorder, and postorder traversal
(v) Display the elements of the BST in level-by-level traversal
(vi) Display the height of the BST*/

#include<iostream>
#include<cstdlib> //for system()
using namespace std;

// QueueNODE CLASS
template <class t>
class QNode
{
public:

t info;
QNode *next;

QNode(t data)
{
info = data;
next = NULL;
}
};

// QUEUE CLASS
template <class T>
class Queue
{
QNode <T> *head;
QNode <T> *tail;

public:

Queue()
{
head = tail = NULL;
}

bool isEmpty()
{
return ( head == NULL )? true : false ;
}

void enque(T data)
{
if( head == NULL )
{
head = tail = new QNode<T>(data);
return;
}

else
{
tail->next = new QNode<T>(data);
tail = tail->next;
}
}//enque()

T deque()
{
T node_info;

if( head == NULL )
{
node_info =  NULL;
}

else if( head == tail )
{
node_info = head->info;
delete(head);
head = tail = NULL;
}

else
{
node_info = head->info;
QNode <T>*p = head;
head = head->next;
delete(p);
}

return node_info;
}// deque()
};

//NODE CLASS
class BSTNode
{
public:
int info;
BSTNode *left, *right;

BSTNode(int data)
{
info = data;
left = right = NULL;
}
};

//TREE CLASS
class BSTree //BinarySearchTree
{
BSTNode *root;

public:

BSTree()
{
root = NULL;
}

// func to add new node to tree
void add_node(int key);

//func to print the node key
void visit(BSTNode *p) { cout << p->info << ' '; }

//func to search a node
bool search(int key);

//functions to traverse the tree
void traverse(); // Breadth-first traversal
void inorder_traverse(BSTNode*); // /*
void preorder_traverse(BSTNode*); // Depth-first traversal
void postorder_traverse(BSTNode*); // */

//func to delete a node from the tree
int delete_node(int);

//func to return height of the tree
int count_height(BSTNode*);

//func to return the root of the tree
BSTNode *getroot() { return root; }
};

int main()
{
BSTree tree;
int choice, key, status;

while(1)
{
system("clear");

cout << "\n\t\t\t<--- BINARY SEARCH TREE --->";
cout << "\n\nAvailable operations :";
cout << "\n\t1. Add a key to the tree";
cout << "\n\t2. Search the tree for presence of a key";
        cout << "\n\t3. Breadth-first traversal of tree";
        cout << "\n\t4. Depth-first traversal of the tree";
        cout << "\n\t5. Delete a key from the tree";
cout << "\n\t6. Count the height of the tree";
        cout << "\n\t7. EXIT";
cout << "\n\nEnter your choice :";

cin>>choice;

switch(choice)
{
case 1:
cout << "\nEnter the key : ";
cin>>key;

if( tree.search(key) )
{
cout << "\n[!] The key " << key << " is already present in the tree!";
break;
}
else tree.add_node(key);
cout << "\n\nDONE!";
break;

case 2:
if( tree.getroot() == NULL ) cout << "\nUnable to search, tree is empty!";

else
{
cout << "\n\nEnter the key to search for :";
cin>>key;

cout << "\nThe key " << key << " is";
if( !tree.search(key) ) cout << " NOT";
cout << " present in the list.";
}
break;

case 3:
if( tree.getroot() == NULL ) cout << "\nFailed, tree empty!";
else
{
cout << "\nThe tree using breadth-first traversal is :\t";
tree.traverse();
}
break;

case 4:
if( tree.getroot() == NULL ) cout << "\nFailed, tree empty!";
else
{
cout << "\nThe tree using depth-first traversal is :\n";
cout << "\ninorder :\t"; tree.inorder_traverse(tree.getroot());
cout << "\n\npreorder:\t"; tree.preorder_traverse(tree.getroot());
cout << "\n\npostorder :\t"; tree.postorder_traverse(tree.getroot());
}
break;

case 5:
if( tree.getroot() == NULL ) cout << "\nUnable to delete, tree is empty!";

else
{
cout << "\nEnter the key to delete :";
cin>>key;

if( tree.delete_node(key) )   cout << "\nDONE!";
else cout << "\nFailed, key " << key << " not present in tree!";
}
break;

case 6:
int height;
if( ( height = tree.count_height(tree.getroot()) ) != 0 )
{
cout << "\nCurrent height = " << height;
}
else
{
cout << "\n[!] Current tree empty!";
}
break;


case 7:
system("clear");
return 0;
}
}//while(1)
return 0;
}


void BSTree:: add_node(int key)
{
if( root == NULL )
{
root = new BSTNode(key);
return;
}

else
{
BSTNode *p = root;

while(1)
{
if( key > p->info ) //go to right
{
if( p->right == NULL )
{
p->right = new BSTNode(key);
return;
}
else p = p->right;
}

else //go to left
{
if( p->left == NULL )
{
p->left = new BSTNode(key);
return;
}
else p = p->left;
}
}//while(1)
}
}//add_node()

bool BSTree:: search(int key)
{
BSTNode *p = root;

while( p != NULL )
{
if( key == p->info ) return true;

else if( key > p->info ) p = p->right;
else p = p->left;
}
return false;
}//search()

void BSTree:: inorder_traverse(BSTNode *p)
{
if( p->left != NULL ) inorder_traverse(p->left); // L
visit(p); // V
if( p->right != NULL ) inorder_traverse(p->right); // R
}

void BSTree:: preorder_traverse(BSTNode *p)
{
visit(p); // V
if( p->left != NULL ) preorder_traverse(p->left); // L
if( p->right != NULL ) preorder_traverse(p->right); // R
}

void BSTree:: postorder_traverse(BSTNode *p)
{
if( p->left != NULL ) postorder_traverse(p->left); // L
if( p->right != NULL ) postorder_traverse(p->right); // R
visit(p); // V
}

void BSTree:: traverse()
{
Queue <BSTNode*> q;

q.enque(root);

while( !q.isEmpty() )
{
BSTNode *node = q.deque();

visit(node);

if( node->left != NULL ) q.enque(node->left);
if( node->right != NULL ) q.enque(node->right);
}
}//traverse()

int BSTree:: delete_node(int key)
{
/*
if the node to be deleted is root
*/
if( key == root->info )
{
if( root->right == NULL && root->left == NULL )
{
delete(root);
root = NULL;
}

else if( root->left == NULL || root->right == NULL )
{
BSTNode *temp = root;
root = ( root->left == NULL)? root->right : root->left;
delete(temp);
}

else
{
BSTNode *rtemp = root->left, *temp = root;

while( rtemp->right != NULL ) rtemp = rtemp->right;

rtemp->right = root->right->left;
root->right->left = root->left;
root = root->right;
delete(temp);
}
return true;
}//if( key node = root )

/*
for nodes other than root
*/
else
{
BSTNode *p = root, *temp;

while(1)
{
/*
To check if node to be tested for 'key' is not null.
If it is, key is not present in the tree.
*/
if( p == NULL || ( p->right == NULL && p->left == NULL)  ) return false;  //key not present

if( p->right->info == key ||  p->left->info == key )
{
temp = (p->right->info == key )? p->right : p->left ;

if( temp->right == NULL && temp->left == NULL ) //Node has no child
{
if( temp == p->right ) p->right=NULL;
else p->left= NULL;
delete(temp);
return true;
}

else if( temp->right != NULL && temp->left != NULL ) //Node has 2 children
{
BSTNode *rtemp = temp->left;

while( rtemp->right != NULL ) rtemp = rtemp->right;

rtemp->right = temp->right->left;
temp->right->left = temp->left;
if( temp == p->right ) p->right = temp->right;
else p->left = temp->right;
delete(temp);
return true;
}

else  //NOde has 1 child
{
if( temp == p->right )
{
p->right = (temp->right != NULL)? temp->right : temp->left ;
}
else
{
p->left = (temp->right != NULL )? temp->right : temp->left;
}
delete(temp);
return true;
}
}

else if( key > p->info ) p = p->right;
else p = p->left;
}
}
}//delete_node()

int BSTree:: count_height(BSTNode *p)
{
if( p == NULL ) return 0;

else
{
int left_height = count_height(p->left);
int right_height = count_height(p->right);

if( left_height > right_height ) return left_height + 1 ;
else return right_height+ 1;
}
}//count_height()

