#include<iostream>
using namespace std;

template <class t>
class MyQueue
{
    int s , f , e ;
    t * arr;
public:
    MyQueue()
    {
        s=0;
        f=e=-1;
    }
    MyQueue(int n)
    {
        s = n;
        arr = new t[s];
        f = e = 0;
    }
    int Size()
    {
        return s;
    }
    t Front()
    {
        return arr[f];
    }
    t Back()
    {
        return arr[e];
    }
    bool isFull()
    {
        if((e + 1) == s)
            return true;
        else
            return false;
    }
    bool isEmpty()
    {
        if( e == f )
            return true;
        else
            return false;
    }
    void Insert(t x)
    {
        if(!isFull())
        {
            arr[e] = x;
            e++;
            s++;
        }
        else
            throw;
    }
    t Delete()
    {
        if(!isEmpty())
        {
            t n = arr[f];
            f++;
            s--;
            return n;
        }
        else
            throw;
    }

    void Empty()
    {
        delete []arr;
        t * temp;
        arr = temp;
        f=e=s=0;
    }

};

int main()
{
    MyQueue<int> q(5);
    q.Insert(12);
    q.Insert(1);
    q.Insert(98);
    q.Insert(27);
    q.Insert(46);

    cout<<"\nThe Size:- "<<q.Size();
    cout<<"\nFront element:- "<<q.Front();

    cout<<"\n\t"<<q.Delete();
    cout<<"\nNew Front element:- "<<q.Front();
    cout<<"\nNew Size:- "<<q.Size();

    cout<<"\n\t"<<q.Delete();
    cout<<"\n\t"<<q.Delete();
    cout<<"\nNew Front element:- "<<q.Front();
    cout<<"\nBack element:- "<<q.Back();

    return 0 ;
}

