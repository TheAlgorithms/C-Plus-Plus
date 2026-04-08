#include <iostream>

/**
 * @brief Global array to store queue elements. 
 * Changed name from 'queue' to 'q_arr' to avoid ambiguity with std::queue.
 */
int q_arr[10]; 
int front = 0;
int rear = 0;

/**
 * @brief Adds an element to the rear of the queue.
 * @param x The value to be inserted.
 */
void enqueue(int x) {
    if (rear == 10) {
        std::cout << "\nQueue Overflow";
    } else {
        q_arr[rear++] = x;
    }
}

/**
 * @brief Removes an element from the front of the queue.
 */
void dequeue() {
    if (front == rear) {
        std::cout << "\nQueue Underflow";
    } else {
        std::cout << "\n" << q_arr[front++] << " deleted";
        // Shifting elements to maintain the queue at the start of the array
        for (int i = front; i < rear; i++) {
            q_arr[i - front] = q_arr[i];
        }
        rear = rear - front;
        front = 0;
    }
}

/**
 * @brief Displays all elements in the queue.
 */
void show() {
    if (front == rear) {
        std::cout << "\nQueue is Empty";
        return;
    }
    for (int i = front; i < rear; i++) {
        std::cout << q_arr[i] << "\t";
    }
}

int main() {
    int ch, x;
    do {
        std::cout << "\n1. Enqueue";
        std::cout << "\n2. Dequeue";
        std::cout << "\n3. Print";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter Your Choice : ";
        std::cin >> ch;
        if (ch == 1) {
            std::cout << "Insert : ";
            std::cin >> x;
            enqueue(x);
        } else if (ch == 2) {
            dequeue();
        } else if (ch == 3) {
            show();
        }
    } while (ch != 0);

    return 0;
}
