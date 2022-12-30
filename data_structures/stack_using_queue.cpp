/**
 * @brief Stack Data Structure Using the Queue Data Structure
 * @details
 * Using 2 Queues inside the Stack class, we can easily implement Stack
 * data structure with heavy computation in push function.
 *
 * References used:
 * [StudyTonight](https://www.studytonight.com/data-structures/stack-using-queue)
 * @author [tushar2407](https://github.com/tushar2407)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <queue>     /// for queue data structure

/**
 * @namespace data_structures
 * @brief Data structures algorithms
 */
namespace data_structures {
/**
 * @namespace stack_using_queue
 * @brief Functions for the [Stack Using
 * Queue](https://www.studytonight.com/data-structures/stack-using-queue)
 * implementation
 */
namespace stack_using_queue {
/**
 * @brief Stack Class implementation for basic methods of Stack Data Structure.
 */
struct Stack {
    std::queue<int64_t> main_q;       ///< stores the current state of the stack
    std::queue<int64_t> auxiliary_q;  ///< used to carry out intermediate
                                      ///< operations to implement stack
    uint32_t current_size = 0;        ///< stores the current size of the stack

    /**
     * Returns the top most element of the stack
     * @returns top element of the queue
     */
    int top() { return main_q.front(); }

    /**
     * @brief Inserts an element to the top of the stack.
     * @param val the element that will be inserted into the stack
     * @returns void
     */
    void push(int val) {
        auxiliary_q.push(val);
        while (!main_q.empty()) {
            auxiliary_q.push(main_q.front());
            main_q.pop();
        }
        swap(main_q, auxiliary_q);
        current_size++;
    }

    /**
     * @brief Removes the topmost element from the stack
     * @returns void
     */
    void pop() {
        if (main_q.empty()) {
            return;
        }
        main_q.pop();
        current_size--;
    }

    /**
     * @brief Utility function to return the current size of the stack
     * @returns current size of stack
     */
    int size() { return current_size; }
};
}  // namespace stack_using_queue
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::stack_using_queue::Stack s;
    s.push(1);  /// insert an element into the stack
    s.push(2);  /// insert an element into the stack
    s.push(3);  /// insert an element into the stack

    assert(s.size() == 3);  /// size should be 3

    assert(s.top() == 3);  /// topmost element in the stack should be 3

    s.pop();               /// remove the topmost element from the stack
    assert(s.top() == 2);  /// topmost element in the stack should now be 2

    s.pop();  /// remove the topmost element from the stack
    assert(s.top() == 1);

    s.push(5);             /// insert an element into the stack
    assert(s.top() == 5);  /// topmost element in the stack should now be 5

    s.pop();               /// remove the topmost element from the stack
    assert(s.top() == 1);  /// topmost element in the stack should now be 1

    assert(s.size() == 1);  /// size should be 1
}

/**
 * @brief Main function
 * Creates a stack and pushed some value into it.
 * Through a series of push and pop functions on stack,
 * it demostrates the functionality of the custom stack
 * declared above.
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
