#include <stdio.h>
#include <stdlib.h>
/* Structure of a node */
struct node
{
    int data;          //Data part
    struct node *next; //Address part
} * head;

/* Functions used in the program */
void createList(int n);
int countPairs(struct Node *head1, struct Node *head2, int x)
{
    int count = 0;

    struct Node *p1, *p2;

    // traverse the 1st linked list
    for (p1 = head1; p1 != NULL; p1 = p1->next)

        // for each node of 1st list
        // traverse the 2nd list

        for (p2 = head2; p2 != NULL; p2 = p2->next)

            // if sum of pair is equal to 'x'
            // increment count
            if ((p1->data + p2->data) == x)
                count++;

    // required count of pairs
    return count;
}

void displayList();

int main()
{
    int n, choice;

    /*
     * Create a singly linked list of n nodes
     */
    printf("Enter the total number of nodes: ");
    scanf("%d", &n);
    createList(n);

    cout << "Count = "
         << countPairs(head1, head2,20);

    printf("\nData in the list\n");
    displayList();

    return 0;
}

/*
 * Create a list of n nodes
 */
void createList(int n)
{
    struct node *newNode, *temp;
    int data, i;

    if (n <= 0)
    {
        printf("List size must be greater than zero.\n");
        return;
    }

    head = (struct node *)malloc(sizeof(struct node));

    /*
     * If unable to allocate memory for head node
     */
    if (head == NULL)
    {
        printf("Unable to allocate memory.");
    }
    else
    {
        /*
         * Read data of node from the user
         */
        printf("Enter the data of node 1: ");
        scanf("%d", &data);

        head->data = data; // Link the data field with data
        head->next = NULL; // Link the address field to NULL

        temp = head;

        /*
         * Create n nodes and adds to linked list
         */
        for (i = 2; i <= n; i++)
        {
            newNode = (struct node *)malloc(sizeof(struct node));

            /* If memory is not allocated for newNode */
            if (newNode == NULL)
            {
                printf("Unable to allocate memory.");
                break;
            }
            else
            {
                printf("Enter the data of node %d: ", i);
                scanf("%d", &data);

                newNode->data = data; // Link the data field of newNode with data
                newNode->next = NULL; // Link the address field of newNode with NULL

                temp->next = newNode; // Link previous node i.e. temp to the newNode
                temp = temp->next;
            }
        }

        printf("SINGLY LINKED LIST CREATED SUCCESSFULLY\n");
    }
}
void displayList()
{
    struct node *temp;

    /*
     * If the list is empty i.e. head = NULL
     */
    if (head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = head;
        while (temp != NULL)
        {
            printf("Data = %d\n", temp->data); // Print the data of current node
            temp = temp->next;                 // Move to next node
        }
    }
}
