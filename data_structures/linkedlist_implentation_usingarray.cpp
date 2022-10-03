/**
 * \file
 * \brief Linked list implementation using Arrays
 *
 * The difference between the pointer implementation of linked list and array
 * implementation of linked list:
 * 1. The NULL is represented by -1;
 * 2. Limited size. (in the following case it is 100 nodes at max). But we can
 * reuse the nodes that are to be deleted by again linking it bacj to the list.
 */

#include<iostream>
using namespace std;
struct node{
int data;
node*next;
};
node *head,*newnode,*temp;
void traversal(struct node*ptr);
void insertion();
void deletion();
int search();
int main()
{
char ch;
int choice;
head = NULL;
do
{

cout<<"\n \t\t Menu Driven Program";
cout<<"\n 1. Traversal \n 2. Insertion \n 3. Deletion \n 4. Searching";
cout<<"\n Enter your choice:";
cin>>choice;
switch(choice)
{
        case 1: traversal(head);
                break;
        case 2: insertion();
                break;
        case 3: deletion();
                break;
        case 4: int pos;
                pos=search();
                if(pos==-1)
                cout<<"\n Element not found";
                else
                cout<<"\n Element is found at Position:"<<pos;
                break;
        default:cout<<"wrong choice";
}
        cout<<"\n Do you want to continue?";
        cout<<"(Press y/n)";
        cin>>ch;
        }while(ch=='y');

return 0;
}

void traversal(struct node*ptr)
{   while(ptr!=NULL)
    {
        cout<<ptr->data<<" ";
        ptr=ptr->next;
}
}

void insertion()
{
    newnode=new node();
    cout<<"\n Enter data:";
    cin>>newnode->data;
    newnode->next=NULL;
    if(head==NULL)
    head=temp=newnode;
    else
    {
        temp->next=newnode;
        temp=newnode;
    }
}
void deletion()
{
       if(head==NULL)
       cout<<"\n List is empty";
       temp=head;
       head=head->next;
       free(temp);
}
int search()
{       int element;
        cout<<"\n Enter element to be searched:";
        cin>>element;
        temp=head;
        int count=0;
        while(temp!=0)
        {
                count++;
                if(temp->data==element)
                return count;
                temp=temp->next;
        }
        return -1;

}

