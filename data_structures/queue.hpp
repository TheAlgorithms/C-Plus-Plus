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
    /**
     * @brief prints the queue into the std::cout
     */
    void display() const {
        std::cout << "Front --> ";
        display_all(this->queueFront.get());
        std::cout << '\n';
        std::cout << "Size of queue: " << size << '\n';
    }

    /**
     * @brief converts the queue into the std::vector
     * @return std::vector containning all of the elements of the queue in the
     * same order
     */
    std::vector<value_type> toVector() const {
        return push_all_to_vector(this->queueFront.get(), this->size);
    }

 private:
    /**
     * @brief throws an exception if queue is empty
     * @exception std::invalid_argument if queue is empty
     */
    void ensureNotEmpty() const {
        if (isEmptyQueue()) {
            throw std::invalid_argument("Queue is empty.");
        }
    }

 public:
    /**
     * @brief checks if the queue has no elements
     * @return true if the queue is empty, false otherwise
     */
    bool isEmptyQueue() const { return (queueFront == nullptr); }

    /**
     * @brief inserts a new item into the queue
     */
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
        ++size;
    }

    /**
     * @return the first element of the queue
     * @exception std::invalid_argument if queue is empty
     */
    value_type front() const {
        ensureNotEmpty();
        return queueFront->data;
    }

    /**
     * @brief removes the first element from the queue
     * @exception std::invalid_argument if queue is empty
     */
    void deQueue() {
        ensureNotEmpty();
        queueFront = queueFront->next;
        --size;
    }

    /**
     * @brief removes all elements from the queue
     */
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
