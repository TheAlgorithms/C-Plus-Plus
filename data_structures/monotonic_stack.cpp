#include <iostream>
#include <vector>

class MonotonicStack {
private:
    std::vector<int> stack;

public:
    // Push an element while maintaining the monotonic property
    void push(int value) {
        while (!stack.empty() && stack.back() > value) {
            stack.pop_back();
        }
        stack.push_back(value);
    }

    // Pop the top element
    void pop() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }

    // Get the top element
    int top() {
        if (!stack.empty()) {
            return stack.back();
        }
        throw std::out_of_range("Stack is empty");
    }

    // Check if the stack is empty
    bool empty() {
        return stack.empty();
    }
};

int main() {
    MonotonicStack ms;
    ms.push(3);
    ms.push(1);
    ms.push(2);
    ms.push(0);

    while (!ms.empty()) {
        std::cout << ms.top() << " ";
        ms.pop();
    }

    return 0;
}
