/**
 * @file caesar_cipher.cpp
 * @brief Implementation of [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher) algorithm.
 *
 * @details
 * In cryptography, a Caesar cipher, also known as Caesar's cipher, the shift cipher, 
 * Caesar's code or Caesar shift, is one of the simplest and most widely known encryption 
 * techniques. It is a type of substitution cipher in which each letter in the plaintext 
 * is replaced by a letter some fixed number of positions down the alphabet. For example, 
 * with a left shift of 3, D would be replaced by A, E would become B, and so on. 
 * The method is named after Julius Caesar, who used it in his private correspondence.
 *
 * ### Algorithm
 * The encryption can also be represented using modular arithmetic by first transforming 
 * the letters into numbers, according to the scheme, A → 0, B → 1, ..., Z → 25.
 * Encryption of a letter x by a shift n can be described mathematically as,
 * \f[ E(x) = (x + n)\;\mbox{mod}\; 26\f]
 * while decryption can be described as,
 * \f[ D(x) = (x - n) \;\mbox{mod}\; 26\f]
 * 
 * \note This program implements caesar cipher for only uppercase English alphabet characters (i.e. A-Z). 
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
    /** \namespace caesar
     * \brief Functions for [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher) algorithm.
     */
    namespace caesar {   
        namespace {
            /**
             * This function finds character for given value (i.e.A-Z)
             * @param x value for which we want character 
             * @returns  corresponding character for perticular value
             */        
            inline char get_char(const int x) {
                // By adding 65 we are scaling 0-25 to 65-90. 
                // Which are in fact ASCII values of A-Z. 
                return char(x + 65); 
            }
            /**
             * This function finds value for given character (i.e.0-25)
             * @param c character for which we want value
             * @returns returns corresponding value for perticular character
             */  
            inline int get_value(const char c) {
                // A-Z have ASCII values in range 65-90.
                // Hence subtracting 65 will scale them to 0-25.
                return int(c - 65);
            }
        } // Unnamed namespace
        /**
         * Encrypt given text using caesar cipher.
         * @param text text to be encrypted
         * @param shift number of shifts to be applied
         * @returns new encrypted text
         */
        std::string encrypt (const std::string &text, const int &shift) {
            std::string encrypted_text = ""; // Empty string to store encrypted text
            for (char c : text) { // Going through each character
                int place_value = get_value(c); // Getting value of character (i.e. 0-25)
                place_value = (place_value + shift) % 26; // Applying encryption formula
                char new_char = get_char(place_value); // Getting new character from new value (i.e. A-Z)
                encrypted_text += new_char; // Appending encrypted character
            }
            return encrypted_text; // Returning encrypted text
        }
        /**
         * Decrypt given text using caesar cipher.
         * @param text text to be decrypted
         * @param shift number of shifts to be applied
         * @returns new decrypted text
         */        
        std::string decrypt (const std::string &text, const int &shift) {
            std::string decrypted_text = ""; // Empty string to store decrypted text
            for (char c : text) { // Going through each character
                int place_value = get_value(c); // Getting value of character (i.e. 0-25)
                place_value = (place_value - shift) % 26;// Applying decryption formula
                if(place_value < 0) { // Handling case where remainder is negative 
                    place_value = place_value + 26;
                }
                char new_char = get_char(place_value); // Getting original character from decrypted value (i.e. A-Z)
                decrypted_text += new_char; // Appending decrypted character
            }
            return decrypted_text; // Returning decrypted text
        }
    } // namespace caesar
} // namespace ciphers

/**
 * Function to test above algorithm
 */
void test() {
    // Test 1
    std::string text1 = "ALANTURING";
    std::string encrypted1 = ciphers::caesar::encrypt(text1, 17);
    std::string decrypted1 = ciphers::caesar::decrypt(encrypted1, 17);
    assert(text1 == decrypted1);
    std::cout << "Original text : " << text1;
    std::cout << " , Encrypted text (with shift = 21) : " << encrypted1;
    std::cout << " , Decrypted text : "<< decrypted1 << std::endl;
    // Test 2
    std::string text2 = "HELLOWORLD";
    std::string encrypted2 = ciphers::caesar::encrypt(text2, 1729);
    std::string decrypted2 = ciphers::caesar::decrypt(encrypted2, 1729);
    assert(text2 == decrypted2);
    std::cout << "Original text : " << text2;
    std::cout << " , Encrypted text (with shift = 1729) : " << encrypted2;
    std::cout << " , Decrypted text : "<< decrypted2 << std::endl;
}

/** Driver Code */
int main() {
    // Testing
    test();
    return 0;
}
