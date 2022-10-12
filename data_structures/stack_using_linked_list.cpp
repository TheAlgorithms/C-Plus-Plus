#include <iostream>

struct node {
    int val;
    node *next;
};

node *top_var;

void push(int x) {
    node *n = new node;
    n->val = x;
    n->next = top_var;
    top_var = n;
}

void pop() {
    if (top_var == nullptr) {
        std::cout << "\nUnderflow";
    } else {
        node *t = top_var;
        std::cout << "\n" << t->val << " deleted";
        top_var = top_var->next;
        delete t;
    }
}

void show() {
    node *t = top_var;
    while (t != nullptr) {
        std::cout << t->val << "\n";
        t = t->next;
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
