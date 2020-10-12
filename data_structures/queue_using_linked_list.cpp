#include <iostream>

struct node {
    int val;
    node *next;
};

node *front, *rear;

void Enque(int x) {
    if (rear == nullptr) {
        node *n = new node;
        n->val = x;
        n->next = nullptr;
        rear = n;
        front = n;
    }

    else {
        node *n = new node;
        n->val = x;
        n->next = nullptr;
        rear->next = n;
        rear = n;
    }
}

void Deque() {
    if (rear == nullptr && front == nullptr) {
        std::cout << "\nUnderflow";
    } else {
        node *t = front;
        std::cout << "\n" << t->val << " deleted";
        front = front->next;
        delete t;
        if (front == nullptr)
            rear = nullptr;
    }
}

void show() {
    node *t = front;
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}

int main() {
    int ch, x;
    do {
        std::cout << "\n1. Enque";
        std::cout << "\n2. Deque";
        std::cout << "\n3. Print";
        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        if (ch == 1) {
            std::cout << "\nInsert : ";
            std::cin >> x;
            Enque(x);
        } else if (ch == 2) {
            Deque();
        } else if (ch == 3) {
            show();
        }
    } while (ch != 0);

    return 0;
}
