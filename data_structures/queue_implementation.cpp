/**
 * @author [saqlain](https://github.com/Mysterious786)
 * @file
 *
 * Implementation of a Queue using Single Stacks.
 *
 */

#include <iostream>  /// for IO operations
#include <stack>     /// for stack operations
#include <cstdlib>   /// for datatype conversion
/**
 * @brief Data structures
 * @namespace
 */
namespace data_structures
{
    /**
     * Queue data structure.Store elements in FIFO
     * (first-in-first-out) manner.
     *
     */

    class Queue
    {
        std::stack<int> s;

    public:
        /**
         * Pushes data to the back of queue
         */
        void enqueue(int data)
        {
            /**
             *  Push item into the First Stack
             */
            s.push(data);
        }

        /**
         * Remove an item from the queue
         */
        int dequeue()
        {
            /**
             * Determines whether the stack is empty
             */
            if (s.empty())
            {
                std::cout << "Underflow!!";
                exit(0);
            }

            /**
             *Removes item from the Stack
             */
            int top = s.top();
            s.pop();

            
            /**
             * Determines whether the stack becomes empty,and returns the popped item
             */
            if (s.empty())
            {
                return top;
            }

            /**
             * Recursion call
             */
            int item = dequeue();

            /**
             * push popped item back into the stack
             */
            s.push(top);

            
            /**
             * return the result of dequeue() call
             */
            return item;
        }
    };
}
/**
 * Main function, calls enqueue and dequeue
 */
int main()
{

    int keys[] = {1, 2, 3, 4, 5};
    Queue q;

    /**
     * Adding key to the Queue
     */

    for (int key : keys)
    {
        q.enqueue(key);
    }
    /**
     * Print
     *
     */
    std::cout << q.dequeue() << " ";
    std::cout << q.dequeue() << " ";

    return 0;
}

