#include <iostream>
using namespace std;


//node defined
class node
{
public:
    int data;
    node* link;
    node(int d)
    {
        data = d;
        link = NULL;
    }

};

//printing the linked list
void print(node* head)
{
    node* current = head;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current-> link;
    }
    cout << endl;
}

//creating the linked list with 'n' nodes
node* createlist(int n)
{
    node* head = NULL;
    node* t = NULL;
    for (int i = 0; i < n; i++)
    {
        node* temp = NULL;
        int num;
        cin >> num;
        temp = new node(num);
        if (head == NULL)
        {
            head = temp;
            t = temp;
            continue;
        }
        if (t->link == NULL) t->link = temp;
        t = temp;
    }
    return head;
}


//performing selection sort on the linked list in an iterative manner
void my_selection_sort_linked_list(node* &head)
{
    node* min = head;
    node* current = min->link;
    node* previous = min;
    node* temp = NULL;
    while (min->link != NULL)
    {
        while (current != NULL)
        {
            if (current->data < min->data)
            {
                if (temp == NULL)
                {
                    if (previous == min)
                    {
                        head = current;
                        min->link = current->link;
                        current->link = previous;
                        min = current;
                        current = previous->link;
                    }
                    else
                    {
                        head = current;
                        previous->link = current->link;
                        current->link = min;
                        min = current;
                        current = previous->link;
                    }
                }
                else
                {
                    temp->link = current;
                    previous->link = current->link;
                    current->link = min;
                    min = current;
                    current = previous->link;
                }
            }
            else
            {
                previous = previous->link;
                current = current->link;
            }
        }
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
    node* head = NULL;
    int n;
    cout << "enter the no. of nodes : ";    //taking input from user about the number of nodes in linked list
    cin >> n;
    if (n == 0) return 0;
    head = createlist(n);                   //creating the list
    cout << "original list is : ";
    print(head);                            //printing the original linked list
    my_selection_sort_linked_list(head);    //applying selection sort
    cout << "sorted list is : ";
    print(head);                            //printing the sorted linked list
    return 0;
}