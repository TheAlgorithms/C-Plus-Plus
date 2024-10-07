#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

/**
 * A class to perform binary addition of two binary strings.
 */
class Solution {
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
            carry = sum / 2; // Determine the carry for the next bit
            result.push_back((sum % 2) + '0'); // Append the sum's current bit to result
        }

        // If there's still a carry left, append it
        if (carry) {
            result.push_back('1');
        }

        // The result is built in reverse order, so reverse it before returning
        std::reverse(result.begin(), result.end());
        return result;
    }
};

/**
 * Function to run tests for the addBinary method.
 */
void runTests() {
    Solution solution;

    // Test case for two binary strings of equal length without any carry over.
    assert(solution.addBinary("1010", "1101") == "10111");

    // Test case for two binary strings of equal length with a carry over.
    assert(solution.addBinary("1111", "1111") == "11110");

    // Test case for two binary strings where one is longer than the other.
    assert(solution.addBinary("101", "11") == "1000");

    // Test case for a binary string of all zeros.
    assert(solution.addBinary("0", "0") == "0");

    // Test case where both binary strings consist of all ones.
    assert(solution.addBinary("1111", "1111") == "11110");

    // Test case where one binary string is zero and the other is non-zero.
    assert(solution.addBinary("0", "10101") == "10101");
    assert(solution.addBinary("10101", "0") == "10101");

    // Test case for large binary numbers with many digits.
    assert(solution.addBinary("101010101010101010101010101010", "110110110110110110110110110110") == "1100001100001100001100001100000");

    // Test case where one binary string is much longer than the other.
    assert(solution.addBinary("1", "11111111") == "100000000");

    // Test case for adding empty strings (edge case).
    assert(solution.addBinary("", "") == "0");

    // Test case where both binary strings consist of alternating ones and zeros.
    assert(solution.addBinary("10101010", "01010101") == "11111111");

    std::cout << "All tests passed!" << std::endl;
}

/**
 * Main function to execute the program.
 */
int main() {
    runTests();
    return 0;
}
