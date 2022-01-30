/**
 * @file
 * @brief [Stack implementation to check Valid Parentheses in string]
   (https://leetcode.com/problems/valid-parentheses/)
 *
 * @details
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid. Input string is valid if:
 * Open brackets closed by same type of brackets
 * Open brackets closed in correct order
 *
 * Time Complexity: O(n)
 * Space complexity: O(n)
 * @author [Tuan Dang](https://github.com/tuan-dang-0)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for cout
#include <map>       /// for std::map
#include <stack>     /// for std::stack

/**
 * @namespace others
 * @brief Other algorithms
 */
namespace others {

/**
 * @namespace valid_parentheses
 * @brief Functions for the [Check Valid Parentheses in string]
   (https://leetcode.com/problems/valid-parentheses/)
 *
 */
namespace valid_parentheses {
/**
 * @brief The main function checks validity
 * @param "input" is the string whose validity will be checked
 * @returns a boolean after checking whether parentheses are valid in string
 */

bool is_valid(std::string input) {
    // Map closing brackets to respective opening bracket
    std::map<char, char> brackets;
    brackets[')'] = '(';
    brackets['}'] = '{';
    brackets[']'] = '[';

    std::stack<char> stk;

    // Go through every character in string
    for (char character : input) {
        // If current character is an opening bracket, push to stack
        if (character == '(' || character == '{' || character == '[')
            stk.push(character);

        // If current character is a closing bracket, check to see if top of
        // stack is the corresponding open bracket
        if (character == ')' || character == '}' || character == ']') {
            if (!stk.empty() && stk.top() == brackets[character])
                stk.pop();

            // If there is not an opening bracket to match current closing
            // bracket, string invalid
            else
                return false;

        }
    }

    // If there are open parentheses unmatched, string invalid
    if (!stk.empty()) {
        return false;

    }

    return true;
}
}  // namespace valid_parentheses
}  // namespace others

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // input = "}", returns false
    assert(others::valid_parentheses::is_valid("}") == false);
    // input = "(}", returns false
    assert(others::valid_parentheses::is_valid("(}") == false);
    // input = "(){}[]", returns true
    assert(others::valid_parentheses::is_valid("(){}[]") == true);
    // input = "{[[]{}]}", returns true
    assert(others::valid_parentheses::is_valid("{[[]{}]}") == true);

    std::cout << "All test cases passed!" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
