/**
 * \file priority_queue.cpp
 * \brief [Priority Queue Data Structure]
 *[(Priority Queue)](https://en.wikipedia.org/wiki/Priority_queue)
 *\details
 *A priority queue is a type of queue that arranges elements based on their
 *priority values. Elements with higher priority values are typically retrieved
 *before elements with lower priority values. In a priority queue, each element
 *has a priority value associated with it. When you add an element to the queue,
 *it is inserted in a position based on its priority value.
 *\author[AbhirajBose](https://github.com/AbhirajBose)
 *
 */
#include <iostream>
using namespace std;
/**
 * A structure for Node
 * By defining a structure,we set the data and priority part within it
 */
struct Node {
    int data;      // defining data part of a node
    int priority;  // defining priority part of a node
    Node* next;
};
/**
 * A class for PriorityQueue
 * Here we define the private elements and the public elements
 * Private elements can be accessed only when the class is called
 * Public elements can be accessed globally
 */
class PQ {
 private:
    Node* front;

 public:
    PQ() { front = NULL; }
    // calling functions through the class
    void insert(int, int);
    void clear();
    bool isEmpty();
    void display();
};
/**
 * Insert function is used to add a new value to a queue
 * It adds the value according to the priority provided by the user
 */
void PQ::insert(int value, int p) {
    Node* newNode = new Node;  // creating a newNode
    newNode->data = value;
    newNode->priority = p;
    if (front == NULL || p < front->priority) {
        newNode->next = front;

        front = newNode;
    } else {
        Node* curr = front;
        while (curr->next && curr->next->priority <= p) {
            curr = curr->next;
        }
        newNode->next = curr->next;

        curr->next = newNode;
    }
}
/**
 * Deleting elements using clear function
 * clear() function is used to delete the elements
 * this is done using defining the temporary variable first
 * then assingning it using front and then changing the next pointer
 * Finally deleting the temp variable
 */
void PQ::clear() {
    while (!isEmpty()) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}
/**
 * isEmpty() function is used to check whether the queue is empty or not
 * if the queue is empty,then it returns front as NULL
 */
bool PQ::isEmpty() { return front == NULL; }
/**
 * display() function is used to display the whole queue
 * if the queue is empty it returns,"Empty Queue"
 */
void PQ::display() {
    if (isEmpty()) {
        cout << "Priority Queue is empty" << endl;
        return;
    }
    Node* temp = front;
    while (temp != NULL) {
        cout << "Value: " << temp->data << endl;
        cout << "Priority: " << temp->priority << endl;

        temp = temp->next;
    }
}
/**
 * Main function
 * This is the function where we call all the values
 * This is the function where we create an object
 * Here,we take the items as input from the user and pass them
 * We pass the values while calling the function,i.e,call by reference
 * We use do while loop and switch case to make a menu driven program
 */
int main() {
    PQ p;
    int ch;
    cout << "1.Insert" << endl;
    cout << "2.Remove" << endl;
    cout << "3.Display" << endl;
    cout << "4.Exit" << endl;
    do {
        cout << "Enter your choice" << endl;
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter the value to be inserted" << endl;
                int value, priority;
                cin >> value;
                cout << "Enter the priority" << endl;
                cin >> priority;
                p.insert(value, priority);

            case 2:
                p.clear();
                break;
            case 3:
                p.display();
                break;
            case 4:
                exit(1);
                break;
            default:
                cout << "Invalid Choice" << endl;
        }
    } while (ch != 5);
    return 0;
}