/**
 * @file
 * @brief Implementation of a queue using a file.
 * @details
 * This program implements a queue using a file.
 * It includes a template class `MyQueue` defining the queue interface,
 * and a class `QueueFile` implementing the queue using a file as storage.
 * * @algorithm
 * The qoeoe include two pointers to the head and the tail of the qoueue
 * And it also contain fstraem file there the data of the queue kept.
 * When removing the value of the head indexOfFirst increase by one
 * @author [Your Name](https://github.com/your_handle)
 */

#include <fstream>
#include <iostream>
#include <string>


/**
 * @interface MyQueue
 * @brief A generic queue interface.
 * @tparam T The type of elements stored in the queue.
 */
template <class T>
class MyQueue {
 public:
    /// Clears the queue.
    virtual void clear() = 0;

    /// Removes and returns the front element of the queue.
    virtual T dequeue() = 0;

    /// Adds an element to the rear of the queue.
    virtual void enqueue(T value) = 0;

    /// Returns the front element of the queue without removing it.
    virtual T front() = 0;

    /// Checks if the queue is empty.
    virtual bool isEmpty() = 0;

    /// Destructor.
    virtual ~MyQueue() {}
};

/**
 * @class QueueFile
 * @brief A queue implementation using a file as storage.
 * @tparam T The type of elements stored in the queue.
 */
template <class T>
class QueueFile : public MyQueue<T> {
    int queueSize = 10;
    int indexOfFirst = 0;
    int indexOfLast = 0;
    fstream data;

    /// Checks if the queue is full.
    bool isFull() { return indexOfFirst == indexOfLast + 1; }

 public:
    /**
     * @brief Constructor for QueueFile.
     * @param size The size of the queue.
     */
    QueueFile(int size = 100) : queueSize(size) {
        data.open("queue.dat", ios::out);
        T stam;
        for (int i = 0; i < size; i++) {
            data.write((char*)&stam, sizeof(T));
        }
        data.close();
        data.open("queue.dat", ios::out | ios::in);
        if (!data)
            throw "error in opening";
    }

    /// Clears the queue.
    void clear() override {
        indexOfFirst = 0;
        indexOfLast = 0;
    }

    /// Checks if the queue is empty.
    bool isEmpty() override { return indexOfFirst == indexOfLast; }

    /// Returns the front element of the queue without removing it.
    T front() override {
        if (this->isEmpty())
            throw "underflow";
        data.seekg(indexOfFirst * sizeof(T), ios::beg);
        T s;
        data.read((char*)&s, sizeof(T));
        return s;
    }

    /// Removes and returns the front element of the queue.
    T dequeue() override {
        if (this->isEmpty())
            throw "underflow";
        data.seekg(indexOfFirst * sizeof(T), ios::beg);
        T s;
        data.read((char*)&s, sizeof(T));
        if (indexOfFirst == queueSize)
            indexOfFirst = 0;
        else
            indexOfFirst++;
        return s;
    }

    /// Adds an element to the rear of the queue.
    void enqueue(T value) override {
        if (this->isFull())
            throw "overflow";
        data.seekp(indexOfLast * sizeof(T), ios::beg);
        data.write((char*)&value, sizeof(value));
        if (indexOfLast == queueSize)
            indexOfLast = 0;
        else
            indexOfLast++;
    }

    /// Destructor
    ~QueueFile() override { data.close(); }
};

/**
 * @brief Main function.
 * @returns 0 on exit.
 */
int main() {
    return 0;
}
