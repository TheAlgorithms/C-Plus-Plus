#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
};
class Queue
{
    node *front;
    node *rear;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
    }
    void createNode(int val)
    {
        node *ptr;
        node *nn;
        nn = new node;
        ptr = front;
        nn->data = val;
        nn->next = NULL;
        front = nn;
        rear = nn;
    }
    void enqueue(int val)
    {
        if (front == NULL || rear == NULL)
        {
            createNode(val);
        }
        else
        {
            node *ptr;
            node *nn;
            ptr = front;
            nn = new node;
            nn->data = val;
            rear->next = nn;
            nn->next = front;
            rear = nn;
        }
    }
    void dequeue()
    {
        node *n;
        n = front;
        front = front->next;
        delete (n);
    }
    void traverse()
    {
        node *ptr;
        ptr = front;
        do
        {
            cout << ptr->data << " ";
            ptr = ptr->next;
        } while (ptr != rear->next);
        cout << front->data;
        cout << endl;
    }
};
int main(void)
{
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    q.enqueue(60);
    q.enqueue(70);
    q.traverse();
    q.dequeue();
    q.traverse();
    return 0;
}