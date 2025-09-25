/**
 * @file
 * @brief Evaluation of [Postfix
 * Expression](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
 * @author [Darshana Sarma](https://github.com/Darshana-Sarma)
 * @details
 * Create a stack to store operands (or values).
 * Scan the given expression and do following for every scanned element.
 * If the element is a number, push it into the stack
 * If the element is a operator, pop operands for the operator from stack.
 * Evaluate the operator and push the result back to the stack
 * When the expression is ended, the number in the stack is the final answer
 */
#include <algorithm>  // for all_of
#include <cassert>    // for assert
#include <iostream>   // for io operations
#include <stack>      // for std::stack
#include <string>     // for stof
#include <vector>     // for std::vector

/**
 * @namespace others
 * @brief Other algorithms
 */
namespace others {
/**
 * @namespace postfix_expression
 * @brief Functions for Postfix Expression algorithm
 */
namespace postfix_expression {

/**
 * @brief Checks if scanned string is a number
 * @param s scanned string
 * @returns bool boolean value if string is number
 */
bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

/**
 * @brief Evaluate answer using given last two operands from and operation
 * @param a second last added operand which will be used for evaluation
 * @param b last added operand which will be used for evaluation
 * @param operation to be performed with respective floats
 * @param stack containing numbers
 * @returns none
 */
void evaluate(float a, float b, const std::string &operation,
              std::stack<float> &stack) {
    float c = 0;
    const char *op = operation.c_str();
    switch (*op) {
        case '+':
            c = a + b;  // Addition of numbers
            stack.push(c);
            break;

        case '-':
            c = a - b;  // Subtraction of numbers
            stack.push(c);
            break;

        case '*':
            c = a * b;  // Multiplication of numbers
            stack.push(c);
            break;

        case '/':
            c = a / b;  // Division of numbers
            stack.push(c);
            break;

        default:
            std::cout << "Operator not defined\n";
            break;
    }
}

/**
 * @brief Postfix Evaluation algorithm to compute the value from given input
 * array
 * @param input vector of strings consisting of numbers and operations
 * @returns stack[stackTop] returns the top value from the stack
 */
float postfix_evaluation(const std::vector<std::string> &input) {
    std::stack<float> stack;

    for (const auto &scan : input) {
        if (is_number(scan)) {
            stack.push(std::stof(scan));

        } else {
            const float op2 = stack.top();
            stack.pop();
            const float op1 = stack.top();
            stack.pop();

            evaluate(op1, op2, scan, stack);
        }
    }

    std::cout << stack.top() << "\n";

    return stack.top();
}
}  // namespace postfix_expression
}  // namespace others

/**
 * @brief Test function 1 with input array
 * {'2', '3', '1', '*', '+', '9', '-'}
 * @returns none
 */
static void test_function_1() {
    std::vector<std::string> input = {"2", "3", "1", "*", "+", "9", "-"};

    float answer = others::postfix_expression::postfix_evaluation(input);

    assert(answer == -4);
}

/**
 * @brief Test function 2 with input array
 * {'100', '200', '+', '2', '/', '5', '*', '7', '+'}
 * @returns none
 */
static void test_function_2() {
    std::vector<std::string> input = {"100", "200", "+", "2", "/",
                                      "5",   "*",   "7", "+"};
    float answer = others::postfix_expression::postfix_evaluation(input);

    assert(answer == 757);
}

static void test_function_3() {
    std::vector<std::string> input = {
        "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
        "1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
        "+", "+", "+", "+", "+", "+", "+", "+", "+", "+", "+",
        "+", "+", "+", "+", "+", "+", "+", "+", "+", "+"};
    float answer = others::postfix_expression::postfix_evaluation(input);

    assert(answer == 22);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test_function_1();
    test_function_2();
    test_function_3();

    std::cout << "\nTest implementations passed!\n";

    return 0;
}
