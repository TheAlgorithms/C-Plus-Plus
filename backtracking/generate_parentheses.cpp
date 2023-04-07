/**
 * @file
 * @brief Generates all combinations of well-formed parentheses.
 *
 * @details a sequence of parentheses is well-formed if each opening parentheses
 has a corresponding closing parenthesis
 *  and the closing parentheses are correctly ordered
 *
 * @author [Giuseppe Coco](https://github.com/WoWS17)

 */

#include <cassert>
#include <iostream>
#include <vector>

class generate_parentheses {
 private:
    std::vector<std::string> res;  // Contains all possible valid patterns

    /**
     * @brief function that implements backtracking
     *
     * @param str string build during backtracking
     * @param n number of pairs of parentheses
     * @param closed number of closed parentheses
     * @param open number of open parentheses
     */

    void makeStrings(std::string str, int n, int closed, int open) {
        if (closed > open)  // We can never have more closed than open
            return;

        if (str.length() == 2 * n and
            closed != open)  // closed and open must be the same
            return;

        if (str.length() == 2 * n) {
            res.push_back(str);
            return;
        }

        makeStrings(str + ')', n, closed + 1, open);
        makeStrings(str + '(', n, closed, open + 1);
    }

 public:
    /**
     * @brief wrapper interface
     *
     * @param n number of pairs of parentheses
     * @return all well-formed pattern of parentheses
     */
    std::vector<std::string> generate_parenthesis(int n) {
        res.clear();
        std::string str = "(";
        makeStrings(str, n, 0, 1);
        return res;
    }
};

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    int n;
    std::vector<std::string> patterns;
    generate_parentheses p;

    n = 1;
    patterns = {{"()"}};
    assert(p.generate_parenthesis(n) == patterns);

    n = 3;
    patterns = {{"()()()"}, {"()(())"}, {"(())()"}, {"(()())"}, {"((()))"}};

    assert(p.generate_parenthesis(n) == patterns);

    n = 4;
    patterns = {{"()()()()"}, {"()()(())"}, {"()(())()"}, {"()(()())"},
                {"()((()))"}, {"(())()()"}, {"(())(())"}, {"(()())()"},
                {"(()()())"}, {"(()(()))"}, {"((()))()"}, {"((())())"},
                {"((()()))"}, {"(((())))"}};
    assert(p.generate_parenthesis(n) == patterns);

    std::cout << "All tests passed\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}