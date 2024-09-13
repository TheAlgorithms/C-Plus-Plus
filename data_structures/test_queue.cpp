#include <cassert>   /// for assert
#include <iostream>  /// for std::cout

#include "./queue.hpp"

template <typename T>
void testConstructedQueueIsEmpty() {
    const queue<T> curQueue;
    assert(curQueue.isEmptyQueue());
}

void testEnQueue() {
    queue<int> curQueue;
    curQueue.enQueue(10);
    assert(curQueue.toVector() == std::vector<int>({10}));
    curQueue.enQueue(20);
    assert(curQueue.toVector() == std::vector<int>({10, 20}));
    curQueue.enQueue(30);
    curQueue.enQueue(40);
    assert(curQueue.toVector() == std::vector<int>({10, 20, 30, 40}));
}

void testDeQueue() {
    queue<int> curQueue;
    curQueue.enQueue(10);
    curQueue.enQueue(20);
    curQueue.enQueue(30);

    curQueue.deQueue();
    assert(curQueue.toVector() == std::vector<int>({20, 30}));

    curQueue.deQueue();
    assert(curQueue.toVector() == std::vector<int>({30}));

    curQueue.deQueue();
    assert(curQueue.isEmptyQueue());
}

void testFront() {
    queue<int> curQueue;
    curQueue.enQueue(10);
    assert(curQueue.front() == 10);
    curQueue.enQueue(20);
    assert(curQueue.front() == 10);
}

void testQueueAfterClearIsEmpty() {
    queue<int> curQueue;
    curQueue.enQueue(10);
    curQueue.enQueue(20);
    curQueue.enQueue(30);
    curQueue.clear();
    assert(curQueue.isEmptyQueue());
}

void testFrontThrowsAnInvalidArgumentWhenQueueEmpty() {
    const queue<int> curQueue;
    bool wasException = false;
    try {
        curQueue.front();
    } catch (const std::invalid_argument&) {
        wasException = true;
    }
    assert(wasException);
}

void testDeQueueThrowsAnInvalidArgumentWhenQueueEmpty() {
    queue<int> curQueue;
    bool wasException = false;
    try {
        curQueue.deQueue();
    } catch (const std::invalid_argument&) {
        wasException = true;
    }
    assert(wasException);
}

int main() {
    testConstructedQueueIsEmpty<int>();
    testConstructedQueueIsEmpty<double>();
    testConstructedQueueIsEmpty<std::vector<long double>>();

    testEnQueue();
    testDeQueue();

    testQueueAfterClearIsEmpty();

    testFrontThrowsAnInvalidArgumentWhenQueueEmpty();
    testDeQueueThrowsAnInvalidArgumentWhenQueueEmpty();

    std::cout << "All tests pass!\n";
    return 0;
}
