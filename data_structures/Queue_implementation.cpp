/**
 * QueueImplementation.cpp
 * Saqlain Zarjis Ansari (https://github.com/Mysterious786)
 * https://en.wikibooks.org/wiki/Data_Structures/Stacks_and_Queues 
 * Implementation of Queue using two Stacks 
 */

#include <iostream>
#include <stack>
#include <queue>

/** Definition of the queue class */
struct Queue
{
   

    std::stack<int> stack1, stack2;

  
    void enqueue(int x)
     {
        /** Move all elements from s1 to s2*/ 
        
        while (!stack1.empty()) /// Determine whether the stack1 is empty
        {
            stack2.push(stack1.top());
            stack1.pop();
        }

        /**Push item into s1*/ 
        stack1.push(x);

        /**Push everything back to s1*/ 

        while (!stack2.empty()) /// Determine whether the stack2 is empty 
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
    }

    /**Remove item front the Stack*/
    int dequeue()
    {
        /**Determine whether first stack is empty*/ 
        if (stack1.empty())
        {
            std::cout << "queue is Empty";
            exit(0);
        }

        /**Return the top of stack1*/ 
        int x = stack1.top();
        stack1.pop();
        return x;
    }
};

int main()
{
    Queue q;
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);

    std::cout << q.dequeue() <<" ";
    std::cout << q.dequeue() <<" ";
    std::cout << q.dequeue()<<" ";
    std::cout << q.dequeue()<<" ";
    std::cout << q.dequeue()<<" ";


    return 0;
}
// DATA_STRUCTURES_QUEUE_IMPLEMENTATION_USING_TWO_STACKS

  

