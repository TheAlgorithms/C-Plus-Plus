/* The difference between the pointer implementation of linked list and array implementation of linked list:
 1. The NULL is represented by -1;
 2. Limited size. (in the following case it is 100 nodes at max). But we can reuse the nodes that are to be deleted by again linking it bacj to the list.
*/

#include <iostream>
using namespace std;
struct Node
{
    int data;
    int next;
};
Node AvailArray[100]; //array that will act as nodes of a linked list.
int head = -1;
int avail = 0;
void initialise_list()
{
    for (int i = 0; i <= 98; i++)
    {
        AvailArray[i].next = i + 1;
    }
    AvailArray[99].next = -1; //indicating the end of the linked list.
}

int getnode() //This will return the index of the first free node present in the avail list
{
    int NodeIndexToBeReturned = avail;
    avail = AvailArray[avail].next;
    return NodeIndexToBeReturned;
}

void freeNode(int nodeToBeDeleted) //This function when called will delete the node with the index presented as an argument, and will put back that node into the array.
{
    AvailArray[nodeToBeDeleted].next = avail;
    avail = nodeToBeDeleted;
}

void insertAtTheBeginning(int data) //The function will insert the given data into the front of the linked list.
{
    int newNode = getnode();
    AvailArray[newNode].data = data;
    AvailArray[newNode].next = head;
    head = newNode;
}

void insertAtTheEnd(int data)
{
    int newNode = getnode();
    int temp = head;
    while (AvailArray[temp].next != -1)
    {
        temp = AvailArray[temp].next;
    }
    //temp is now pointing to the end node.
    AvailArray[newNode].data = data;
    AvailArray[newNode].next = -1;
    AvailArray[temp].next = newNode;
}

void display()
{
    int temp = head;
    while (temp != -1)
    {
        cout << AvailArray[temp].data << "->";
        temp = AvailArray[temp].next;
    }
    cout << "-1" << endl;
    ;
}

int main()
{
    initialise_list();
    int x, y, z;
    for (;;)
    {
        cout << "1. Insert At The Beginning" << endl;
        cout << "2. Insert At The End" << endl;
        cout << "3. Display" << endl;
        cout << "4.Exit" << endl;
        cout << "Enter Your choice" << endl;
        cin >> z;
        switch (z)
        {
        case 1:
            cout << "Enter the number you want to enter" << endl;
            cin >> x;
            insertAtTheBeginning(x);
            break;
        case 2:
            cout << "Enter the number you want to enter" << endl;
            cin >> y;
            insertAtTheEnd(y);
            break;
        case 3:
            cout << "The linked list contains the following element in order" << endl;
            display();
            break;
        case 4:
            exit(0);
        default:
            cout << "The entered choice is not correct" << endl;
        }
    }
}
