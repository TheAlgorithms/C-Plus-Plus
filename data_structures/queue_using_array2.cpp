#include <iostream>
using namespace std;

#define SIZE 10
int queue[SIZE];
int front = 0, rear = 0;

void Enque(int x) {
    if (rear == SIZE) {
        cout << "\nOverflow";
    } else {
        queue[rear++] = x;
    }
}

void Deque() {
    if (front == rear) {
        cout << "\nUnderflow";
    } else {
        cout << "\n" << queue[front] << " deleted";
        front++;  // Just move the front pointer

        // Reset when queue becomes empty
        if (front == rear) {
            front = 0;
            rear = 0;
        }
    }
}

void show() {
    if (front == rear) {
        cout << "\nQueue is empty!";
        return;
    }
    for (int i = front; i < rear; i++) {
        cout << queue[i] << "\t";
    }
}

int main() {
    int ch, x;
    do {
        cout << "\n\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Print";
        cout << "\n0. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "\nInsert: ";
                cin >> x;
                Enque(x);
                break;
            case 2:
                Deque();
                break;
            case 3:
                show();
                break;
            case 0:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nInvalid choice!";
        }
    } while (ch != 0);

    return 0;
}
