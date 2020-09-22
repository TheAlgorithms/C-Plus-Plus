/**
 * @file
 * @brief Evaluation of Postfix Expression
 * @author [Darshana Sarma](https://github.com/Darshana-Sarma)
 * @details
 * Create a stack to store operands (or values).
 * Scan the given expression and do following for every scanned element.
 * If the element is a number, push it into the stack
 * If the element is a operator, pop operands for the operator from stack.
 * Evaluate the operator and push the result back to the stack
 * When the expression is ended, the number in the stack is the final answer
 */
#include <array>     // for std::array
#include <cassert>   // for assert
#include <iostream>  // for io operations

// Maximum size for stack
const int MAX_SIZE = 20;

// Defining stack
std::array<float, MAX_SIZE> stack;

// Index of top value in stack array
int stackTop;

/**
 * Pushing operand, also called the number in the array to the stack
 * @param operand float value from the input array or evaluation
 * @returns none
 */
void push(float operand) {
    stackTop++;
    stack[stackTop] = operand;
}

/**
 * Popping operand, also called the number from the stack
 * @param none
 * @returns operand float on top of stack
 */
float pop() {
    float operand = stack[stackTop];
    stackTop--;
    return operand;
}

/**
 * Evaluate answer using given operands and operation
 * @param a float
 * @param b float
 * @param operation operation to be performed with respective floats
 * @returns none
 */
void evaluate(float a, float b, char operation) {
    float c = 0;
    switch (operation) {
        case '+':
            c = a + b;
            push(c);
            break;

        case '-':
            c = a - b;
            push(c);
            break;

        case '*':
            c = a * b;
            push(c);
            break;

        case '/':
            c = a / b;
            push(c);
            break;

        default:
            std::cout << "Operator not defined\n";
            break;
    }
}

/**
 * Postfix Evaluation algorithm to compute the value from given input array
 * @param input Array of characters consisting of numbers and operations
 * @param N Array size
 * @returns stack[stackTop] returns the top value from the stack
 */
template <std::size_t N>
float postfix_evaluation(std::array<char, N> input) {
    stackTop = -1;
    int j = 0;
    while (input[j]) {
        char scan = input[j];
        if (isalnum(scan)) {
            push(static_cast<float>(scan - '0'));

        } else {
            float op2 = pop();
            float op1 = pop();

            evaluate(op1, op2, scan);
        }
        j++;
    }

    std::cout << stack[stackTop] << "\n";

    return stack[stackTop];
}

/**
 * Test function 1 with input array
 * {'2', '3', '1', '*', '+', '9', '-'}
 * @returns none
 */
static void test_function_1() {
    std::array<char, 7> input = {'2', '3', '1', '*', '+', '9', '-'};

    float answer = postfix_evaluation(input);

    assert(answer == -4);
}

/**
 * Test function 2 with input array
 * {'1', '2', '+', '2', '/', '5', '*', '7', '+'}
 * @returns none
 */
static void test_function_2() {
    std::array<char, 9> input = {'2', '2', '+', '2', '/', '5', '*', '7', '+'};
    float answer = postfix_evaluation(input);

    assert(answer == 11);
}

/**
 * Main function
 */
int main() {
    test_function_1();
    test_function_2();

    return 0;
}
