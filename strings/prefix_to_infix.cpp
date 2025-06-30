/**
 * @file
 * @brief Converts prefix expressions to infix using a stack.
 * @details
 * Traverses from right to left, building binary operations.
 * See [Prefix to Infix](https://www.geeksforgeeks.org/prefix-infix-conversion/)
 * for reference and algorithm details.
 */

#include <cassert>   /// for assert
#include <cctype>    /// for isalnum
#include <iostream>  /// for std::cout
#include <stack>     /// for std::stack
#include <string>    /// for std::string

/**
 * @namespace expression
 * @brief Algorithms for expression parsing and conversion
 */
namespace expression {

/**
 * @brief Check if the character is an operator.
 */
bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

/**
 * @brief Convert prefix expression to infix.
 * @param prefix the input prefix expression
 * @return infix expression as a string
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
            std::string expr = "(" + op1 + ch + op2 + ")";
            stk.push(expr);
        }
    }

    return (stk.size() == 1) ? stk.top() : "Invalid Expression";
}

}  // namespace expression

/**
 * @brief Self-test implementations
 */
static void test() {
    assert(expression::prefix_to_infix("*-A/BC-/AKL") ==
           "((A-(B/C))*((A/K)-L))");
    assert(expression::prefix_to_infix("+AB") == "(A+B)");
    assert(expression::prefix_to_infix("*+AB-CD") == "((A+B)*(C-D))");

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 */
int main() {
    test();
    return 0;
}