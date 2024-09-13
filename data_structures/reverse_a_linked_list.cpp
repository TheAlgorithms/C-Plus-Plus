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
    Node* next;   /// pointer to the next value on the list
};

/**
 *  @brief creates a deep copy of a list starting at the input node
 *  @param[in] node pointer to the first node/head of the list to be copied
 *  @return pointer to the first node/head of the copied list or nullptr
 */
Node* copy_all_nodes(const Node* const node) {
    if (node) {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        Node* res = new Node();
        res->val = node->val;
        res->next = copy_all_nodes(node->next);
        return res;
    }
    return nullptr;
}

/**
 * A list class containing a sequence of links
 */
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class list {
 private:
    Node* head = nullptr;  // link before the actual first element
    void delete_all_nodes();
    void copy_all_nodes_from_list(const list& other);

 public:
    bool isEmpty() const;
    void insert(int32_t new_elem);
    void reverseList();
    void display() const;
    int32_t top() const;
    int32_t last() const;
    int32_t traverse(int32_t index) const;
    ~list();
    list() = default;
    list(const list& other);
    list& operator=(const list& other);
};

/**
 * @brief Utility function that checks if the list is empty
 * @returns true if the list is empty
 * @returns false if the list is not empty
 */
bool list::isEmpty() const { return head == nullptr; }

/**
 * @brief Utility function that adds a new element at the end of the list
 * @param new_elem element be added at the end of the list
 */
void list::insert(int32_t n) {
    try {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        Node* new_node = new Node();
        Node* temp = nullptr;
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
    } catch (std::bad_alloc& exception) {
        std::cerr << "bad_alloc detected: " << exception.what() << "\n";
    }
}

/**
 * @brief Utility function for reversing a list
 * @brief Using the current, previous, and next pointer.
 * @returns void
 */
void list::reverseList() {
    Node* curr = head;
    Node* prev = nullptr;
    Node* next_node = nullptr;
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
int32_t list::top() const {
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
int32_t list::last() const {
    if (!isEmpty()) {
        Node* t = head;
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
int32_t list::traverse(int32_t index) const {
    Node* current = head;

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

/**
 *  @brief calls delete operator on every node in the represented list
 */
void list::delete_all_nodes() {
    while (head != nullptr) {
        const auto tmp_node = head->next;
        delete head;
        head = tmp_node;
    }
}

list::~list() { delete_all_nodes(); }

void list::copy_all_nodes_from_list(const list& other) {
    assert(isEmpty());
    head = copy_all_nodes(other.head);
}

/**
 *  @brief copy constructor creating a deep copy of every node of the input
 */
list::list(const list& other) { copy_all_nodes_from_list(other); }

/**
 *  @brief assignment operator creating a deep copy of every node of the input
 */
list& list::operator=(const list& other) {
    if (this == &other) {
        return *this;
    }
    delete_all_nodes();

    copy_all_nodes_from_list(other);
    return *this;
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

void test_copy_constructor() {
    data_structures::linked_list::list L;
    L.insert(10);
    L.insert(20);
    L.insert(30);
    data_structures::linked_list::list otherList(L);
    otherList.insert(40);

    L.insert(400);

    assert(L.top() == 10);
    assert(otherList.top() == 10);
    assert(L.traverse(1) == 20);
    assert(otherList.traverse(1) == 20);

    assert(L.traverse(2) == 30);
    assert(otherList.traverse(2) == 30);

    assert(L.last() == 400);
    assert(otherList.last() == 40);
}

void test_assignment_operator() {
    data_structures::linked_list::list L;
    data_structures::linked_list::list otherList;
    L.insert(10);
    L.insert(20);
    L.insert(30);
    otherList = L;

    otherList.insert(40);
    L.insert(400);

    assert(L.top() == 10);
    assert(otherList.top() == 10);
    assert(L.traverse(1) == 20);
    assert(otherList.traverse(1) == 20);

    assert(L.traverse(2) == 30);
    assert(otherList.traverse(2) == 30);

    assert(L.last() == 400);
    assert(otherList.last() == 40);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    test_copy_constructor();
    test_assignment_operator();
    return 0;
}
