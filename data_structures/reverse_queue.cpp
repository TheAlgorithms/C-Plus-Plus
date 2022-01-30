/**
 * @brief Reversing a Queue using a Stack
 * @details
 * Using 1 stack inside the Stack class, we can easily implement a 
 * reverse queue operation with heavy computation in push function. 
 *
 * References used:
 * [StudyTonight] (https://www.studytonight.com/data-structures/stack-using-queue)
 * @author [AvianTheFly(https://github.com/AvianTheFly)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <queue>     /// for queue data structure
#include <stack>     /// for stack data structure
#include <chrono>    /// time data

/**
 * @namespace data_strcutres
 * @brief Data structures algorithms
 */
namespace data_structures {
/**
 * @namespace reverse_queue
 * @brief Functions to reverse a queue using a stack implementation
 */
namespace reverse_queue{
/**
 * @brief Utility function to print the queue
 */
    void print(std::queue<int>& Queue) {
        while (!Queue.empty()) {
            std::cout << Queue.front() << " ";
            Queue.pop();
        }
    }
/**
 * @brief Utility function to reverse the queue using a stack
 */
    void reverse_queue(std::queue<int>& Queue){    
        std::stack<int> Stack;
        int n = Queue.size();

        for (int i = 0; i < n; i++) {
            Stack.push(Queue.front());
            Queue.pop();
        }
        for (int i = 0; i < n; i++) {
            Queue.push(Stack.top());
            Stack.pop();
        }
    }

}  // namespace reverse_queue
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */


static void test1() {
    std::queue<int> Queue;
    Queue.push(1);
    Queue.push(2);
    Queue.push(3);
    data_structures::reverse_queue::reverse_queue(Queue);
    assert(Queue.front() == 3); Queue.pop();
    assert(Queue.front() == 2); Queue.pop();
    assert(Queue.front() == 1); Queue.pop();
}
static void test2(){
    std::queue<int> Queue;
    Queue.push(-1);
    Queue.push(24);
    Queue.push(-9);
    data_structures::reverse_queue::reverse_queue(Queue);
    assert(Queue.front() == -9); Queue.pop();
    assert(Queue.front() == 24); Queue.pop();
    assert(Queue.front() == -1); Queue.pop();
}
static void test(){
    test1();
    test2();
}


/**
 * @brief Self-test implementations
 * @returns void
 */

/**
 * @brief Main function
 * Creates a queue and pushes some values into it.
 * Using push and pop fuinction to stack
 * we can reverse the queue by pushing the stack onto a queue
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    std::queue<int> Queue;
    Queue.push(1);
    Queue.push(2);
    Queue.push(3);

    auto start = std::chrono::high_resolution_clock::now();
    data_structures::reverse_queue::reverse_queue(Queue);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to execute: "<< duration.count() <<"ms"<<std::endl;
    std::cout << "Reverse of Queue: ";
    data_structures::reverse_queue::print(Queue);
   
    return 0;
}