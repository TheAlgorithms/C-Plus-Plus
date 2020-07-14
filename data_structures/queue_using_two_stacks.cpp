/*
    Implementation of a Queue using two Stacks.

    Functions:
        Push  -> Inserts element to the end of the queue
        Pop   -> Removes element from the front
        Peek  -> Returns element from the front (no removing)
        Empty -> Checks whether the queue is empty
*/

#include <iostream>

#include "./stack.h"

class MyQueue {
 private:
    stack<int> s1, s2;

    /** Helper function for rearranging elements in stacks */
    void rearrange();

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
};

/**
 * Appends element to the end of the queue
 */
void MyQueue::push(int x) { s1.push(x); }

/**
 * Removes element from the front of the queue
 */
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

/**
 * Helper function for rearranging elements from
 * one stack into another.
 */
void MyQueue::rearrange() {
    if (s2.isEmptyStack()) {
        while (!s1.isEmptyStack()) {
            int temp = s1.top();
            s1.pop();
            s2.push(temp);
        }
    }
}

/**
 * Returns element in the front.
 * Does not remove it.
 */
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

/**
 * Checks whether a queue is empty
 */
bool MyQueue::empty() { return s2.isEmptyStack() && s1.isEmptyStack(); }

/**
 * Main function
 */
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
