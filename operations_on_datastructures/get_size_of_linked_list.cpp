#include <iostream>
// We won't add using namspace std header, instead will use std:: tag

class Node {
 public:
    int val;
    Node *next;

    Node(int v, Node *n) : val(v), next(n) {}  // Default constructor for Node
};

int getSize(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + getSize(root->next);  // Each node will return a 1
                                     // the total will
                                     // add up to be the size
}

int main() {
    Node *myList = new Node(0, NULL);  // Initializes the LinkedList
    Node *temp = myList;
    for (int i = 1; i < 10;
         i++) {  // Creates a linked lists of total size 10, numbered 1 - 10
        temp->next = new Node(i, NULL);
        temp = temp->next;
    }
    // Creating some other lists for checking purposes
    Node *secondList = new Node(0, NULL);  // List of size 1
    Node *thirdList = NULL;                // List of size 0

    std::cout << getSize(myList) << std::endl
              << getSize(secondList) << std::endl
              << getSize(thirdList) << std::endl;

    return 0;
}
