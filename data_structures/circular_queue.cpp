#include<iostream>

class circularqueue
{
    public:
        int size, f, r;
        int *arr;
};

int isempty(circularqueue *q)
{
    if(q->f == q->r)
    {
        return 1;
    }
    return 0;
}


int isfull(circularqueue *q)
{
    if((q->r + 1) % q->size == q->f)
    {
        return 1;
    }
    return 0;
}

void enque(circularqueue *q, int val)
{
    if(isfull(q))
    {
        std::cout<<"Queue Overflow";
    }

    else
    {   
        q->r = (q->r + 1) % q->size;
        q->arr[q->r] = val;
        std::cout<<"Enqueued Element : "<<val<<endl;
    }
    
}

int deque(circularqueue *q)
{   
    int a = -1;
    if(isempty(q))
    {
        std::cout<<"No element to Deque";
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
    circularqueue q;

    q.size = 4;
    q.f = q.r = 0;
    q.arr = new int(q.size * sizeof(int));

    // Enque few elements
    enque(&q, 12);
    enque(&q, 15);
    enque(&q, 16);
    std::cout<<"Dequeing element : "<<deque(&q)<<endl;
    std::cout<<"Dequeing element : "<<deque(&q)<<endl;
    std::cout<<"Dequeing element : "<<deque(&q)<<endl;

    enque(&q, 20);
    enque(&q, 20);
    enque(&q, 20);

    if (isempty(&q))
    {
        std::cout<<"Circular Queue is Empty";
    }

    if (isfull(&q))
    {
        std::cout<<"Circular Queue is Full";
    }

    return 0;
}
