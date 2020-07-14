#include <bits/stdc++.h>

#include <iostream>
using namespace std;

class MyQueue {
 private:
    stack<int> s1, s2;

 public:
    /** Initializes queue. */
    MyQueue(){};

    /** Pushes x to the back of queue. */
    void push(int x);

    /** Removes an element from the front of the queue. */
    int pop();

    /** Returns first element, without removing it. */
    int peek();

    /** Returns whether the queue is empty. */
    bool empty();

    void rearrange();
};

void MyQueue::push(int x) { s1.push(x); }

int MyQueue::pop() {
    rearrange();
    int temp = 0;
    if (!empty()) {
        temp = s2.top();
        s2.pop();
    } else {
        cout << "Queue is empty" << endl;
    }
    return temp;
}

void MyQueue::rearrange() {
    if (s2.empty()) {
        while (!s1.empty()) {
            int temp = s1.top();
            s1.pop();
            s2.push(temp);
        }
    }
}

int MyQueue::peek() {
    rearrange();
    int temp = 0;
    if (!empty()) {
        temp = s2.top();
    } else {
        cout << "Queue is empty" << endl;
    }
    return temp;
}

bool MyQueue::empty() { return s2.empty() && s1.empty(); }

int main() {
    MyQueue que;

    que.pop();
    que.peek();

    que.push(2);
    que.push(5);
    que.push(0);
    que.push(4);
    que.push(9);

    while (!que.empty()) {
        cout << que.peek() << endl;
        cout << que.pop() << endl;
    }

    return 0;
}