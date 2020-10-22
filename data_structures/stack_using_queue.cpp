/**
 * @file
 * @brief Implement a last in first out (LIFO) stack using queues. The implemented stack should support all the functions of a normal queue (push, top, pop, and empty).
 * @author [Neha Labhasetwar](https://github.com/nehalabhasetwar)
 */

#include <iostream>  // for standard IO operations
#include <cassert>   // defines one macro function (assert) that can be used as a standard debugging tool
#include <queue>     // This header is part of the containers library, designed to operate in FIFO context
/**
 * @namespace data_structures
 * @brief In this approach we will see how to Implement Stack using Single Queue,
 * 1.Push the element to the Queue :
 *   -Check the size of Queue and store it in variable "s".
 *   -Iterate from 0 to "s" and Pop the element from queue and push the same element to Queue. By doing this, last inserted data will come at first position in Queue.
 * 2.Pop Operation:
 *   -Pop the elements from Queue.
 * 3.top Operation:
     -Return front element from Queue.
*/
namespace data_structures {
/**
 * @namespace stack_using_queue
 * @brief Functions for [Stack using queue](https://leetcode.com/problems/implement-stack-using-queues) implementation
 */
namespace stack_using_queue {
/**
 * @brief Assuming we already have a class implemented for Queue, we will first design the class for Stack.
 * It will have the methods push() , pop() , top() , and empty() and one queue.
 */
class MyStack
{
    /** initialize queue */
    std::queue <int> q;      //empty queue q of int type

    public:

    MyStack() = default;                                 //default constructor for stack

/**
 * @brief Function to Push element onto stack
 * @param x number to be pushed
 * @returns void
 */
    void push(int x)
    {
        q.push(x);                                  //let's assume x=3,queue=1,2 , then queue will become 1,2,3
        int s=q.size();                             //get size of queue
        for(int i=0;i<s-1;i++)                      //here we will invert queue (1,2,3 -> 2,3,1 -> 3,1,2)
        {
            int y=q.front();                        //because if we want to remove from stack so our element should be at front in queue
            q.pop();
            q.push(y);
        }
    }
/**
 * @brief Function to Remove the element on top of the stack and return that element.
 * @returns element that is deleted from the stack
 */
    int pop()
    {
        int y=q.front();
        q.pop();
        return y;
    }
/**
 * @brief Function to Get the topmost element from stack.
 * @returns element on the top of stack
 */
    int top()
    {
        return q.front();
    }
/**
 * @brief Function to Return whether the stack is empty.
 * @return if stack is empty, returns true, else false
 */
    bool empty()
    {
        return q.empty();
    }
};
} // namespace stack_using_queue
} // namespace data_structures
/**
 * @brief Test Implementations
 * @returns void
 */
static void tests()
{
    data_structures::stack_using_queue::MyStack obj;            //  object of MyStack class

    std::cout << "Test #1\n";
    obj.push(2);
    obj.push(5);
    obj.push(0);
    assert(obj.top() == 0);
    assert(obj.pop() == 0);
    assert(obj.top() == 5);
    assert(obj.pop() == 5);
    assert(obj.top() == 2);
    assert(obj.pop() == 2);
    assert(obj.empty() == true);
    std::cout << "PASSED TEST 1\n";

    std::cout << "Test #2\n";
    obj.push(-1);
    assert(obj.empty() == false);
    assert(obj.top() == -1);
    assert(obj.pop() == -1);
    std::cout << "PASSED TEST 2\n";
}
/**
 * @brief Main function calling tests function
 * @returns 0 on exit
 */
int main()
{
    tests(); // Execute the Tests
    return 0;
}
