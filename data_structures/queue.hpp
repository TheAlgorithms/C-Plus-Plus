/* This class specifies the basic operation on a queue as a linked list */
#ifndef DATA_STRUCTURES_QUEUE_HPP_
#define DATA_STRUCTURES_QUEUE_HPP_

#include "node.hpp"

/** Definition of the queue class */
template <class ValueType>
class queue {
    using node_type = Node<ValueType>;

 public:
    using value_type = ValueType;
    /** Show queue */
    void display() const {
        std::cout << "Front --> ";
        display_all(this->queueFront.get());
        std::cout << '\n';
        std::cout << "Size of queue: " << size << '\n';
    }

    std::vector<value_type> toVector() const {
        return push_all_to_vector(this->queueFront.get(), this->size);
    }

 private:
    void ensureNotEmpty() const {
        if (isEmptyQueue()) {
            throw std::invalid_argument("Queue is empty.");
        }
    }

 public:
    /** Determine whether the queue is empty */
    bool isEmptyQueue() const { return (queueFront == nullptr); }

    /** Add new item to the queue */
    void enQueue(const value_type& item) {
        auto newNode = std::make_shared<node_type>();
        newNode->data = item;
        newNode->next = nullptr;
        if (isEmptyQueue()) {
            queueFront = newNode;
            queueRear = newNode;
        } else {
            queueRear->next = newNode;
            queueRear = queueRear->next;
        }
        size++;
    }

    /** Return the first element of the queue */
    value_type front() const {
        ensureNotEmpty();
        return queueFront->data;
    }

    /** Remove the top element of the queue */
    void deQueue() {
        ensureNotEmpty();
        queueFront = queueFront->next;
        size--;
    }

    /** Clear queue */
    void clear() {
        queueFront = nullptr;
        queueRear = nullptr;
        size = 0;
    }

 private:
    std::shared_ptr<node_type> queueFront =
        {}; /**< Pointer to the front of the queue */
    std::shared_ptr<node_type> queueRear =
        {}; /**< Pointer to the rear of the queue  */
    std::size_t size = 0;
};

#endif  // DATA_STRUCTURES_QUEUE_HPP_
