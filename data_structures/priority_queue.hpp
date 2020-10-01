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

#ifndef DATA_STRUCTURES_PRIORITY_QUEUE_H_
#define DATA_STRUCTURES_PRIORITY_QUEUE_H_

#include <cassert>
#include <iostream>

using Priority = int;

static constexpr int LOWEST_PRIORITY = -1;

/** Definition of the node */
template <class Kind, class Priority>
struct node {
    Kind data;
    node<Kind, Priority> *next;
    Priority prior;  // priority level which must be >= 0
};

/** Definition of the priority queue class */
template <class Kind, class Priority>
class queue {
 public:
    /** Show queue */
    void display() {
        node<Kind, Priority> *current = queueFront;
        std::cout << "Front --> ";
        while (current != nullptr) {
            std::cout << "(" << current->data << "," << current->prior
                      << ")    ";
            current = current->next;
        }
        std::cout << std::endl;
        std::cout << "Size of queue: " << size << std::endl;
    }

    /** Default constructor*/
    queue() {
        queueFront = nullptr;
        queueRear = nullptr;
        size = 0;
    }

    /** Destructor */
    ~queue() = default;

    /** Determine whether the queue is empty */
    bool isEmptyQueue() { return (queueFront == nullptr); }

    /** Add new item to the queue. */
    void insert(Kind item, Priority lvl) {
        auto *newNode = new node<Kind, Priority>;
        newNode->data = item;
        newNode->next = nullptr;
        newNode->prior = lvl;
        if (queueFront == nullptr) {
            queueFront = newNode;
            queueRear = newNode;
        } else {
            queueRear->next = newNode;
            queueRear = queueRear->next;
        }
        size++;
    }

    /** Return the data of the first element of the queue */
    Kind frontData() {
        assert(queueFront != nullptr);
        return queueFront->data;
    }

    /** Return the  first element of the queue */
    node<Kind, Priority> *front() { return queueFront; }

    /** Return the  last element of the queue */
    node<Kind, Priority> *last() { return queueRear; }

    /**
     * Remove the element from the queue that has the highest priority
     * and return it.
     */
    node<Kind, Priority> *deQueue() {
        if (!isEmptyQueue()) {
            size--;
            node<Kind, Priority> *temp = queueFront;
            auto *prev = new node<Kind, Priority>;
            auto *maxPrev = new node<Kind, Priority>;
            node<Kind, Priority> *after = queueFront->next;
            Priority max = queueFront->prior;
            node<Kind, Priority> *maxElem = queueFront;
            /** Find the highest priority element */
            while (temp != nullptr && (temp == queueRear || temp->next != nullptr)) {
                if (temp->prior > max) {
                    max = temp->prior;
                    maxPrev = prev;
                    maxElem = temp;
                    after = temp->next;
                }
                prev = temp;
                temp = temp->next;
            }

            if (maxElem == queueFront) {
                queueFront = queueFront->next;
            } else if (maxElem == queueRear) {
                maxPrev->next = nullptr;
                queueRear = maxPrev;
            } else if (maxPrev != nullptr) {
                maxPrev->next = after;
                if (after == nullptr) {
                    queueRear = maxPrev;
                }
            }
            maxElem->next = nullptr;
            return maxElem;
        } else {
            std::cout << "Queue is empty !" << std::endl;
            return nullptr;
        }
    }

    /** Clear queue */
    void clear() { queueFront = nullptr; }

    /** Get the size of the queue*/
    int getSize() { return size; }

 private:
    node<Kind, Priority> *queueFront; // < Pointer to the front of the queue 
    node<Kind, Priority> *queueRear;  // < Pointer to the rear of the queue  
    int size;                         // < Invariant that keeps track the size of the queue
};

#endif  // DATA_STRUCTURES_PRIORITY_QUEUE_H_
