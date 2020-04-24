#include <iostream>
#include <assert.h>
#include "stack.h"

using namespace std;

/* Default constructor*/
template <class Type>
stack<Type>::stack()
{
    stackTop = NULL;
    size = 0;
}

/* Destructor */
template <class Type>
stack<Type>::~stack()
{
}

/* Display for testing */
template <class Type>
void stack<Type>::display()
{
    node<Type> *current = stackTop;
    cout << "Top --> ";
    while(current != NULL) {
        cout<<current->data<< "  ";
        current = current -> next;
    }
    cout <<endl;
    cout << "Size of stack: " << size << endl;
}

/* Determine whether the stack is empty */
template <class Type>
bool stack<Type>::isEmptyStack()
{
    return (stackTop == NULL);
}

/* Clear stack */
template <class Type>
void stack<Type>::clear()
{
    stackTop = NULL;
}

/* Add new item to the stack */
template <class Type>
void stack<Type>::push(Type item)
{
    node<Type> *newNode;
    newNode = new node<Type>;
    newNode->data = item;
    newNode->next = stackTop;
    stackTop = newNode;
    size++;
}

/* Return the top element of the stack */
template <class Type>
Type stack<Type>::top()
{
    assert(stackTop != NULL);
    return stackTop->data;
}

/* Remove the top element of the stack */
template <class Type>
void stack<Type>::pop()
{
    node<Type> *temp;
    if(!isEmptyStack()) {
        temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
        size--;
    } else {
        cout << "Stack is empty !" << endl;
    }
}

/* Operator "=" */
template <class Type>
stack<Type> stack<Type>::operator=(stack<Type> & otherStack)
{
    node<Type> *newNode, *current, *last;

    if (stackTop != NULL) /* If stack is no empty, make it empty */
        stackTop = NULL;
    if (otherStack.stackTop == NULL)
        stackTop = NULL;
    else {
        current = otherStack.stackTop;
        stackTop = new node<Type>;
        stackTop->data = current->data;
        stackTop->next = NULL;
        last = stackTop;
        current = current ->next;
        /* Copy the remaining stack */
        while (current != NULL)
        {
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
