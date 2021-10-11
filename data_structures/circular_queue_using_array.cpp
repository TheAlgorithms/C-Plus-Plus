/*
    C++ program : Circular Queue using array
*/

#include<iostream>      //for input output
#include<stdlib.h>      //for system("cls")
#include<conio.h>       //for getch()
using namespace std;

#define MAX 10          //max size of array

int Queue[MAX];
int front = -1;
int rear = -1;

int isFull()
{
	if((front == 0 && rear == MAX-1) || (front == rear+1))
    {
        return 1;
    }
    return 0;
}

int isEmpty()
{
	if (front == -1)
    {
        return 1;
    }
    return 0;
}

void insert(int item)
{
    if(isFull())
    {
        cout<<"\tQueue Overflow \n";
        return;
    }
    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        if(rear == MAX-1)
            rear = 0;
        else
            rear = rear+1;
    }
    Queue[rear] = item ;
}

void del()
{
    if (isEmpty())
    {
        cout<<"\tQueue Underflow\n";
        return ;
    }
    cout<<"\tElement deleted from queue is : "<<Queue[front]<<"\n";
    if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        if(front == MAX-1)
            front = 0;
        else
            front = front+1;
    }
}

void peek()
{
	if( isEmpty() )
	{
		cout<<"\n\tQueue Underflow\n";
		return;
	}
	cout<<"\tElement at the front is "<<Queue[front]<<"\n";
}

void display()
{
    int front_pos = front, rear_pos = rear;
    if(isEmpty())
    {
        cout<<"\tQueue is empty\n";
        return;
    }
    cout<<"\tQueue elements :\n\t";
    if(front_pos <= rear_pos )
        while(front_pos <= rear_pos)
        {
            cout<<Queue[front_pos]<<" ";
            front_pos++;
        }
    else
    {
        while(front_pos <= MAX-1)
        {
            cout<<Queue[front_pos]<<" ";
            front_pos++;
        }
        front_pos = 0;
        while(front_pos <= rear_pos)
        {
            cout<<Queue[front_pos]<<" ";
            front_pos++;
        }
    }
    cout<<"\n";
}

int main()
{
    int choice, item;
    int i=0;
    do
    {
        system("cls");                      //clears the screen
        cout<<"\t\t**********MENU**********\n\tBasic Linear Queue (array implementation) Operations:";
        cout<<"\n\t1.Insert";
        cout<<"\n\t2.Delete";
        cout<<"\n\t3.Display element at the front";
        cout<<"\n\t4.Display all elements of the queue";
        cout<<"\n\t5.Check if Queue is completely empty";
        cout<<"\n\t6.Check if Queue is completely full";
        cout<<"\n\t7.Exit";
        cout<<"\n\nEnter your choice: ";
	    cin>>choice;

        char ch;
        switch(choice)
        {
            case 1 :
                    do{
                        int n;
                        cout<<"\n\tHow many elements do you want to enter (<="<<MAX-i<<"): ";
                        cin>>n;
                        n=n+i;
                        cout<<endl;
                        for(; i<n; i++)
                        {
                            cout<<"\tElement #"<<i+1<<" :";
                            cin>>item;
                            insert(item);
                        }
                        cout<<"\nInsert more?(y/n):";
                        cin>>ch;
                    }while(ch=='y' || ch=='Y');
                    break;
            case 2 :
                    do{
                        del();
                        i--;
                        display();
                        cout<<"\nDelete more?(y/n):";
                        cin>>ch;
                    }while(ch=='y' || ch=='Y');
                    break;
            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                if(isEmpty())
                    cout<<"\tQueue is Empty!";
                else
                    cout<<"\tQueue is not Empty.";
                break;

            case 6:
                if(isFull())
                    cout<<"\tQueue is Full!";
                else
                    cout<<"\tQueue is not Full.";
                break;

            case 7:
                exit(0);
            default:
                    cout<<"Wrong choice\n";
        }
        cout<<"\nPress any key to continue...";
        getch();
    }while(choice!=7);
    return 0;
}
