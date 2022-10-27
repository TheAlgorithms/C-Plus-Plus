#include <cstdio>
#include <cstdlib>
#include <iostream>

struct node {
    int val;
    node *prev;  // node for double linked list created
    node *next;
} * start;  // head/topmost/starting pointer for linked list

class double_linked_list {
 public:
    double_linked_list() { start = NULL; }
    void insert(int x);
    void remove(int x);
    void search(int x);
    void show();
    void reverseShow();
};

void double_linked_list::insert(int x) {
    node *t = start;
    if (start != NULL) {  // checks if linked list is empty
        while (t->next != NULL) {
            t = t->next;  // if linked list is not empty it reaches end of the
                          // list
        }
        node *n = new node;
        t->next = n;  // last element of list points towards new node
        n->prev =
            t;  // new node's prev pointer now points towards end of list node
        n->val = x;  // value of new node initialised
        n->next = NULL;
    } else {
        node *n = new node;
        n->val = x;      // initialise node value
        n->prev = NULL;  // prev of only node should be null
        n->next = NULL;  // next of only node should be null
        start = n;       // pointer to beginning of list
    }
}

void double_linked_list::remove(int x) {
    node *t = start;
    while (t != NULL && t->val != x) {
        t = t->next;  // iteratively reaches deletion value or end of list(if
                      // value unavailable)
    }
    if (t == NULL) {
        return;  // returns if list is empty value not found
    }
    if (t->prev == NULL) {
        if (t->next == NULL) {
            start = NULL;  // if only 1 element is present the value is
                           // initialised to null
        } else {
            start = t->next;     // shifts start pointer to next element
            start->prev = NULL;  // removes 1st element
        }
    } else if (t->next == NULL) {
        t->prev->next = NULL;  // last element is assigned null value
    } else {
        t->prev->next = t->next;  // to remove a node in the middle
        t->next->prev = t->prev;
    }
    delete t;
}

void double_linked_list::search(int x) {
    node *t = start;
    int found = 0;
    while (t != NULL) {
        if (t->val == x) {
            std::cout << "\nFound";  // checks if value found
            found = 1;
            break;
        }
        t = t->next;  // else continues moving to next element
    }
    if (found == 0) {  // checks if value not found after all elements checked
        std::cout << "\nNot Found";
    }
}

void double_linked_list::show() {
    node *t = start;
    while (t != NULL) {
        std::cout << t->val << "\t";
        t = t->next;  // shows current element then pointer shifts to next
                      // element
    }
}

void double_linked_list::reverseShow() {
    node *t = start;
    while (t != NULL && t->next != NULL) {
        t = t->next;  // end of pointer reached
    }
    while (t != NULL) {
        std::cout << t->val << "\t";  // elements shown
        t = t->prev;                  // pointer shifts to previous element
    }
}

int main() {
    int choice, x;
    double_linked_list ob;
    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Delete";
        std::cout << "\n3. Search";
        std::cout << "\n4. Forward print";
        std::cout << "\n5. Reverse print";
        std::cout << "\n\nEnter you choice : ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "\nEnter the element to be inserted : ";
                std::cin >> x;
                ob.insert(x);
                break;
            case 2:
                std::cout << "\nEnter the element to be removed : ";
                std::cin >> x;
                ob.remove(x);
                break;
            case 3:
                std::cout << "\nEnter the element to be searched : ";
                std::cin >> x;
                ob.search(x);
                break;
            case 4:
                ob.show();
                break;
            case 5:
                ob.reverseShow();
                break;
        }
    } while (choice != 0);
    return 0;
}
