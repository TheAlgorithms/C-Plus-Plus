#include <iostream>

struct node {
    int data;
    struct node* next;
};
class Queue {
    node* front=nullptr;
    node* rear=nullptr;

public:
    Queue() = default; 
    void createNode(int val) {
        auto* nn = new node;
        nn->data = val;
        nn->next = nullptr;
        front = nn;
        rear = nn;
    }
    void enqueue(int val) {
        if (front == nullptr || rear == nullptr) {
            createNode(val);
        }
        else {
            node* nn;
            nn = new node;
            nn->data = val;
            rear->next = nn;
            nn->next = front;
            rear = nn;
        }
    }
    void dequeue() {
        node* n;
        n = front;
        if (n) {
            front = front->next;
            delete n;
        }
    }
    void traverse() {
        node* ptr;
        ptr = front;
        if (ptr) {
            do {
                std::cout << ptr->data << " ";
                ptr = ptr->next;
            } while (ptr != rear->next);
            std::cout << front->data << std::endl;
        }
    }
};
int main(void) {
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