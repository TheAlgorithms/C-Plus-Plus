/**
 * @file
 * @author danghai
 * @author [Piotr Idzik](https://github.com/vil02)
 * @brief  This class specifies the basic operation on a stack as a linked list
 **/
#ifndef DATA_STRUCTURES_STACK_HPP_
#define DATA_STRUCTURES_STACK_HPP_

#include <stdexcept>  /// for std::invalid_argument

#include "node.hpp"  /// for Node

/** Definition of the stack class
 * \tparam value_type type of data nodes of the linked list in the stack should
 * contain
 */
template <class ValueType>
class stack {
 public:
    using value_type = ValueType;

    /** Show stack */
    void display() const {
        std::cout << "Top --> ";
        display_all(this->stackTop.get());
        std::cout << '\n';
        std::cout << "Size of stack: " << size << std::endl;
    }

    std::vector<value_type> toVector() const {
        return push_all_to_vector(this->stackTop.get(), this->size);
    }

 private:
    void ensureNotEmpty() const {
        if (isEmptyStack()) {
            throw std::invalid_argument("Stack is empty.");
        }
    }

 public:
    /** Determine whether the stack is empty */
    bool isEmptyStack() const { return (stackTop == nullptr); }

    /** Add new item to the stack */
    void push(const value_type& item) {
        auto newNode = std::make_shared<Node<value_type>>();
        newNode->data = item;
        newNode->next = stackTop;
        stackTop = newNode;
        size++;
    }

    /** Return the top element of the stack */
    value_type top() const {
        ensureNotEmpty();
        return stackTop->data;
    }

    /** Remove the top element of the stack */
    void pop() {
        ensureNotEmpty();
        stackTop = stackTop->next;
        size--;
    }

    /** Clear stack */
    void clear() {
        stackTop = nullptr;
        size = 0;
    }

 private:
    std::shared_ptr<Node<value_type>> stackTop =
        {};                /**< Pointer to the stack */
    std::size_t size = 0;  ///< size of stack
};

#endif  // DATA_STRUCTURES_STACK_HPP_
