#include<iostream>
using namespace std;

void enqueue();
int dequeue();
bool isEmpty();
bool isFull();
void peek();
void display();

int stack[10],front =-1,rear =-1;

void enqueue(int item)
{
    if(isFull())                
        cout<<" Queue is OverFlow ";
    else
        if(front == -1) front = 0;
            rear++;
            stack[rear] = item;
            cout<<"Inserted "<<item<< endl;
}
int dequeue()
{
    int temp;
    if(isEmpty())              
        cout<<"Queue is Underflow \n ";
    else
      temp = stack[front];
      if (front >= rear)
        {
            front = -1;
            rear = -1;
        } /* Q has only one element, so we reset the queue after deleting it. */
      else
        {
            front++;
        }
      cout<< "Deleted " <<temp<< endl;
      return temp; 
}
void peek()
{
    if(isEmpty())
        cout<<"Underflow, stack is empty \n";
    else
        cout<<"top most element is = "<<stack[rear];
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
    if (isEmpty())
    {
      cout<< "Empty Queue" << endl;
    } 
    else 
    {
      cout<<"Front index-> " << front;
      cout<<" \n Items -> ";

      for (i = front; i <= rear; i++)
        {
            cout<<stack[i] <<"  ";
            cout<<"Rear index-> " << rear << endl;
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