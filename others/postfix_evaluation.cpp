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
#include <cstdio>     // for fprintf and printf
#include <cstdlib>    // for exit
#include <iostream>   // for io operations
#include <random>     // for mt19937
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
 * @brief Checks whether a token is a non-negative integer literal.
 * @param s token to test
 * @return true if s is non-empty and every character is an ASCII digit
 * @note Invariant: any non-empty digit string is a number; inserting any
 *       non-digit character, or an empty string, is not. Pure function.
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

namespace {
float remove_from_stack(std::stack<float> &stack) {
    if (stack.empty()) {
        throw std::invalid_argument("Not enough operands");
    }
    const auto res = stack.top();
    stack.pop();
    return res;
}
}  // namespace

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
            const auto op2 = remove_from_stack(stack);
            const auto op1 = remove_from_stack(stack);

            evaluate(op1, op2, scan, stack);
        }
    }

    const auto res = remove_from_stack(stack);
    if (!stack.empty()) {
        throw std::invalid_argument("Too many operands");
    }
    return res;
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

static void test_single_input() {
    std::vector<std::string> input = {"1"};
    float answer = others::postfix_expression::postfix_evaluation(input);

    assert(answer == 1);
}

static void test_not_enough_operands() {
    std::vector<std::string> input = {"+"};
    bool throws = false;
    try {
        others::postfix_expression::postfix_evaluation(input);
    } catch (std::invalid_argument &) {
        throws = true;
    }
    assert(throws);
}

static void test_not_enough_operands_empty_input() {
    std::vector<std::string> input = {};
    bool throws = false;
    try {
        others::postfix_expression::postfix_evaluation(input);
    } catch (std::invalid_argument &) {
        throws = true;
    }
    assert(throws);
}

static void test_too_many_operands() {
    std::vector<std::string> input = {"1", "2"};
    bool throws = false;
    try {
        others::postfix_expression::postfix_evaluation(input);
    } catch (std::invalid_argument &) {
        throws = true;
    }
    assert(throws);
}

/**
 * Property tests for is_number(). Fixed seed, so every run is identical.
 * Generator is restricted to ASCII so isdigit() is never given a negative char.
 */
static void test_is_number_properties() {
    using others::postfix_expression::is_number;
    std::mt19937 rng(12345);  // fixed seed
    int checks = 0;
    auto fail = [](const char* what, const std::string& s, bool exp, bool act) {
        std::fprintf(stderr, "FAIL %s on \"%s\": expected %d, actual %d\n",
                     what, s.c_str(), exp, act);
        std::exit(1);
    };

    // Small readable cases first (literal expected values, worked out by hand).
    // postfix_evaluation.cpp:41 empty check and digit check
    struct Small { const char* s; bool expected; };
    const Small smalls[] = {{"0", true},    {"7", true},   {"757", true},
                            {"7570", true}, {"757a", false}, {"", false},
                            {"+", false},   {"4 2", false}};
    for (const Small& c : smalls) {
        bool actual = is_number(std::string(c.s));  // postfix_evaluation.cpp:41
        ++checks;
        if (actual != c.expected) fail("small case", c.s, c.expected, actual);
    }

    // 100 generated digit strings (length 1..9): must all be numbers.
    // postfix_evaluation.cpp:41 all_of with isdigit ensures non-empty digits return true
    for (int i = 0; i < 100; i++) {
        std::string s;
        int len = 1 + rng() % 9;
        for (int k = 0; k < len; k++) s += char('0' + rng() % 10);
        bool a = is_number(s), b = is_number(std::string(s));  // fresh equal input
        ++checks;
        if (!a) fail("digits are a number", s, true, a);
        ++checks;
        if (a != b) fail("repeat gives same result", s, a, b);

        // Insert one non-digit at a random position: must stop being a number.
        // postfix_evaluation.cpp:41 any non-digit causes all_of to return false
        const char bad[] = {'-', '+', '.', ' ', 'a', '*', '/'};
        std::string t = s;
        t.insert(t.begin() + rng() % (t.size() + 1), bad[rng() % 7]);
        ++checks;
        if (is_number(t)) fail("non-digit breaks it", t, false, true);
    }
    std::printf("PROPERTY_CHECKS=%d\n", checks);
}

/**
 * @brief Test neighboring postfix expression:
 * {"2", "3", "1", "*", "+", "4", "-"} -> 1
 */
static void test_neighbor_expression() {
    std::vector<std::string> input = {"2", "3", "1", "*", "+", "4", "-"};
    float answer = others::postfix_expression::postfix_evaluation(input);
    assert(answer == 1);  // postfix_evaluation.cpp:100 (2 + (3 * 1)) - 4 = 1
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test_function_1();
    test_function_2();
    test_function_3();
    test_neighbor_expression();
    test_single_input();
    test_not_enough_operands();
    test_not_enough_operands_empty_input();
    test_too_many_operands();
    test_is_number_properties();

    std::cout << "\nTest implementations passed!\n";

    return 0;
}
