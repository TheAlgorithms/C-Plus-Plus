/**
 * @file
 * @brief Converts infix expressions to prefix notation using reversal and
 * infix-to-postfix logic.
 * @details
 * Uses the idea that prefix = reverse(postfix(reverse(infix))).
 * See [Prefix notation](https://en.wikipedia.org/wiki/Polish_notation) for
 * theory and use cases.
 */

#include <algorithm>  /// for std::reverse
#include <cassert>    /// for assert
#include <cctype>     /// for isalnum
#include <iostream>   /// for std::cout
#include <stack>      /// for std::stack
#include <string>     /// for std::string

/**
 * @namespace expression
 * @brief Algorithms for expression parsing and conversion
 */
namespace expression {

/**
 * @brief Check if a character is an operator.
 */
bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

/**
 * @brief Get precedence of an operator.
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
 * @brief Check if an operator is right-associative.
 */
bool is_right_associative(char op) { return op == '^'; }

/**
 * @brief Convert infix to postfix (reused from infix_to_postfix.cpp).
 */
std::string infix_to_postfix(const std::string &expr) {
    std::stack<char> ops;
    std::string result;

    for (char token : expr) {
        if (std::isspace(token))
            continue;

        if (std::isalnum(token)) {
            result += token;
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                result += ops.top();
                ops.pop();
            }
            if (!ops.empty())
                ops.pop();
        } else if (is_operator(token)) {
            while (!ops.empty() && is_operator(ops.top())) {
                char top = ops.top();
                if ((is_right_associative(token) &&
                     precedence(token) < precedence(top)) ||
                    (!is_right_associative(token) &&
                     precedence(token) <= precedence(top))) {
                    result += top;
                    ops.pop();
                } else
                    break;
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

/**
 * @brief Convert infix expression to prefix using reverse + postfix conversion.
 * @param expr input infix expression
 * @returns prefix expression
 */
std::string infix_to_prefix(const std::string &expr) {
    std::string rev_expr = expr;
    std::reverse(rev_expr.begin(), rev_expr.end());

    for (char &ch : rev_expr) {
        if (ch == '(')
            ch = ')';
        else if (ch == ')')
            ch = '(';
    }

    std::string postfix = infix_to_postfix(rev_expr);
    std::reverse(postfix.begin(), postfix.end());
    return postfix;
}

}  // namespace expression

/**
 * @brief Self-tests
 */
static void test() {
    assert(expression::infix_to_prefix("(a-b/c)*(a/k-l)") == "*-a/bc-/akl");
    assert(expression::infix_to_prefix("a+b*c") == "+a*bc");
    assert(expression::infix_to_prefix("((a+b)*c)-d^e^f") == "-*+abc^d^ef");

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 */
int main() {
    test();
    return 0;
}