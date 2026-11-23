/**
 * @file
 * @brief Implementation of a [FIFO Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))
 * using a singly linked list.
 *
 * @details
 * Supports enqueueing at the rear, dequeueing from the front, inspecting the
 * front element, and checking emptiness in O(1) time per operation, with
 * automatic cleanup of allocated nodes upon destruction.
 */

#include <cassert>   // for assert
#include <iostream>  // for std::cout, std::endl
#include <stdexcept> // for std::underflow_error

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {

/**
 * @brief A FIFO queue backed by a singly linked list.
 */
class LinkedQueue {
 private:
    /**
     * @brief Internal node structure representing an element in the queue.
     */
    struct Node {
        int val;          ///< Stored integer value
        Node* next;       ///< Pointer to the next node toward the rear

        /**
         * @brief Constructs a node with a given value and optional next pointer.
         * @param value Integer value to store
         * @param next_node Pointer to the next node (defaults to nullptr)
         */
        explicit Node(int value, Node* next_node = nullptr)
            : val(value), next(next_node) {}
    };

    Node* front_{nullptr};  ///< Pointer to the front (oldest) node
    Node* rear_{nullptr};   ///< Pointer to the rear (newest) node

 public:
    /**
     * @brief Constructs an empty queue.
     */
    LinkedQueue() = default;

    /**
     * @brief Destroys the queue and frees all remaining dynamically allocated nodes.
     */
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    /**
     * @brief Checks whether the queue contains no elements.
     * @return `true` if empty, `false` otherwise
     */
    bool isEmpty() const noexcept { return front_ == nullptr; }

    /**
     * @brief Inserts an element at the rear of the queue.
     * @param x Value to insert
     */
    void enqueue(int x) {
        Node* new_node = new Node(x, nullptr);
        if (isEmpty()) {
            front_ = new_node;
            rear_ = new_node;
        } else {
            rear_->next = new_node;
            rear_ = new_node;
        }
    }

    /**
     * @brief Removes and returns the element at the front of the queue.
     * @return Value of the removed front element
     * @throws std::underflow_error if the queue is empty
     */
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue underflow: cannot dequeue from an empty queue");
        }
        Node* temp = front_;
        int removed_val = temp->val;
        front_ = front_->next;
        if (front_ == nullptr) {
            rear_ = nullptr;
        }
        delete temp;
        return removed_val;
    }

    /**
     * @brief Returns the value at the front of the queue without removing it.
     * @return Value at the front of the queue
     * @throws std::underflow_error if the queue is empty
     */
    int front() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty: no front element");
        }
        return front_->val;
    }
};

}  // namespace data_structures

/**
 * @brief Self-test implementations using assertions.
 * @returns `void`
 */
static void test() {
    data_structures::LinkedQueue q;
    assert(q.isEmpty());

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    assert(!q.isEmpty());
    assert(q.front() == 10);

    // FIFO order verification
    assert(q.dequeue() == 10);
    assert(q.front() == 20);
    assert(q.dequeue() == 20);
    assert(q.front() == 30);

    // Enqueue after partial dequeue
    q.enqueue(40);
    assert(q.dequeue() == 30);
    assert(q.dequeue() == 40);
    assert(q.isEmpty());

    // Underflow check on empty queue
    bool caught_underflow = false;
    try {
        q.dequeue();
    } catch (const std::underflow_error&) {
        caught_underflow = true;
    }
    assert(caught_underflow);

    // Destructor cleanup check with remaining elements
    data_structures::LinkedQueue q2;
    q2.enqueue(100);
    q2.enqueue(200);
    assert(!q2.isEmpty());
}

/**
 * @brief Main execution entrypoint.
 * @returns `0` on success
 */
int main() {
    test();  // run self-test assertions
    std::cout << "All linked queue tests passed successfully!" << std::endl;
    return 0;
}