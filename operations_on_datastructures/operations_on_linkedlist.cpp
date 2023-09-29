#include <stdio.h>
#include <stdlib.h>
// contributed by "THE GEEKY ABHI"
// a simple program to understand the operations on linkedlist
struct node
{
    int data;
    struct node *next;
};
struct node *start = NULL;

void search() 
{
    int target;
    printf("enter the element you want to search : ");
    scanf("%d" , &target);
    struct node*p = start;
    
    int pos= 1;
    while (p->data!= target)
    {
        pos++;

        p=p->next;

        if(p== NULL)
        {
            printf("Element is not present in the linked list \n");
            return;
        }
    }

    printf("Element found at position : %d " , pos);
    
}

void display()
{
    if (start == NULL)
    {
        printf("Please create a linkedList first \n");
        return;
    }
    struct node *p = start;
    while (p != NULL)
    {
        printf("%d --> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

void create()
{

    start = (struct node *)malloc(sizeof(struct node));
    struct node *p = start;
    int item;
    int n;
    printf("Enter the size of the linked list : ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        printf("Enter the data for %d element: ", i);
        scanf("%d", &item);
        p->data = item;
        if (i < n) // Allocate memory only if it's not the last node
        {
            p->next = (struct node *)malloc(sizeof(struct node));
            p = p->next;
        }
        else
        {
            p->next = NULL; // Set the next of the last node to NULL
        }
    }
}

void add_beg()
{
    if (start == NULL)
    {
        printf("Please create a linkedList first \n");
        return;
    }
    int item;
    struct node *p, *temp;
    p = start;
    printf("Enter the element: ");
    scanf("%d", &item);

    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->next = p;
    start = temp;
}

void add_pos()
{

    if (start == NULL)
    {
        printf("Please create a linkedList first \n");
        return;
    }
    int pos, item;
    printf("Enter the position : ");
    scanf("%d", &pos);

    printf("Enter the Item : ");
    scanf("%d", &item);

    struct node *temp, *p;
    p = start;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;

    for (int i = 1; i < pos - 1; i++)
    {
        p = p->next;
    }

    temp->next = p->next;
    p->next = temp;
}
void add_after()
{
    if (start == NULL)
    {
        printf("Please create a linkedList first \n");
        return;
    }
    int pos, item;
    printf("Enter the position : ");
    scanf("%d", &pos);

    printf("Enter the Item : ");
    scanf("%d", &item);

    struct node *temp, *p;
    p = start;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;

    for (int i = 1; i < pos ; i++)
    {
        p = p->next;
    }

    temp->next = p->next;
    p->next = temp;
}

void get_size()
{
     if (start == NULL)
    {
        printf("Please create a linkedList first \n");
        return;
    }

    struct node *p = start;
    int count=0;

    while(p!=NULL)
    {
        count++;
        p= p->next;
    }

    printf("\nSize of linkedList is : %d " , count );
}

void add_end()
{
     if (start == NULL)
    {
        printf("Please create a linkedList first \n");
        return;
    }

    struct node *p = start , *temp;

    int item;
    printf("Enter the number : ");
    scanf("%d" , &item);
    temp = (struct node*) malloc(sizeof(struct node));


    while(p->next!=NULL)
    {
        p = p->next;

    }
    temp->data = item;

    p->next = temp;
    temp->next = NULL;


    
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n-----------------Menu---------------------\n");
        printf("1.Create a linked list \n2.Display\n3.Add at beginnnig\n4.Add at given position\n5.Add after position\n6.Insert at end\n7.Get size of linkedlist\n 8. Search in linkedlist\n\tYour choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create();
            break; 
        case 2:
            display();
            break;
        case 3:
            add_beg();
            break;
        case 4:
            add_pos();
            break;
        case 5:
            add_after();
            break;

        case 6:
        add_end();
        break;

        case 7:
        get_size();

        case 8:
        search();
        break;
        default:
            printf("Enter valid numbers only ");
        }
    }
    return 0;
}
