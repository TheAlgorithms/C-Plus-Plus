/* Program to implement a stack using 
two queues */
#include <bits/stdc++.h>

using namespace std;

class Stack
{
    queue<int> q1, q2;
    int curr_size;

public:
    Stack()
    {
        curr_size = 0;
    }

    void push(int val)
    {
        curr_size++;

        q2.push(val);

        while (!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }

        queue<int> q = q1;
        q1 = q2;
        q2 = q;
    }

    void pop()
    {
        if (q1.empty())
            return;
        q1.pop();
        curr_size--;
    }

    int top()
    {
        if (q1.empty())
            return -1;
        return q1.front();
    }

    int size()
    {
        return curr_size;
    }
};

// Driver code
int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    while (s.size() > 0)
    {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}