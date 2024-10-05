/**
 * @file
 * @brief Implementation of Monotonic Stack
 * @details
 * This is an implementation of a monotonic stack which maintains the stack in increasing order.
 * Elements are pushed such that the stack remains monotonic.
 * If an element is pushed that is smaller than the top element, the top elements are popped until the correct position is found.
 * @see https://en.wikipedia.org/wiki/Monotonic_Stack
 * @author [Your Name](https://github.com/yourhandle)
 */

#include <iostream>
#include <vector>
#include <stdexcept>  // for std::out_of_range

/**
 * @namespace algorithms
 * @brief A namespace for various algorithm implementations
 */
namespace algorithms {

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
            stack.pop_back();
        }
        stack.push_back(value);
    }

    /**
     * @brief Pop the top element
     */
    void pop() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }

    /**
     * @brief Get the top element
     * @return the top element of the stack
     * @throws std::out_of_range if the stack is empty
     */
    int top() const {
        if (!stack.empty()) {
            return stack.back();
        }
        throw std::out_of_range("Stack is empty");
    }

    /**
     * @brief Check if the stack is empty
     * @return true if the stack is empty, false otherwise
     */
    bool empty() const {
        return stack.empty();
    }
};

}  // namespace algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    algorithms::MonotonicStack ms;
    ms.push(3);
    ms.push(1);
    ms.push(2);
    ms.push(0);
    std::vector<int> expected = {0};  // expected final state of the stack
    for (int value : expected) {
        assert(ms.top() == value);
        ms.pop();
    }
    assert(ms.empty() == true);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
