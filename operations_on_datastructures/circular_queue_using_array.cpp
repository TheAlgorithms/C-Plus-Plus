#include <iostream>
using namespace std;

// Define the maximum size of the queue.
const int MAX_SIZE = 10;

int queue[MAX_SIZE]; // Queue array
int front = 0;       // Points to the front of the queue
int rear = 0;        // Points to the next available position for inserting elements
int count = 0;       // Keeps track of the number of elements in the queue

// Function to enqueue an element into the queue
void Enqueue(int x) {
    // Check if the queue is full
    if (count == MAX_SIZE) {
        cout << "\nOverflow: Queue is full, cannot enqueue " << x;
    } else {
        // Insert the element at the rear and move the rear pointer circularly
        queue[rear] = x;
        rear = (rear + 1) % MAX_SIZE;
        count++; // Increase the element count
    }
}

// Function to dequeue an element from the queue
void Dequeue() {
    // Check if the queue is empty
    if (count == 0) {
        cout << "\nUnderflow: Queue is empty, cannot dequeue";
    } else {
        // Display the dequeued element and move the front pointer circularly
        cout << "\n" << queue[front] << " deleted";
        front = (front + 1) % MAX_SIZE;
        count--; // Decrease the element count
    }
}

// Function to display the elements of the queue
void show() {
    if (count == 0) {
        cout << "\nQueue is empty";
        return;
    }

    cout << "\nQueue elements: ";
    // Loop through the valid elements using modular arithmetic
    for (int i = 0; i < count; i++) {
        cout << queue[(front + i) % MAX_SIZE] << "\t";
    }
}

// Main function with a menu-driven approach for queue operations
int main() {
    int choice, x;
    
    do {
        // Display menu
        cout << "\n\nMenu:";
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Show";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Enqueue an element
                cout << "\nInsert: ";
                cin >> x;
                Enqueue(x);
                break;

            case 2:
                // Dequeue an element
                Dequeue();
                break;

            case 3:
                // Show the current queue elements
                show();
                break;

            case 0:
                // Exit the loop
                cout << "\nExiting...";
                break;

            default:
                // Handle invalid input
                cout << "\nInvalid choice, please try again.";
        }

    } while (choice != 0); // Continue until the user chooses to exit

    return 0;
}
