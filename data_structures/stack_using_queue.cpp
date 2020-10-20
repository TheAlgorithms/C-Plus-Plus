/**
 * @file
 * @brief Implement a last in first out (LIFO) stack using queues.
          The implemented stack should support all the functions of a normal queue (push, top, pop, and empty).
 * @author [Neha Labhasetwar](https://github.com/nehalabhasetwar)
 */

#include <iostream>
#include <queue>
#include <cassert>

class MyStack
{
    /** initialize queue */
    std::queue <int> q;

    public:

    MyStack() = default;                                 //default constructor

/**
 * Function to  Push element onto stack.
 * @param x number to be pushed.
 * @return void.
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

/** Function to Remove the element on top of the stack and return that element.
 *  @return element that is deleted from the stack. */

    int pop()
    {
        int y=q.front();
        q.pop();
        return y;
    }

/** Function to Get the topmost element from stack.
 *  @return element on the top of stack. */

    int top()
    {
        return q.front();
    }

/** Function to Return whether the stack is empty.
 *  @return if stack is empty, returns true, else false.*/

    bool empty()
    {
        return q.empty();
    }
};


/** Testing function.
 *  @returns void. */

void stack_test()
{
    MyStack obj;
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
    std::cout << "PASSED\n";

    std::cout << "Test #2\n";
    obj.push(-1);
    assert(obj.empty() == false);
    assert(obj.top() == -1);
    assert(obj.pop() == -1);
    std::cout << "PASSED\n";
}



/** Main function
 * @returns 0 on exit
 */


int main()
{
    stack_test();
    return 0;
}

