#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;

};

int totalNodesInlist;
struct node *head,*n1;
void CreateLinkList(int n)
{
    int i,item;
    struct node *tempptr;
    for(i=0;i<n;i++)
    {
        printf("\n enter item");
        scanf("%d",&item);

        tempptr = (struct node *)malloc(sizeof(struct node));
        if(tempptr == NULL)
        {
            printf("\n error in memory allocation");
            continue;
        }

        tempptr->data = item;
        tempptr->link = NULL;
        if(head == NULL)
        {
            head = tempptr;
            n1 = head;
        }
        else
        {
            n1->link = tempptr;
            n1 = n1->link;
            n1->link = head;
        }
        totalNodesInlist++;
        printf("node inserted\n");

    }
    printf("\n total nodes in Linked List = %d\n",totalNodesInlist);
}

void TraverseLinkList()
{
   struct node *first,*ptr;
   first = head;
   ptr = head;

   if(first != NULL)
   {
      printf("====================================\n");
      printf("linked list elements : ");
       do
       {
           printf("%d  ",ptr->data);
           ptr = ptr->link;
       }while(ptr != first);
      printf("\n");
      printf("=====================================\n");
   }
   else
   {
       printf("empty circular linked list\n");
   }
}

int CountNoOfnodes()
{
    int nodeCnt = 0;
    struct node *first,*ptr;
   first = head;
   ptr = head;

   if(first != NULL)
   {
      printf("====================================\n");
      printf("linked list elements : ");
       do
       {
           printf("%d  ",ptr->data);
           nodeCnt++;
           ptr = ptr->link;
       }while(ptr != first);
      printf("\n");
      printf("=====================================\n");
   }
   else
   {
       printf("empty circular linked list\n");
   }
 return nodeCnt;
}
void insetionAtBeg()
{
    struct node *temp,*ptr,*first;
    int item;
    printf("enter item\n");
    scanf("%d",&item);

    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->link = NULL;

    ptr = head;
    first = head;

    do
    {
        ptr = ptr->link;
    }while(ptr->link != first);

    temp->link = head;
    head = temp;
    ptr->link = temp;
    totalNodesInlist++;
    printf("Node inserted at begining \n");

}
void insertionAtEnd()
{
    struct node *ptr,*temp;
    int item;

    printf("enter item\n");
    scanf("%d",&item);

    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->link = NULL;

    ptr = head;

    do
    {
        ptr = ptr->link;

    }while(ptr->link !=  head);
    printf("ptr->data = %d",ptr->data);
    ptr->link =  temp;
    temp->link = head;
    n1 = n1->link;
    totalNodesInlist++;
    printf("Node inserted at End\n");
}
void insertAfterGivenNode()
{
    struct node *temp,*ptr;

    int item , NdValue;
    printf("Enter item\n");
    scanf("%d",&item);

    printf("Enter Node after which element will be inserted \n");
    scanf("%d",&NdValue);

    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->link = NULL;

    ptr = head;

    do
    {
        ptr = ptr->link;

    }while(ptr->data != NdValue);

    printf("ptr->data = %d\n",ptr->data);
    temp->link = ptr->link;
    ptr->link = temp;

    printf("Node inserted \n");

}
void deleteGivenNode()
{
    int NdValue;
    struct node *curr,*prev,*temp;
    printf("Enter node to be deleted \n");
    scanf("%d",&NdValue);
    prev = head;
    curr = head;

    while(curr->data != NdValue)
    {
        if(curr != prev)
        {
            prev = prev->link;
        }

        curr = curr->link;
    }

    printf("prev->Data = %d\n",prev->data);
    printf("curr->data = %d\n",curr->data);

    temp =curr;
    prev->link = curr->link;
    free(curr);
}
void findLoopinlist()
{
    struct node *first,*slow,*fast;

    first = head;
    slow = first;
    fast = slow;

    while( slow!= NULL && fast != NULL)
    {
        slow = slow->link;
        fast = fast->link->link;

        if(slow == fast)
        {
            printf("loop found \n");
            return ;
        }

    }

    printf("loop not found \n");
 return ;
}
int main()
{
    char choice;
    int noOfNodes , nodeCnt=0;
    while(1)
    {
        printf("==============================================\n");
        printf("                                              \n");
        printf("***** give your choice ***** \n");
        printf("***** Press a for linked list creation ***** \n");
        printf("***** Press b for traversing list *****\n");
        printf("***** Press c for counting nodes in circular linked list *****\n");
        printf("***** Press d for insertion of node at begining *****\n");
        printf("***** Press e for insertion of node at end of list *****\n");
        printf("***** Press f for insertion of node after given node *****\n");
        printf("***** Press g for deleting given node *****\n");
        printf("***** Press h for checking loop in linked list *****\n");
        printf("                                              \n");
        printf("===============================================\n");

        scanf("%c",&choice);

        switch(choice)
        {
            case 'a':
                printf("Enter number of nodes for linklist \n");
                scanf("%d",&noOfNodes);
                CreateLinkList(noOfNodes);
            break;

            case 'b':
                TraverseLinkList();
            break;

            case 'c':
                nodeCnt = 0;
                nodeCnt = CountNoOfnodes();
                printf("no of nodes in circular linked list = %d\n",nodeCnt);
            break;

            case 'd':
                insetionAtBeg();
            break;

            case 'e':
                insertionAtEnd();
            break;

            case 'f':
                insertAfterGivenNode();
            break;

            case 'g':
                deleteGivenNode();
            break;

            case 'h':
                findLoopinlist();
            break;
            default:
                printf("Invalid choice\n");
        }
        fflush(stdin);
    }
    return 0;
}
