/**
 * @file double_linked_list.cpp
 * @brief Implementation of a doubly linked list with basic operations.
 * 
 * This program implements a doubly linked list with operations such as
 * insertion, deletion, search, forward traversal, and reverse traversal.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

/**
 * @brief Node structure for the doubly linked list.
 * 
 * Each node contains an integer value, a pointer to the previous node, 
 * and a pointer to the next node.
 */
struct node {
    int val;      ///< Value stored in the node.
    node *prev;   ///< Pointer to the previous node.
    node *next;   ///< Pointer to the next node.
} *start;        ///< Pointer to the start of the doubly linked list.

/**
 * @brief Class representing a doubly linked list.
 * 
 * This class provides methods to insert, remove, search, display the list 
 * in forward and reverse order.
 */
class double_linked_list {
 public:
    /**
     * @brief Constructor to initialize the doubly linked list.
     */
    double_linked_list() { start = NULL; }

    /**
     * @brief Inserts an element at the end of the doubly linked list.
     * 
     * @param x The value to be inserted.
     * 
     * @note Time Complexity: O(n), where n is the number of nodes in the list.
     * @note Space Complexity: O(1), only extra space for a new node.
     */
    void insert(int x);

    /**
     * @brief Removes the first occurrence of a given value from the list.
     * 
     * @param x The value to be removed.
     * 
     * @note Time Complexity: O(n), where n is the number of nodes in the list.
     * @note Space Complexity: O(1), no extra space used aside from traversal.
     */
    void remove(int x);

    /**
     * @brief Searches for a value in the doubly linked list.
     * 
     * @param x The value to be searched.
     * 
     * @note Time Complexity: O(n), where n is the number of nodes in the list.
     * @note Space Complexity: O(1), no extra space used aside from traversal.
     */
    void search(int x);

    /**
     * @brief Displays the list in forward order.
     * 
     * @note Time Complexity: O(n), where n is the number of nodes in the list.
     * @note Space Complexity: O(1), no extra space used.
     */
    void show();

    /**
     * @brief Displays the list in reverse order.
     * 
     * @note Time Complexity: O(n), where n is the number of nodes in the list.
     * @note Space Complexity: O(1), no extra space used.
     */
    void reverseShow();
};

/**
 * @brief Inserts an element at the end of the doubly linked list.
 * 
 * @param x The value to be inserted.
 */
void double_linked_list::insert(int x) {
    node *t = start;
    if (start != NULL) {
        while (t->next != NULL) {
            t = t->next;
        }
        node *n = new node;
        t->next = n;
        n->prev = t;
        n->val = x;
        n->next = NULL;
    } else {
        node *n = new node;
        n->val = x;
        n->prev = NULL;
        n->next = NULL;
        start = n;
    }
}

/**
 * @brief Removes the first occurrence of a given value from the list.
 * 
 * @param x The value to be removed.
 */
void double_linked_list::remove(int x) {
    node *t = start;
    while (t != NULL && t->val != x) {
        t = t->next;
    }
    if (t == NULL) {
        return;
    }
    if (t->prev == NULL) {  // Removing the first node
        if (t->next == NULL) {
            start = NULL;
        } else {
            start = t->next;
            start->prev = NULL;
        }
    } else if (t->next == NULL) {  // Removing the last node
        t->prev->next = NULL;
    } else {  // Removing a middle node
        t->prev->next = t->next;
        t->next->prev = t->prev;
    }
    delete t;
}

/**
 * @brief Searches for a value in the doubly linked list.
 * 
 * @param x The value to be searched.
 */
void double_linked_list::search(int x) {
    node *t = start;
    int found = 0;
    while (t != NULL) {
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
 * @brief Displays the list in forward order.
 */
void double_linked_list::show() {
    node *t = start;
    while (t != NULL) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}

/**
 * @brief Displays the list in reverse order.
 */
void double_linked_list::reverseShow() {
    node *t = start;
    while (t != NULL && t->next != NULL) {
        t = t->next;
    }
    while (t != NULL) {
        std::cout << t->val << "\t";
        t = t->prev;
    }
}

/**
 * @brief Main function to test the doubly linked list operations.
 * 
 * The function provides a menu to insert, delete, search, and display the list.
 * 
 * @return 0 on successful execution.
 */
int main() {
    int choice, x;
    double_linked_list ob;
    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Delete";
        std::cout << "\n3. Search";
        std::cout << "\n4. Forward print";
        std::cout << "\n5. Reverse print";
        std::cout << "\n\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "\nEnter the element to be inserted: ";
            std::cin >> x;
            ob.insert(x);
            break;
        case 2:
            std::cout << "\nEnter the element to be removed: ";
            std::cin >> x;
            ob.remove(x);
            break;
        case 3:
            std::cout << "\nEnter the element to be searched: ";
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
