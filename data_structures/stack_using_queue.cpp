#include <iostream>
#include <queue>
using namespace std;

class MyStack
{
    public:

    /** Initialize your data structure here. **/
    queue<int> q;                                 //initialize queue
    MyStack() {                                   //default constructor
    }

    /** Push element onto stack. */
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

    /** Removes the element on top of the stack and returns that element. */
    int pop()
    {
        int y=q.front();
        q.pop();
        return y;
    }

    /** Get the top element. */
    int top()
    {
        return q.front();
    }

    /** Returns whether the stack is empty. */
    bool empty()
    {
        return q.empty();
    }
};

int main()
{
   MyStack obj;
   int ch, x;

    do {
        cout << "\n0. Exit";
        cout << "\n1. Push";
        cout << "\n2. Pop";
        cout << "\n3. Print topmost element:";
        cout << "\n4. check whether the stack is empty";
        cout << "\nEnter Your Choice : ";
        cin >> ch;

        if (ch == 1)
            {
                cout << "\nInsert : ";
                cin >> x;
                obj.push(x);
        } else if (ch == 2)
        {
            cout<<obj.pop()<<" deleted\n";
        } else if (ch == 3)
        {
            cout<<"topmost element : "<<obj.top()<<"\n";
        } else if(ch == 4)
        {
            cout<<"status (true/1) or (false/0) : "<<obj.empty()<<"\n";
        }
    } while (ch != 0);


    return 0;

}

