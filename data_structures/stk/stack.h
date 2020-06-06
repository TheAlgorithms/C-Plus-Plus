/* This class specifies the basic operation on a stack as a linked list */
#ifndef DATA_STRUCTURES_STK_STACK_H_
#define DATA_STRUCTURES_STK_STACK_H_

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
    void display();       /* Show stack */
    stack();              /* Default constructor*/
    ~stack();             /* Destructor */
    bool isEmptyStack();  /* Determine whether the stack is empty */
    void push(Type item); /* Add new item to the stack */
    Type top();           /* Return the top element of the stack */
    void pop();           /* Remove the top element of the stack */
    void clear();

    stack<Type> &operator=(const stack<Type> &otherStack);
    // Overload "=" the assignment operator.
 private:
    node<Type> *stackTop; /* Pointer to the stack */
    int size;
};

#endif  // DATA_STRUCTURES_STK_STACK_H_
