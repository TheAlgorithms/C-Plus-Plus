/**
 * @author [S-M-J-I](https://github.com/S-M-J-I)
 * @file
 *
 * Implementation of stack that retrieves the minimum element in constant time.
 * (https://www.baeldung.com/cs/stack-constant-time)
 *
 * @details
 * The MinStack data structure keeps track of the minimum element present in a
 * stack and retrieves them at O(1) time.
 */
#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>

/**
 * @namespace
 * @brief data_structures
 */
namespace data_structures {
/**
 * @brief Class representation of a the minimum stack
 */
class MinStack {
 private:
    /**
     * the mainStack keeps track of the elements in the stack
     * the minStack keeps track of the minimum elements present in the stack so
     * far
     */
    std::stack<int> mainStack, minStack;

 public:
    /**
     * @brief Constructs a new MinStack object to initialize the mainStack and
     * the minStack
     */
    MinStack() = default;

    /**
     * @brief Pushes the data in the stack. If the data is the minimum element
     * so far, then pushes it into the minStack to keep track of it.
     * @param data The element to be pushed to the stack
     */
    void push(int data) {
        if (mainStack.empty()) {
            mainStack.push(data);
            minStack.push(data);
            return;
        }

        mainStack.push(data);
        if (data < minStack.top()) {
            minStack.push(data);
        }
    }

    /**
     * @brief Pops the data from the stack. If the data that is removed is the
     * minimum element, then remove it from the minStack as well.
     * @throws std::out_of_range if the stack is empty
     */
    void pop() {
        if (mainStack.empty()) {
            throw std::out_of_range("Stack underflow");
        }

        int top_ele = mainStack.top();
        mainStack.pop();
        if (top_ele == minStack.top()) {
            minStack.pop();
        }
    }
    /**
     * @brief Gets the minimum element of the stack
     * @return The minimum element at the top of the minStack
     * @throws std::out_of_range if the minStack is empty
     */
    int get_min() {
        if (minStack.empty()) {
            throw std::out_of_range("Stack underflow");
        }
        return minStack.top();
    }
};
}  // namespace data_structures

/**
 * @brief test cases
 */
static void test() {
    data_structures::MinStack minStack;

    // Test pushing elements and checking the minimum element
    minStack.push(10);
    assert(minStack.get_min() == 10);

    minStack.push(20);
    assert(minStack.get_min() == 10);

    minStack.push(30);
    minStack.push(4);
    minStack.push(1);
    assert(minStack.get_min() == 1);

    // Test popping elements
    minStack.pop();
    assert(minStack.get_min() == 4);
    minStack.pop();
    assert(minStack.get_min() == 10);

    // Test minStack underflow
    try {
        minStack.pop();
        minStack.pop();
        minStack.pop();
        minStack.pop();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");
    }

    // Try to get the minimum from empty stack
    try {
        minStack.get_min();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
