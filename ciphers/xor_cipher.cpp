/**
 * @file xor_cipher.cpp
 * @brief Implementation of [XOR cipher](https://en.wikipedia.org/wiki/XOR_cipher) algorithm.
 *
 * @details
 * In cryptography, the simple XOR cipher is a type of additive cipher, an encryption 
 * algorithm that operates according to the principles: 
 *
 * * \f$A {\oplus} 0 = A\f$
 * * \f$A {\oplus} A = 0\f$
 * * \f$ (A {\oplus} B) {\oplus} C = A {\oplus} (B {\oplus} C)\f$
 * * \f$ (B {\oplus} A) {\oplus} B = B {\oplus} 0 = B \f$
 * 
 * 
 * where \f$\oplus\f$ symbol denotes the exclusive disjunction (XOR) operation.
 * This operation is sometimes called modulus 2 addition (or subtraction, which is identical).
 * With this logic, a string of text can be encrypted by applying the bitwise XOR operator to
 * every character using a given key. To decrypt the output, merely reapplying the XOR function 
 * with the key will remove the cipher.
 * 
 * ### Algorithm
 * Choose the key for encryption and apply XOR operation to each character of a string. 
 * Reapplying XOR operation to each character of encrypted string will give original string back.
 * 
 * \note This program implements XOR Cipher for string with ASCII characters. 
 * 
 * @author [Deep Raval](https://github.com/imdeep2905)
 */
#include <iostream>
#include <string>
#include <cassert>

/** \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers {
    /** \namespace XOR
     * \brief Functions for [XOR cipher](https://en.wikipedia.org/wiki/XOR_cipher) algorithm.
     */
    namespace XOR {   
        /**
         * Encrypt given text using XOR cipher.
         * @param text text to be encrypted
         * @param key to be used for encyption
         * @return new encrypted text
         */
        std::string encrypt (const std::string &text, const int &key) {
            std::string encrypted_text = ""; // Empty string to store encrypted text
            for (auto &c: text) { // Going through each character
                char encrypted_char = char(c ^ key); // Applying encyption
                encrypted_text += encrypted_char; // Appending encrypted character
            }
            return encrypted_text; // Returning encrypted text
        }
        /**
         * Decrypt given text using XOR cipher.
         * @param text text to be encrypted
         * @param key to be used for decryption
         * @return new decrypted text
         */        
        std::string decrypt (const std::string &text, const int &key) {
            std::string decrypted_text = ""; // Empty string to store decrypted text
            for (auto &c : text) { // Going through each character
                char decrypted_char = char(c ^ key); // Applying decryption
                decrypted_text += decrypted_char; // Appending decrypted character
            }
            return decrypted_text; // Returning decrypted text
        }
    } // namespace XOR
} // namespace ciphers

/**
 * Function to test above algorithm
 */
void test() {
    // Test 1
    std::string text1 = "Whipalsh! : Do watch this movie...";
    std::string encrypted1 = ciphers::XOR::encrypt(text1, 17);
    std::string decrypted1 = ciphers::XOR::decrypt(encrypted1, 17);
    assert(text1 == decrypted1);
    std::cout << "Original text : " << text1;
    std::cout << " , Encrypted text (with key = 17) : " << encrypted1;
    std::cout << " , Decrypted text : "<< decrypted1 << std::endl;
    // Test 2
    std::string text2 = "->Valar M0rghulis<-";
    std::string encrypted2 = ciphers::XOR::encrypt(text2, 29);
    std::string decrypted2 = ciphers::XOR::decrypt(encrypted2, 29);
    assert(text2 == decrypted2);
    std::cout << "Original text : " << text2;
    std::cout << " , Encrypted text (with key = 29) : " << encrypted2;
    std::cout << " , Decrypted text : "<< decrypted2 << std::endl;
}

/** Driver Code */
int main() {
    // Testing
    test();
    return 0;
}
