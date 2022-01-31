#include <iostream>
using namespace std;

int queue[10];
int front = 0;
int rear = 0;

void Enque(int x) {
    if (rear == 10) {
        cout << "\nOverflow";
    } else {
        queue[rear++] = x;
    }
}

void Deque() {
    if (front == rear) {
        cout << "\nUnderflow";
    }

    else {
        cout << "\n" << queue[front++] << " deleted";
        for (int i = front; i < rear; i++) {
            queue[i - front] = queue[i];
        }
        rear = rear - front;
        front = 0;
    }
}

void show() {
    for (int i = front; i < rear; i++) {
        cout << queue[i] << "\t";
    }
}

void reverse() {
    if (front == rear){
        cout << "\n Underflow";
    }else {
        for (int i = front; i <= rear / 2 - 1; i++) {
            int temp = queue[i];
            queue[i] = queue[rear - i - 1];
            queue[rear - i - 1] = temp;
        }
    }
}

int main() {
    int ch, x;
    do {
        cout << "\n1. Enque";
        cout << "\n2. Deque";
        cout << "\n3. Print";
        cout << "\n4. Reverse";
        cout << "\nEnter Your Choice : ";
        cin >> ch;
        if (ch == 1) {
            cout << "\nInsert : ";
            cin >> x;
            Enque(x);
        } else if (ch == 2) {
            Deque();
        } else if (ch == 3) {
            show();
        } else if (ch == 4) {
            reverse();
        }
    } while (ch != 0);

    return 0;
}
