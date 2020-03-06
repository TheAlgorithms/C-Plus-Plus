#include <iostream>
#include <assert.h>
#include "queue.h"

using namespace std;

/* Default constructor*/
template <class Kind>
queue<Kind>::queue()
{
    queueFront = NULL;
    queueRear = NULL;
    size = 0;
}

/* Destructor */
template <class Kind>
queue<Kind>::~queue()
{
}

/* Display for testing */
template <class Kind>
void queue<Kind>::display()
{
    node<Kind> *current = queueFront;
    cout << "Front --> ";
    while(current != NULL) {
        cout<<current->data<< "    ";
        current = current -> next;
    }
    cout <<endl;
    cout << "Size of queue: " << size << endl;
}

/* Determine whether the queue is empty */
template <class Kind>
bool queue<Kind>::isEmptyQueue()
{
    return (queueFront == NULL);
}

/* Clear queue */
template <class Kind>
void queue<Kind>::clear()
{
    queueFront = NULL;
}

/* Add new item to the queue */
template <class Kind>
void queue<Kind>::enQueue(Kind item)
{
    node<Kind> *newNode;
    newNode = new node<Kind>;
    newNode->data = item;
    newNode->next = NULL;
    if (queueFront == NULL) {
        queueFront = newNode;
        queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = queueRear->next;
    }
    size++;
}

/* Return the top element of the queue */
template <class Kind>
Kind queue<Kind>::front()
{
    assert(queueFront != NULL);
    return queueFront->data;
}

/* Remove the element of the queue */
template <class Kind>
void queue<Kind>::deQueue()
{
    node<Kind> *temp;
    if(!isEmptyQueue()) {
        temp = queueFront;
        queueFront = queueFront->next;
        delete temp;
        size--;
    } else {
        cout << "Queue is empty !" << endl;
    }
}

