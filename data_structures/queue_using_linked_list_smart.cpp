#include <iostream>
#include <memory>
using namespace std;

struct node {
    int val;
    shared_ptr<node> next;
};

shared_ptr<node> front, rear;

void Enque(int x) {
    if (rear == nullptr) {
        shared_ptr<node> n = make_shared<node>();
        n->val = x;
        n->next = nullptr;
        rear = n;
        front = n;
    }

    else {
        shared_ptr<node> n = make_shared<node>();
        n->val = x;
        n->next = nullptr;
        rear->next = n;
        rear = n;
    }
}

void Deque() {
    if (rear == nullptr && front == nullptr) {
        cout << "\nUnderflow";
    } else {
        shared_ptr<node> t = front;
        cout << "\n" << t->val << " deleted";
        front = front->next;
        // delete t;
        if (front == nullptr)
            rear = nullptr;
    }
}

void show() {
    shared_ptr<node> t = front;
    while (t != nullptr) {
        cout << t->val << "\t";
        t = t->next;
    }
}

int main() {
    int ch, x;
    do {
        cout << "\n1. Enque";
        cout << "\n2. Deque";
        cout << "\n3. Print";
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
