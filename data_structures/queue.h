/* This class specifies the basic operation on a queue as a linked list */
#ifndef DATA_STRUCTURES_QUEUE_H_
#define DATA_STRUCTURES_QUEUE_H_

#include <cassert>
#include <iostream>

/** Definition of the node */
template <class Kind>
struct node {
    Kind data;
    node<Kind> *next;
};

/** Definition of the queue class */
template <class Kind>
class queue {
 public:
    /** Show queue */
    void display() {
        node<Kind> *current = queueFront;
        std::cout << "Front --> ";
        while (current != NULL) {
            std::cout << current->data << "    ";
            current = current->next;
        }
        std::cout << std::endl;
        std::cout << "Size of queue: " << size << std::endl;
    }

    /** Default constructor*/
    queue() {
        queueFront = NULL;
        queueRear = NULL;
        size = 0;
    }

    /** Destructor */
    ~queue() {}

    /** Determine whether the queue is empty */
    bool isEmptyQueue() { return (queueFront == NULL); }

    /** Add new item to the queue */
    void enQueue(Kind item) {
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

    /** Return the first element of the queue */
    Kind front() {
        assert(queueFront != NULL);
        return queueFront->data;
    }

    /** Remove the top element of the queue */
    void deQueue() {
        node<Kind> *temp;
        if (!isEmptyQueue()) {
            temp = queueFront;
            queueFront = queueFront->next;
            delete temp;
            size--;
        } else {
            std::cout << "Queue is empty !" << std::endl;
        }
    }

    /** Clear queue */
    void clear() { queueFront = NULL; }

 private:
    node<Kind> *queueFront; /**< Pointer to the front of the queue */
    node<Kind> *queueRear;  /**< Pointer to the rear of the queue  */
    int size;
};

#endif  // DATA_STRUCTURES_QUEUE_H_
