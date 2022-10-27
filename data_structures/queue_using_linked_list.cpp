#include <iostream>
using namespace std;

struct node {
    int val;
    node *next;
};

node *front, *rear;

void Enque(int x) {
    if (rear == NULL) {  // check if queueis empty
        node *n = new node;
        n->val = x;
        n->next = NULL;
        rear = n;
        front = n;  // front and rear pointer assigned to only queue element
    }

    else {
        node *n = new node;
        n->val = x;
        n->next = NULL;
        rear->next = n;  // adds node to rear of the queue
        rear = n;  // shifts pointer so that it points towards newly added last
                   // element
    }
}

void Deque() {
    if (rear == NULL && front == NULL) {  // checks if queue is empty
        cout << "\nUnderflow";
    } else {
        node *t = front;
        cout << "\n" << t->val << " deleted";
        front = front->next;  // shifts front pointer as first element has to be
                              // deleted
        delete t;
        if (front == NULL)  // checks if the deletion makes queue empty
            rear = NULL;    // initialises rear as null when queue has been
                            // emptied
    }
}

void show() {
    node *t = front;
    while (t != NULL) {
        cout << t->val << "\t";  // displays all elements till last
        t = t->next;             // element of queue is displayed
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
