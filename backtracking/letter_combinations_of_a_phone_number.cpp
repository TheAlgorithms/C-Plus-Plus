/**
 * @file
 * @brief Generates letter combinations for given digits using backtracking.
 *
 * @details
 * This code generates all possible letter combinations corresponding to a given
 * string of digits. It uses the concept of backtracking to explore all possible
 * combinations of letters for each digit.
 *
 * The function letterCombinations takes a string of digits as input and returns
 * a vector containing all the generated letter combinations. Each digit is
 * mapped to a set of letters, and the function backtracks to explore all
 * possible combinations by appending one letter at a time for each digit.
 *
 * The main test function demonstrates the correctness of letterCombinations by
 * running multiple test cases and checking the output against the expected
 * results. The expected vectors are now initialized one by one for better
 * clarity.
 *
 * @author [Saurabh Kushwaha](https://github.com/sOR-o)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace backtracking
 * @brief Backtracking algorithms
 */
namespace backtracking {
/**
 * @namespace letter_combinations
 * @brief Functions for generating letter combinations from digits using
 * backtracking.
 */
namespace letter_combinations {
/**
 * @brief Recursive utility function to generate letter combinations.
 * @param digit The input digit string to generate combinations for.
 * @param output The current output combination being formed.
 * @param index The index of the current digit being processed.
 * @param ans Vector to store the generated combinations.
 * @param mpp Array containing the mapping of digits to letters.
 */
void solve(const std::string& digit, std::string& output, int index,
           std::vector<std::string>& ans,
           const std::array<std::string, 10>& mpp) {
    if (index >= digit.length()) {
        ans.push_back(output);
        return;
    }

    int num = digit[index] - '0';
    std::string value = mpp[num];

    for (int i = 0; i < value.size(); i++) {
        output.push_back(value[i]);
        solve(digit, output, index + 1, ans, mpp);
        output.pop_back();
    }
}

/**
 * @brief Generates letter combinations for a given digit string.
 * @param digit The input digit string to generate combinations for.
 * @returns A vector containing all the generated letter combinations.
 */
std::vector<std::string> letterCombinations(const std::string& digit) {
    std::vector<std::string> ans;

    if (digit.empty()) {
        return ans;
    }

    std::string output = "";
    int index = 0;

    std::array<std::string, 10> mpp = {"",    "",    "abc",  "def", "ghi",
                                       "jkl", "mno", "pqrs", "tuv", "wxyz"};
    solve(digit, output, index, ans, mpp);
    return ans;
}
}  // namespace letter_combinations
}  // namespace backtracking

/**
 * @brief Test function to verify the correctness of letterCombinations.
 * @details Runs multiple test cases and checks if the generated combinations
 * match the expected results. If all test cases pass, it prints "All test cases
 * passed!" to indicate the correctness of the implementation.
 */
static void test() {
    // Test Case 1
    std::string digits1 = "23";
    std::vector<std::string> combinations1 =
        backtracking::letter_combinations::letterCombinations(digits1);
    std::vector<std::string> expected1;
    expected1.push_back("ad");
    expected1.push_back("ae");
    expected1.push_back("af");
    expected1.push_back("bd");
    expected1.push_back("be");
    expected1.push_back("bf");
    expected1.push_back("cd");
    expected1.push_back("ce");
    expected1.push_back("cf");
    assert(combinations1 == expected1);

    // Test Case 2
    std::string digits2 = "7";
    std::vector<std::string> combinations2 =
        backtracking::letter_combinations::letterCombinations(digits2);
    std::vector<std::string> expected2;
    expected2.push_back("p");
    expected2.push_back("q");
    expected2.push_back("r");
    expected2.push_back("s");
    assert(combinations2 == expected2);

    // Test Case 3
    std::string digits3 = "9";
    std::vector<std::string> combinations3 =
        backtracking::letter_combinations::letterCombinations(digits3);
    std::vector<std::string> expected3;
    expected3.push_back("w");
    expected3.push_back("x");
    expected3.push_back("y");
    expected3.push_back("z");
    assert(combinations3 == expected3);

    // Test Case 4 (Empty Input)
    std::string digits4 = "";
    std::vector<std::string> combinations4 =
        backtracking::letter_combinations::letterCombinations(digits4);
    assert(combinations4.empty());

    std::cout << "All test cases passed!\n";
}

/**
 * @brief Main function.
 * @returns 0 on exit.
 */
int main() {
    // Run the test function
    test();
    return 0;
}
