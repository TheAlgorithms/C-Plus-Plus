#include <iostream>

int queue[10];
int front = 0;
int rear = 0;

void Enque(int x) {
    if (rear == 10) {
        std::cout << "\nOverflow";
    } else {
        queue[rear++] = x;
    }
}

void Deque() {
    if (front == rear) {
        std::cout << "\nUnderflow";

    } else {
        std::cout << "\n" << queue[front++] << " deleted";
        for (int i = front; i < rear; i++) {
            queue[i - front] = queue[i];
        }
        rear = rear - front;
        front = 0;
    }
}

void show() {
    for (int i = front; i < rear; i++) {
        std::cout << queue[i] << "\t";
    }
}

int main() {
    int ch, x;
    do {
        std::cout << "\n0. Exit";
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
