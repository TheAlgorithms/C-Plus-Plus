#include<iostream>
using namespace std;
struct node
{  int x;
    node *next,*prev;
};
class binary
{    node *head=NULL,*temp=NULL, *head1=NULL,*temp1=NULL, *head2=NULL,*temp2=NULL,*temp3=NULL,*head3=NULL;
     int c,i;
      public:
       node *create();
       void insert();
       void binary1();
       void binary2();
       void addition();
       void com();
       void comp();
       void display();
};
node *binary::create()
{   node *p=new(struct node);
     cout<<"enter binary Number: ";
     cin>>c;
     p->x=c;
     p->next=NULL;
     p->prev=NULL;
     return  p;
  }
  void binary::insert()
  {
       node *p=create();

     if(head==NULL)
     {    head=p;
     }
    else
    {      temp=head;
          while(temp->next!=NULL)
          {    temp=temp->next;   }
              temp->next=p;
              p->prev=temp;

     }

   }
   void binary:: binary1()
    { int a;
       cout<<"enter the no. of bits: ";
        cin>>a;
         head=NULL;
        for(i=0;i<a;i++)
        {  insert();      }
          head1=head;
         display();
         head=NULL;
         temp1=head1;
     }
      void binary:: binary2()
    {     int a;
       cout<<"enter the no. of bits: ";
        cin>>a;
         head=NULL;
        for(i=0;i<a;i++)
        {  insert();      }
           head2=head;
         display();
         head=NULL;
      }

      void binary::addition()
      {   int carry=0;
         temp1=head1;
         while(temp1->next!=NULL)
         {   temp1=temp1->next;     }

          temp2=head2;
         while(temp2->next!=NULL)
         {   temp2=temp2->next;     }

         while(temp1!=NULL)
          {      node *p=new(struct node);
                 p->next=NULL;
                 p->prev=NULL;
                 if(temp1->x==0&&temp2->x==0)
                 {      p->x=0+carry;  carry=0;      }
                 if(temp1->x==0&&temp2->x==1)
                 {      if(carry==0)
                        {p->x=1;     carry=0; }
                         else
                         {  p->x=0;  carry=1;
                         }
                 }
                   if(temp1->x==1&&temp2->x==0)
                 {       if(carry==0)
                         {p->x=1;     carry=0; }
                         else
                         {  p->x=0;  carry=1;
                         }
                 }
                   if(temp1->x==1&&temp2->x==1)
                 {        if(carry==0)
                        {p->x=0;     carry=1; }
                         else
                         {  p->x=1;  carry=1; }
                 }
               if(temp3==NULL)
               {   temp3=p;     }
               else
               {
                  p->next=temp3;
                  temp3=p;
               }

              temp1=temp1->prev;
              temp2=temp2->prev;
         }
      node *p=new(struct node);
                p->x=carry;
                 p->next=NULL;
                 p->prev=NULL;
           if(temp3==NULL)
               {   temp3=p;     }
               else
               {
                  p->next=temp3;
                  temp3=p;
               }
               head3=temp3;
     temp3=head3;  cout<<"\n";
      while(temp3->next!=NULL)
      { cout<<" "<<temp3->x;;
        temp3=temp3->next;
      } cout<<" "<<temp3->x<<"\n";

}
void binary::com()
       { while(temp1!=NULL)
        {  node *p=new(struct node);
           p->next=NULL;
           p->prev=NULL;
           if(temp1->x==0)
             p->x=1;
            else
             p->x=0;

         if(head==NULL)
         {    head=p;
         }
         else
         {      temp=head;
                while(temp->next!=NULL)
                {    temp=temp->next;   }
                temp->next=p;
                p->prev=temp;

          }
           temp1=temp1->next;
        }  cout<<"\n1's compliment of  binary no.";
         display();

        int f=0;
        while(temp!=NULL)
        {   if(temp->x==1)
            {   temp->x=0;   }
            else
            {   temp->x=1;   f=1;
                break;
            } temp=temp->prev;
        }
        if(f==0)
        {  node *p=new(struct node);
           p->next=NULL;
           p->prev=NULL;
           p->x=1;
           temp=head;
           head=p;
           head->next=temp;
           temp->prev=head;
         }
       cout<<"\n2's compliment of  binary no.";
         display();
      }
   void binary::comp()
   {

      cout<<"\n for first binary no.";
         temp1=head1;
         com();
         head=NULL;
      cout<<"\n for second binary no. ";
         temp1=head2;
         com();
   }





    void binary::display()
   {  temp=head;  cout<<"\n";
      while(temp->next!=NULL)
      { cout<<" "<<temp->x;;
        temp=temp->next;
      } cout<<" "<<temp->x<<"\n";
   }
          int main()
          {   cout<<"\n Doubly Linked List Programe for Binary operations "<<endl;

              binary b;
              int m;
              char ch;

             do{    cout<<"\nenter the choice";
                         cout<<"\n Enter 1 insert binary1";
                         cout<<"\n Enter 2 insert binary 2";
                         cout<<"\n Enter 3 add binary no.s";
                         cout<<"\n Enter 4 for 1's and 2's compliment of binary no."<<endl;
                         cin>>m;
                         switch(m)
                         {   case 1:   b.binary1();
                                                 break;
                              case 2:   b.binary2();
                                                 break;
                              case 3:   b.addition();
                                                 break;
                              case 4:   b.comp();
                                                 break;
                               default: cout<<"unknown choice";
                            }
                            cout<<" \nDo you want to continue press y  :";                        //Kumari Palak
                           cin>>ch;
                   }while(ch=='y'||ch=='Y');


              return 0;
              }
