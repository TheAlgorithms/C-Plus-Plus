#include <iostream>

struct node {
    int val;
    node *next;
};

node *stack_idx;

void push(int x) {
    node *n = new node;
    n->val = x;
    n->next = stack_idx;
    stack_idx = n;
}

void pop() {
    if (stack_idx == NULL) {
        std::cout << "\nUnderflow";
    } else {
        node *t = stack_idx;
        std::cout << "\n" << t->val << " deleted";
        stack_idx = stack_idx->next;
        delete t;
    }
}

void show() {
    node *t = stack_idx;
    while (t != NULL) {
        std::cout << t->val << "\n";
        t = t->next;
    }
}

int main() {
    int ch, x;
    do {
        std::cout << "\n1. Push";
        std::cout << "\n2. Pop";
        std::cout << "\n3. Print";
        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        if (ch == 1) {
            std::cout << "\nInsert : ";
            std::cin >> x;
            push(x);
        } else if (ch == 2) {
            pop();
        } else if (ch == 3) {
            show();
        }
    } while (ch != 0);

    return 0;
}
