#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int num;
    node *next;
}*head; //node constructed

void createlist(int n);
void reverse(node **head);
void display();

int main()
{
    int n,num,item;

    cout<<"Enter the number of nodes: ";
    cin>>n;
    createlist(n);
    cout<<"\nLinked list data: \n";
    display();
    cout<<"\nAfter reversing\n";
    reverse(&head);
    display();
   return 0;
}
void createlist(int n) //function to create linked list.
{
    struct node *newnode, *tmp;
    int num, i;

    head = (struct node *)malloc(sizeof(struct node));
    if(head == NULL)
    {
        cout<<" Memory can not be allocated";
    }
    else
    {

        cout<<"Enter the data for node 1: ";
        cin>>num;
        head-> num = num;
        head-> next = NULL; //Links the address field to NULL
        tmp = head;

        for(i=2; i<=n; i++)
        {
            newnode = (struct node *)malloc(sizeof(struct node));


            if(newnode == NULL) //If newnode is null no memory cannot be allotted
            {
                cout<<"Memory can not be allocated";
                break;
            }
            else
            {
                cout<<"Enter the data for node "<<i<<": "; // Entering data in nodes.
                cin>>num;
                newnode->num = num;
                newnode->next = NULL;
                tmp->next = newnode;
                tmp = tmp->next;
            }
        }
    }
}

void reverse(node **head) //function to reverse linked list
{
    struct node *temp = NULL;
    struct node *prev = NULL;
    struct node *current = (*head);
    while(current != NULL) {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    (*head) = prev;
}
void display()//function to display linked list
{
    struct node *tmp;
    if(head == NULL)
    {
        cout<<"List is empty";
    }
    else
    {
        tmp = head;
        while(tmp != NULL)
        {
            cout<<tmp->num<<" ";
            tmp = tmp->next;
        }
    }
}
