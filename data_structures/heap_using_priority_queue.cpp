/**
 * @file
 * @brief Perform Minheap and Maxheap using [priority
 * queue](http://www.cplusplus.com/reference/queue/priority_queue/)
 * @details
 * In competitive coding I have used this datastructure a lot for Minheap and
 * Maxheap operations, it is very useful and timecomplexity is equivalent to
 * minheap and maxheap.
 * @author [Shubham Singhal](https://github.com/singhalshubham8)
 * @see heap_using_priority_queue.cpp
 */

#include <cassert>
#include <iostream>
#include <queue>

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Adding elements into priority queue which is eventaully maxHeap
    std::priority_queue<int> maxheap;
    maxheap.push(3);
    maxheap.push(1);
    maxheap.push(5);
    maxheap.push(2);
    assert(maxheap.size() == (size_t)4);

    // Extracting elements from maxheap and checking if top of the datastructure
    // contains maximum value or not
    assert(maxheap.top() == 5);
    maxheap.pop();
    assert(maxheap.top() == 3);
    maxheap.pop();
    assert(maxheap.top() == 2);
    maxheap.pop();
    assert(maxheap.top() == 1);
    maxheap.pop();
    assert(maxheap.empty());

    // Adding elements in minHeap
    std::priority_queue<int, std::vector<int>, std::greater<>> minheap;
    minheap.push(3);
    minheap.push(1);
    minheap.push(5);
    minheap.push(2);
    assert(minheap.size() == (size_t)4);

    // Extracting elements from minheap and checking if top of the datastructure
    // contains minimum value or not
    assert(minheap.top() == 1);
    minheap.pop();
    assert(minheap.top() == 2);
    minheap.pop();
    assert(minheap.top() == 3);
    minheap.pop();
    assert(minheap.top() == 5);
    minheap.pop();
    assert(minheap.empty());

    std::cout << "Test implementations passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // execute the tests
    // code here
    return 0;
}