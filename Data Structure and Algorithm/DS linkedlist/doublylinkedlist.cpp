#include<iostream>
using namespace std;

struct node  
{  
    struct node *prev;  
    struct node *next;  
    int data;  
};  

struct node *head;  

void insertion_beginning();  
void insertion_last();  
void insertion_specified();  
void deletion_beginning();  
void deletion_last();  
void deletion_specified();  
void display();  
void search(); 

void insertion_beginning()  
{  
   struct node *ptr;   
   int item;  
   ptr = (struct node *)malloc(sizeof(struct node));  
   if(ptr == NULL)  
   {  
       cout<<"\n OVERFLOW";  
   }  
   else  
   {  
        cout<<"\nEnter Item value";  
        cin>>item;  
      
   if(head==NULL)  
   {  
       ptr->next = NULL;  
       ptr->prev=NULL;  
       ptr->data=item;  
       head=ptr;  
   }  
   else   
   {  
       ptr->data=item;  
       ptr->prev=NULL;  
       ptr->next = head;  
       head->prev=ptr;  
       head=ptr;  
   }  
   cout<<"\n Node inserted\n";  
}  
     
}  
void insertion_last()  
{  
   struct node *ptr,*temp;  
   int item;  
   ptr = (struct node *) malloc(sizeof(struct node));  
   if(ptr == NULL)  
   {  
       cout<<"\n OVERFLOW";  
   }  
   else  
   {  
       cout<<"\n Enter value";  
       cin>>item;  
        ptr->data=item;  
       if(head == NULL)  
       {  
           ptr->next = NULL;  
           ptr->prev = NULL;  
           head = ptr;  
       }  
       else  
       {  
          temp = head;  
          while(temp->next!=NULL)  
          {  
              temp = temp->next;  
          }  
          temp->next = ptr;  
          ptr ->prev=temp;  
          ptr->next = NULL;  
          }  
             
       }  
     cout<<"\n node inserted\n";  
    }  
void insertion_specified()  
{  
   struct node *ptr,*temp;  
   int item,loc,i;  
   ptr = (struct node *)malloc(sizeof(struct node));  
   if(ptr == NULL)  
   {  
       cout<<"\n OVERFLOW";  
   }  
   else  
   {  
       temp=head;  
       cout<<"Enter the location";  
       cin>>loc;  
       for(i=0;i<loc;i++)  
       {  
           temp = temp->next;  
           if(temp == NULL)  
           {  
               cout<<"\n There are less than elements "<< loc;  
               return;  
           }  
       }  
       cout<<"Enter value";  
       cin>>item;  
       ptr->data = item;  
       ptr->next = temp->next;  
       ptr -> prev = temp;  
       temp->next = ptr;  
       temp->next->prev=ptr;  
       cout<<"\n node inserted \n";  
   }  
}  
void deletion_beginning()  
{  
    struct node *ptr;  
    if(head == NULL)  
    {  
        cout<<"\n UNDERFLOW";  
    }  
    else if(head->next == NULL)  
    {  
        head = NULL;   
        free(head);  
        cout<<"\n node deleted \n";  
    }  
    else  
    {  
        ptr = head;  
        head = head -> next;  
        head -> prev = NULL;  
        free(ptr);  
        cout<<"\n node deleted \n";  
    }  
  
}  
void deletion_last()  
{  
    struct node *ptr;  
    if(head == NULL)  
    {  
        cout<<"\n UNDERFLOW";  
    }  
    else if(head->next == NULL)  
    {  
        head = NULL;   
        free(head);   
        cout<<"\n node deleted\n";  
    }  
    else   
    {  
        ptr = head;   
        if(ptr->next != NULL)  
        {  
            ptr = ptr -> next;   
        }  
        ptr -> prev -> next = NULL;   
        free(ptr);  
        cout<<"\n node deleted\n";  
    }  
}  
void deletion_specified()  
{  
    struct node *ptr, *temp;  
    int val;  
    cout<<"\n Enter the data after which the node is to be deleted : ";  
    cin>>val;  
    ptr = head;  
    while(ptr -> data != val)  
    ptr = ptr -> next;  
    if(ptr -> next == NULL)  
    {  
        cout<<"\n Can't delete\n";  
    }  
    else if(ptr -> next -> next == NULL)  
    {  
        ptr ->next = NULL;  
    }  
    else  
    {   
        temp = ptr -> next;  
        ptr -> next = temp -> next;  
        temp -> next -> prev = ptr;  
        free(temp);  
        cout<<"\n node deleted\n";  
    }     
}  
void display()  
{  
    struct node *ptr;  
    cout<<"\n printing values...\n";  
    ptr = head;  
    while(ptr != NULL)  
    {  
        cout<<"\n"<<ptr->data;  
        ptr=ptr->next;  
    }  
}   
void search()  
{  
    struct node *ptr;  
    int item,i=0,flag;  
    ptr = head;   
    if(ptr == NULL)  
    {  
        cout<<"\n Empty List\n";  
    }  
    else  
    {   
        cout<<"\n Enter item which you want to search? \n";   
        cin>>item;  
        while (ptr!=NULL)  
        {  
            if(ptr->data == item)  
            {  
                cout<<"\n item found at location" <<i+1;  
                flag=0;  
                break;  
            }   
            else  
            {  
                flag=1;  
            }  
            i++;  
            ptr = ptr -> next;  
        }  
        if(flag==1)  
        {  
            cout<<"\n Item not found \n";  
        }  
    }             
}  

int main ()  
{  
int choice = 0;  
    while(choice != 9)  
    {  
        cout<<"\n\n*********Main Menu*********\n";  
        cout<<"\n Choose one option from the following list ...\n";  
        cout<<"\n 1. insert in begining"; 
        cout<<"\n 2. insert at last ";
        cout<<"\n 3. insert at any random location ";
        cout<<"\n 4. Delete from Beginning ";
        cout<<"\n 5. Delete from last ";
        cout<<"\n 6. Delete node after specified location "; 
        cout<<"\n 7. Search for an element ";
        cout<<"\n 8. Show ";
        cout<<"\n 9. exit  ";
        cout<<"\nEnter your choice?\n";         
        cin >> choice;  
 
        switch(choice)  
        {  
            case 1: insertion_beginning();  
                    break;  
            case 2: insertion_last();  
                    break;  
            case 3: insertion_specified();  
                    break;  
            case 4: deletion_beginning();  
                    break;  
            case 5: deletion_last();  
                    break;  
            case 6: deletion_specified();  
                    break;  
            case 7: search();  
                    break;  
            case 8: display();  
                    break;  
            case 9: exit(0);  
                    break;  
            default: cout<<"Please enter valid choice..";  
        }  
    }  
}  