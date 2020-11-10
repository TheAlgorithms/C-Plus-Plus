/*
    Write a program to implement Linear Queue using array.
    Functions to implement
        Enqueue (Insertion)
        Dequeue (Deletion)
*/
#include <iostream>
#include <vector>

constexpr uint8_t max_size{10};

class Queue_Array {
public:
    Queue_Array();
    void enqueue(const int8_t&);
    int dequeue();
    void display() const;
private:
    int8_t front{-1};
    int8_t rear{-1};
    std::vector<int8_t> arr{};
};

Queue_Array::Queue_Array() {
    arr.resize(max_size);
}

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

void Queue_Array::display() const {
    if (front == -1) {
        std::cout << "\nStack is empty";
    } else {
        for (int8_t i{front}; i <= rear; ++i) std::cout << arr.at(i) << " ";
    }
}

int main() {
    int op{0}, data{0};

    Queue_Array ob;

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
