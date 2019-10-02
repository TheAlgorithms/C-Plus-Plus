/*
Author: Anshu Kumar
Sorting a Linked List using Insertion Sort in C++.
Example:
Consider a singly linked list
 3-> 7-> 2-> 8-> 1-> 9-> 9-> 5-> 6-> NULL
After insertion sort, the resultant list should be
 1-> 2-> 3-> 5-> 6-> 7-> 8-> 9-> 9-> NULL
 */

    #include <bits/stdc++.h>
    #include<iostream>
    using namespace std;
     
    
    struct node
    {
       int data;
       node * next;
    };
     
    /*Function that inserts nodes in front of
    Given Linked List*/
    void InsFront(node **head,int data)
    {
       node *temp = new node;
       temp->data = data;
       temp->next = *head;
       *head = temp; 
    }
    /*Function that inserts nodes in sorted order*/
    void sorted_insert(node **head, int n)
    {
       
       node *temp = new node;
       temp->data = n;
     
       
       if(*head == NULL||(*head)->data >= n)
       {
          
          temp->next = *head;
          *head = temp;
       }
     
       else
       {
          
          node *prev = *head;
          node *curr = prev->next;
     
          
          while(curr != NULL)
          {
             
             if(prev->data < n && n < curr->data)
             {
                
                prev->next = temp;
                temp->next = curr;
                return;
             }
     
             
             prev = prev->next;
             curr = curr->next;
          }
     
          
          prev->next = temp;
          temp->next= curr;
       }
    }
    /*Function to apply insertion sort on list*/
    void ins_sort(node **head)
    {
       
       if(*head == NULL)
          return;
       
       
       node *sorted_list = NULL;
       
       node *curr = *head;
       
       while(curr != NULL)
       {
         
          sorted_insert(&sorted_list,curr->data);
          curr = curr->next;
       }
       
       
       *head = sorted_list;
    }
    
    void printList(node *head)
    {
      while (head != NULL)
      {
         cout<<head->data<<"-> ";
         head = head->next;
      }
      cout<<"NULL";
    }
     
    /* Driver program to test above functions*/
    int main()
    {
       node* head = NULL;
     
        InsFront(&head, 6);
        InsFront(&head, 5);
        InsFront(&head, 9);
        InsFront(&head, 9);
        InsFront(&head, 1);
        InsFront(&head, 8);
        InsFront(&head, 2);
        InsFront(&head, 7);
        InsFront(&head, 3);
      
        cout<<"Linked list is:\n";
        printList(head);
     
        /*Calling Insertion sort function*/
        ins_sort(&head);
        
        cout<<"\nSorted Linked list is:\n";
        printList(head);
        
      return 0;
    }


/*
 Output:
    Linked list is:
    3-> 7-> 2-> 8-> 1-> 9-> 9-> 5-> 6-> NULL
    Sorted Linked list is:
    1-> 2-> 3-> 5-> 6-> 7-> 8-> 9-> 9-> NULL
*/
