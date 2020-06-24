#include <iostream>

struct node {
    int val;
    node *next;
};

node *top;

void push(int x) {
    node *n = new node;
    n->val = x;
    n->next = top;
    top = n;
}

void pop() {
    if (top == nullptr) {
        std::cout << "\nUnderflow";
    } else {
        node *t = top;
        std::cout << "\n" << t->val << " deleted";
        top = top->next;
        delete t;
    }
}

void show() {
    node *t = top;
    while (t != nullptr) {
        std::cout << t->val << "\n";
        t = t->next;
    }
}

int main() {
    int ch, x;
    do {
        std::cout << "\n0. Exit";
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
