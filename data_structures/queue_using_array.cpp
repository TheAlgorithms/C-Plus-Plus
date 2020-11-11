/**
 * @file
 * @brief Implementation of Linear Queue using array.
 * @details
 * The Linear Queue is a data structure used for holding a sequence of
 * values, which can be added to the end line (enqueue), removed from
 * head of line (dequeue) and displayed.
 * ### Algorithm
 * Values can be added by increasing the `rear` variable by 1 (which points to 
 * the end of the array), then assigning new value to `rear`'s element of the array.
 * 
 * Values can be removed by increasing the `front` variable by 1 (which points to 
 * the first of the array), so it cannot reached any more.
 */
#include <iostream>
#include <vector>

constexpr uint8_t max_size{10};

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {

/**
 * @namespace linked_list
 * @brief Functions for singly linked list algorithm
 */
namespace linked_list {

/**
 * Queue_Array class containing the main data and also index of head and tail of the array.
 */
class Queue_Array {
public:
    Queue_Array();
    void enqueue(const int8_t&);
    int dequeue();
    void display() const;
private:
    int8_t front{-1};           ///< Index of head of the array
    int8_t rear{-1};            ///< Index of tail of the array
    std::vector<int8_t> arr{};  ///< All stored data
};


/**
* Queue_Array constructor. Initializes the maximum number of data than can be saved.
*/
Queue_Array::Queue_Array() {
    arr.resize(max_size);
}

/**
 * function adds new element to the end of the queue
 * @param ele to be added to the end of the queue
 */
void Queue_Array::enqueue(const int8_t& ele) {
    if (rear == arr.size() - 1) {
        std::cout << "\nStack is full";
    } else if (front == -1 && rear == -1) {
        front = rear = 0;
        arr.at(rear) = ele;
    } else if (rear < arr.size()) {
        ++rear;
        arr.at(rear) = ele;
    }
}

/**
 * function removes the element at the first of the queue
 * @returns data that is deleted if queue is not empty
 */
int Queue_Array::dequeue() {
    int8_t d{0};
    if (front == -1) {
        std::cout << "\nstack is empty ";
        return 0;
    } else if (front == rear) {
        d = arr.at(front);
        front = rear = -1;
    } else {
        d = arr.at(front++);
    }

    return d;
}

/**
 * function shows all elements in the queue
 */
void Queue_Array::display() const {
    if (front == -1) {
        std::cout << "\nStack is empty";
    } else {
        for (int8_t i{front}; i <= rear; ++i) std::cout << arr.at(i) << " ";
    }
}

}  // namespace linked_list
}  // namespace data_structures


/**
 * Main function:
 * Allows the user add and delete values from the queue.
 * Also allows user to display values in the queue.
 * @returns 0 on exit
 */
int main() {
    int op{0}, data{0};
    data_structures::linked_list::Queue_Array ob;

    std::cout << "\n1. enqueue(Insertion) ";
    std::cout << "\n2. dequeue(Deletion)";
    std::cout << "\n3. Display";
    std::cout << "\n4. Exit";
    while (true) {
        std::cout << "\nEnter your choice ";
        std::cin >> op;
        if (op == 1) {
            std::cout << "Enter data  ";
            std::cin >> data;
            ob.enqueue(data);
        } else if (op == 2) {
            data = ob.dequeue();
            std::cout << "\ndequeue element is:\t" << data;
        } else if (op == 3) {
            ob.display();
        } else if (op == 4) {
            exit(0);
        } else {
            std::cout << "\nWrong choice ";
        }
    }

    return 0;
}
