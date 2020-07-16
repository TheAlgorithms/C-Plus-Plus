/**
 * @author [shoniavika](https://github.com/shoniavika)
 * @file
 *
 * Implementation of a Queue using two Stacks.
 */

#include <cassert>
#include <iostream>

#include "./stack.h"

/**
 * @brief Queue data structure. Stores elements in FIFO
 * (first-in-first-out) manner.
 * @tparam T datatype to store in the queue
 */
template <typename T>
class MyQueue {
 private:
    stack<T> s1, s2;

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
    void push(T x);

    /**
     * Removes an element from the front of the queue.
     */
    T pop();

    /**
     * Returns first element, without removing it.
     */
    T peek();

    /**
     * Returns whether the queue is empty.
     */
    bool empty();
};

/**
 * Appends element to the end of the queue
 */
template <typename T>
void MyQueue<T>::push(T x) {
    s1.push(x);
}

/**
 * Removes element from the front of the queue
 */
template <typename T>
T MyQueue<T>::pop() {
    rearrange();
    T temp = 0;
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
template <typename T>
void MyQueue<T>::rearrange() {
    if (s2.isEmptyStack()) {
        while (!s1.isEmptyStack()) {
            T temp = s1.top();
            s1.pop();
            s2.push(temp);
        }
    }
}

/**
 * Returns element in the front.
 * Does not remove it.
 */
template <typename T>
T MyQueue<T>::peek() {
    rearrange();
    T temp = 0;
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
template <typename T>
bool MyQueue<T>::empty() {
    return s2.isEmptyStack() && s1.isEmptyStack();
}

/**
 * Testing function
 */
void queue_test() {
    MyQueue<int> que;
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

    MyQueue<double> que2;
    std::cout << "Test #3\n";
    que2.push(2.31223);
    que2.push(3.1415926);
    que2.push(2.92);
    assert(que2.peek() == 2.31223);
    assert(que2.pop() == 2.31223);
    assert(que2.peek() == 3.1415926);
    assert(que2.pop() == 3.1415926);
    assert(que2.peek() == 2.92);
    assert(que2.pop() == 2.92);
    std::cout << "PASSED\n";
}

/**
 * Main function, calls testing function
 */
int main() {
    queue_test();
    return 0;
}
