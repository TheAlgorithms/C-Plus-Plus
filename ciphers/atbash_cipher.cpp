/**
 * @file
 * @brief [Atbash Cipher](https://en.wikipedia.org/wiki/Atbash) implementation
 * @details The Atbash cipher is a subsitution cipher where the letters of the
 * alphabet are in reverse. For example, A is replaced with Z, B is replaced
 * with Y, etc.
 *
 * ### Algorithm
 * The algorithm takes a string, and looks up the corresponding reversed letter
 * for each letter in the word and replaces it. Spaces are ignored and case is
 * preserved.
 *
 * @author [Focusucof](https://github.com/Focusucof)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <map>       /// for std::map
#include <string>    /// for std::string

/** \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers {
/** \namespace atbash
 * \brief Functions for the [Atbash
 * Cipher](https://en.wikipedia.org/wiki/Atbash) implementation
 */
namespace atbash {
std::map<char, char> atbash_cipher_map = {
    {'a', 'z'}, {'b', 'y'}, {'c', 'x'}, {'d', 'w'}, {'e', 'v'}, {'f', 'u'},
    {'g', 't'}, {'h', 's'}, {'i', 'r'}, {'j', 'q'}, {'k', 'p'}, {'l', 'o'},
    {'m', 'n'}, {'n', 'm'}, {'o', 'l'}, {'p', 'k'}, {'q', 'j'}, {'r', 'i'},
    {'s', 'h'}, {'t', 'g'}, {'u', 'f'}, {'v', 'e'}, {'w', 'd'}, {'x', 'c'},
    {'y', 'b'}, {'z', 'a'}, {'A', 'Z'}, {'B', 'Y'}, {'C', 'X'}, {'D', 'W'},
    {'E', 'V'}, {'F', 'U'}, {'G', 'T'}, {'H', 'S'}, {'I', 'R'}, {'J', 'Q'},
    {'K', 'P'}, {'L', 'O'}, {'M', 'N'}, {'N', 'M'}, {'O', 'L'}, {'P', 'K'},
    {'Q', 'J'}, {'R', 'I'}, {'S', 'H'}, {'T', 'G'}, {'U', 'F'}, {'V', 'E'},
    {'W', 'D'}, {'X', 'C'}, {'Y', 'B'}, {'Z', 'A'}, {' ', ' '}

};

/**
 * @brief atbash cipher encryption and decryption
 * @param text Plaintext to be encrypted
 * @returns encoded or decoded string
 */
std::string atbash_cipher(const std::string& text) {
    std::string result;
    for (char letter : text) {
        result += atbash_cipher_map[letter];
    }
    return result;
}

}  // namespace atbash
}  // namespace ciphers

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::string text = "Hello World";
    std::string expected = "Svool Dliow";
    std::string encrypted_text = ciphers::atbash::atbash_cipher(text);
    std::string decrypted_text = ciphers::atbash::atbash_cipher(encrypted_text);
    assert(expected == encrypted_text);
    assert(text == decrypted_text);
    std::cout << "Original text: " << text << std::endl;
    std::cout << ", Expected text: " << expected << std::endl;
    std::cout << ", Encrypted text: " << encrypted_text << std::endl;
    std::cout << ", Decrypted text: " << decrypted_text << std::endl;
    std::cout << "\nAll tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
