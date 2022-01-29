/**
 * @author [sng125](https://github.com/sng125)
 * @file
 * @brief Implementation of [Reversing a Queue](https://www.geeksforgeeks.org/reversing-a-queue/)
 * @details
 * A queue can be reversed by using a temporary Stack data structure which follows Last In First Out (LIFO).
 * By popping every element of a queue into a stack, the last element inserted will be the first element to
 * leave the stack, and the first element inserted will be the last element to leave the stack.
 */

#include <iostream> // for IO operations
#include <cassert> // for asserting during testing
#include <queue> // for testing stl queue
#include <stack> // for storing reversed queue

/**
 * @brief Function reverses a queue of integers using a stack data structure
 * @returns the original queue with reversed values
 */
std::queue<int> reverse_queue(std::queue<int> q) {
    std::stack<int> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    return q;
}

/**
 * @brief Tests reverse_queue by comparing with original queue reversed with
 * for loop
 * @returns void
 */
void test_reverse_queue() {
    // Creates a queue of numbers from 'start' to 'end'
    int start = 1;
    int end = 10;
    std::queue<int> q;
    std::cout << "Original queue: ";
    for (int i=start; i<=end; i++){
        std::cout << i << " ";
        q.push(i);
    }

    // Queue values should equal numbers from 'end' to 'start'
    q = reverse_queue(q);
    std::cout << "\nReversed queue: ";
    for (int i=end; i>=start; i--){
        assert(q.front() == i);
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\nQueue was successfully reversed" << std::endl;
}

/**
 * @brief Main method
 * @returns returns 0 on exit
 */
int main() {
    test_reverse_queue();
    return 0;
}