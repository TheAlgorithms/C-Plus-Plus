/**
 * @file
 * @brief Implementation of a
 * [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) using a
 * singly linked list with proper OOPS encapsulation.
 */

#include <cassert>    /// for assert
#include <iostream>   /// for std::cout and std::cin
#include <stdexcept>  /// for std::underflow_error

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {

/**
 * @brief Node structure for the linked list
 */
struct Node {
    int val;
    Node* next;

    explicit Node(int value, Node* next_node = nullptr)
        : val(value), next(next_node) {}
};

/**
 * @brief Stack class implemented using a singly linked list
 */
class LinkedStack {
 private:
    Node* top_var;  ///< Pointer to the top node of the stack

 public:
    /**
     * @brief Default constructor initializing an empty stack
     */
    LinkedStack() : top_var(nullptr) {}

    /**
     * @brief Destructor to free all dynamically allocated nodes
     */
    ~LinkedStack() {
        while (!isEmpty()) {
            Node* temp = top_var;
            top_var = top_var->next;
            delete temp;
        }
    }

    /**
     * @brief Check if the stack is empty
     * @returns true if stack has no elements, false otherwise
     */
    bool isEmpty() const { return top_var == nullptr; }

    /**
     * @brief Push an element onto the top of the stack
     * @param x value to insert
     */
    void push(int x) {
        Node* n = new Node(x, top_var);
        top_var = n;
    }

    /**
     * @brief Pop the top element from the stack
     */
    void pop() {
        if (isEmpty()) {
            std::cout << "\nUnderflow";
            return;
        }
        Node* t = top_var;
        std::cout << "\n" << t->val << " deleted";
        top_var = top_var->next;
        delete t;
    }

    /**
     * @brief Return the top element without removing it
     * @returns value at the top of the stack
     */
    int peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return top_var->val;
    }

    /**
     * @brief Display all elements in the stack from top to bottom
     */
    void show() const {
        Node* t = top_var;
        while (t != nullptr) {
            std::cout << t->val << "\n";
            t = t->next;
        }
    }
};

}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    data_structures::LinkedStack s;
    assert(s.isEmpty());

    s.push(10);
    s.push(20);
    s.push(30);
    assert(!s.isEmpty());
    assert(s.peek() == 30);

    s.pop();
    assert(s.peek() == 20);

    s.pop();
    s.pop();
    assert(s.isEmpty());
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run automated self-tests

    data_structures::LinkedStack stack;
    int ch = 0, x = 0;
    do {
        std::cout << "\n0. Exit or Ctrl+C";
        std::cout << "\n1. Push";
        std::cout << "\n2. Pop";
        std::cout << "\n3. Print";
        std::cout << "\nEnter Your Choice: ";
        std::cin >> ch;
        switch (ch) {
            case 0:
                break;
            case 1:
                std::cout << "\nInsert : ";
                std::cin >> x;
                stack.push(x);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                stack.show();
                break;
            default:
                std::cout << "Invalid option!\n";
                break;
        }
    } while (ch != 0);

    return 0;
}