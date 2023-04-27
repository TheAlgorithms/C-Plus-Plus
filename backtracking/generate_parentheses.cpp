/**
 * @file
 * @brief Well-formed [Generated
 * Parentheses](https://leetcode.com/explore/interview/card/top-interview-questions-medium/109/backtracking/794/) with all combinations.
 *
 * @details a sequence of parentheses is well-formed if each opening parentheses
 * has a corresponding closing parenthesis
 * and the closing parentheses are correctly ordered
 *
 * @author [Giuseppe Coco](https://github.com/WoWS17)

 */

#include <cassert>   /// for assert
#include <iostream>  /// for I/O operation
#include <vector>    /// for vector container

/**
 * @brief Backtracking algorithms
 * @namespace backtracking
 */
namespace backtracking {
/**
 * @brief generate_parentheses class
 */
class generate_parentheses {
 private:
    std::vector<std::string> res;  ///< Contains all possible valid patterns

    void makeStrings(std::string str, int n, int closed, int open);

 public:
    std::vector<std::string> generate(int n);
};

/**
 * @brief function that adds parenthesis to the string.
 *
 * @param str string build during backtracking
 * @param n number of pairs of parentheses
 * @param closed number of closed parentheses
 * @param open number of open parentheses
 */

void generate_parentheses::makeStrings(std::string str, int n,
                                                     int closed, int open) {
    if (closed > open)  // We can never have more closed than open
        return;

    if ((str.length() == 2 * n) &&
        (closed != open)) {  // closed and open must be the same
        return;
    }

    if (str.length() == 2 * n) {
        res.push_back(str);
        return;
    }

    makeStrings(str + ')', n, closed + 1, open);
    makeStrings(str + '(', n, closed, open + 1);
}

/**
 * @brief wrapper interface
 *
 * @param n number of pairs of parentheses
 * @return all well-formed pattern of parentheses
 */
std::vector<std::string> generate_parentheses::generate(int n) {
    backtracking::generate_parentheses::res.clear();
    std::string str = "(";
    generate_parentheses::makeStrings(str, n, 0, 1);
    return res;
}
}  // namespace backtracking

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    int n = 0;
    std::vector<std::string> patterns;
    backtracking::generate_parentheses p;

    n = 1;
    patterns = {{"()"}};
    assert(p.generate(n) == patterns);

    n = 3;
    patterns = {{"()()()"}, {"()(())"}, {"(())()"}, {"(()())"}, {"((()))"}};

    assert(p.generate(n) == patterns);

    n = 4;
    patterns = {{"()()()()"}, {"()()(())"}, {"()(())()"}, {"()(()())"},
                {"()((()))"}, {"(())()()"}, {"(())(())"}, {"(()())()"},
                {"(()()())"}, {"(()(()))"}, {"((()))()"}, {"((())())"},
                {"((()()))"}, {"(((())))"}};
    assert(p.generate(n) == patterns);

    std::cout << "All tests passed\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
