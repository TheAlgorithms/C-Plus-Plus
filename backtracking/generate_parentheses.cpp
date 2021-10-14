/**
 * @file
 * @brief Generate all valid parenthses
 * @details
 * Given n parenthesis pairs, generate all valid parenthesis configurations.
 * (While the solution is my own, this problem can be found on LeetCode and in
 * The Elements of Programming Interviews.)
 * @author [Sumukh Atreya](https://github.com/sumukhatreya)
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
namespace generate_valid_parentheses {

/**
 * @brief The generate_parens function generates all the valid parenthesis
 * combinations.
 * @param left_parens is number of left parentheses.
 * @param right_parens is the number of right parentheses. left_parens always
 * equals right_parens when the function is initially called.
 * @param paren is the valid parenthesis string.
 * @param all_parens is the vector that contains all valid parenthesis
 * configurations.
 * @returns void
 */
void generate_parens(const int left_parens, const int right_parens,
                     std::string paren, std::vector<std::string>& all_parens) {
    if (right_parens < left_parens) {
        return;
    }
    if (right_parens == 0 and left_parens == 0) {
        all_parens.push_back(paren);
        return;
    }
    if (left_parens > 0) {
        generate_parens(left_parens - 1, right_parens, paren + "(", all_parens);
    }
    if (right_parens > 0) {
        generate_parens(left_parens, right_parens - 1, paren + ")", all_parens);
    }
    return;
}

/**
 * @brief The print_parens function does some basic error handling, calls the
 * generate_parens function, and returns the vector containing all valid paren
 * configurations. combinations.
 * @param n is the number of parenthesis pairs. Note that n == left_parens ==
 * right_parens.
 * @returns vector that contains all valis parenthsesis configurations.
 */
std::vector<std::string> print_parens(const int n) {
    std::vector<std::string> all_valid_parens;
    try {
        if (n < 0) {
            throw n;
        }
        generate_parens(n, n, "", all_valid_parens);
    } catch (int ex) {
        std::cout << "Inavlid input: " << n << "\n";
    }
    return all_valid_parens;
}
}  // namespace generate_valid_parentheses
}  // namespace backtracking

/**
 * @brief Utility function to compare two vectors of strings (in this case
 * parenthesis strings) to check if they have the same contents.
 * @param vec_one: first vector to compare
 * @param vec_two: second vector to compare
 * @returns bool
 */
bool compare(std::vector<std::string>& vec_one,
             std::vector<std::string>& vec_two) {
    if (vec_one.size() != vec_two.size()) {
        return false;
    }
    for (auto& i : vec_one) {
        bool found = false;
        for (auto& j : vec_two) {
            if (i == j) {
                found = true;
                break;
            }
        }
        if (found == false) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    std::cout << "First test\n";
    std::vector<std::string> res_first;
    assert(backtracking::generate_valid_parentheses::print_parens(-2) ==
           res_first);
    std::cout << "Test passed" << std::endl;

    std::cout << "Second test\n";
    std::vector<std::string> res_second{""};
    assert(backtracking::generate_valid_parentheses::print_parens(0) ==
           res_second);
    std::cout << "Test passed" << std::endl;

    std::cout << "Third test\n";
    std::vector<std::string> res_third{"()"};
    assert(backtracking::generate_valid_parentheses::print_parens(1) ==
           res_third);
    std::cout << "Test passed" << std::endl;

    std::cout << "Fourth test\n";
    std::vector<std::string> res_fourth{"((()))", "(()())", "()()()", "(())()",
                                        "()(())"};
    std::vector<std::string> res =
        backtracking::generate_valid_parentheses::print_parens(3);
    assert(compare(res_fourth, res) == true);
    std::cout << "Test passed" << std::endl;
}

int main() {
    test();
    return 0;
}
