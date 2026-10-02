/*
    Write a program to implement Queue using linkedlist.
*/
#include <cassert>
#include <iostream>

struct linkedlist {
    int data;
    linkedlist *next;
};
class stack_linkedList {
 public:
    linkedlist *front;
    linkedlist *rear;

    stack_linkedList() { front = rear = NULL; }
    void enqueue(int);
    int dequeue();
    void display();
};
void stack_linkedList::enqueue(int ele) {
    linkedlist *temp = new linkedlist();
    temp->data = ele;
    temp->next = NULL;

    if (front == NULL)
        front = rear = temp;
    else {
        rear->next = temp;
        rear = temp;
    }
}
int stack_linkedList::dequeue() {
    linkedlist *temp;
    int ele = 0;  // defined sentinel for the empty-queue case below
    if (front == NULL) {
        std::cout << "\nStack is empty";
    } else {
        temp = front;
        ele = temp->data;
        if (front == rear)  // if length of queue is 1;
            rear = rear->next;
        front = front->next;
        delete (temp);
    }
    return ele;
}
void stack_linkedList::display() {
    if (front == NULL)
        std::cout << "\nStack is empty";

    else {
        linkedlist *temp;
        temp = front;
        while (temp != NULL) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
}

/*
    Self-test: dequeue() must never read uninitialized memory. On an empty
    queue it should return a defined sentinel (0) instead of whatever
    happens to be on the stack.
*/
static void tests() {
    stack_linkedList q;

    assert(q.dequeue() == 0);  // empty queue before any enqueue

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    assert(q.dequeue() == 10);
    assert(q.dequeue() == 20);
    assert(q.dequeue() == 30);

    assert(q.dequeue() == 0);  // empty again after draining the queue

    std::cout << "All tests have successfully passed!\n";
}

int main() {
    tests();

    int op, data;
    stack_linkedList ob;
    std::cout << "\n1. enqueue(Insertion) ";
    std::cout << "\n2. dequeue(Deletion)";
    std::cout << "\n3. Display";
    std::cout << "\n4. Exit";

    while (1) {
        std::cout << "\nEnter your choice ";
        std::cin >> op;
        if (op == 1) {
            std::cout << "Enter data ";
            std::cin >> data;
            ob.enqueue(data);
        } else if (op == 2)
            data = ob.dequeue();
        else if (op == 3)
            ob.display();
        else if (op == 4)
            exit(0);
        else
            std::cout << "\nWrong choice ";
    }
    return 0;
}
