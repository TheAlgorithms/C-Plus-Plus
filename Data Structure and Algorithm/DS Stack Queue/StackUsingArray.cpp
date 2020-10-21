#include<iostream>
using namespace std;

void push();
int pop();
bool isEmpty();
bool isFull();
void peek();
void display();

int stack[10],top=-1;

void push(int item)
{
    if(isFull())                
        cout<<"OverFlow";
    else
        top++;
        stack[top]=item;
}
int pop()
{
    int temp;
    if(isEmpty())              
        cout<<"Underflow\n";
    else
        temp= stack[top];
        top--;
        return temp;  
}
void peek()
{
    if(isEmpty())
        cout<<"Underflow, stack is empty \n";
    else
        cout<<"top most element is = "<<stack[top];
}
bool isEmpty()
{
    if(top==-1)
        return true;
    else
        return false;    
}
bool isFull()
{
    if(top==9)
        return true;
    else
        return false;
}
void display()
{
    if(isEmpty())
    cout<<"Stack empty";
    else
        for(int i=top;i>=0;i--){
		    cout<<stack[i]<<" \t "; } 
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
                    push(item);
                    break;
            case 2: cout<<"element deleted is \t"<<pop()<<"\n";
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