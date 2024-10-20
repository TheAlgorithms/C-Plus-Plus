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
    int val;
    node *prev;
    node *next;
} * start;
    int val;      ///< Value stored in the node.
    node *prev;   ///< Pointer to the previous node.
    node *next;   ///< Pointer to the next node.
} *start;        ///< Pointer to the start of the doubly linked list.
Commenting on lines +1 to +23
Comment
 
Leave a comment
 

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
@@ -38,6 +107,11 @@ void double_linked_list::insert(int x) {
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
@@ -46,22 +120,27 @@ void double_linked_list::remove(int x) {
    if (t == NULL) {
        return;
    }
    if (t->prev == NULL) {
    if (t->prev == NULL) {  // Removing the first node
        if (t->next == NULL) {
            start = NULL;
        } else {
            start = t->next;
            start->prev = NULL;
        }
    } else if (t->next == NULL) {
    } else if (t->next == NULL) {  // Removing the last node
        t->prev->next = NULL;
    } else {
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
@@ -78,6 +157,9 @@ void double_linked_list::search(int x) {
    }
}

/**
 * @brief Displays the list in forward order.
 */
void double_linked_list::show() {
    node *t = start;
    while (t != NULL) {
@@ -86,6 +168,9 @@ void double_linked_list::show() {
    }
}

/**
 * @brief Displays the list in reverse order.
 */
void double_linked_list::reverseShow() {
    node *t = start;
    while (t != NULL && t->next != NULL) {
@@ -97,6 +182,13 @@ void double_linked_list::reverseShow() {
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
@@ -106,21 +198,21 @@ int main() {
        std::cout << "\n3. Search";
        std::cout << "\n4. Forward print";
        std::cout << "\n5. Reverse print";
        std::cout << "\n\nEnter you choice : ";
        std::cout << "\n\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "\nEnter the element to be inserted : ";
            std::cout << "\nEnter the element to be inserted: ";
            std::cin >> x;
            ob.insert(x);
            break;
        case 2:
            std::cout << "\nEnter the element to be removed : ";
            std::cout << "\nEnter the element to be removed: ";
            std::cin >> x;
            ob.remove(x);
            break;
        case 3:
            std::cout << "\nEnter the element to be searched : ";
            std::cout << "\nEnter the element to be searched: ";
            std::cin >> x;
            ob.search(x);
            break;
