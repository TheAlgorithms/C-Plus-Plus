//C++ program for sorting a linked list
#include <iostream>
using namespace std;
// Definition of the ListNode structure
// Represents a node in the linked list
struct ListNode {
    int val;         // Value of the node
    ListNode* next;  // Pointer to the next node
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Function to find the middle node of the linked list using slow and fast
// pointers
ListNode* mid(ListNode* h) {
    ListNode *s = h, *f = h->next; //Here 's' is the slow pointer and 'f' is the fast pointer
    while (f && f->next) {
        s = s->next;
        f = f->next->next;
    }
    return s;
}

// Function to merge two sorted linked lists
ListNode* mg(ListNode* l, ListNode* r) {
    if (l == nullptr)
        return r;  // If left list is empty, return right list
    if (r == nullptr)
        return l;           // If right list is empty, return left list
    if (l->val < r->val) {  // Compare values and recursively merge
        l->next = mg(l->next, r);
        return l;
    } else {
        r->next = mg(l, r->next);
        return r;
    }
}

// Function to sort the linked list using merge sort
ListNode* sortList(ListNode* h) {
    if (h == nullptr || h->next == nullptr)
        return h;          // Base case: list is empty or has one node
    ListNode* m = mid(h);  // Find the middle node
    ListNode *l = h, *r = m->next;
    m->next = nullptr;  // Split the list into two halves
    l = sortList(l);    // Recursively sort the left half
    r = sortList(r);    // Recursively sort the right half
    return mg(l, r);    // Merge the two sorted halves
}

// Function to push a new node with a given value to the front of the list
void push(ListNode** h, int new_val) {
    ListNode* new_node = new ListNode(new_val);
    new_node->next = *h;
    *h = new_node;
}

int main() {
    ListNode* head = nullptr;

    // Push elements into the list
    push(&head, 1);
    push(&head, 10);
    push(&head, -8);
    push(&head, 3);
    push(&head, 7);

    // Sort the list using merge sort
    head = sortList(head);

    // Print the sorted list
    ListNode* temp = head;
    while (temp) {
        cout << temp->val << " ";  // Print the value of each node
        temp = temp->next;         // Move to the next node
    }
    cout << endl;

    return 0;
}
