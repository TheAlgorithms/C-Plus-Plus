// program/operations  on doubly linked list

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;
struct node *n1 = NULL;
int totalNoOfNodes = 0;
void createLinklist(int n)
{
    int i,item;
    struct node *ptr;
    for(i=0;i<n;i++)
    {
       printf("enter data \n");
       scanf("%d",&item);

       ptr = (struct node *)malloc(sizeof(struct node));
       ptr->data = item;
       ptr->next = NULL;
       ptr->prev = NULL;

       if(head == NULL)
       {
           head = ptr;
           n1 = ptr;
       }
       else
       {
           n1->next = ptr;
           ptr->prev = n1;
           n1 = n1->next;
       }

     totalNoOfNodes++;
     printf("Node created \n");
    }
 printf("Total number of nodes  = %d \n",totalNoOfNodes);
}

void traverseList()
{
    struct node *ptr;
    ptr = head;
    printf("=================================================\n");
    printf("Forword Traversing .. \n");
    while(ptr != NULL)
    {
        printf("  %d",ptr->data);
        ptr = ptr->next;
    }

    ptr = n1;
    printf("\n------------------------------------------------\n");
    printf("Backword Traversing ...\n");
    while(ptr != NULL)
    {
        printf(" %d",ptr->data);
        ptr = ptr->prev;
    }
    printf("\n=================================================\n");
}
void insertAtBegin()
{
    int item;
    struct node *ptr;

    printf("Enter item value\n");
    scanf("%d",&item);

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data =item;
    ptr->next = NULL;
    ptr->prev = NULL;

    ptr->next = head;
    head->prev = ptr;
    head = ptr;

    totalNoOfNodes++;
    printf("Node inserted at first\n");
    printf("Total number of nodes  = %d \n",totalNoOfNodes);

}

void insertAtEnd()
{
    int item;
    struct node *ptr;

    printf("Enter data value \n");
    scanf("%d",&item);

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = item;
    ptr->next = NULL;
    ptr->prev = NULL;

    n1->next = ptr;
    ptr->prev = n1;
    n1 = n1->next;

    totalNoOfNodes++;
    printf("node inserted at end\n");
    printf("Total number of nodes  = %d \n",totalNoOfNodes);

}

void insertAfterGivenNode()
{
    int NodeData,item;
    struct node *ptr,*temp,*temp1;

    printf("Enter item\n");
    scanf("%d",&item);

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = item;
    ptr->next = NULL;
    ptr->prev = NULL;

    printf("Enter node Value \n");
    scanf("%d",&NodeData);

    temp = head;
    temp1 = head->next;
    while(temp->data != NodeData)
    {
        temp = temp->next;
        temp1 = temp1->next;
    }

    //printf("temp->data = %d\n",temp->data);
    //printf("temp1->data = %d\n",temp1->data);

    ptr->prev = temp;
    ptr->next = temp->next;
    temp->next = ptr;
    temp1->prev = ptr;

    totalNoOfNodes++;
    printf("node inserted after desired node \n");
    printf("Total number of nodes  = %d \n",totalNoOfNodes);


}

void insertBeforeGivenNode()
{
    int item,Nodedata;
    struct node *ptr,*temp,*temp1;

    printf("Enter data value \n");
    scanf("%d",&item);

    ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = item;
    ptr->next = NULL;
    ptr->prev = NULL;

    printf("Enter node data \n");
    scanf("%d",&Nodedata);

    temp = head;
    temp1 = head->next;

    while(temp1->data != Nodedata)
    {
        temp=temp->next;
        temp1 = temp1->next;
    }

    //printf("temp->data = %d\n",temp->data);
    //printf("temp1->data = %d\n",temp1->data);

    ptr->prev = temp;
    ptr->next = temp1;
    temp->next = ptr;
    temp1->prev = ptr;

    totalNoOfNodes++;
    printf("Node inserted \n");
    printf("Total number of nodes  = %d \n",totalNoOfNodes);

}

void reverseLinkedlist()
{
    struct node *first , *second , *third ;
    first = head;
    second = head;
    third = head->next;
    first->next = NULL;
    n1 = first;
    //printf("first->data = %d \n",first->data);
    //printf("second->data = %d \n",second->data);
    //printf("third->data = %d \n",third->data);
    while(third != NULL)
    {
        second = third;
        third = third->next;
        second->next = first;
        first->prev = second;
        first = second;
       // printf("In loop first->data = %d \n",first->data);
        //printf("In loop second->data = %d \n",second->data);
       // printf("In loop third->data = %d \n",third->data);

    }
    head = second;
    second->prev = NULL;
   // printf("Forword list data : first->data = %d , second->data = %d ",
            //first->data,second->data);

}

