#include <iostream>  //for io operations

struct node {
    int val;  // node of linked list declared
    node *next;
};

node *top_var;  // initialises top of the stack

void push(int x) {
    node *n = new node;
    n->val = x;         // initialises the input value of the new node as x
    n->next = top_var;  // passes the next pointer to top of stack
    top_var = n;        // top now points to the new node created
}

void pop() {
    if (top_var == nullptr) {  // checks for empty stack
        std::cout << "\nUnderflow";
    } else {
        node *t = top_var;  // points to top element to store deletion
        std::cout << "\n" << t->val << " deleted";  // outputs element deleted
        top_var = top_var->next;  // moves top pointer to next element
        delete t;                 // deletes top element
    }
}

void show() {
    node *t = top_var;
    while (t != nullptr) {
        std::cout << t->val << "\n";
        t = t->next;  // shifts pointer till stack bottom is reached
    }
}

int main() {
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
                push(x);
                break;
            case 2:
                pop();
                break;
            case 3:
                show();
                break;
            default:
                std::cout << "Invalid option!\n";
                break;
        }
    } while (ch != 0);

    return 0;
}
