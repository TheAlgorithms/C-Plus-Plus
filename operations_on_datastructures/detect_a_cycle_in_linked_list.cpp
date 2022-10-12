#include <iostream>
using namespace std;

struct node {
    int val;
    node *next;
};

node *start;
node *tail;

/**
 * @brief insert function
 * @param x is the data associated with the node in a linked list.
 * @param pos signifies if to insert the node at the end of linked list (tail
 * node) or after adding it to the tail of the linked list make it point at some
 * node in the linked list (that creates a cycle).
 */
void insert(int x, int pos) {
    node *t = start;

    // new node
    node *n = new node;
    n->val = x;
    n->next = NULL;

    if (start == NULL) {
        start = n;
        tail = n;
    } else {
        if (pos == -1) {
            // add node at the tail
            tail->next = n;
            // update tail pointer
            tail = n;
        } else {
            // link last node to the node at position "pos"
            int i = 1;
            while (t && i < pos) {
                t = t->next;
                i++;
            }
            // add node at the tail
            tail->next = n;
            // make tail node point at a node in the linked list
            n->next = t;
        }
    }
}

/**
 *  @brief detect_cycle_in_linked_list function
Fast and slow pointers are basic idea behind the implementation.
While the slow pointer reaches a node, the fast pointer reaches the next to
next node.
If a cycle exits in a linked list, after a traversal of slow and
fast pointers in the linked list, it is guaranted that the slow and fast
pointers will point at the same node at some point of time.
If there exists no cycle, then that fast pointer will end up at NULL pointer.
In this way, a cycle is detected in a linked list.
 * @returns true if cycel exists int he linked list, false if it doesn't.
 */
bool detect_cycle_in_linked_list(node *p) {
    node *slow, *fast;
    slow = fast = p;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }
    return false;
}

void show() {
    node *t = start;
    while (t != NULL) {
        cout << t->val << " ";
        t = t->next;
    }
    cout << endl;
}

int main() {
    insert(1, -1);
    insert(2, -1);
    insert(3, -1);
    insert(4, -1);
    insert(5, 0);

    if (detect_cycle_in_linked_list(start))
        cout << "Cycle detected!" << endl;
    else
        cout << "No cycle detected." << endl;

    /**
    * Comment the above part and uncommnent the lines below to see how the
    program detects a cycle:
    insert(1, -1);
    insert(2, -1);
    insert(3, -1);
    insert(4, -1);
    insert(5, 2);
    if (detect_cycle_in_linked_list(start))
        cout << "Cycle detected!" << endl;
    else
        cout << "No cycle detected." << endl;
    */

    return 0;
}