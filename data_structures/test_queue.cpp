#include <iostream>
#include <string>

#include "./queue.h"

/*int main() {
    queue<std::string> q;
    std::cout << "---------------------- Test construct ----------------------"
              << std::endl;
    q.display();
    std::cout
        << "---------------------- Test isEmptyQueue ----------------------"
        << std::endl;
    if (q.isEmptyQueue())
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
    std::cout << "---------------------- Test enQueue ----------------------"
              << std::endl;
    std::cout << "After Hai, Jeff, Tom, Jkingston go into queue: " << std::endl;
    q.enQueue("Hai");
    q.enQueue("Jeff");
    q.enQueue("Tom");
    q.enQueue("Jkingston");
    q.display();
    std::cout << "---------------------- Test front ----------------------"
              << std::endl;
    std::string value = q.front();
    if (value == "Hai")
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
    std::cout << "---------------------- Test deQueue ----------------------"
              << std::endl;
    q.display();
    q.deQueue();
    q.deQueue();
    std::cout << "After Hai, Jeff left the queue: " << std::endl;
    q.display();
    return 0;
}*/

// Another way to write queue
struct Queue {
    int front, rear, capacity;
    int* queue;
    Queue(int c) {
        front = rear = 0;
        capacity = c;
        queue = new int;
    }

    ~Queue() { delete[] queue; }

    // function to insert an element
    // at the rear of the queue
    void queueEnqueue(int data) {
        // check queue is full or not
        if (capacity == rear) {
            printf("\nQueue is full\n");
            return;
        }

        // insert element at the rear
        else {
            queue[rear] = data;
            rear++;
        }
        return;
    }

    // function to delete an element
    // from the front of the queue
    void queueDequeue() {
        // if queue is empty
        if (front == rear) {
            printf("\nQueue is  empty\n");
            return;
        }

        // shift all the elements from index 2 till rear
        // to the left by one
        else {
            for (int i = 0; i < rear - 1; i++) {
                queue[i] = queue[i + 1];
            }

            // decrement rear
            rear--;
        }
        return;
    }

    // print queue elements
    void queueDisplay() {
        int i;
        if (front == rear) {
            printf("\nQueue is Empty\n");
            return;
        }

        // traverse front to rear and print elements
        for (i = front; i < rear; i++) {
            printf(" %d <-- ", queue[i]);
        }
        return;
    }

    // print front of queue
    void queueFront() {
        if (front == rear) {
            printf("\nQueue is Empty\n");
            return;
        }
        printf("\nFront Element is: %d", queue[front]);
        return;
    }
};

int main() {
    // Use the queue as class
}