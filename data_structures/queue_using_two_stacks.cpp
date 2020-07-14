/**
 * @author [shoniavika](https://github.com/shoniavika)
 * @file
 *
 * Implementation of a Queue using two Stacks.
 */

#include <cassert>
#include <iostream>

#include "./stack.h"

class MyQueue {
 private:
    stack<int> s1, s2;

    /**
     * Helper function for rearranging elements in stacks
     */
    void rearrange();

 public:
    /**
     * Constructor for queue.
     */
    MyQueue() = default;

    /**
     * Pushes x to the back of queue.
     */
    void push(int x);

    /**
     * Removes an element from the front of the queue.
     */
    int pop();

    /**
     * Returns first element, without removing it.
     */
    int peek();

    /**
     * Returns whether the queue is empty.
     */
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
 * Testing function
 */
void queue_test() {
    MyQueue que;
    std::cout << "Test #1\n";
    que.push(2);
    que.push(5);
    que.push(0);
    assert(que.peek() == 2);
    assert(que.pop() == 2);
    assert(que.peek() == 5);
    assert(que.pop() == 5);
    assert(que.peek() == 0);
    assert(que.pop() == 0);
    assert(que.empty() == true);
    std::cout << "PASSED\n";

    std::cout << "Test #2\n";
    que.push(-1);
    assert(que.empty() == false);
    assert(que.peek() == -1);
    assert(que.pop() == -1);
    std::cout << "PASSED\n";
}

/**
 * Main function, calls testing function
 */
int main() {
    queue_test();
    return 0;
}
