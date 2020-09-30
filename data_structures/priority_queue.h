/**
 * @file
 * @author [Tuan Ho](https://github.com/ttuanho)
 * @brief Implementation of [Priority
 * queue](https://en.wikipedia.org/wiki/Priority_queue) an abstract data type
 * similar to regular queue or stack data structure in which each element
 * additionally has a "priority" associated with it.
 * @note improvised from queue.h
 * @see queue.h
 */


#include <cassert>
#include <iostream>

typedef int Priority;

#define LOWEST_PRIORITY -1;

using namespace std;

/** Definition of the node */
template <class Kind, class Priority>
struct node {
    Kind data;
    node<Kind, Priority> *next;
    Priority prior;       // priority level which must be >= 0
};

/** Definition of the priority queue class */
template <class Kind, class Priority>
class queue {
 public:
    /** Show queue */
    void display() {
        node<Kind, Priority> *current = queueFront;
        cout << "Front --> ";
        while (current != NULL) {
            cout << "(" << current->data << ","<< current->prior << ")    ";
            current = current->next;
        }
        cout << endl;
        cout << "Size of queue: " << size << endl;
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

    /** Add new item to the queue. */
    void insert(Kind item, Priority lvl) {
        node<Kind, Priority> *newNode;
        newNode = new node<Kind, Priority>;
        newNode->data = item;
        newNode->next = NULL;
        newNode->prior = lvl;
        if (queueFront == NULL) {
            queueFront = newNode;
            queueRear = newNode;
        }
        else {
            queueRear->next = newNode;
            queueRear = queueRear->next;
        }
        size++;
    }

    /** Return the data of the first element of the queue */
    Kind frontData() {
        assert(queueFront != NULL);
        return queueFront->data;
    }

    /** Return the  first element of the queue */
    node<Kind, Priority> *front() {
        return queueFront;
    }

    /** Return the  last element of the queue */
    node<Kind, Priority> *last() {
        return queueRear;
    }

    /**
     * Remove the element from the queue that has the highest priority
     * and return it.
     */
    node<Kind, Priority> *deQueue() {
        if (!isEmptyQueue()) {
            node<Kind, Priority> *temp = queueFront;
            node<Kind, Priority> *prev = NULL;
            node<Kind, Priority> *after = queueFront->next;
            Priority max = queueFront->prior;
            node<Kind, Priority> *maxElem = queueFront;
            while (temp->next != NULL || temp == queueRear) {
                if (temp->prior > max) {
                    max = temp->prior;
                    maxElem = temp;
                }
                temp = temp->next;
                prev = temp;
                after = temp->next;
            }
            if (prev != NULL) {
                prev->next = after;
                if (after == NULL)
                    queueRear = prev;
            // If the queue has one node, return NULL.
            } else {
                queueFront = NULL;
                queueRear = NULL;
                return NULL;
            }

            size--;
            return maxElem;
        } else {
            cout << "Queue is empty !" << endl;
            return NULL;
        }
    }

    /** Clear queue */
    void clear() { queueFront = NULL; }

    /** Get the size of the queue*/
    int getSize() { return size; }

 private:
    node<Kind, Priority> *queueFront; /**< Pointer to the front of the queue */
    node<Kind, Priority> *queueRear;  /**< Pointer to the rear of the queue  */
    int size;
};

