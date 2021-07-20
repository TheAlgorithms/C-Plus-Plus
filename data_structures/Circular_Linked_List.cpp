#include <bits/stdc++.h>

using namespace std;

class node//POINTER VARIAVLE//AS WE CANNOT STRORE PONTERS IN NORMAL CLASS VARIABLE//
{ public:
    int data;
    class node*next;//SELF POINTER, SELF REFENTIAL POINTER//
}*new_,*head,*tail,*temp; //CLASS POINTER VARIABLE//

void display()
{
    cout<<"YOUR ENTERED LIST ITEMS ARE :- "<<endl;
    temp=head;//INITIALLY TAKING HEAD AS TEMP and moving temp to get next elements using  Data = (temp->next ) //
    while(temp->next!=head)
    {
        cout<<temp->data<<"->";
        temp=temp->next;//Then shifting the Temp to next Element using (temp->next)//
    }
     cout<<temp->data<<endl;


}
int count_node()
 {  int num =0;
     temp=head;
     while(temp->next!=head)
     {
         temp=temp->next;
         num++;
     }

     return num+1;
 }
void  add_beg()
{  int value;
    new_=(class node *)malloc(sizeof(class node));
    cout<<"Enter the data "<<endl;
    cin>>value;
    temp=head;
    while(temp->next!=head)
    {
        temp=temp->next;

    }
    temp->next=new_;
    new_->data=value;
    new_->next=head;
    head=new_;
}
void add_end()
{ int value;
    new_=(class node *)malloc(sizeof(class node));
    cout<<"Enter the data "<<endl;
    cin>>value;
    new_->data=value;
    if(head==0)
    {
        new_->next=0;
        head=new_;
    }else{
    temp=head;
    while(temp->next!=head)
    {
        temp=temp->next;
    }
    new_->next=temp->next;
    temp->next=new_;

    }
}
void add_pos()
{ int value;
  int i,j;
  cout<<"Enter the position to add starting from 1 "<<endl;
  cin>>i;
  /*if(i>count_node())
  {
      cout<<"you have no such element "<<endl;
  }*/
  new_=(class node *)malloc(sizeof(class node));
    cout<<"Enter the data "<<endl;
    cin>>value;
    new_->data=value;
    new_->next=0;
  temp=head;
   for( j=1;j<i-1;j++)
    {
        temp=temp->next;
    }
    new_->next=temp->next;
    temp->next=new_;
}
void del_beg()
{
    if(head==0){
        cout<<"list is empty "<<endl;
    }else{
        temp=head;
        while(temp->next!=head){
            temp=temp->next;
        }
        temp->next=head->next;;
        head=head->next;

    }
}
void del_end()
{
    if(head==0)
    {
        cout<<"List is empty "<<endl;
    }else{
    temp=head;
    while(temp->next->next!=head)
    {
        temp=temp->next;
    }
    temp->next=temp->next->next;

    }
}
void del_pos()
{    int i;

     cout<<"Enter the position you want to delete starting from 1 "<<endl;
     cin>>i;
     if(head==0)
     {
         cout<<"NO elements in the list "<<endl;
     }else{
     temp=head;
     int k;
     for(k=1;k<i-1;k++)
     {

       temp=temp->next;
     }
     temp->next=temp->next->next;


     }
}

/*void rev_list()
{
    class node *next,*current,*prev ;
    while(temp->next!=head){
            temp=temp->next;
        }
    prev = temp;

    current =head;
    while(current!=0)
    {
        next=current->next;
        current->next= prev;
        prev=current;
        current=next;
    }
    head=prev;


}*/

int main()
{ int n,i,value;
    cout<<"Hello enter the initial size of list "<<endl;
    cin>>n;
    for(i=0;i<n;i++)
    {    //DYNAMIC MEMORY ALLOCATION//
        cout<<"ENTER THE "<<i+1 <<" no ELEMENT OF THE LIST"<<endl;
        new_=(class node *)malloc(sizeof(class node));//TYPE CAST(for what type of data type we are allocating the memory)+MALLOC(to allocate the memory)+Size(how much memory should be allocated)//
        cin>>value;
        new_->data=value;
        new_->next=0;
        if(head==0)//CHEACKING IF THE HEAD VARIABLE IS ASSIGNED BEFORE OR NOT //
        {
            head=new_;
            tail=new_;
        }else{//IF HEAD IS ALREADY ASSIGNED THEN THE ADD IS ADDED TO CURRENT TAILS ADDRESS AND NEW TAIL WILL BE THE NEW_//
         tail->next=new_;
         tail=new_;
         tail->next=head;
        }
     }
     display();
     int out=0;
      cout<<"Now if you want to edit the list :-"<<endl;
            cout<<" TO add an element at begining press :- 1  "<<endl;
            cout<<" TO add an element at end press :- 2  "<<endl;
            cout<<" TO add an element at specific position press :- 3  "<<endl;
            cout<<" TO delete an element at begining press :- 4  "<<endl;
            cout<<" TO delete an element at end press :- 5  "<<endl;
            cout<<" TO delete an element at specific position press :- 6  "<<endl;
            cout<<" TO count the no of element in the list press :- 7  "<<endl;
            cout<<" TO exit and print result  press :- 8  "<<endl;

    while(out!=1) {
            int choice;
           cout<<"Enter your choice "<<endl;
           cin>>choice;

     switch(choice)
         {
        case 1:
            {
                add_beg();
                display();
            }
        break;
          case 2:
            {
                add_end();
                display();
            }
        break;
         case 3:
            {
                add_pos();
                display();
            }
        break;
        case 4:
            {
                del_beg();
                display();
            }
        break;
          case 5:
            {
                del_end();
                display();
            }
        break;
          case 6:
            {
                del_pos();
                display();
            }
        break;
         case 7:
            {  cout<<"your total no of output :- ";
               int k= count_node();
               cout<<k<<endl;
            }
        break;
         case 8:
            {
                out=1;
                display();
            }
        break;
         default:
            {
                cout<<"Enter the correct choice "<<endl;
            }
         }
              }


    return 0;
}

