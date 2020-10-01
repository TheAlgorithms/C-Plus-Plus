/**
 * @file
 * @brief Perform Minheap and Maxheap using priority queue
 * @details
 * In competitive coding I have used this datastructure a lot for Minheap and
 * Maxheap operations, it is very useful and timecomplexity is equivalent to
 * minheap and maxheap. http://www.cplusplus.com/reference/queue/priority_queue/
 * @author [Shubham Singhal](https://github.com/singhalshubham8)
 * @see heap_using_priority_queue.cpp
 */

#include <cassert>
#include <iostream>
#include <queue>

/** Test function */
static void test() {
    // Adding elements into priority queue which is eventaully maxHeap
    std::priority_queue<int> maxheap;
    maxheap.push(3);
    maxheap.push(1);
    maxheap.push(5);
    maxheap.push(2);
    assert(maxheap.size() == (size_t)4);

    // Checking max element in priority queue removing each element in one time
    assert(maxheap.top() == 5);
    maxheap.pop();
    assert(maxheap.top() == 3);
    maxheap.pop();
    assert(maxheap.top() == 2);
    maxheap.pop();
    assert(maxheap.top() == 1);
    maxheap.pop();
    assert(maxheap.empty());

    // Creating a minheap and checking next max element in min heap using
    // priority queue
    std::priority_queue<int, std::vector<int>, std::greater<int>> minheap;
    minheap.push(3);
    minheap.push(1);
    minheap.push(5);
    minheap.push(2);
    assert(minheap.size() == (size_t)4);

    // Checking max element in priority queue
    assert(minheap.top() == 1);
    minheap.pop();
    assert(minheap.top() == 2);
    minheap.pop();
    assert(minheap.top() == 3);
    minheap.pop();
    assert(minheap.top() == 5);
    minheap.pop();
    assert(minheap.empty());
}

/** Main function */
int main(int argc, char *argv[]) {
    test();  // execute the tests
    // code here
    return 0;
}