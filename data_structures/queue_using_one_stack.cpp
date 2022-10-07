/*
  @author [Rajat Garg](https://github.com/Rajat379)
  @file

  Implementation of a Queue using one Stack.
*/

#include <cassert>
#include <iostream>
#include <stack>

namespace {
/**
 * @brief Queue data structure. Stores elements in FIFO
 * (first-in-first-out) manner.
 * @tparam T datatype to store in the queue
 */
template <typename T>
class QueueWithStack {
 private:
    std::stack<T> stackQueue;

 public:
    /*
      Constructor for queue.
     */
    QueueWithStack() = default;

    /*
      Pushes x to the back of queue.
    */
    void enqueue(T x);

    /*
      Removes an element from the front of the queue.
    */
    T dequeue();

    /*
      Returns whether the queue is empty.
    */
    bool empty() const;
};

/*
  Appends element to the end of the queue
*/
template <typename T>
void QueueWithStack<T>::enqueue(T x) {
    stackQueue.push(x);
}

/*
  Removes element from the front of the queue
*/
template <typename T>
T QueueWithStack<T>::dequeue() {
    if (!stackQueue.empty()) {
        T popNum = stackQueue.top();
        stackQueue.pop();

        if (stackQueue.empty()) {
            return popNum;
        }

        //	Recursive call
        T tempItem = dequeue();

        //	Push popped item back in the stack
        stackQueue.push(popNum);

        //	Return the recursive call
        return tempItem;
    }
}

/*
  Checks whether a queue is empty
*/
template <typename T>
bool QueueWithStack<T>::empty() const {
    return stackQueue.empty();
}
}  // namespace

/*
  Testing function
*/
void queue_test() {
    QueueWithStack<int> q1;
    std::cout << "Test #1\n";
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    assert(q1.dequeue() == 1);
    assert(q1.dequeue() == 2);
    assert(q1.dequeue() == 3);
    assert(q1.empty() == true);

    std::cout << "PASSED\n";

    std::cout << "Test #2\n";
    QueueWithStack<double> q2;
    q2.enqueue(2.31223);
    q2.enqueue(3.1415926);
    q2.enqueue(2.92);

    assert(q2.empty() == false);
    assert(q2.dequeue() == 2.31223);
    assert(q2.dequeue() == 3.1415926);
    assert(q2.dequeue() == 2.92);
    assert(q2.empty() == true);
    std::cout << "PASSED\n";
}

/*
   Main function, calls testing function
 */
int main() {
    queue_test();
    return 0;
}