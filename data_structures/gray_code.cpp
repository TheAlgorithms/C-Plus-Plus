#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

/**
 *
 * A Gray code is a binary numeral system where two successive values
 * differ in only one bit. It is commonly used in various applications
 * such as error correction, analog-to-digital conversion, and rotary
 * encoders. This program focuses on generating Gray code sequences for
 * a given number of bits using bitwise XOR operations.
 *
 * Approach:
 * - The Gray code sequence is generated iteratively for each possible
 *   value within the range of 0 to 2^n, where n is the specified number
 *   of bits.
 * - The generation process involves bitwise XOR operations to create
 *   the Gray code, ensuring that each consecutive pair of values differs
 *   in only one bit.
 * - The generated Gray codes are then converted to binary representation
 *   using std::bitset and trimmed to the required number of bits.
 * - The resulting Gray code sequences are stored in a vector of strings.
 */

/**
 * @brief Generates Gray code sequence for a given number of bits.
 *
 * The Gray code is a binary numeral system where two successive values
 * differ in only one bit. This function generates the Gray code sequence
 * for a given number of bits using bitwise XOR operations.
 *
 * @param n The number of bits for the Gray code sequence.
 * @return A vector of strings representing the Gray code sequence.
 */
std::vector<std::string> generateGrayCode(int n) {
    assert(n > 0 && "Invalid input: Number of bits should be greater than 0.");

    std::vector<std::string> grayCode;
    grayCode.reserve(1 << n);
    for (int i = 0; i < (1 << n); ++i) {
        // Generate the Gray code using XOR
        int gray = i ^ (i >> 1);

        // Convert the integer to binary representation
        std::bitset<32> binary(gray);
        std::string grayCodeStr = binary.to_string().substr(32 - n);

        grayCode.push_back(grayCodeStr);
    }

    return grayCode;
}

/**
 * @brief Prints a vector of strings.
 *
 * @param vec The vector of strings to be printed.
 */
void printVector(const std::vector<std::string>& vec) {
    for (const auto& code : vec) {
        std::cout << code << std::endl;
    }
}

/**
 * @brief Tests the generateGrayCode function with various test cases.
 *
 * The function iterates through each test case, calculates the result using the
 * generateGrayCode function, checks if the result matches the expected result,
 * and prints a success message for each test case.
 */
void testGenerateGrayCode() {
    // Test cases with expected Gray code sequences
    std::vector<std::pair<int, std::vector<std::string>>> testCases = {
        {1, {"0", "1"}},
        {2, {"00", "01", "11", "10"}},
        {3, {"000", "001", "011", "010", "110", "111", "101", "100"}},
        {4,
         {"0000", "0001", "0011", "0010", "0110", "0111", "0101", "0100",
          "1100", "1101", "1111", "1110", "1010", "1011", "1001", "1000"}},
        {5, {"00000", "00001", "00011", "00010", "00110", "00111", "00101",
             "00100", "01100", "01101", "01111", "01110", "01010", "01011",
             "01001", "01000", "11000", "11001", "11011", "11010", "11110",
             "11111", "11101", "11100", "10100", "10101", "10111", "10110",
             "10010", "10011", "10001", "10000"}},
    };

    for (const auto& testCase : testCases) {
        int n = testCase.first;
        const std::vector<std::string>& expected = testCase.second;
        std::vector<std::string> result = generateGrayCode(n);
        assert(result == expected);
        std::cout << "Test passed!" << std::endl;
    }
}

/**
 * @brief The main function to demonstrate and test the Gray code generator.
 *
 * Calls the testGenerateGrayCode function to run the test cases for the
 * generateGrayCode function and prints the results.
 */
int main() {
    testGenerateGrayCode();
    return 0;
}
