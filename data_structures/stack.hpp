/**
 * @file
 * @author danghai
 * @brief  This class specifies the basic operation on a stack as a linked list
 **/
#ifndef DATA_STRUCTURES_STACK_HPP_
#define DATA_STRUCTURES_STACK_HPP_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

/** Definition of the node as a linked-list
 * \tparam ValueType type of data nodes of the linked list should contain
 */
template <class ValueType>
struct node {
    ValueType data = {};  ///< data at current node
    std::shared_ptr<node<ValueType>> next =
        {};  ///< pointer to the next ::node instance
};

template <typename Node, typename Action>
void traverse(const std::shared_ptr<Node>& inNode, const Action& action) {
    if (inNode) {
        action(inNode);
        traverse(inNode->next, action);
    }
}

/** Definition of the stack class
 * \tparam value_type type of data nodes of the linked list in the stack should
 * contain
 */
template <class ValueType>
class stack {
 public:
    using value_type = ValueType;

    /** Show stack */
    void display() {
        std::cout << "Top --> ";
        traverse(stackTop, [](const std::shared_ptr<node<value_type>> inNode) {
            std::cout << inNode->data << "  ";
        });
        std::cout << std::endl;
        std::cout << "Size of stack: " << size << std::endl;
    }

    std::vector<value_type> toVector() const {
        std::vector<value_type> res;
        res.reserve(this->size);
        traverse(stackTop,
                 [&res](const std::shared_ptr<node<value_type>> inNode) {
                     res.push_back(inNode->data);
                 });
        return res;
    }

 public:
    /** Determine whether the stack is empty */
    bool isEmptyStack() { return (stackTop == nullptr); }

    /** Add new item to the stack */
    void push(const value_type& item) {
        auto newNode = std::make_shared<node<value_type>>();
        newNode->data = item;
        newNode->next = stackTop;
        stackTop = newNode;
        size++;
    }

    /** Return the top element of the stack */
    value_type top() const {
        assert(stackTop != nullptr);
        return stackTop->data;
    }

    /** Remove the top element of the stack */
    void pop() {
        if (!isEmptyStack()) {
            stackTop = stackTop->next;
            size--;
        } else {
            std::cout << "Stack is empty !" << std::endl;
        }
    }

    /** Clear stack */
    void clear() {
        stackTop = nullptr;
        size = 0;
    }

 private:
    std::shared_ptr<node<value_type>> stackTop =
        {};                /**< Pointer to the stack */
    std::size_t size = 0;  ///< size of stack
};

#endif  // DATA_STRUCTURES_STACK_HPP_
