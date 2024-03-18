/**
 * @file
 * @brief Implementation of a stack data structure
 * @details
 * This implementation provides functionalities to push, pop, and view elements
 * of the stack. It also includes a self-test method to ensure proper
 * functionality.
 */

#include <cassert>    /// For assert
#include <iostream>   /// For IO operations
#include <stdexcept>  /// For std::out_of_range

/*
 * @namespace
 * @brief Data structures
 */
namespace data_structures {
/**
 * @brief Class representation of a stack
 * @tparam T The type of the elements in the stack
 */
template <typename T>
class Stack {
 private:
    T* stack;        ///< Pointer to the stack array
    int stackSize;   ///< Maximum size of the stack
    int stackIndex;  ///< Index pointing to the top element of the stack

 public:
    /**
     * @brief Constructs a new Stack object
     *
     * @param size Maximum size of the stack
     */
    Stack(int size) : stackSize(size), stackIndex(0) { stack = new T[size]; }

    /**
     * @brief Destroys the Stack object
     */
    ~Stack() { delete[] stack; }

    /**
     * @brief Pushes an element onto the stack
     *
     * @param element Element to push onto the stack
     * @return true if the element was successfully pushed onto the stack, false
     * otherwise
     */
    bool push(T element) {
        if (stackIndex == stackSize) {
            return false;
        } else {
            stack[stackIndex++] = element;
            return true;
        }
    }

    /**
     * @brief Pops an element from the stack
     *
     * @return The popped element
     * @throws std::out_of_range if the stack is empty
     */
    T pop() {
        if (stackIndex == 0) {
            throw std::out_of_range("Stack is empty");
        } else {
            return stack[--stackIndex];
        }
    }

    /**
     * @brief Displays all elements in the stack
     */
    void show() {
        for (int i = 0; i < stackIndex; i++) {
            std::cout << stack[i] << "\n";
        }
    }

    /**
     * @brief Displays the topmost element of the stack
     *
     * @return The topmost element of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T topmost() const {
        if (stackIndex > 0) {
            return stack[stackIndex - 1];
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }

    /**
     * @brief Displays the bottom element of the stack
     *
     * @return The bottom element of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T bottom() const {
        if (stackIndex > 0) {
            return stack[0];
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }
};
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::Stack<int> stack(5);

    // Test push, pop, topmost and bottom operations
    assert(stack.push(10) == true);
    assert(stack.push(20) == true);
    assert(stack.push(30) == true);
    assert(stack.push(40) == true);
    assert(stack.push(50) == true);
    assert(stack.push(60) == false);

    assert(stack.pop() == 50);
    assert(stack.pop() == 40);
    assert(stack.pop() == 30);

    assert(stack.topmost() == 20);
    assert(stack.bottom() == 10);

    assert(stack.pop() == 20);
    assert(stack.pop() == 10);

    // Test for exceptions when stack is empty
    try {
        stack.topmost();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is empty");
    }

    try {
        stack.bottom();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is empty");
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
