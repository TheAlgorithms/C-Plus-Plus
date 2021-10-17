/**
 * @file atbash_cipher.cpp
 * @brief atbash cipher implementation
 *
 * @author
 */
#include <cassert>  // for assert
#include <map>      // for std::map
#include <string>   // for std::string
#include <iostream>

/** \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers {
/** \namespace atbash
 * \brief atbash cipher implementation
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
std::string atbash_cipher(std::string text) {
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
    std::cout << "Original text: " << text;
    std::cout << ", Expected text: " << expected;
    std::cout << ", Encrypted text: " << encrypted_text;
    std::cout << ", Decrypted text: " << decrypted_text << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}