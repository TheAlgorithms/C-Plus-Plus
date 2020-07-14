#include <iostream>

#include "./stack.h"

#define MAX 100

class MyQueue {
 private:
    stack<int> s1, s2;

 public:
    /** Initializes queue. */
    MyQueue() = default;

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
        std::cout << "Queue is empty" << std::endl;
    }
    return temp;
}

void MyQueue::rearrange() {
    if (s2.isEmptyStack()) {
        while (!s1.isEmptyStack()) {
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
        std::cout << "Queue is empty" << std::endl;
    }
    return temp;
}

bool MyQueue::empty() { return s2.isEmptyStack() && s1.isEmptyStack(); }

int main() {
    // Test queue functionality
    MyQueue que;

    que.pop();
    que.peek();

    que.push(2);
    que.push(5);
    que.push(0);
    que.push(4);
    que.push(9);

    while (!que.empty()) {
        std::cout << que.peek() << std::endl;
        std::cout << que.pop() << std::endl;
    }

    return 0;
}