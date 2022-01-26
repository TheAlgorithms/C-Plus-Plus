/**
 * @file
 * @brief Length of longest substring (without repeating characters)
 * @author [Katherine Hartley] (https://github.com/krhartley)
 * @date 01-23-2022
 */

#include <cassert>        /// for assert
#include <string>         /// for substr()
#include <unordered_map>  /// for std::unordered_map
#include <iostream>       /// for IO operations

namespace longest_substr_length {

    /**
     * @brief Find the length of the longest substring by 
     * iterating through string characters and recording 
     * letter counts in unordered map.
     * 
     * @param input    input string
     * @return         int for length of longest subtring
     */
    template<class T>
    int longest(T input) {

        std::string sub = "";
        std::string temp = "";

        std::unordered_map<std::string, int> counts;

        for (int i = 0; i < input.length(); i++) {
            counts[input.substr(i, 1)] = 1;

            for (int j = i + 1; j < input.length(); j++) {

                if (counts[input.substr(j, 1)] == 0) {
                    counts[input.substr(j, 1)] = 1;

                    if (j == input.length() - 1) {
                        temp = input.substr(i, j - i + 1);

                        if (temp.length() > sub.length()) {
                            sub = temp;
                        }
                    }
                }
                else {
                    temp = input.substr(i, j - i);

                    if (temp.length() > sub.length()) {
                        sub = temp;
                    }

                    break;
                }
            }
            counts.clear();

            if (sub.length() == input.length() - i) {
                break;
            }
        }

        return sub.length();
    }
} // namespace longest_substr_length

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    /* Test 1:
        "abbcdef" returns 5 */
    std::cout << "Test 1: ";
    std::string input = "abbcdef";
    assert(longest_substr_length::longest(input) == 5); // this ensures that the algorithm works as expected
    std::cout << "Passed" << std::endl;

    /* Test 2:
        "bbbbb" returns 1 */
    std::cout << "Test 2: ";
    input = "bbbbb";
    assert(longest_substr_length::longest(input) == 1);
    std::cout << "Passed" << std::endl;

    /* Test 3:
        "abcddef" returns 4 */
    std::cout << "Test 3: ";
    input = "abcddef";
    assert(longest_substr_length::longest(input) == 4);
    std::cout << "Passed" << std::endl;

    /* Test 4:
        "abbbbcd" returns 3 */
    std::cout << "Test 4: ";
    input = "abbbbcd";
    assert(longest_substr_length::longest(input) == 3);
    std::cout << "Passed" << std::endl;

    /* Test 5:
        "test" returns 3 */
    std::cout << "Test 5: ";
    input = "test";
    assert(longest_substr_length::longest(input) == 3);
    std::cout << "Passed" << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char* argv[]) {
    test();  // run self-test implementations
    return 0;
}
