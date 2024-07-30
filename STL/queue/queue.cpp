#include <bits/stdc++.h>
using namespace std;

// queue is the FIFO first in first out
// all the operations are done in O(1) complexity
// everything is similar to stack

int Queue()
{
    queue<int> a;
    a.push(332);
    a.push(23);
    a.push(938);

    a.pop();
    a.pop();

    a.back() += 5; // it will add 5 to the last elment of the queue

    cout << a.front() << endl; // returns the front element of the queue
}

int main()
{
    Queue();
    return 0;
}