#include <iostream>
#include <cassert> // For test case assertions
#include <stdexcept> // For runtime error handling

/**
 * @brief A class to represent a circular queue.
 * 
 * This Queue class uses a fixed-size array to implement a circular queue.
 * It supports basic operations like enqueue, dequeue, and display.
 */
class Queue {
private:
    static const int MAX_SIZE = 10; ///< The maximum number of elements the queue can hold
    int queue[MAX_SIZE]; ///< Array to store the queue elements
    int front;           ///< Index pointing to the front of the queue
    int rear;            ///< Index pointing to the next available position for inserting elements
    int count;           ///< The number of elements currently in the queue

public:
    /**
     * @brief Constructs a new Queue object.
     * 
     * Initializes front, rear, and count to 0.
     */
    Queue();

    /**
     * @brief Enqueues an element into the queue.
     * 
     * Adds an element to the rear of the queue. If the queue is full, it prints an overflow message.
     * 
     * @param x The element to enqueue
     */
    void Enqueue(int x);

    /**
     * @brief Dequeues an element from the queue.
     * 
     * Removes the element from the front of the queue. If the queue is empty, it prints an underflow message.
     */
    void Dequeue();

    /**
     * @brief Displays the elements of the queue.
     * 
     * Prints the elements of the queue from front to rear. If the queue is empty, it prints an appropriate message.
     */
    void Show() const;

    /**
     * @brief Gets the current number of elements in the queue.
     * 
     * @return The number of elements in the queue
     */
    int getCount() const;

    /**
     * @brief Gets the front element of the queue.
     * 
     * Returns the front element of the queue. Throws a runtime error if the queue is empty.
     * 
     * @return The front element of the queue
     * @throws std::runtime_error if the queue is empty
     */
    int getFrontElement() const;

    /**
     * @brief Gets the rear element of the queue.
     * 
     * Returns the rear element of the queue. Throws a runtime error if the queue is empty.
     * 
     * @return The rear element of the queue
     * @throws std::runtime_error if the queue is empty
     */
    int getRearElement() const;
};

// Constructor definition
Queue::Queue() {
    front = 0;
    rear = 0;
    count = 0;
}

void Queue::Enqueue(int x) {
    if (count == MAX_SIZE) {
        std::cout << "\nOverflow: Queue is full, cannot enqueue " << x;
    } else {
        queue[rear] = x;
        rear = (rear + 1) % MAX_SIZE;
        count++;
    }
}

void Queue::Dequeue() {
    if (count == 0) {
        std::cout << "\nUnderflow: Queue is empty, cannot dequeue";
    } else {
        std::cout << "\n" << queue[front] << " deleted";
        front = (front + 1) % MAX_SIZE;
        count--;
    }
}

void Queue::Show() const {
    if (count == 0) {
        std::cout << "\nQueue is empty";
        return;
    }

    std::cout << "\nQueue elements: ";
    for (int i = 0; i < count; i++) {
        std::cout << queue[(front + i) % MAX_SIZE] << "\t";
    }
}

int Queue::getCount() const {
    return count;
}

int Queue::getFrontElement() const {
    if (count == 0) {
        throw std::runtime_error("Queue is empty");
    }
    return queue[front];
}

int Queue::getRearElement() const {
    if (count == 0) {
        throw std::runtime_error("Queue is empty");
    }
    return queue[(rear - 1 + MAX_SIZE) % MAX_SIZE];
}

/**
 * @brief Runs automated test cases for the Queue class.
 * 
 * This function tests the queue functionality including enqueueing, dequeueing, overflow, and underflow scenarios.
 */
void runTestCases() {
    Queue q;

    // Test case 1: Enqueue elements
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    assert(q.getFrontElement() == 10);
    assert(q.getRearElement() == 30);
    std::cout << "\nTest Case 1 passed: Enqueue elements";

    // Test case 2: Dequeue an element
    q.Dequeue(); // Should dequeue 10
    assert(q.getFrontElement() == 20);  // Front should now be 20
    assert(q.getCount() == 2);          // Count should decrease to 2
    std::cout << "\nTest Case 2 passed: Dequeue element";

    // Test case 3: Enqueue and dequeue combination
    q.Enqueue(40); // Enqueue one more element
    q.Enqueue(50);
    assert(q.getRearElement() == 50); // The last enqueued element should be 50
    q.Dequeue(); // Should dequeue 20
    assert(q.getFrontElement() == 30); // Front element should now be 30
    std::cout << "\nTest Case 3 passed: Enqueue and dequeue combination";

    // Test case 4: Overflow
    for (int i = 0; i < 7; i++) {
        q.Enqueue(60 + i);  // Keep adding until the queue is full
    }
    q.Enqueue(100); // This should trigger overflow
    assert(q.getCount() == 10);  // Queue should be full
    std::cout << "\nTest Case 4 passed: Overflow check";

    // Test case 5: Underflow
    for (int i = 0; i < 10; i++) {
        q.Dequeue();  // Dequeue all elements
    }
    q.Dequeue(); // This should trigger underflow
    assert(q.getCount() == 0);  // Queue should be empty
    std::cout << "\nTest Case 5 passed: Underflow check";

    std::cout << "\nAll test cases passed!\n";
}

/**
 * @brief The main function to run the test cases.
 * 
 * This function runs the automated test cases for the queue.
 * 
 * @return int 
 */
int main() {
    runTestCases();  // Run automated test cases
    return 0;
}

