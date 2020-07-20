/**
 * @file
 * @brief Implementation of stack using two queues
 * @author [Gopal-Dahale](https://github.com/Gopal-Dahale)
 * @details
 * In this alogrithm, stack is implemented by making the pop operation costly. 
 * push(x) operation enqueues x to q1. 
 * pop() operation puts the first n-1 elements from q1 to q2 and then dequeue the last element from q1. 
 * Finally the names q1 and q2 are swapped. 
 * The time Complexity of the algorithm is \f$O(n)\f$ for pop() and \f$O(1)\f$ for push(). 
 */

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template <typename T>
class Stack
{
private:
    queue<T> q1, q2;

public:
    /**
    * Pushes the given element to top of stack 
    */
    void push(T data)
    {
        q1.push(data);
    }

    /**
    * Pops the topmost element of stack 
    */
    void pop()
    {
        // push first n-1 elements from q1 to q2
        // pop the last element from q1
        // swap q1 and q2
        if (q1.size() == 0)
            return;

        while (q1.size() > 1)
        {
            q2.push(q1.front());
            q1.pop();
        }
        // pops the last element from q1;
        q1.pop();

        // swaps q1 with q2
        q1.swap(q2);
    }

    /**
    * Returns the topmost element of stack. 
    * Returns -1 if stack is empty
    */
    T top()
    {
        if (q1.size() == 0)
            return -1;

        while (q1.size() > 1)
        {
            q2.push(q1.front());
            q1.pop();
        }

        T top_element = q1.front();
        q2.push(q1.front());
        q1.pop();

        // swaps q1 with q2
        q1.swap(q2);

        return top_element;
    }

    /**
    * Returns the size of stack
    */
    int size()
    {
        return q1.size() + q2.size();
    }

    /**
    * Returns true if stack is empty, otherwise false 
    */
    bool empty()
    {
        return (q1.size() == 0);
    }
};

/**
 * utility function to print stack 
 */
template <typename T>
void print(Stack<T> &s)
{
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "\n";
}

/**
 * Testing function
 */
void test()
{
    Stack<int> s;

    // push
    for (int i = 0; i < 10; i++)
        s.push(i);

    assert(s.size() == 10);

    // iterating over stack
    print(s);

    // now stack is empty
    if (s.empty())
        cout << "stack is empty\n";

    assert(s.top() == -1);

    // since stack is empty, this will return -1
    cout << s.top() << "\n";

    for (int i = 0; i < 10; i++)
        s.push(i);

    // size of stack
    cout << "stack contains " << s.size() << " elements\n";

    print(s);
}

int main()
{
    test();
    return 0;
}
