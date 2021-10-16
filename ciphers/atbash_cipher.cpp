/**
 * @file atbash_cipher.cpp
 * @brief atbash cipher implementation
 *
 * @author
 */
#include <cassert>  // for assert
#include <map>      // for std::map
#include <string>   // for std::string

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
 * @returns std::string
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
 * @brief Function to test above algorithm
 * @returns void
 */
void test() {
    // Test 1
    std::string text = "Hello World";
    std::string expected = "Svool dliow";
    std::string encrypted_text = ciphers::atbash::atbash_cipher(text);
    std::string decrypted_text = ciphers::atbash::atbash_cipher(encrypted_text);
    assert(expected == encrypted_text);
    assert(text == decrypted_text);
    std::cout << "Original text: " << text;
    std::cout << " , Encrypted text: " << encrypted;
    std::cout << " , Decrypted text: " << decrypted << std::endl;
}

int main() {
    test();
    return 0;
}