/* This class specifies the basic operation on a reverse queue using stack */
#ifndef DATA_STRUCTURES_QUEUE_H_
#define DATA_STRUCTURES_QUEUE_H_
#include <iostream>
#include <stack>
using namespace std;

/** Definition of Node */
template <class Type>
struct node
{
    Type data;
    node<Type> *next;
};

/** Definition of queue class */
template <class Type>
class queue {
private:
    node<Type> *top;
    node<Type> *rear;
    int size;

public:
    /** Constructor */
    queue()
    {
        top = nullptr;
        rear = nullptr;
        size = 0;
    }

    /** Destructor */
    ~queue() {}

    /** Check if the queue is empty */
    bool isEmpty() {return top == nullptr;}

    /** Add node to queue */
    void enqueue(Type in)
    {
        node<Type> *newNode = new node<Type>;
        newNode->data = in;
        newNode->next = nullptr;
        if(top == nullptr)
        {
            top = newNode;
            rear = newNode;
        }else
        {
            rear->next = newNode;
            rear = rear->next;
        }
        size++;
    }

    /** get first element */
    Type front()
    {
        if(top == nullptr)
        {
            throw logic_error("error: no element in queue.");
        }
        else
        {
            return top->data;
        }
    }

    /** remove first element */
    void pop()
    {
        if(top == nullptr)
        {
            cout << "no element in queue." << endl;
            return;
        }
        node<Type> *temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    /** clear queue */
    void clear()
    {
        top = nullptr;
        size = 0;
    }

    /** reverse queue using STL stack */
    void reverse()
    {
        stack<Type> st;
        while (top)
        {
            st.push(top->data);
            pop();
        }
        while (!st.empty())
        {
            enqueue(st.top());
            st.pop();
        }
    }

    int getSize()
    {
        return size;
    }

};

///test

int main()
{
    cout << "test1: " << endl;
    ///reverse test:
    queue<int> q;
    q.enqueue(2);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    q.enqueue(10);
    q.enqueue(11);
    q.reverse();
    while (!q.isEmpty())
    {
        cout << q.front() << endl;
        q.pop();
    }

    cout << "test2: " << endl;
    ///clear test:
    queue<int> w;
    w.enqueue(2);
    w.enqueue(4);
    w.enqueue(5);
    w.enqueue(6);
    cout << w.getSize() << endl;
    w.clear();
    cout << w.getSize() << endl;

    cout << "test3: " << endl;
    ///pop test:
    queue<int> e;
    e.enqueue(2);
    e.enqueue(4);
    e.enqueue(5);
    e.enqueue(6);
    cout << e.getSize() << endl;
    e.pop();
    cout << e.getSize() << endl;

    return 0;
}

#endif  // DATA_STRUCTURES_QUEUE_H_