/**
 * @file stack_using_queue.cpp
 * @brief Stack Data Structure Using the Queue Data Structure
 * @details
 * Using 2 Queues inside the Stack class, we can easily implement Stack
 * data structure with heavy computation in push function.
 * @author [tushar2407](https://github.com/tushar2407)
 */
#include<iostream>
#include <queue>
// using namespace std;
namespace{
    /**
     * Stack Class implementation for basic methods of Stack Data Structure.  
     */
    struct Stack
    {
        std::queue<int> main_q; ///< stores the current state of the stack
        std::queue<int> auxiliary_q; ///< used to carry out intermediate operations to implement stack
        int current_size = 0; ///< stores the current size of the stack
        
        /**
         * Returns the top most element of the stack
         * @return top element of the queue
         */
        int top()
        {
            return main_q.front();
        }

        /**
         * Inserts an element to the top of the stack.
         * @param val is the element which will be inserted into the stack
         */
        void push(int val)
        {
            auxiliary_q.push(val);
            while(!main_q.empty())
            {
                auxiliary_q.push(main_q.front());
                main_q.pop();
            }
            swap(main_q, auxiliary_q);
            current_size++;
        }
        
        /**
         * Removes the topmost element from the stack
         */
        void pop()
        {
            if(main_q.empty())
                return ;
            main_q.pop();
            current_size--;
        }

        /**
         * Returns the current size of the stack.
         * @return current size of stack
         */
        int size()
        {
            return current_size;
        }
    };
}

/**
 * Main function:
 * Creates a stack and pushed some value into it.
 * Through a series of push and pop functions on stack,
 * it demostrates the functionality of the custom stack
 * declared above.
 * @returns 0 on exit
 */
int main()
{

    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
  
    std::cout << "current size: " << s.size() << "\n";
    std::cout << s.top() << "\n";
    s.pop();
    std::cout << s.top() << "\n";
    s.pop();
    std::cout << s.top() << "\n";
    s.push(5);
    std::cout<<s.top()<<"\n";
    s.pop();
    std::cout<<s.top()<<"\n";
  
    std::cout << "current size: " << s.size() << "\n";

    return 0;

}