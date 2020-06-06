#include "./stack.h"

#include <cassert>
#include <iostream>

/* Default constructor*/
template <class Type>
stack<Type>::stack() {
    stackTop = NULL;
    size = 0;
}

/* Destructor */
template <class Type>
stack<Type>::~stack() {}

/* Display for testing */
template <class Type>
void stack<Type>::display() {
    node<Type> *current = stackTop;
    std::cout << "Top --> ";
    while (current != NULL) {
        std::cout << current->data << "  ";
        current = current->next;
    }
    std::cout << std::endl;
    std::cout << "Size of stack: " << size << std::endl;
}

/* Determine whether the stack is empty */
template <class Type>
bool stack<Type>::isEmptyStack() {
    return (stackTop == NULL);
}

/* Clear stack */
template <class Type>
void stack<Type>::clear() {
    stackTop = NULL;
}

/* Add new item to the stack */
template <class Type>
void stack<Type>::push(Type item) {
    node<Type> *newNode;
    newNode = new node<Type>;
    newNode->data = item;
    newNode->next = stackTop;
    stackTop = newNode;
    size++;
}

/* Return the top element of the stack */
template <class Type>
Type stack<Type>::top() {
    assert(stackTop != NULL);
    return stackTop->data;
}

/* Remove the top element of the stack */
template <class Type>
void stack<Type>::pop() {
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

/* Operator "=" */
template <class Type>
stack<Type> &stack<Type>::operator=(const stack<Type> &otherStack) {
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

#include <string>
/** force instantiate to export the type class */
template class stack<std::string>;
template class stack<int>;
