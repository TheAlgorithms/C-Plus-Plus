/**
 * @file
 * @brief Expression conversion utilities: infix to postfix/prefix and prefix to
 * infix
 * @details
 * This module provides functions to convert expressions between
 * infix, postfix (Reverse Polish Notation), and prefix (Polish Notation)
 * using the Shunting Yard algorithm and stack-based methods.
 * See: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */

#include <algorithm>  /// for std::reverse
#include <cassert>    /// for assert
#include <cctype>     /// for isalnum, isspace
#include <iostream>   /// for IO operations
#include <stack>      /// for std::stack
#include <string>     /// for std::string

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
 * @brief Returns precedence level of operator.
 * @param op operator character
 * @return integer precedence
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
 * @brief Returns true if operator is right-associative.
 * @param op operator character
 * @return true if right-associative
 */
bool is_right_associative(char op) { return op == '^'; }

/**
 * @brief Converts an infix expression to postfix notation.
 * @param expr input infix expression
 * @return postfix expression as string
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
                ops.pop();  // discard '('
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

/**
 * @brief Converts an infix expression to prefix notation.
 * @param expr input infix expression
 * @return prefix expression as string
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

/**
 * @brief Converts a prefix expression to infix notation.
 * @param prefix input prefix expression
 * @return infix expression or "Invalid Expression" on error
 */
std::string prefix_to_infix(const std::string &prefix) {
    std::stack<std::string> stk;

    for (int i = static_cast<int>(prefix.length()) - 1; i >= 0; --i) {
        char ch = prefix[i];
        if (std::isspace(ch))
            continue;

        if (std::isalnum(ch)) {
            stk.push(std::string(1, ch));
        } else if (is_operator(ch)) {
            if (stk.size() < 2)
                return "Invalid Expression";

            std::string op1 = stk.top();
            stk.pop();
            std::string op2 = stk.top();
            stk.pop();
            stk.push("(" + op1 + ch + op2 + ")");
        }
    }

    return (stk.size() == 1) ? stk.top() : "Invalid Expression";
}

}  // namespace expression

/**
 * @brief Self-tests for the expression conversion functions.
 */
static void test() {
    using namespace expression;

    // Infix to Postfix
    assert(infix_to_postfix("a+(b*c-(d/e^f)*g)*h") == "abc*def^/g*-h*+");
    assert(infix_to_postfix("A*(B+C)") == "ABC+*");
    assert(infix_to_postfix("A+B*C") == "ABC*+");
    assert(infix_to_postfix("((A+B)*C)-D^E^F") == "AB+C*DEF^^-");

    // Infix to Prefix
    assert(infix_to_prefix("(a-b/c)*(a/k-l)") == "*-a/bc-/akl");

    // Prefix to Infix
    assert(prefix_to_infix("*-A/BC-/AKL") == "((A-(B/C))*((A/K)-L))");

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main driver
 */
int main() {
    test();
    return 0;
}