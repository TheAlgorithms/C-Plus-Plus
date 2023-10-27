/**
 * \file priority_queue.cpp
 * \brief [Priority Queue Data Structure]
 *[(Priority Queue)](https://en.wikipedia.org/wiki/Priority_queue)
 *\details
 *A priority queue is a type of queue that arranges elements based on their priority values.
 *Elements with higher priority values are typically retrieved before elements with lower priority values.
 *In a priority queue, each element has a priority value associated with it.
 *When you add an element to the queue, it is inserted in a position based on its priority value.
 *\author[AbhirajBose](https://github.com/AbhirajBose)
 *
 */
#include <iostream>
using namespace std;
/*A structure for Node*/
struct Node {      // defining node of a LinkedList
    int data;      // defining data part of a node
    int priority;  // defining priority part of a node
    Node* next;    // Node pointer points to next
};
/*A class for Min Heap*/
class PQ {             // defining class
 private:              // can be accessed only when the class is called
    Node* front;       // Node pointer points to next
 public:               // can be accessed globally
    PQ() {             // constructor
        front = NULL;  // initializing front as NULL
    }
    void insert(int, int);  // calling insert function
    void clear();          // calling remove function
    bool isEmpty();         // calling isEmpty function
    void display();         // calling display function
};
void PQ::insert(
    int value,
    int p)  // using scope resolution operator to use the class variables
{
    Node* newNode = new Node;  // creating a newNode
    newNode->data = value;     // assigning value to the data part of newNode
    newNode->priority = p;     // assidning p to the priority part of newNode
    if (front == NULL || p < front->priority)  // comparing and checking
    {
        newNode->next = front;  // if the condition is true,then assigning front
                                // to the next part of newNode
        front = newNode;
    } else {
        Node* curr =
            front;  // Node pointer pointing to curr is assigned as front
        while (curr->next &&
               curr->next->priority <= p)  // comparing and checking
        {
            curr = curr->next;  // changing the pointer
        }
        newNode->next = curr->next;  // assigning the next part of newNode with
                                     // next part of curr
        curr->next = newNode;        // assigning next part of curr as newNode
    }
}
void PQ::clear()  // using scope resolution operator to use the class variables
{
    while (!isEmpty())  // checking if the list is empty or not
    {
        Node* temp =
            front;  // Node pointer pointing to temp is assigned as front
        front = front->next;  // changing the pointer
        delete temp;          // deleting the temporary variable
    }
}
bool PQ::isEmpty() {       // using scope resolution operator to use the class
                           // variables
    return front == NULL;  // checking if front equals NULL
}
void PQ::display() {  // using scope resolution operator to use the class
                      // variables
    if (isEmpty()) {
        cout << "Priority Queue is empty" << endl;
        return;
    }
    Node* temp = front;
    while (temp != NULL)  // traversing over the List using while loop
    {
        cout << "Value: " << temp->data << endl;         // printing the value
        cout << "Priority: " << temp->priority << endl;  // printing the
                                                         // priority
        temp = temp->next;                               // changing the pointer
    }
}
int main()  // calling main function
{
    PQ p;    // creating object
    int ch;  // initializing ch variable
    cout << "1.Insert" << endl;
    cout << "2.Remove" << endl;
    cout << "3.Display" << endl;
    cout << "4.Exit" << endl;
    do {
        cout << "Enter your choice" << endl;
        cin >> ch;   // taking choice as input
        switch (ch)  // using switch case
        {
            case 1:
                cout << "Enter the value to be inserted" << endl;
                int value, priority;
                cin >> value;  // taking value as input
                cout << "Enter the priority" << endl;
                cin >> priority;            // taking priority as input
                p.insert(value, priority);  // passing the values to the
                                            // function
                break;
            case 2:
                p.clear();  // calling remove function
                break;
            case 3:
                p.display();  // calling display function
                break;
            case 4:
                exit(1);  // exiting the function
                break;
            default:
                cout << "Invalid Choice" << endl;
        }
    } while (ch != 5);  // checking the condition
    return 0;
}