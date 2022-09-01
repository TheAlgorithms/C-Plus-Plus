/**
 * @file
 * @brief
 * [Generate valid
 * parentheses](http://www.cs.toronto.edu/~mhsadi/code-repository/4-GenerateValidParenthesisV1.html)
 * puzzle
 *
 * @details
 * The **generate valid parentheses** is the problem of generating all
 * combinations of well-formed parentheses for given n pairs of parentheses.
 *
 * @author [Kartik Kapgate](https://github.com/10kartik)
 *
 */
#include <iostream>
#include <string>
#include <vector>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace generate_valid_parentheses
 * @brief Functions for
 * [generate_valid_parentheses](https://leetcode.com/problems/generate-parentheses/)
 * puzzle.
 */
namespace generate_valid_parentheses {
/**
 * Utility function to print all generated valid combinations
 * @param combinations vector of string storing all the valid combinations
 */
void printSolution(std::vector<std::string> &combinations) {
    std::cout << "\n";
    for (int i = 0; i < combinations.size(); i++) {
        std::cout << "" << combinations[i] << " ";
        std::cout << "\n";
    }
}

/**
 * Generates all combinations of balanced parentheses
 * @param combinations vector of string storing all the valid combinations
 * @param str string which is maninpulated to become valid combination
 * @param n int value holding number of opening parentheses '(' in str
 * @param m int value holding number of opening parentheses ')' in str
 */
void generateParentheses(std::vector<std::string> &combinations,
                         std::string str, int n, int m) {
    if (n == 0 && m == 0) {
        combinations.push_back(str);
        return;
    }

    // if opening brackets in str are greater than closing brackets
    // we can add ')' to str
    if (m > 0) {
        backtracking::generate_valid_parentheses::generateParentheses(
            combinations, str + ")", n, m - 1);
    }

    // if count of opening brackets to be added in str is greater than zero
    // we can add '(' to str
    if (n > 0) {
        backtracking::generate_valid_parentheses::generateParentheses(
            combinations, str + "(", n - 1, m + 1);
    }
}
}  // namespace generate_valid_parentheses
}  // namespace backtracking

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int n = 4;
    std::vector<std::string> combinations;

    backtracking::generate_valid_parentheses::generateParentheses(combinations,
                                                                  "", n, 0);
    backtracking::generate_valid_parentheses::printSolution(combinations);
    return 0;
}
