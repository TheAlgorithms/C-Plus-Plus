// C++ program to rotate a linked list counter clock wise

#include <bits/stdc++.h>
using namespace std;

/* Link list node */
class Node {
public:
    int data;
    Node* next;
};

// This function rotates a linked list counter-clockwise and updates the head. 
// The function assumes that k is smaller than size of linked list. 
// It doesn't modify the list if k is greater than or equal to size.
void rotate(Node** head_ref, int k)
{
    if (k == 0)
        return;

    Node* current = *head_ref;

    // current will either point to kth or NULL after this loop.
    int count = 1;
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }

    // If current is NULL, k is greater than or equal to count of nodes in linked list. Don't change the list in this case
    if (current == NULL)
        return;

    // current points to kth node. Store it in a variable. kthNode points to node 40 in the above example
    Node* kthNode = current;

    // current will point to last node after this loop
    while (current->next != NULL)
        current = current->next;

    // Change next of last node to previous head
    current->next = *head_ref;

    // Change head to (k+1)th node
    *head_ref = kthNode->next;

    // change next of kth node to NULL
    kthNode->next = NULL;
}

/* UTILITY FUNCTIONS */
/* Function to push a node */
void push(Node** head_ref, int new_data)
{
    /* allocate node */
    Node* new_node = new Node();

    /* put in the data */
    new_node->data = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Function to print linked list */
void printList(Node* node)
{
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
}

/* Driver code*/
int main()
{
    /* Start with the empty list */
    Node* start = NULL;

    int cnt;
    cout << "Enter number of nodes: ";
    cin >> cnt;
    cout << endl;

    for(int i=0;i<cnt;i++)
    {
        cout << "Enter node" << (i+1) << ": ";
        int data;
        cin >> data;
        push(&start, data);
    }

    cout << endl;
    cout << "Linked list before rotation:";
    printList(start);
    cout << endl;

    cout << "Enter position from where to rotate: ";
    int pos;
    cin >> pos;
    rotate(&start, pos);
    cout << endl;

    cout << "\nLinked list after rotation: ";
    printList(start);
    cout << endl;

    return 0;
}

// This is code is contributed by bhanupsingh10
