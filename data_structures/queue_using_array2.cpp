#include <iostream>
using namespace std;

int arrayQueue[10];
int front = 0;
int rear = 0;

void Enque(int x) {
    if (rear == 10) {
        cout << "\nOverflow";
    } else {
        arrayQueue[rear++] = x;
    }
}

void Deque() {
    if (front == rear) {
        cout << "\nUnderflow";
    }

    else {
        cout << "\n" << arrayQueue[front++] << " deleted";
        for (int i = front; i < rear; i++) {
            arrayQueue[i - front] = arrayQueue[i];
        }
        rear = rear - front;
        front = 0;
    }
}

void show() {
	cout<<"\nQueue: ";
    for (int i = front; i < rear; i++) {
        cout << arrayQueue[i] << "\t";
    }
    cout<<"\n";
}

int main() {
    int ch, x;
    do {
        cout << "\n1. Enque  \t\t\t  0. Exit";
        cout << "\n2. Deque";
        cout << "\n3. Print";
        //cout << "\n0. Exit";
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
        } 
    } while (ch != 0);

    return 0;
}
