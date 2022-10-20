//Stack is an LIFO data structure which means last in first out.
//Queue is an FIF0 data structure which means first in first out.
// iostream stands for  standard input-output stream,this header file contains definitions of objects like cin, cout.
// stacks and queue library are used for implementing inbuilt stacks and queues
#include <iostream>
#include <stack>
#include <queue>

struct Queue
{
    //std is an abbreviation of "standard". std is the "standard namespace". cout , cin are only defined in the “std” namespace. 

    std::stack<int> stack1, stack2;

    // enqueue --> function used to push element
    void enqueue(int x)
    {
        // Move all elements from s1 to s2
        while (!stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }

        // Push item into s1
        stack1.push(x);

        // Push everything back to s1
        while (!stack2.empty())
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
    }

    // Dequeue(function to remove an element) an item from the queue
    int dequeue()
    {
        // if first stack is empty
        if (stack1.empty())
        {
            std::cout << "queue is Empty";
            exit(0);
        }

        // Return the top of stack1
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
// OUTPUT-->  3 4 5 6 7 


