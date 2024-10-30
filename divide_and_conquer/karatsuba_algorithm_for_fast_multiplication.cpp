/**
 * @file
 * @brief Implementation of the [Karatsuba algorithm for fast
 * multiplication](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
 * @details
 * Given two strings in binary notation, this implementation multiplies them 
 * using the Karatsuba algorithm, achieving O(n^log2(3)) time complexity.
 * @authors [Swastika Gupta](https://github.com/Swastyy), [Ameer Carlo Lubang](https://github.com/poypoyan)
 */

#include <cassert>   // for assert
#include <cstring>   // for string
#include <iostream>  // for IO operations

namespace divide_and_conquer {
namespace karatsuba_algorithm {

/**
 * @brief Binary addition of two binary strings.
 * @param first, the input string 1
 * @param second, the input string 2
 * @returns the sum as a binary string
 */
std::string add_strings(const std::string &first, const std::string &second) {
    std::string result;
    int carry = 0, sum = 0;
    size_t len1 = first.size(), len2 = second.size();
    size_t max_len = std::max(len1, len2);

    // Add bits from right to left
    for (size_t i = 0; i < max_len || carry; ++i) {
        if (i < len1) carry += first[len1 - 1 - i] - '0';
        if (i < len2) carry += second[len2 - 1 - i] - '0';
        
        result.push_back((carry % 2) + '0');  // Current bit
        carry /= 2;  // Carry for next bit
    }

    // The result is in reverse order
    std::reverse(result.begin(), result.end());
    return result;
}

/**
 * @brief The main function implements Karatsuba's algorithm for fast multiplication.
 * @param str1 the input string 1
 * @param str2 the input string 2
 * @returns the product number value
 */
int64_t karatsuba_algorithm(const std::string &str1, const std::string &str2) {
    if (str1 == "0" || str2 == "0") return 0; // Handle multiplication by zero
    if (str1 == "1") return std::stoll(str2); // Handle multiplication by one
    if (str2 == "1") return std::stoll(str1);

    size_t len1 = str1.size(), len2 = str2.size();
    size_t n = std::max(len1, len2);
    
    // Make lengths even
    if (n % 2 != 0) {
        str1 = '0' + str1;
        str2 = '0' + str2;
        n++;
    }

    size_t fh = n / 2; // Half the size
    std::string Xl = str1.substr(0, len1 - fh);
    std::string Xr = str1.substr(len1 - fh);
    std::string Yl = str2.substr(0, len2 - fh);
    std::string Yr = str2.substr(len2 - fh);

    // Recursive calls
    int64_t product1 = karatsuba_algorithm(Xl, Yl);
    int64_t product2 = karatsuba_algorithm(Xr, Yr);
    int64_t product3 = karatsuba_algorithm(add_strings(Xl, Xr), add_strings(Yl, Yr));

    return product1 * (1LL << (2 * fh)) + (product3 - product1 - product2) * (1LL << fh) + product2;
}

/**
 * @brief Self-test implementations
 */
static void test() {
    // 1st test
    std::string s11 = "1";     // 1
    std::string s12 = "1010";  // 10
    assert(karatsuba_algorithm(s11, s12) == 10);

    // 2nd test
    std::string s21 = "11";    // 3
    std::string s22 = "1010";  // 10
    assert(karatsuba_algorithm(s21, s22) == 30);

    // 3rd test
    std::string s31 = "110";   // 6
    std::string s32 = "1010";  // 10
    assert(karatsuba_algorithm(s31, s32) == 60);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run self-test implementations
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
