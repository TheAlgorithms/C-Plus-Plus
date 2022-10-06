/**
 * @file
 * @brief Implementation of [Reversing
 * a single linked list](https://simple.wikipedia.org/wiki/Linked_list)
 * @details
 * The linked list is a data structure used for holding a sequence of
 * values, which can be added, displayed, reversed, or removed.
 * ### Algorithm
 * Values can be added by iterating to the end of a list (by following
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

 * [A graphic explanation and view of what's happening behind the
 *scenes](https://drive.google.com/file/d/1pM5COF0wx-wermnNy_svtyZquaCUP2xS/view?usp=sharing)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for I/O operations
#include <memory>    /// for dynamic memory
#include <new>       /// for managing  dynamic storage

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
    int32_t val;  /// value of the current link
    Node *next;   /// pointer to the next value on the list
};

/**
 * A list class containing a sequence of links
 */
class list {
 private:
    Node *head;  // link before the actual first element
 public:
    /**
     * List constructor. Initializes the first link.
     */
    list() {
        head = nullptr;  // Initialize the first link
    }
    bool isEmpty();
    void insert(int32_t new_elem);
    void reverseList();
    void display();
    int32_t top();
    int32_t last();
    int32_t traverse(int32_t index);
};

/**
 * @brief Utility function that checks if the list is empty
 * @returns true if the list is empty
 * @returns false if the list is not empty
 */
bool list::isEmpty() { return head == nullptr; }

/**
 * @brief Utility function that adds a new element at the end of the list
 * @param new_elem element be added at the end of the list
 */
void list::insert(int32_t n) {
    try {
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
    } catch (std::bad_alloc &exception) {
        std::cerr << "bad_alloc detected: " << exception.what() << "\n";
    }
}

/**
 * @brief Utility function for reversing a list
 * @brief Using the current, previous, and next pointer.
 * @returns void
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
 * @brief Utility function to find the top element of the list
 * @returns the top element of the list
 */
int32_t list::top() {
    if (!isEmpty()) {
        return head->val;
    } else {
        throw std::logic_error("List is empty");
    }
}
/**
 *  @brief Utility function to find the last element of the list
 *  @returns the last element of the list
 */
int32_t list::last() {
    if (!isEmpty()) {
        Node *t = head;
        while (t->next != nullptr) {
            t = t->next;
        }
        return t->val;
    } else {
        throw std::logic_error("List is empty");
    }
}
/**
 *  @brief Utility function to find the i th element of the list
 *  @returns the i th element of the list
 */
int32_t list::traverse(int32_t index) {
    Node *current = head;

    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            return (current->val);
        }
        count++;
        current = current->next;
    }

    /* if we get to this line,the caller was asking for a non-existent element
    so we assert fail */
    exit(1);
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
    L.insert(-12);
    L.insert(-20);
    L.insert(18);
    assert(L.top() == 11);
    assert(L.last() == 18);
    L.reverseList();
    // Reversal Testing
    assert(L.top() == 18);
    assert(L.traverse(1) == -20);
    assert(L.traverse(2) == -12);
    assert(L.traverse(3) == 10);
    assert(L.traverse(4) == 15);
    assert(L.traverse(5) == 12);
    assert(L.last() == 11);
    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
