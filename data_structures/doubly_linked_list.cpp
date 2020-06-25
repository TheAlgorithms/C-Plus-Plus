#include <cstdio>
#include <cstdlib>
#include <iostream>

/**
 * Initialize variables
 */
struct node {
    int val;
    node *prev;
    node *next;
} * start;

class double_linked_list {
 public:
    double_linked_list() { start = nullptr; }
    void insert(int x);
    void remove(int x);
    void search(int x);
    void show();
    void reverseShow();
};

/**
 * Instert node into list
 */
void double_linked_list::insert(int x) {
    node *t = start;
    if (start != nullptr) {
        while (t->next != nullptr) {
            t = t->next;
        }
        node *n = new node;
        t->next = n;
        n->prev = t;
        n->val = x;
        n->next = nullptr;
    } else {
        node *n = new node;
        n->val = x;
        n->prev = nullptr;
        n->next = nullptr;
        start = n;
    }
}

/**
 * Remove node from list
 */
void double_linked_list::remove(int x) {
    node *t = start;
    while (t != nullptr && t->val != x) {
        t = t->next;
    }
    if (t == nullptr) {
        return;
    }
    if (t->prev == nullptr) {
        if (t->next == nullptr) {
            start = nullptr;
        } else {
            start = t->next;
            start->prev = nullptr;
        }
    } else if (t->next == nullptr) {
        t->prev->next = nullptr;
    } else {
        t->prev->next = t->next;
        t->next->prev = t->prev;
    }
    delete t;
}

/**
 * Search a node from list
 */
void double_linked_list::search(int x) {
    node *t = start;
    int found = 0;
    while (t != nullptr) {
        if (t->val == x) {
            std::cout << "\nFound";
            found = 1;
            break;
        }
        t = t->next;
    }
    if (found == 0) {
        std::cout << "\nNot Found";
    }
}

/**
 * Show all nodes from list
 * Ascendent order.
 */
void double_linked_list::show() {
    node *t = start;
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}

/**
 * Show all nodes from list
 * Descendent order.
 */
void double_linked_list::reverseShow() {
    node *t = start;
    while (t != nullptr && t->next != nullptr) {
        t = t->next;
    }
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->prev;
    }
}

/**
 * Main function
 */
int main() {
    int choice, x;
    double_linked_list ob;
    do {
        std::cout << "\n0. Exit";
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

        default:
            if (choice == 0) {
                break;
            }
            std::cout << "Wrong option; type an option : ";
            std::cin >> choice;

            break;
        }
    } while (choice != 0);
    return 0;
}
