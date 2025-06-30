/**
 * @file
 * @brief Conversion of infix expressions to postfix using the Shunting Yard
 * algorithm.
 * @details
 * Infix expressions (e.g., A + B) are converted to postfix (e.g., AB+) to
 * simplify evaluation. See [Shunting Yard
 * Algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
 */

#include <cassert>   /// for assert
#include <cctype>    /// for isalnum, isspace
#include <iostream>  /// for IO operations
#include <stack>     /// for std::stack
#include <string>    /// for std::string

/**
 * @namespace expression
 * @brief Algorithms for expression parsing and conversion
 */
namespace expression {

/**
 * @brief Checks if the given character is a supported operator.
 * @param c input character
 * @return true if operator, false otherwise
 */
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/**
 * @brief Returns precedence level of operator
 */
int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

/**
 * @brief Returns true if operator is right-associative
 */
bool is_right_associative(char op) { return op == '^'; }

/**
 * @brief Converts an infix expression to postfix (RPN).
 * @param expr the input infix expression
 * @return postfix expression as string
 */
std::string infix_to_postfix(const std::string &expr) {
    std::stack<char> ops;
    std::string result;

    for (char token : expr) {
        if (std::isspace(token)) {
            continue;
        }
        if (std::isalnum(token)) {
            result += token;
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                result += ops.top();
                ops.pop();
            }
            if (!ops.empty()) {
                ops.pop();  // remove '('
            }
        } else if (is_operator(token)) {
            while (!ops.empty() && is_operator(ops.top())) {
                char top = ops.top();
                if ((is_right_associative(token) &&
                     precedence(token) < precedence(top)) ||
                    (!is_right_associative(token) &&
                     precedence(token) <= precedence(top))) {
                    result += top;
                    ops.pop();
                } else {
                    break;
                }
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        result += ops.top();
        ops.pop();
    }

    return result;
}

}  // namespace expression

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(expression::infix_to_postfix("a+(b*c-(d/e^f)*g)*h") ==
           "abc*def^/g*-h*+");
    assert(expression::infix_to_postfix("A*(B+C)") == "ABC+*");
    assert(expression::infix_to_postfix("A+B*C") == "ABC*+");
    assert(expression::infix_to_postfix("((A+B)*C)-D^E^F") == "AB+C*DEF^^-");

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 */
int main() {
    test();
    return 0;
}