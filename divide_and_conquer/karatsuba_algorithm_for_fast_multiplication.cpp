/**
 * @file
 * @brief Implementation of the [Karatsuba algorithm for fast
 * multiplication](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
 * @details
 * Given two strings in binary notation we want to multiply them and return the
 * value. Simple approach is to multiply bits one by one which will give the time
 * complexity of around O(n^2). To make it more efficient we will be using
 * Karatsuba algorithm to find the product which will solve the problem
 * O(nlogn) of time.
 * @author [Swastika Gupta](https://github.com/Swastyy)
 * @author [Ameer Carlo Lubang](https://github.com/poypoyan)
 */

#include <cassert>   /// for assert
#include <cstring>   /// for string
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace divide_and_conquer
 * @brief Divide and Conquer algorithms
 */
namespace divide_and_conquer {
/**
 * @namespace karatsuba_algorithm
 * @brief Functions for the [Karatsuba algorithm for fast
 * multiplication](https://en.wikipedia.org/wiki/Karatsuba_algorithm) implementation
 */
namespace karatsuba_algorithm {
/**
 * @brief Binary addition
 * @param first, the input string 1
 * @param second, the input string 2
 * @returns the sum binary string
 */
std::string add_strings(std::string first, std::string second) {
    std::string result;  // to store the resulting sum bits

    // Make the string lengths equal by padding with zeros
    int64_t len1 = first.size();
    int64_t len2 = second.size();

    if (len1 < len2) {
        first.insert(0, len2 - len1, '0'); // Pad first with zeros
    } else if (len1 > len2) {
        second.insert(0, len1 - len2, '0'); // Pad second with zeros
    }

    int64_t length = first.size();
    int64_t carry = 0;

    for (int64_t i = length - 1; i >= 0; i--) {
        int64_t firstBit = first.at(i) - '0';  // Convert char to int
        int64_t secondBit = second.at(i) - '0'; // Convert char to int

        // Calculate sum and carry
        int64_t sum = firstBit + secondBit + carry; // Add bits and carry
        result.insert(result.begin(), (sum % 2) + '0'); // Append the result bit
        carry = sum / 2; // Update carry for next iteration
    }

    // If there's a carry left, add it to the result
    if (carry) {
        result.insert(result.begin(), '1'); // Add carry at the front
    }

    return result;
}

/**
 * @brief Wrapper function for substr that considers leading zeros.
 * @param str, the binary input string.
 * @param x1, the substr parameter integer 1
 * @param x2, the substr parameter integer 2
 * @param n, is the length of the "whole" string: leading zeros + str
 * @returns the "safe" substring for the algorithm *without* leading zeros
 * @returns "0" if substring spans to leading zeros only
 */
std::string safe_substr(const std::string &str, int64_t x1, int64_t x2, int64_t n) {
    int64_t len = str.size();

    if (len >= n) {
        return str.substr(x1, x2);
    }

    int64_t y1 = x1 - (n - len);  // index in str of first char of substring of "whole" string
    int64_t y2 = (x1 + x2 - 1) - (n - len);  // index in str of last char of substring of "whole" string

    if (y2 < 0) {
        return "0";
    } else if (y1 < 0) {
        return str.substr(0, y2 + 1);
    } else {
        return str.substr(y1, x2);
    }
}

/**
 * @brief The main function implements Karatsuba's algorithm for fast
 * multiplication
 * @param str1 the input string 1
 * @param str2 the input string 2
 * @returns the product number value
 */
int64_t karatsuba_algorithm(std::string str1, std::string str2) {
    int64_t len1 = str1.size();
    int64_t len2 = str2.size();
    int64_t n = std::max(len1, len2);

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return (str1[0] - '0') * (str2[0] - '0');
    }

    int64_t fh = n / 2;     // first half of string
    int64_t sh = n - fh;  // second half of string

    std::string Xl = divide_and_conquer::karatsuba_algorithm::safe_substr(str1, 0, fh, n);   // first half of first string
    std::string Xr = divide_and_conquer::karatsuba_algorithm::safe_substr(str1, fh, sh, n);  // second half of first string

    std::string Yl = divide_and_conquer::karatsuba_algorithm::safe_substr(str2, 0, fh, n);   // first half of second string
    std::string Yr = divide_and_conquer::karatsuba_algorithm::safe_substr(str2, fh, sh, n);  // second half of second string

    // calculating the three products of inputs of size n/2 recursively
    int64_t product1 = karatsuba_algorithm(Xl, Yl);
    int64_t product2 = karatsuba_algorithm(Xr, Yr);
    int64_t product3 = karatsuba_algorithm(
        divide_and_conquer::karatsuba_algorithm::add_strings(Xl, Xr),
        divide_and_conquer::karatsuba_algorithm::add_strings(Yl, Yr));

    return product1 * (1 << (2 * sh)) +
           (product3 - product1 - product2) * (1 << sh) +
           product2;  // combining the three products to get the final result.
}
}  // namespace karatsuba_algorithm
}  // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::string s11 = "1";     // 1
    std::string s12 = "1010";  // 10
    std::cout << "1st test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(s11, s12) == 10);
    std::cout << "passed" << std::endl;

    // 2nd test
    std::string s21 = "11";    // 3
    std::string s22 = "1010";  // 10
    std::cout << "2nd test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(s21, s22) == 30);
    std::cout << "passed" << std::endl;

    // 3rd test
    std::string s31 = "110";   // 6
    std::string s32 = "1010";  // 10
    std::cout << "3rd test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(s31, s32) == 60);
    std::cout << "passed" << std::endl;

    // Additional tests
    std::string s41 = "1101";   // 13
    std::string s42 = "1011";   // 11
    std::cout << "4th test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(s41, s42) == 143);
    std::cout << "passed" << std::endl;

    std::string s51 = "0";       // 0
    std::string s52 = "1010";    // 10
    std::cout << "5th test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(s51, s52) == 0);
    std::cout << "passed" << std::endl;

    std::string s61 = "1111";   // 15
    std::string s62 = "1111";   // 15
    std::cout << "6th test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(s61, s62) == 225);
    std::cout << "passed" << std::endl;
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
