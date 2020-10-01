#include<iostream>
using namespace std;

class CircularQueue
{
    public:
        int size, f, r;
        int *arr;
};

int isEmpty(CircularQueue *q)
{
    if(q->f == q->r)
    {
        return 1;
    }
    return 0;
}


int isFull(CircularQueue *q)
{
    if((q->r + 1) % q->size == q->f)
    {
        return 1;
    }
    return 0;
}

void Enque(CircularQueue *q, int val)
{
    if(isFull(q))
    {
        cout<<"Queue Overflow";
    }

    else
    {   
        q->r = (q->r + 1) % q->size;
        q->arr[q->r] = val;
        cout<<"Enqueued Element : "<<val<<endl;
    }
    
}

int Deque(CircularQueue *q)
{   
    int a = -1;
    if(isEmpty(q))
    {
        cout<<"No element to Deque";
    }

    else
    {
        q->f = (q->f + 1) % q->size;
        a = q->arr[q->f];
    }
    
    return a;
}

int main()
{   
    CircularQueue q;

    q.size = 4;
    q.f = q.r = 0;
    q.arr = new int(q.size * sizeof(int));

    // Enque few elements
    Enque(&q, 12);
    Enque(&q, 15);
    Enque(&q, 16);
    cout<<"Dequeing element : "<<Deque(&q)<<endl;
    cout<<"Dequeing element : "<<Deque(&q)<<endl;
    cout<<"Dequeing element : "<<Deque(&q)<<endl;

    Enque(&q, 20);
    Enque(&q, 20);
    Enque(&q, 20);

    if (isEmpty(&q))
    {
        cout<<"Circular Queue is Empty";
    }

    if (isFull(&q))
    {
        cout<<"Circular Queue is Full";
    }

    return 0;
}