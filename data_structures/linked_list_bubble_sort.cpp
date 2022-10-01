/**
 * @file
 * @brief Bubble sort algorithm
 *
 * The working principle of the Bubble sort algorithm:
Bubble sort algorithm is the bubble sorting algorithm. The most important reason
for calling the bubble is that the largest number is thrown at the end of this
algorithm. This is all about the logic. In each iteration, the largest number is
expired and when iterations are completed, the sorting takes place.
What is Swap?
Swap in the software means that two variables are displaced.
An additional variable is required for this operation. x = 5, y = 10.
We want x = 10, y = 5. Here we create the most variable to do it.
int z;
z = x;
x = y;
y = z;
The above process is a typical displacement process.
When x assigns the value to x, the old value of x is lost.
That's why we created a variable z to create the first value of the value of x,
and finally, we have assigned to y.
Bubble Sort Algorithm Analysis (Best Case - Worst Case - Average Case)
Bubble Sort Worst Case Performance is O (n²). Why is that? Because if you
remember Big O Notation, we were calculating the complexity of the algorithms in
the nested loops. The n * (n - 1) product gives us O (n²) performance. In the
worst case all the steps of the cycle will occur. Bubble Sort (Avarage Case)
Performance. Bubble Sort is not an optimal algorithm. in average, O (n²)
performance is taken. Bubble Sort Best Case Performance. O (n). However, you
can't get the best status in the code we shared above. This happens on the
optimized bubble sort algorithm. It's right down there.
What is Linked List?
 The linked list is a data structure used for holding a sequence of
 values, which can be added, removed and displayed.
 its Algorithm -
 Values can be added by iterating to the end of a list(by following
 the pointers) starting from the first link. Whichever link points to null
 is considered the last link and is pointed to the new value.
 Values can be removed by also iterating through the list. When the node
 containing the value is found, the node pointing to the current node is made
 to point to the node that the current node is pointing to, and then returning
 the current node to heap store.
 */
#include <iostream>
// This is the structure of a node
class Node
{
public:
    int data;
    Node *next; // the pointer to next node in singly linked list
};
// swap function
Node *swap(Node *ptr1, Node *ptr2)
{
    Node *tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

// bubblesort function
int bubbleSort(Node **head, int count)
{
    Node **h; // using double pointers
    int i, j, swapped;

    for (i = 0; i < count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            Node *p1 = *h;
            Node *p2 = p1->next;

            if (p1->data > p2->data)
            {

                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        if (swapped == 0)
            break;
    }
}

void printList(Node *n)
{
    while (n != NULL)
    {
        std::cout << n->data << " -> ";
        n = n->next;
    }
    std::cout << "NULL" << std::endl;
}

void insertAtTheBegin(Node **start_ref, int data)
{
    Node *ptr1 = new Node;

    ptr1->data = data;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}

int main()
{
    int arr[10];
    int size, i;
    std::cout << "Enter ten numbers to be sorted in linked list: \n";
    // inserting 10 values
    for (i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
    Node *head = NULL;
    size = sizeof(arr) / sizeof(arr[0]);

    for (i = 0; i < size; i++)
    {
        insertAtTheBegin(&head, arr[i]);
    }
    std::cout << "Linked list before sorting: \n";
    printList(head);
    bubbleSort(&head, size);
    std::cout << "Linked list after sorting: \n";
    printList(head);

    return 0;
}
