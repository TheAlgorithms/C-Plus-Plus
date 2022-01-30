#include <time.h>

#include <iostream>
#include <stack>
using namespace std;

struct node {
    int val;
    node *next;
};

node *front, *rear;
int count;

void Enque(int x) {
    if (rear == NULL) {
        node *n = new node;
        n->val = x;
        n->next = NULL;
        rear = n;
        front = n;
    }

    else {
        node *n = new node;
        n->val = x;
        n->next = NULL;
        rear->next = n;
        rear = n;
    }

    count++;
}

void Deque(bool print) {
    if (rear == NULL && front == NULL) {
        cout << "\nUnderflow";
    } else {
        count--;
        node *t = front;
        if (print) {
            cout << "\n" << t->val << " deleted";
        }
        front = front->next;
        delete t;
        if (front == NULL)
            rear = NULL;
    }
}

void show() {
    node *t = front;
    while (t != NULL) {
        cout << t->val << "\t";
        t = t->next;
    }
}

static void Reverse1() {
    stack<int> s;
    while (count != 0) {
        int x = front->val;
        s.push(x);
        Deque(false);
    }
    while (!s.empty()) {
        int x = s.top();
        Enque(x);
        s.pop();
    }
}

static void Reverse2() {
    if (count == 0) {
        return;
    }

    int x = front->val;
    Deque(false);

    Reverse2();

    Enque(x);
}

int main() {
    int ch, x;
    clock_t t;
    do {
        cout << "\n1. Enque";
        cout << "\n2. Deque";
        cout << "\n3. Print";
        cout << "\n4. Reverse with stack";
        cout << "\n5. Reverse with recursion";
        cout << "\nEnter Your Choice : ";
        cin >> ch;
        if (ch == 1) {
            cout << "\nInsert : ";
            cin >> x;
            Enque(x);
        } else if (ch == 2) {
            Deque(true);
            cout << "\n";
        } else if (ch == 3) {
            show();
        } else if (ch == 4) {
            t = clock();
            Reverse1();
            t = clock() - t;
            show();
            cout << "\nThis took " << t << " units of time.\n";
        } else if (ch == 5) {
            t = clock();
            Reverse2();
            t = clock() - t;
            show();
            cout << "\nThis took " << t << " units of time.\n";
        }

    } while (ch != 0);

    return 0;
}
