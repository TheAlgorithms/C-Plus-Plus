/* This class specifies the basic operation on a stack as a linked list */
#ifndef DATA_STRUCTURES_STACK_H_
#define DATA_STRUCTURES_STACK_H_

#include <cassert>
#include <iostream>

/* Definition of the node */
template <class Type>
struct node {
    Type data;
    node<Type> *next;
};

/* Definition of the stack class */
template <class Type>
class stack {
 public:
    /** Show stack */
    void display() {
        node<Type> *current = stackTop;
        std::cout << "Top --> ";
        while (current != NULL) {
            std::cout << current->data << "  ";
            current = current->next;
        }
        std::cout << std::endl;
        std::cout << "Size of stack: " << size << std::endl;
    }

    /** Default constructor*/
    stack() {
        stackTop = NULL;
        size = 0;
    }

    /** Destructor */
    ~stack() {}

    /** Determine whether the stack is empty */
    bool isEmptyStack() { return (stackTop == NULL); };

    /** Add new item to the stack */
    void push(Type item) {
        node<Type> *newNode;
        newNode = new node<Type>;
        newNode->data = item;
        newNode->next = stackTop;
        stackTop = newNode;
        size++;
    }

    /** Return the top element of the stack */
    Type top() {
        assert(stackTop != NULL);
        return stackTop->data;
    }

    /** Remove the top element of the stack */
    void pop() {
        node<Type> *temp;
        if (!isEmptyStack()) {
            temp = stackTop;
            stackTop = stackTop->next;
            delete temp;
            size--;
        } else {
            std::cout << "Stack is empty !" << std::endl;
        }
    }

    /** Clear stack */
    void clear() { stackTop = NULL; }

    /** Overload "=" the assignment operator */
    stack<Type> &operator=(const stack<Type> &otherStack) {
        node<Type> *newNode, *current, *last;

        /* If stack is no empty, make it empty */
        if (stackTop != NULL) {
            stackTop = NULL;
        }
        if (otherStack.stackTop == NULL) {
            stackTop = NULL;
        } else {
            current = otherStack.stackTop;
            stackTop = new node<Type>;
            stackTop->data = current->data;
            stackTop->next = NULL;
            last = stackTop;
            current = current->next;
            /* Copy the remaining stack */
            while (current != NULL) {
                newNode = new node<Type>;
                newNode->data = current->data;
                newNode->next = NULL;
                last->next = newNode;
                last = newNode;
                current = current->next;
            }
        }
        size = otherStack.size;
        return *this;
    }

 private:
    node<Type> *stackTop; /**< Pointer to the stack */
    int size;
};

#endif  // DATA_STRUCTURES_STACK_H_
