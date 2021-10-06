// Program to implement a stack using two queue.
#include <bits/stdc++.h>

using namespace std;

class Stack {
    queue<int> q1, q2;  // queue's q1 & q2
    int curr_size;

 public:
    Stack() { curr_size = 0; }

    void push(int x) {
        curr_size++;

        // Push x first in empty q2
        q2.push(x);

        // Push all the remaining elements in q1 to q2.
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        // swap the names of two queues
        queue<int> q = q1;
        q1 = q2;
        q2 = q;
    }

    void pop() {
        // if no elements are there in q1
        if (q1.empty())
            return;
        q1.pop();
        curr_size--;
    }

    void showQueue() {
        queue<int> temp = q1;  // clone the queue q1 in temp
        while (!temp.empty()) {
            cout << " " << temp.front();
            temp.pop();
        }
        cout << endl;
        return;
    }

    int top() {
        if (q1.empty())
            return -1;
        return q1.front();
    }

    int size() { return curr_size; }
};

int main() {
    Stack s;
    int choice, xinput;
    do {
        cout << "\nEnter Your Choice : ";
        cout << "\n1. Push";
        cout << "\n2. Pop";
        cout << "\n3. Print. \n";
        cin >> choice;  // selecting your choice
        if (choice == 1) {
            std::cout << "\nPush : ";
            std::cin >> xinput;
            s.push(xinput);  // push into the stack
            cout << "current size: " << s.size() << endl;
        } else if (choice == 2) {
            s.pop();  // pop from the stack
            cout << "current size: " << s.size() << endl;
        } else if (choice == 3) {
            s.showQueue();  // print the stack
        }
    } while (choice != 0);
    return 0;
}
