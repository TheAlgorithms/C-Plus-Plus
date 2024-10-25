#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cctype>

bool isOperator(const std::string &s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool isNumber(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), [](char c) { return std::isdigit(c) || c == '.'; });
}

float evaluate(float a, float b, const std::string &op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    throw std::invalid_argument("Unknown operator");
}

float prefixEvaluation(const std::vector<std::string> &expression) {
    std::stack<float> stack;

    // Traverse the expression from right to left
    for (auto it = expression.rbegin(); it != expression.rend(); ++it) {
        const std::string &token = *it;

        if (isNumber(token)) {
            stack.push(std::stof(token));
        } else if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid prefix expression");
            }
            float op1 = stack.top(); stack.pop();
            float op2 = stack.top(); stack.pop();
            float result = evaluate(op1, op2, token);
            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid prefix expression");
    }

    return stack.top();
}

int main() {
    // Example expressions
    std::vector<std::string> expression1 = {"+", "*", "2", "3", "1"}; // Equivalent to (2 * 3) + 1
    std::vector<std::string> expression2 = {"-", "+", "100", "200", "/", "5", "2"}; // Equivalent to (100 + 200) - (5 / 2)

    try {
        float result1 = prefixEvaluation(expression1);
        std::cout << "Result of expression1: " << result1 << std::endl; // Expected output: 7

        float result2 = prefixEvaluation(expression2);
        std::cout << "Result of expression2: " << result2 << std::endl; // Expected output: 297.5
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}