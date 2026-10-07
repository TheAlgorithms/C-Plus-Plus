#include <iostream>

struct node {
    int data;
    struct node* next;
};
class Queue {
    node* front = nullptr;
    node* rear = nullptr;

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

 public:
    Queue() = default;
    ~Queue() {
        while (front) {
            dequeue();
        }
    }

 private:
    void createNode(int val) {
        auto* nn = new node;
        nn->data = val;
        nn->next = nullptr;
        front = nn;
        rear = nn;
    }

 public:
    void enqueue(int val) {
        if (front == nullptr || rear == nullptr) {
            createNode(val);
        } else {
            node* nn = new node;
            nn->data = val;
            rear->next = nn;
            nn->next = front;
            rear = nn;
        }
    }
    void dequeue() {
        if (front == nullptr) {
            return;
        }
        const node* const n = front;
        if (front == rear) {
            front = nullptr;
            rear = nullptr;
        } else {
            front = front->next;
            rear->next = front;
        }
        delete n;
    }
    void traverse() {
        if (front == nullptr) {
            return;
        }
        const node* ptr = front;
        do {
            std::cout << ptr->data << ' ';
            ptr = ptr->next;
        } while (ptr != front);
        std::cout << '\n';
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