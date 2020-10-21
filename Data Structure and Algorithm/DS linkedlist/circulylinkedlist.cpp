#include<iostream>
using namespace std;

struct node   
{  
    int data;  
    struct node *next;   
};  
struct node *head;  
  
void beginsert ();   
void lastinsert ();  
void randominsert();  
void begin_delete();  
void last_delete();  
void random_delete();  
void display();  
void search();  


void beginsert()  
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
        cout<<"\n Enter the node data?";  
        cin>>item;  
        ptr -> data = item;  
        if(head == NULL)  
        {  
            head = ptr;  
            ptr -> next = head;  
        }  
        else   
        {     
            temp = head;  
            while(temp->next != head)  
                temp = temp->next;  
            ptr->next = head;   
            temp -> next = ptr;   
            head = ptr;  
        }   
        cout<<"\n node inserted \n";  
    }  
              
}  
void lastinsert()  
{  
    struct node *ptr,*temp;   
    int item;  
    ptr = (struct node *)malloc(sizeof(struct node));  
    if(ptr == NULL)  
    {  
        cout<<"\n OVERFLOW\n";  
    }  
    else  
    {  
        cout<<"\n Enter Data?";  
        cin>>item;  
        ptr->data = item;  
        if(head == NULL)  
        {  
            head = ptr;  
            ptr -> next = head;    
        }  
        else  
        {  
            temp = head;  
            while(temp -> next != head)  
            {  
                temp = temp -> next;  
            }  
            temp -> next = ptr;   
            ptr -> next = head;  
        }    
        cout<<"\n node inserted\n";  
    }   
}  
void begin_delete()  
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
    {   ptr = head;   
        while(ptr -> next != head)  
            ptr = ptr -> next;   
        ptr->next = head->next;  
        free(head);  
        head = ptr->next;  
        cout<<"\n node deleted\n";  
  
    }  
}  
void last_delete()  
{  
    struct node *ptr, *preptr;  
    if(head==NULL)  
    {  
        cout<<"\n UNDERFLOW";  
    }  
    else if (head ->next == head)  
    {  
        head = NULL;  
        free(head);  
        cout<<"\n node deleted\n";  
  
    }  
    else   
    {  
        ptr = head;  
        while(ptr ->next != head)  
        {  
            preptr=ptr;  
            ptr = ptr->next;  
        }  
        preptr->next = ptr -> next;  
        free(ptr);  
        cout<<"\n node deleted\n";  
  
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
        cout<<"\n Enter item which you want to search? \n";   
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
                cout<<" item found at location "<<i+1;  
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
int main()  
{  
    int choice = 0;  
    while(choice != 7)   
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
            case 1: beginsert();      
                    break;  
            case 2: lastinsert();         
                    break;  
            case 3: begin_delete();       
                    break;  
            case 4: last_delete();        
                    break;  
            case 5: search();         
                    break;  
            case 6: display();        
                    break;  
            case 7: exit(0);  
                    break;  
            default: cout<<"Please enter valid choice..";  
        }  
    }  
}  