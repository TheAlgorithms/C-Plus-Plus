/**
 * @file
 * @brief Implementation of the [A1Z26
 * cipher](https://www.dcode.fr/letter-number-cipher)
 * @details The A1Z26 cipher is a simple substiution cipher where each letter is
 * replaced by the number of the order they're in. For example, A corresponds to
 * 1, B = 2, C = 3, etc.
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */

#include <algorithm>  /// for std::transform and std::replace
#include <cassert>    /// for assert
#include <cstdint>    /// for uint8_t
#include <iostream>   /// for IO operations
#include <map>        /// for std::map
#include <sstream>    /// for std::stringstream
#include <string>     /// for std::string
#include <vector>     /// for std::vector

/**
 * @namespace ciphers
 * @brief Algorithms for encryption and decryption
 */
namespace ciphers {
/**
 * @namespace a1z26
 * @brief Functions for [A1Z26](https://www.dcode.fr/letter-number-cipher)
 * encryption and decryption implementation
 */
namespace a1z26 {

std::map<uint8_t, char> a1z26_decrypt_map = {
    {1, 'a'},  {2, 'b'},  {3, 'c'},  {4, 'd'},  {5, 'e'},  {6, 'f'},  {7, 'g'},
    {8, 'h'},  {9, 'i'},  {10, 'j'}, {11, 'k'}, {12, 'l'}, {13, 'm'}, {14, 'n'},
    {15, 'o'}, {16, 'p'}, {17, 'q'}, {18, 'r'}, {19, 's'}, {20, 't'}, {21, 'u'},
    {22, 'v'}, {23, 'w'}, {24, 'x'}, {25, 'y'}, {26, 'z'},
};

std::map<char, uint8_t> a1z26_encrypt_map = {
    {'a', 1},  {'b', 2},  {'c', 3},  {'d', 4},  {'e', 5},  {'f', 6},  {'g', 7},
    {'h', 8},  {'i', 9},  {'j', 10}, {'k', 11}, {'l', 12}, {'m', 13}, {'n', 14},
    {'o', 15}, {'p', 16}, {'q', 17}, {'r', 18}, {'s', 19}, {'t', 20}, {'u', 21},
    {'v', 22}, {'w', 23}, {'x', 24}, {'y', 25}, {'z', 26}};

/**
 * @brief a1z26 encryption implementation
 * @param text is the plaintext input
 * @returns encoded string with dashes to seperate letters
 */
std::string encrypt(std::string text) {
    std::string result;
    std::transform(text.begin(), text.end(), text.begin(),
                   ::tolower);  // convert string to lowercase
    std::replace(text.begin(), text.end(), ':', ' ');
    for (char letter : text) {
        if (letter != ' ') {
            result += std::to_string(
                a1z26_encrypt_map[letter]);  // convert int to string and append
                                             // to result
            result += "-";  // space out each set of numbers with spaces
        } else {
            result.pop_back();
            result += ' ';
        }
    }
    result.pop_back();  // remove leading dash
    return result;
}

/**
 * @brief a1z26 decryption implementation
 * @param text is the encrypted text input
 * @param bReturnUppercase is if the decoded string should be in uppercase or
 * not
 * @returns the decrypted string in all uppercase or all lowercase
 */
std::string decrypt(const std::string& text, bool bReturnUppercase = false) {
    std::string result;

    // split words seperated by spaces into a vector array
    std::vector<std::string> word_array;
    std::stringstream sstream(text);
    std::string word;
    while (sstream >> word) {
        word_array.push_back(word);
    }

    for (auto& i : word_array) {
        std::replace(i.begin(), i.end(), '-', ' ');
        std::vector<std::string> text_array;

        std::stringstream ss(i);
        std::string res_text;
        while (ss >> res_text) {
            text_array.push_back(res_text);
        }

        for (auto& i : text_array) {
            result += a1z26_decrypt_map[stoi(i)];
        }

        result += ' ';
    }
    result.pop_back();  // remove any leading whitespace

    if (bReturnUppercase) {
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    }
    return result;
}

}  // namespace a1z26
}  // namespace ciphers

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::string input = "Hello World";
    std::string expected = "8-5-12-12-15 23-15-18-12-4";
    std::string output = ciphers::a1z26::encrypt(input);

    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "TEST PASSED";

    // 2nd test
    input = "12-15-23-5-18-3-1-19-5";
    expected = "lowercase";
    output = ciphers::a1z26::decrypt(input);

    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "TEST PASSED";

    // 3rd test
    input = "21-16-16-5-18-3-1-19-5";
    expected = "UPPERCASE";
    output = ciphers::a1z26::decrypt(input, true);

    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "TEST PASSED";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
