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
void deletion_beginning();  
void deletion_last();  
void display();  
void search();  


void insertion_beginning()  
{  
   struct node *ptr,*temp;   
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
    ptr->data=item;  
   if(head==NULL)  
   {  
      head = ptr;  
      ptr -> next = head;   
      ptr -> prev = head;   
   }  
   else   
   {  
       temp = head;   
    while(temp -> next != head)  
    {  
        temp = temp -> next;   
    }  
    temp -> next = ptr;  
    ptr -> prev = temp;  
    head -> prev = ptr;  
    ptr -> next = head;  
    head = ptr;  
   }  
   cout<<"\n Node inserted \n";  
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
           head = ptr;  
           ptr -> next = head;   
           ptr -> prev = head;   
       }  
       else  
       {  
          temp = head;  
          while(temp->next !=head)  
          {  
              temp = temp->next;  
          }  
          temp->next = ptr;  
          ptr ->prev=temp;  
          head -> prev = ptr;  
      ptr -> next = head;  
        }  
   }  
    cout<<" \n node inserted \n";  
}  
  
void deletion_beginning()  
{  
    struct node *temp;  
    if(head == NULL)  
    {  
        cout<<"\n UNDERFLOW";  
    }  
    else if(head->next == head)  
    {  
        head = NULL;   
        free(head);  
        cout<<"\n node deleted \n";  
    }  
    else  
    {  
        temp = head;   
        while(temp -> next != head)  
        {  
            temp = temp -> next;  
        }  
        temp -> next = head -> next;  
        head -> next -> prev = temp;  
        free(head);  
        head = temp -> next;  
    }  
  
}  
void deletion_last()  
{  
    struct node *ptr;  
    if(head == NULL)  
    {  
       cout<<"\n UNDERFLOW";  
    }  
    else if(head->next == head)  
    {  
        head = NULL;   
        free(head);   
        cout<<"\n node deleted\n";  
    }  
    else   
    {  
        ptr = head;   
        if(ptr->next != head)  
        {  
            ptr = ptr -> next;   
        }  
        ptr -> prev -> next = head;  
        head -> prev = ptr -> prev;    
        free(ptr);  
        cout<<"\n node deleted \n";  
    }  
}  
  
void display()  
{  
    struct node *ptr;  
    ptr=head;  
    if(head == NULL)  
    {  
        cout<<"\n nothing to print";  
    }     
    else  
    {  
        cout<<"\n printing values ... \n";  
          
        while(ptr -> next != head)  
        {  
          
            cout<<"\n"<<ptr -> data;  
            ptr = ptr -> next;  
        }  
        cout<<"\n"<<ptr -> data;  
    }  
              
}  
  
void search()  
{  
    struct node *ptr;  
    int item,i=0,flag=1;  
    ptr = head;   
    if(ptr == NULL)  
    {  
        cout<<"\n Empty List\n";  
    }  
    else  
    {   
        cout<<"\n Enter item which you want to search?\n";   
        cin>>item;  
        if(head ->data == item)  
        {  
            cout<<"item found at location "<<i+1;  
            flag=0;  
        }  
        else   
        {  
        while (ptr->next != head)  
        {  
            if(ptr->data == item)  
            {  
                cout<<"item found at location "<<i+1;  
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
        }  
        if(flag != 0)  
        {  
            cout<<"Item not found\n";  
        }  
    }            
}  

int main ()  
{  
int choice =0;  
    while(choice != 9)  
    {  
        cout<<"\n\n*********Main Menu*********\n";  
        cout<<"\n Choose one option from the following list ...\n";  
        cout<<"\n 1. insert in begining"; 
        cout<<"\n 2. insert at last ";
        cout<<"\n 3. Delete from Beginning ";
        cout<<"\n 4. Delete from last ";
        cout<<"\n 5. Search for an element ";
        cout<<"\n 6. Show ";
        cout<<"\n 7. exit  ";
        cout<<"\nEnter your choice?\n";         
        cin >> choice; 

        switch(choice)  
        {  
            case 1: insertion_beginning();  
                    break;  
            case 2: insertion_last();  
                    break;  
            case 3: deletion_beginning();  
                    break;  
            case 4: deletion_last();  
                    break;  
            case 5: search();  
                    break;  
            case 6: display();  
                    break;  
            case 7: exit(0);  
                    break;  
            default:cout<<"Please enter valid choice..";  
        }  
    }  
}  