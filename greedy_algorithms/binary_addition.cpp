/**
 * @file binary_addition.cpp
 * @brief Adds two binary numbers and outputs resulting string
 * @see https://www.geeksforgeeks.org/cpp-program-to-add-two-binary-strings/
 * @details The algorithm for adding two binary strings works by processing them
 * from right to left, similar to manual addition. It starts by determining the
 * longer string's length to ensure both strings are fully traversed. For each
 * pair of corresponding bits and any carry from the previous addition, it
 * calculates the sum. If the sum exceeds 1, a carry is generated for the next
 * bit. The results for each bit are collected in a result string, which is
 * reversed at the end to present the final binary sum correctly. This method
 * efficiently handles varying string lengths and carrying during addition.
 * @author [Muhammad Junaid Khalid](https://github.com/mjk22071998)
 */

#include <algorithm>  /// for reverse function
#include <cassert>    /// for tests
#include <iostream>   /// for input and outputs
#include <string>     /// for sting class

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * A class to perform binary addition of two binary strings.
 */
class BinaryAddition {
 public:
    /**
     * Adds two binary strings and returns the result as a binary string.
     *
     * @param a The first binary string.
     * @param b The second binary string.
     * @return The sum of the two binary strings as a binary string.
     */
    std::string addBinary(const std::string& a, const std::string& b) {
        std::string result;
        int carry = 0;
        int maxLength = std::max(a.size(), b.size());

        // Traverse both strings from the end to the beginning
        for (int i = 0; i < maxLength; ++i) {
            // Get the current bits from both strings, if available
            int bitA = (i < a.size()) ? (a[a.size() - 1 - i] - '0') : 0;
            int bitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;

            // Calculate the sum of bits and carry
            int sum = bitA + bitB + carry;
            carry = sum / 2;  // Determine the carry for the next bit
            result.push_back((sum % 2) +
                             '0');  // Append the sum's current bit to result
        }
        if (carry) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};
}  // namespace greedy_algorithms

/**
 * Function to run tests for the addBinary method.
 */
void tests() {
    BinaryAddition binaryAddition;

    assert(binaryAddition.addBinary("1010", "1101") == "10111");
    assert(binaryAddition.addBinary("1111", "1111") == "11110");
    assert(binaryAddition.addBinary("101", "11") == "1000");
    assert(binaryAddition.addBinary("0", "0") == "0");
    assert(binaryAddition.addBinary("1111", "1111") == "11110");
    assert(binaryAddition.addBinary("0", "10101") == "10101");
    assert(binaryAddition.addBinary("10101", "0") == "10101");
    assert(binaryAddition.addBinary("101010101010101010101010101010",
                                    "110110110110110110110110110110") ==
           "1100001100001100001100001100000");
    assert(binaryAddition.addBinary("1", "11111111") == "100000000");
    assert(binaryAddition.addBinary("", "") == "");
    assert(binaryAddition.addBinary("10101010", "01010101") == "11111111");
}

/**
 * Main function to execute the program.
 */
int main() {
    tests();
    return 0;
}
