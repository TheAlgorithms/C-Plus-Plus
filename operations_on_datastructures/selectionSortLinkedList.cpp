#include <iostream>
using namespace std;

//node defined
class node
{
public:
    int data;
    node *link;
    node(int d)
    {
        data = d;
        link = NULL;
    }
};

//printing the linked list
void print(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

//creating the linked list with 'n' nodes
node *createlist(int n)
{
    node *head = NULL;
    node *t = NULL;
    for (int i = 0; i < n; i++)
    {
        node *temp = NULL;
        int num;
        cin >> num;
        temp = new node(num);
        if (head == NULL)
        {
            head = temp;
            t = temp;
            continue;
        }
        if (t->link == NULL)
            t->link = temp;
        t = temp;
    }
    return head;
}

//performing selection sort on the linked list in an iterative manner
void my_selection_sort_linked_list(node *&head)
{
    node *min = head;          //throughout the algorithm 'min' is used to denote the node with min value out of all the nodes left for scanning
                               //while scanning if we find a node 'X' with value lesser than min,
                               //then we update the pointers in such a way that 'X' becomes the predecessor of 'min'
    node *current = min->link; // 'current' refers to the current node we are scanning
    node *previous = min;      //'previous' refers to the node that is previous to the current node
    node *temp = NULL;         // 'temp' in this algo is used to point to the last node of the sorted part of the linked list.
                               //eg. If at any time instance the state of the linked list is suppose 1->2->5->3->8->NULL
                               //then, we see that "1->2" is the sorted part of the LL, and therefore temp will be pointing to the last node of the sorted part,i.e,'2'
                               //We keep on arranging the Linked list in such a way that after each iteration the node with 'min' value is placed at its correct position.
                               //Eg. Let suppose initially we have 5->4->1->3->2->NULL
                               //After 1st iteration : 1->4->5->3->2->NULL and so on

    while (min->link != NULL) //so that all the nodes are scanned or until there exists a node
    {
        //pick the first node from the unsorted part and assume that it is the minimum and then start scanning from the next node

        while (current != NULL) //suppose you choose the min node to be X, then scan starts from the (X+1)th node until its NULL. current = (X+1)th node and min = X
        {
            if (current->data < min->data) //if the current node is smaller than the presumed node 'min'
            {
                if (temp == NULL) //temp stays null for the first iteration, therefore it symbolizes that we are scanning for the first time
                {
                    if (previous == min) //if the 'previous' is pointing to the 'min' node
                    {
                        //Update the pointers
                        head = current; //update the head pointer with the current node
                        min->link = current->link;
                        current->link = previous;
                        min = current;
                        current = previous->link;
                    }
                    else //if the 'previous' is not pointing to the 'min' node
                    {
                        //Update the pointers
                        head = current; //update the head pointer with the current node
                        previous->link = current->link;
                        current->link = min;
                        min = current;
                        current = previous->link;
                    }
                }
                else //if 'temp' is not NULL, i.e., its not the 1st iteration
                {
                    temp->link = current;
                    previous->link = current->link;
                    current->link = min;
                    min = current;
                    current = previous->link;
                }
            }
            else //if the current node is greater than min, just move the previous and the current pointer a step further
            {
                previous = previous->link;
                current = current->link;
            }
        }

        //update the pointers. Set 'temp' to the last node in the sorted part. Make 'min' move a step further so that 'min' points to the 1st node of the unsorted part
        //start the iteration again
        temp = min;
        min = min->link;
        previous = min;
        current = min->link;
    }
}

// Test cases:

// enter the no. of nodes : 5
// 8 9 3 1 4
// original list is : 8 9 3 1 4
// sorted list is : 1 3 4 8 9

// enter the no. of nodes : 3
// -1 -2 -3
// original list is : -1 -2 -3
// sorted list is : -3 -2 -1

// enter the no. of nodes : 8
// 8 7 6 5 4 3 2 1
// original list is : 8 7 6 5 4 3 2 1
// sorted list is : 1 2 3 4 5 6 7 8

// enter the no. of nodes : 6
// 5 3 4 1 -2 -4
// original list is : 5 3 4 1 -2 -4
// sorted list is : -4 -2 1 3 4 5

int main()
{
    node *head = NULL;
    int n;
    cout << "enter the no. of nodes : "; //taking input from user about the number of nodes in linked list
    cin >> n;
    if (n == 0)
        return 0;
    head = createlist(n); //creating the list
    cout << "original list is : ";
    print(head);                         //printing the original linked list
    my_selection_sort_linked_list(head); //applying selection sort
    cout << "sorted list is : ";
    print(head); //printing the sorted linked list
    return 0;
}