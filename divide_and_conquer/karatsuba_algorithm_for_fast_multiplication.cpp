/**
 * @file
 * @brief Implementation of the [Karatsuba algorithm for fast
 * multiplication](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
 * @details
 * Given two strings in binary notation we want to multiply them and return the
 * value Simple approach is to multiply bits one by one which will give the time
 * complexity of around O(n^2). To make it more efficient we will be using
 * Karatsuba' algorithm to find the product which will solve the problem
 * O(nlogn) of time.
 * @author [Swastika Gupta](https://github.com/Swastyy)
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
 * multiplication](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
 */
namespace karatsuba_algorithm {
/**
 * @brief Helper function for the main function, that implements Karatsuba's
 * algorithm for fast multiplication
 * @param first the input string 1
 * @param second the input string 2
 * @returns the concatenated string
 */
std::string addStrings(std::string first, std::string second) {
    std::string result;  // To store the resulting sum bits

    int64_t len1 = first.size();
    int64_t len2 = second.size();
    int64_t length = std::max(len1, len2);
    std::string zero = "0";
    if (len1 < len2)  // make the string lengths equal
    {
        for (int64_t i = 0; i < len2 - len1; i++) {
            zero += first;
            first = zero;
        }
    } else if (len1 > len2) {
        zero = "0";
        for (int64_t i = 0; i < len1 - len2; i++) {
            zero += second;
            second = zero;
        }
    }
    int64_t carry = 0;
    for (int64_t i = length - 1; i >= 0; i--) {
        int64_t firstBit = first.at(i) - '0';
        int64_t secondBit = second.at(i) - '0';

        int64_t sum = (firstBit ^ secondBit ^ carry) + '0';  // sum of 3 bits
        std::string temp;
        temp = std::to_string(sum);
        temp += result;
        result = temp;

        carry = (firstBit & secondBit) | (secondBit & carry) |
                (firstBit & carry);  // sum of 3 bits
    }

    if (carry) {
        result = '1' + result;  // adding 1 incase of overflow
    }
    return result;
}
/**
 * @brief The main function implements Karatsuba's algorithm for fast
 * multiplication
 * @param str1 the input string 1
 * @param str2 the input string 2
 * @returns the multiplicative number value
 */
int64_t karatsuba_algorithm(std::string str1, std::string str2) {
    int64_t len1 = str1.size();
    int64_t len2 = str2.size();
    int64_t n = std::max(len1, len2);
    std::string zero = "0";
    if (len1 < len2) {
        for (int64_t i = 0; i < len2 - len1; i++) {
            zero += str1;
            str1 = zero;
        }
    } else if (len1 > len2) {
        zero = "0";
        for (int64_t i = 0; i < len1 - len2; i++) {
            zero += str2;
            str2 = zero;
        }
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return (str1[0] - '0') * (str2[0] - '0');
    }
    int64_t fh = n / 2;     // first half of string
    int64_t sh = (n - fh);  // second half of string

    std::string Xl = str1.substr(0, fh);   // first half of first string
    std::string Xr = str1.substr(fh, sh);  // second half of first string

    std::string Yl = str2.substr(0, fh);   // first half of second string
    std::string Yr = str2.substr(fh, sh);  // second half of second string

    // Calculating the three products of inputs of size n/2 recursively
    int64_t product1 = karatsuba_algorithm(Xl, Yl);
    int64_t product2 = karatsuba_algorithm(Xr, Yr);
    int64_t product3 = karatsuba_algorithm(
        divide_and_conquer::karatsuba_algorithm::addStrings(Xl, Xr),
        divide_and_conquer::karatsuba_algorithm::addStrings(Yl, Yr));

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
    std::string s11 = "1";
    std::string s12 = "1010";
    std::cout << "1st test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s11, s12) == 10);  // here the multiplication is 10
    std::cout << "passed" << std::endl;

    // 2nd test
    std::string s21 = "11";
    std::string s22 = "1010";
    std::cout << "2nd test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s21, s22) == 30);  // here the multiplication is 30
    std::cout << "passed" << std::endl;

    // 3rd test
    std::string s31 = "110";
    std::string s32 = "1010";
    std::cout << "3rd test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s31, s32) == 60);  // here the multiplication is 60
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
