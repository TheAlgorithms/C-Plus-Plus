#include <iostream>

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
    // Each node will return 1 so the total adds up to be the size
    return 1 + getSize(root->next);
}

/*
 * @brief This function dealocates memory related to the given list
 * It recursively deletes all of the nodes of the input list.
 * @param room the root/head of the input list
 * @warning Plese note that the memory for each node has to be alocated using new.
 */
void deleteList(Node *const root) {
    if (root != NULL)
    {
        deleteList(root->next);
        delete root;
    }
}

int main() {
    Node *myList = new Node(0, NULL);  // Initializes the LinkedList
    Node *temp = myList;
    // Creates a linked lists of total size 10, numbered 1 - 10
    for (int i = 1; i < 10; i++) {
        temp->next = new Node(i, NULL);
        temp = temp->next;
    }
    // Creating other lists for checking purposes
    Node *secondList = new Node(0, NULL);  // List of size 1
    Node *thirdList = NULL;                // List of size 0

    std::cout << getSize(myList) << std::endl
              << getSize(secondList) << std::endl
              << getSize(thirdList) << std::endl;
    deleteList(secondList);
    deleteList(myList);

    return 0;
}
