#include<iostream>
using namespace std;
template <class X>
class Stack
{
    X *arr;
    int top ;
    int capacity;
public:
    Stack(int size)
    {
        arr = new X[size];
        capacity = size;
        top = -1;
    }

    void push(X x)
    {
        if(isFull())
        {
            cout<<"\nOverflow";
            return;
        }
        arr[++top]  =  x;
    }

    void pop()
    {
        if(isEmpty())
        {
            cout<<"\nUndereflow";
        }
        top--;
    }
    int Size()
    {
        return (top+1);
    }
    bool isEmpty()
    {
        if(top==-1)
            return true;
    }
    bool isFull()
    {
        if (top == capacity)
            return true;
    }
    X GetTop()
    {
        if(!isEmpty())
            return (arr[top]);

    }
};

int main()
{
    Stack<int> pt(5);
    pt.push(5);
    pt.push(9);
    pt.pop();
    int n = pt.GetTop();
    cout<<"\nPopped Element is:- "<<n;
    pt.push(3);

    cout<<"\nTop element is:- "<<pt.GetTop()<<endl;
    cout<<"\nStack Size:- "<<pt.Size()<<endl;
    pt.pop();
    cout<<"\nPopped element is:- "<<pt.GetTop();
    if(pt.isEmpty())
        cout<<"\nStack is empty";
    else
        cout<<"\nStack is not empty";
    return 0;
}
