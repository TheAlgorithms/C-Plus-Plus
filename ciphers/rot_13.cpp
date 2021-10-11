/**
 * @brief [ROT13 Encoding and
 * Decoding](https://en.wikipedia.org/wiki/ROT13) implementation
 * ROT13 ("rotate by 13 places", sometimes hyphenated ROT-13) is a simple letter
 * substitution cipher that replaces a letter with the 13th letter after it in
 * the alphabet. ROT13 is a special case of the Caesar cipher which was
 * developed in ancient Rome.
 * @author [pond](https://github.com/pond-e)
 */
#include <iostream>
#include <string>

/**
 * @namespace ciphers
 * @brief Cipher algorithms
 */
namespace ciphers {
/**
 *  @namespace rot13
 *  @brief Functions for [rot13 encode and
 * decode](https://en.wikipedia.org/wiki/ROT13) implementation.
 * */
namespace rot13 {

std::string rot13_encode(std::string s) {
    // Encode only A~Z, a~z.
    int tmp = 0;
    for (char& i : s) {
        if (i >= 'A' && i <= 'Z') {
            tmp = i - 'A';
            // Shift by 13 characters
            tmp += 13;
            tmp %= 26;
            i = 'A' + tmp;
        } else if (i >= 'a' && i <= 'z') {
            tmp = i - 'a';
            // Shift by 13 characters
            tmp += 13;
            tmp %= 26;
            i = 'a' + tmp;
        }
    }
    return s;
}

std::string rot13_decode(std::string s) {
    // Decode only A~Z, a~z .
    int tmp = 0;
    for (char& i : s) {
        if (i >= 'A' && i <= 'Z') {
            tmp = i - 'A';
            // Fixed so that the value does not become negative when "-13" is
            // set.
            tmp += 26;
            // Shift by 13 characters
            tmp -= 13;
            tmp %= 26;
            i = 'A' + tmp;
        } else if (i >= 'a' && i <= 'z') {
            tmp = i - 'a';
            // Fixed so that the value does not become negative when "-13" is
            // set.
            tmp += 26;
            // Shift by 13 characters
            tmp -= 13;
            tmp %= 26;
            i = 'a' + tmp;
        }
    }
    return s;
}
}  // namespace rot13
}  // namespace ciphers

static void test() {
    std::string s;
    s = "test_WOrd01";

    s = ciphers::rot13::rot13_encode(s);
    std::cout << "rot13_encode:" << s << std::endl;

    s = ciphers::rot13::rot13_decode(s);
    std::cout << "rot13_decode:" << s << std::endl;
}

int main() {
    test();  // run self-test implementations
    return 0;
}