void findPairswithGivenSum()
{
    int sum;
    printf("Enter sum\n");
    scanf("%d",&sum);
    struct node *first,*last,*temp;
    temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    printf("temp->data = %d",temp->data);
    first = head;
    last = temp;
    while(first != last)
    {
        if((first->data + last->data)== sum)
        {
            printf("pair = ( %d , %d )\n",first->data,last->data);
            first=first->next;
            last = last->prev;
        }
        else if((first->data + last->data) > sum)
        {
            last = last->prev;
        }
        else if((first->data + last->data) < sum )
        {
            first = first->next;
        }

        if(first->next == last || last->prev == first)
        {
             if((first->data + last->data)== sum)
             {
               printf("pair = ( %d , %d )\n",first->data,last->data);
             }
            break;
        }
    }
}
/*inserting node in sorted way in sorted linked list */
void insertNodeInSortedway()
{
    struct node *temp,*ptr;
    int val;
    printf("Enter node value \n");
    scanf("%d",&val);

    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    temp->prev = NULL;

    ptr = head;
    while(ptr->next!=NULL)
    {
        if( temp->data > ptr->data && temp->data < ptr->next->data)
        {
            temp->next = ptr->next;
            ptr->next = temp;
            temp->prev = ptr;
            printf("Node inserted \n");
        }

        ptr = ptr->next;
    }

   // printf("ptr->data = %d\n",ptr->data);
    if(temp->data > ptr->data)
    {
        ptr->next = temp;
        temp->prev = ptr;
        n1 = n1->next;
    }

}

int GetPairCnt(struct node *first,struct node *second , int value)
{
    int cnt = 0;
    if((first->data+second->data)==value)
    {
        cnt++;
        first = first->next;
        second = second->next;
    }

    if((first->data+second->data)<value)
    {
        first= first->next;
    }
    else
    {
        second=second->prev;
    }

    return cnt;
}
void calculateTriplet()
{
    int sum ,tripletCnt=0;
    struct node *first,*current,*last;
    printf("Enter sum \n");
    scanf("%d",&sum);

    last = head;
    while(last->next != NULL)
    {
        last= last->next;
    }

    for(current = head;current!=NULL;current=current->next)
    {
        first = current->next;

        tripletCnt +=GetPairCnt(first,last,sum-current->data);

    }

    printf("Triplet count = %d\n",tripletCnt);
}

void deleteAllOccurancesOfNode()
{
    int nodeValue;
    struct node *curr,*pre,*temp;
    printf("Enter Node value \n");
    scanf("%d",&nodeValue);
    curr = head->next;
    pre = head;

    if(pre->data == nodeValue)
    {
        pre = pre->next;
        head = pre;
    }
    while(curr!=NULL)
    {
         if(curr->data == nodeValue)
         {
             pre->next = curr->next;
             curr->next->prev = pre;
             curr = pre->next;

             printf("Node deleted\n");
         }
         else
         {
            pre = pre->next;
            curr= curr->next;
         }
         printf("prev->next = %d\n",pre->data);
         printf("curr->data = %d\n",curr->data);

    }

}
int main()
{
   char choice;
   int noOfNodes;
   while(1)
   {
        printf("==============================================\n");
        printf("                                              \n");
        printf("***** give your choice ***** \n");
        printf("***** Press a for linked list creation ***** \n");
        printf("***** Press b for traversing list *****\n");
        printf("***** Press c for insertion of node at begining *****\n");
        printf("***** Press d for insertion of node at end *****\n");
        printf("***** Press e for inserting node after given node *****\n");
        printf("***** Press f for inserting node before given node *****\n");
        printf("***** Press g for reversing Double linked list *****\n");
        printf("***** Press h for finding pairs with given sum *****\n");
        printf("***** Press i for insert node in sorted way *****\n");
        printf("***** Press j for calculating triplet with sum equal to value *****\n");
        printf("***** Press k for deleting all occurances of given node *****\n");
        printf("***** Press m for removing all duplicates from sorted linked list *****\n");
        printf("                                              \n");
        printf("===============================================\n");
        scanf("%c",&choice);
        switch(choice)
        {
            case 'a':
                printf("Enter number of nodes for linklist \n");
                scanf("%d",&noOfNodes);
                createLinklist(noOfNodes);
            break;

            case 'b':
                traverseList();
            break;

            case 'c':
                insertAtBegin();
            break;

            case 'd':
                insertAtEnd();
            break;

            case 'e':
                insertAfterGivenNode();
            break;

            case 'f':
                insertBeforeGivenNode();
            break;

            case 'g':
                reverseLinkedlist();
            break;

            case 'h':
                findPairswithGivenSum();
            break;

            case 'i':
                insertNodeInSortedway();
            break;

            case 'j':
                calculateTriplet();
            break;

            case 'k':
                deleteAllOccurancesOfNode();
            break;

            default:
                printf("Invalid choice \n");
        }
        fflush(stdin);
   }

    return 0;
}
