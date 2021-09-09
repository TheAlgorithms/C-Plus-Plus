/**
 * @file
 * @brief Implementation of reversing a single linked list algorithm.
 * @details
 * The linked list is a data structure used for holding a sequence of
 * values, which can be added, displayed,reversed or removed.
 * ### Algorithm
 * Values can be added by iterating to the end of a list(by following
 * the pointers) starting from the first link. Whichever link points to null
 * is considered the last link and is pointed to the new value.
 *
 * Linked List can be reversed by using 3 pointers: current, previous, and
 * next_node; we keep iterating until the last node. Meanwhile, before changing
 * to the next of current, we store it in the next_node pointer, now we store
 * the prev pointer in the current of next, this is where the actual reversal
 * happens. And then we move the prev and current pointers one step forward.
 * Then the head node is made to point to the last node (prev pointer) after
 * completion of an iteration.
 * Graphic Explanation:https://bit.ly/3nbVrFe
 */
#include <cassert>   /// for assert
#include <iostream>  /// for I/O operations
#include <memory>    /// for dynamic memory

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {
/**
 * @namespace linked_list
 * @brief Functions for singly linked list algorithm
 */
namespace linked_list {
/**
 * A Node class containing a value and pointer to another link
 */
class Node {
 public:
    int val;     /// value of the current link
    Node *next;  /// pointer to the next value on the list
};

/**
 * A list class containing a sequence of links
 */
class list {
 private:
    Node *head = nullptr;  // link before the actual first element
 public:
    /**
     * List constructor. Initializes the first link.
     */
    list() {
        // Initialize the first link
    }
    bool isEmpty();
    void insert(int32_t new_elem);
    void reverseList();
    void display();
    int top();
    int last();
};

/**
 * function checks if list is empty
 * @returns true if list is empty
 * @returns false if list is not empty
 */
bool list::isEmpty() {
    if (head == nullptr) {
        return true;
    } else {
        return false;
    }
}

/**
 * function adds new element to the end of the list
 * @param new_elem to be added to the end of the list
 */
void list::insert(int32_t n) {
    Node *new_node = new Node();
    Node *temp = nullptr;
    new_node->val = n;
    new_node->next = nullptr;
    if (isEmpty()) {
        head = new_node;
    } else {
        temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

/**
 * function reverseList for reversing the  list
 * @brief Using current,previous and next pointer.
 * @returns 'void'
 */
void list::reverseList() {
    Node *curr = head;
    Node *prev = nullptr, *next_node = nullptr;
    while (curr != nullptr) {
        next_node = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_node;
    }
    head = prev;
}

/**
 * function to find the top element of the list
 * @returns 'int n'
 * @brief returns the first element in the list
 */
int list::top() {
    if (!isEmpty()) {
        int n = head->val;
        return n;
    }
    else
    return 0;
    
}
/**
 * function to find the last element of the list
 *  @returns 'int t->val'
 *  @brief returns the last element of the list
 */
int list::last() {
    if (!isEmpty()) {
        Node *t = head;
        while (t->next != nullptr) {
            t = t->next;
        }
        return t->val;
    }
    else return 0;
    
}
}  // namespace linked_list
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::linked_list::list L;
    // 1st test

    L.insert(11);
    L.insert(12);
    L.insert(15);
    L.insert(10);
    L.insert(12);
    L.insert(20);
    L.insert(18);
    assert(L.top() == 11);
    assert(L.last() == 18);
    L.reverseList();
    // Reversal Testing
    assert(L.top() == 18);
    assert(L.last() == 11);
    std::cout << "Passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
