/*
    Write a program to implement Linear Queue using array.

    Functions to implement
        Enqueue (Insertion)
        Dequeue (Deletion)

*/
#include<iostream>
using namespace std;

#define MAXSIZE 10

class Queue_Array
{
    int front;
    int rear;
    int size;
    public:
    Queue_Array()
    {
        front=-1;
        rear=-1;
        size=MAXSIZE;
    }
    int *arr=new int[size];
    void enqueue(int);
    int  dequeue();
    void display();

};
void Queue_Array::enqueue(int ele)
{
    if(rear==size-1)
        cout<<"\nStack is full";
    else if(front==-1 && rear==-1)
     {
        front=rear=0;
        arr[rear]=ele;
    }
    else if(rear<size)
    {
        rear++;
        arr[rear]=ele;
    }



}
int Queue_Array::dequeue()
{
    int d;
    if(front==-1)
    {
        cout<<"\nstack is empty ";
        return 0;
    }
    else if(front==rear)
    {
        d=arr[front];
        front=rear=-1;
    }
    else
        d=arr[front++];

    return d;
}
void Queue_Array::display()
{
    if(front==-1)
        cout<<"\nStack is empty";
    else
    {
        for(int i=front;i<=rear;i++)
            cout<<arr[i]<<" ";
    }
}

int main()
{
    int op,data;

    Queue_Array ob;


    cout<<"\n1. enqueue(Insertion) ";
    cout<<"\n2. dequeue(Deletion)";
    cout<<"\n3. Display";
    cout<<"\n4. Exit";
    while(1)
    {
        cout<<"\nEnter your choice ";
        cin>>op;
        if(op==1)
        {
            cout<<"Enter data  ";
            cin>>data;
            ob.enqueue(data);
        }
        else if(op==2)
        {
            data=ob.dequeue();
            cout<<"\ndequeue element is:\t"<<data;
        }
        else if(op==3)
            ob.display();
        else if(op==4)
            exit(0);
        else
            cout<<"\nWrong choice ";

    }
}
