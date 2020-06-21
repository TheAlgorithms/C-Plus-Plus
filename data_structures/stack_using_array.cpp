#include <iostream>

int *stack;
int top = 0, stack_size;

void push(int x) {
    if (top == stack_size) {
        std::cout << "\nOverflow";
    } else {
        stack[top++] = x;
    }
}

void pop() {
    if (top == 0) {
        std::cout << "\nUnderflow";
    } else {
        std::cout << "\n" << stack[--top] << " deleted";
    }
}

void show() {
    for (int i = 0; i < top; i++) {
        std::cout << stack[i] << "\n";
    }
}

void topmost() { std::cout << "\nTopmost element: " << stack[top - 1]; }
int main() {
    std::cout << "\nEnter stack_size of stack : ";
    std::cin >> stack_size;
    stack = new int[stack_size];
    int ch, x;
    do {
        std::cout << "\n1. Push";
        std::cout << "\n2. Pop";
        std::cout << "\n3. Print";
        std::cout << "\n4. Print topmost element:";
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
        } else if (ch == 4) {
            topmost();
        }
    } while (ch != 0);

    return 0;
}
