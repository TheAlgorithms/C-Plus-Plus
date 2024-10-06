/**
 * @file
 * @brief Implementation of Monotonic Stack
 * @details
 * This is an implementation of a monotonic stack which maintains the stack in increasing order.
 * Elements are pushed such that the stack remains monotonic.
 * If an element is pushed that is smaller than the top element, the top elements are popped until the correct position is found.
 * @see https://en.wikipedia.org/wiki/Monotonic_Stack
 * @author [Srijan Baniyal](https://github.com/Srijan-Baniyal)
 */

#include <iostream>        /// For IO operations
#include <vector>         /// For std::vector
#include <stdexcept>      /// For std::out_of_range

/**
 * @namespace algorithms
 * @brief A namespace for various algorithm implementations
 */
namespace data_structures {

/**
 * @class MonotonicStack
 * @brief A class representing a monotonic stack which maintains elements in increasing order.
 */
class MonotonicStack {
 private:
    std::vector<int> stack;   ///< Vector to store stack elements

 public:
    /**
     * @brief Push an element while maintaining the monotonic property
     * @param value the value to be pushed onto the stack
     */
    void push(int value) {
        while (!stack.empty() && stack.back() > value) {
            stack.pop_back();  // Pop elements until the correct position is found
        }
        stack.push_back(value);  // Push the new value
    }

    /**
     * @brief Pop the top element
     */
    void pop() {
        if (!stack.empty()) {
            stack.pop_back();  // Remove the top element
        }
    }

    /**
     * @brief Get the top element
     * @return the top element of the stack
     * @throws std::out_of_range if the stack is empty
     */
    int top() const {
        if (!stack.empty()) {
            return stack.back();  // Return the top element
        }
        throw std::out_of_range("Stack is empty");  // Error if stack is empty
    }

    /**
     * @brief Check if the stack is empty
     * @return true if the stack is empty, false otherwise
     */
    bool empty() const {
        return stack.empty();  // Check if the stack is empty
    }
};

}  // namespace algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    algorithms::MonotonicStack ms;  // Create an instance of MonotonicStack
    ms.push(3);                     // Push elements onto the stack
    ms.push(1);
    ms.push(2);
    ms.push(0);
    std::vector<int> expected = {0};  // Expected final state of the stack

    for (int value : expected) {
        assert(ms.top() == value);  // Assert that the top matches expected value
        ms.pop();                   // Pop the top element
    }
    assert(ms.empty() == true);     // Assert that the stack is empty

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // Run self-test implementations
    return 0;
}
