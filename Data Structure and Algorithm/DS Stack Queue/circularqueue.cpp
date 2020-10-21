#include<iostream>
using namespace std;

void enqueue();
int dequeue();
bool isEmpty();
bool isFull();
void peek();
void display();

int queue[10],front =-1,rear =-1,maxsize=10;

void enqueue(int item)
{
    if((rear+1) % maxsize == front)  
    {  
        cout<<"\n OVERFLOW";  
    }  
    else if(front == -1 && rear == -1)  
    {  
        front = 0;  
        rear = 0;  
        queue[rear] = item;  
    }  
    else if(rear == maxsize -1 && front != 0)   
    {  
        rear = 0;  
        queue[rear] = item;  
    }  
    else   
    {  
        rear = (rear+1) % maxsize;  
        queue[rear] = item;  
    }  
    
}  
int dequeue()
{
    if(front == -1 && rear == -1)  
    {  
        cout<<"\nUNDERFLOW\n";  
    }  
    else if(front == rear)  
    {  
        front = -1;  
        rear = -1;  
    }  
    else if(front == maxsize -1)  
    {  
        front = 0;  
    }  
    else
    {
        front = front + 1;  
    }
}
void peek()
{
    if(isEmpty())
        cout<<"Underflow, stack is empty \n";
    else
        cout<<"top most element is = "<<queue[rear];
}
bool isEmpty()
{
    if(front == -1)
        return true;
    else
        return false;    
}
bool isFull()
{
    if(front == 0 && rear == 9)
        return true;
    else
        return false;
}
void display()
{
   int i;        
   if(front == -1)
   { 
      cout<<"\n Circular Queue is Empty!! \n ";  
   }
   else  
    {  
      i = front;  
      cout<<"\n Circular Queue Elements are : \n";  
      if(front <= rear)
       {  
            while(i <= rear)  
            {
                cout<<"\n"<<queue[i++],front,rear;  
            }
        }  
      else
       {  
            while(i <= maxsize - 1)
            {  
                cout<<" \n "<<queue[i++],front,rear;  
            }

            i = 0;

            while(i <= rear)
            {  
                cout<<" \n "<<queue[i++],front,rear;
            }  
       }
    }
}

int main()
{
    int ch,item;
    do
    {
        cout<<"\n 1.push \t 2.pop \t 3.peek \t 4.display \t 5.exit \n\nEnter choice ";
        cin>>ch;
        switch (ch)
        {
            case 1: cout<<"Enter item to push \t \n";
                    cin>>item;
                    enqueue(item);
                    break;
            case 2: cout<<"element deleted is \t"<<dequeue()<<"\n";
                    break;
            case 3: cout<<"element peek is \t \n";
                    peek();
                    break;
            case 4: cout<<"element displayed \t \n";
                    display();
                    break;
            case 5: exit(0);
                    break;
            default:
                    cout<<"Invalid choice";
                    break;
        }
    }while(ch==1 || ch==2 || ch==3 || ch==4);    
}
