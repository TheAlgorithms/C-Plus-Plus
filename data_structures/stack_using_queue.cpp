/**
 * @brief Stack Data Structure Using the Queue Data Structure
 * @details
 * Using 2 Queues inside the Stack class, we can easily implement Stack
 * data structure with heavy computation in push function.
 * 
 * References used: [StudyTonight](https://www.studytonight.com/data-structures/stack-using-queue)
 * @author [tushar2407](https://github.com/tushar2407)
 */
#include <iostream> /// for IO operations
#include <queue>   /// for queue data structure

/**
 * @namespace data_strcutres
 * @brief Data structures algorithms
 */
namespace data_structures {
    /**
     * @brief Stack Class implementation for basic methods of Stack Data Structure.  
     */
    struct Stack
    {
        std::queue<int64_t> main_q; ///< stores the current state of the stack
        std::queue<int64_t> auxiliary_q; ///< used to carry out intermediate operations to implement stack
        uint32_t current_size = 0; ///< stores the current size of the stack
        
        /**
         * Returns the top most element of the stack
         * @returns top element of the queue
         */
        int top()
        {
            return main_q.front();
        }

        /**
         * @brief Inserts an element to the top of the stack.
         * @param val the element that will be inserted into the stack
         * @returns void
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
         * @brief Removes the topmost element from the stack
         * @returns void
         */
        void pop()
        {
            if(main_q.empty())
                return ;
            main_q.pop();
            current_size--;
        }

        /**
         * @brief Utility function to return the current size of the stack
         * @returns current size of stack
         */
        int size()
        {
            return current_size;
        }
    };
} // namespace data_structures

/**
 * @brief Main function
 * Creates a stack and pushed some value into it.
 * Through a series of push and pop functions on stack,
 * it demostrates the functionality of the custom stack
 * declared above.
 * @returns 0 on exit
 */
int main()
{

    data_structures::Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
  
    std::cout << "Current size: " << s.size() << "\n";
    std::cout << s.top() << "\n";
    s.pop();
    std::cout << s.top() << "\n";
    s.pop();
    std::cout << s.top() << "\n";
    s.push(5);
    std::cout << s.top() << "\n";
    s.pop();
    std::cout << s.top() << "\n";

    std::cout << "Current size: " << s.size() << "\n";

    return 0;
}
