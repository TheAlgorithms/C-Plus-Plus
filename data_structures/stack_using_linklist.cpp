#include <iostream>

class Node {
 public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class Stack {
 private:
    Node* top;

 public:
    Stack() : top(nullptr) {}

    void push(int data) {
        Node* new_node = new Node(data);
        if (top == nullptr) {
            top = new_node;
        } else {
            new_node->next = top;
            top = new_node;
        }
    }

    int pop() {
        if (is_empty()) {
            std::cerr << "Stack is empty. Cannot pop." << std::endl;
            return -1;  // Return a sentinel value for an empty stack
        } else {
            int popped_data = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return popped_data;
        }
    }

    bool is_empty() const { return top == nullptr; }

    int peek() const {
        if (is_empty()) {
            std::cerr << "Stack is empty. Cannot peek." << std::endl;
            return -1;  // Return a sentinel value for an empty stack
        } else {
            return top->data;
        }
    }

    void display() const {
        Node* current = top;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "None" << std::endl;
    }

    ~Stack() {
        while (!is_empty()) {
            pop();
        }
    }
};

int main() {
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Stack contents:" << std::endl;
    stack.display();

    std::cout << "Pop: " << stack.pop() << std::endl;
    std::cout << "Pop: " << stack.pop() << std::endl;
    std::cout << "Peek: " << stack.peek() << std::endl;

    std::cout << "Stack contents after popping:" << std::endl;
    stack.display();

    return 0;
}
