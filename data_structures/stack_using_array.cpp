#include <cassert>    /// For std::assert
#include <iostream>   /// For std::cout
#include <memory>     /// For std::unique_ptr
#include <stdexcept>  /// For std::out_of_range

/**
 * @namespace
 * @brief data_structures
 */
namespace data_structures {
/**
 * @brief Class representation of a stack
 * @tparam T The type of the elements in the stack
 */
template <typename T>
class Stack {
 private:
    std::unique_ptr<T[]> stack;  ///< Smart pointer to the stack array
    int stackSize;               ///< Maximum size of the stack
    int stackIndex;  ///< Index pointing to the top element of the stack

 public:
    /**
     * @brief Constructs a new Stack object
     *
     * @param size Maximum size of the stack
     */
    Stack(int size) : stack(new T[size]), stackSize(size), stackIndex(-1) {}

    /**
     * @brief Checks if the stack is full
     *
     * @return true if the stack is full, false otherwise
     */
    bool full() const { return stackIndex == stackSize - 1; }

    /**
     * @brief Checks if the stack is empty
     * @return true if the stack is empty, false otherwise
     */
    bool empty() const { return stackIndex == -1; }

    /**
     * @brief Pushes an element onto the stack
     *
     * @param element Element to push onto the stack
     */
    void push(T element) {
        if (full()) {
            throw std::out_of_range("Stack overflow");
        } else {
            stack[++stackIndex] = element;
        }
    }

    /**
     * @brief Pops an element from the stack
     *
     * @return The popped element
     * @throws std::out_of_range if the stack is empty
     */
    T pop() {
        if (empty()) {
            throw std::out_of_range("Stack underflow");
        }
        return stack[stackIndex--];
    }

    /**
     * @brief Displays all elements in the stack
     */
    void show() const {
        for (int i = 0; i <= stackIndex; i++) {
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
        if (empty()) {
            throw std::out_of_range("Stack underflow");
        }
        return stack[stackIndex];
    }

    /**
     * @brief Displays the bottom element of the stack
     *
     * @return The bottom element of the stack
     * @throws std::out_of_range if the stack is empty
     */
    T bottom() const {
        if (empty()) {
            throw std::out_of_range("Stack underflow");
        }
        return stack[0];
    }
};
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::Stack<int> stack(5);

    // Test empty and full operations
    assert(stack.empty());
    assert(!stack.full());

    // Test pushing elements and checking topmost
    stack.push(10);
    assert(stack.topmost() == 10);

    stack.push(20);
    assert(stack.topmost() == 20);

    stack.push(30);
    stack.push(40);
    stack.push(50);
    assert(stack.full());

    // Test stack overflow
    try {
        stack.push(60);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack overflow");
    }

    // Test popping elements
    assert(stack.pop() == 50);
    assert(stack.pop() == 40);
    assert(stack.pop() == 30);

    // Check topmost and bottom elements
    assert(stack.topmost() == 20);
    assert(stack.bottom() == 10);

    assert(stack.pop() == 20);
    assert(stack.pop() == 10);

    assert(stack.empty());
    assert(!stack.full());

    // Test stack underflow
    try {
        stack.pop();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");
    }

    try {
        stack.topmost();
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack underflow");
    }

    try {
        stack.bottom();
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
