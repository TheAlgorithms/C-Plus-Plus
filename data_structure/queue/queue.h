/* This class specifies the basic operation on a queue as a linked list */
#ifndef QUEUE_H
#define QUEUE_H

/* Definition of the node */
template <class Kind>
struct node
{
    Kind data;
    node<Kind> *next;
};

/* Definition of the queue class */
template <class Kind>
class queue
{
    public:
        void display();        /* Show queue */
        queue();               /* Default constructor*/
        ~queue();              /* Destructor */
        bool isEmptyQueue();   /* Determine whether the queue is empty */
        void enQueue (Kind item); /* Add new item to the queue */
        Kind front();            /* Return the first element of the queue */
        void deQueue();        /* Remove the top element of the queue */
        void clear();

    private:
        node<Kind> *queueFront;  /* Pointer to the front of the queue */
        node<Kind> *queueRear;   /* Pointer to the rear of the queue  */
        int size;
};

#endif

