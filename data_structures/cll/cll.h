/**
 * @file cll.h
 * @brief Declaration of a circular linked list of integers.
 * @details Defines the node structure and the `cll` class interface for
 *          storing and traversing integer values in a circular list.
 */
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

#ifndef CLL_H
#define CLL_H

/**
 * @brief A node in a circular linked list of integers.
 */
struct node {
    int data;
    node* next;
};

/**
 * @brief A circular linked list of integers.
 */
class cll {
 public:
    /**
     * @brief Constructs an empty circular linked list.
     */
    cll();

    /**
     * @brief Destroys the circular linked list object.
     */
    ~cll();

    /**
     * @brief Displays the list contents and its size.
     */
    void display();

    /**
     * @brief Inserts a value at the beginning of the list.
     * @param new_data Integer value to insert.
     */
    void insert_front(int new_data);

    /**
     * @brief Inserts a value at the end of the list.
     * @param new_data Integer value to insert.
     */
    void insert_tail(int new_data);

    /**
     * @brief Gets the number of elements in the list.
     * @return The number of elements in the list.
     */
    int get_size();

    /**
     * @brief Checks whether the list contains a value.
     * @param item_to_find Integer value to search for.
     * @return `true` if the value is found; otherwise, `false`.
     */
    bool find_item(int item_to_find);

    /**
     * @brief Gets the value at the head of the list.
     * @pre The list is not empty.
     * @return The integer value stored in the head node.
     */
    int operator*();

    /**
     * @brief Advances the head to the next node in the list.
     * @pre The list is not empty.
     */
    void operator++();

 protected:
    node* head;
    int total; /* Total element in a list */
};
#endif
