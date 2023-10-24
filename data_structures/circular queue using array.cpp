
#include <iostream>
using namespace std;

class CircQueue {
 private:
    int size;
    int* arr;
    int front;
    int rear;
    int count;

 public:
    CircQueue() {
        size = 4;
        arr = new int[size];
        front = 0;
        rear = 0;
        count = 0;
    }
    bool isFull() {
        if (count == size) {
            return true;
        }
        return false;
    }
    bool isEmpty() {
        if (count == 0) {
            return true;
        }
        return false;
    }
    void enqueue(int x) {
        if (isFull()) {
            cout << "Queue Overflow";
            return;
        }
        arr[rear] = x;
        rear = (rear + 1) % size;
        count++;
    }
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow";
        }
        front = (front + 1) % size;
        count--;
    }
    int getFront() { return arr[front]; }
    void display() {
        while (!isEmpty()) {
            cout << getFront() << endl;
            dequeue();
        }
    }
};

int main() {
    CircQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.display();
    cout << endl;
    cout << "Inserting Again" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();
}
