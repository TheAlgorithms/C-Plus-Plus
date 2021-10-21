/**
 * @file railfence_cipher.cpp
 * @brief  Implementation of [Railfence Cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher)
 * @details
 * The rail fence cipher (also called a zigzag cipher) is a form of classical transposition cipher. It derives its name from the manner in which encryption is performed. 
 * Encryption: In the rail fence cipher, the plaintext is written downwards diagonally on successive "rails" of an imaginary fence, then moving up when the bottom rail is 
 * reached, down again when the top rail is reached, and so on until the whole plaintext is written out. The ciphertext is then read off in rows. 
 * Decryption: Let N  be the number of rails used during encryption. Observe that as the plaintext is written, the sequence of each letter's vertical position on the rails
 * varies up and down in a repeating cycle. In general the sequence repeats with a period of 2 ( N − 1 ).
 * Let L be the length of the string to be decrypted. Suppose for a moment that L is a multiple of 2 ( N − 1 ) and let K = L /2 ( N − 1 ). One begins by splitting the 
 * ciphertext  into strings such that the length of the first and last string is K and the length of each intermediate string is 2 K.
 * @author [Sumaiya Fatma](https://github.com/sumushi)
 */

#include <cassert>
#include <iostream>

/**
 * \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers
{

    /** \namespace railfence
     * \brief Functions for [Railfence cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher) algorithm.
     */
    namespace railfence
    {

        /**
         * Encrypt given text using railfence cipher.
         * @param text text to be encrypted
         * @param key number of rails to be used
         * @returns new encrypted text
         */
        std::string encrypt(const std::string &text, const int &key)
        {
            std::string encrypted_text = ""; // Empty string to store encrypted text
            char rail[key][text.length()];   // Empty matrix to cipher plain text into rails
            for (int i = 0; i < key; i++)
                for (int j = 0; j < text.length(); j++)
                    rail[i][j] = '-'; // Filling the rail matrix to distinguish between filled and unfilled cells
            bool down = 0;            // Using a flag to check whether to move up or down
            int r = 0, c = 0;         //r defines the row number and c defines the coloumn number

            for (int i = 0; i < text.length(); i++) // iterating through each character of provided string and putting it at the right place in rail matrix
            {
                if (r == 0 || r == key - 1) // if at first or last row
                    down = !down;           // reverse the direction of filling
                rail[r][c++] = text[i];     // Fill in the cell and move one column forward
                if (down)
                {
                    r++; // if direction is down, move one row below
                }
                else
                {
                    r--; // if direction is up, move one row above
                }
            }
            for (int i = 0; i < key; i++)
            {
                for (int j = 0; j < text.length(); j++) // iterating through each element of rail matrix left to right
                {
                    if (rail[i][j] != '-')
                    {
                        encrypted_text += rail[i][j]; // If matrix was filled, adding the filled character to output
                    }
                }
            }
            return encrypted_text; // Returning encrypted text
        }
        /**
         * Decrypt given text using railfence cipher.
         * @param text text to be decrypted
         * @param key number of rails to be used
         * @returns new decrypted text
         */
        std::string decrypt(const std::string &text, const int &key)
        {
            std::string decrypted_text = ""; // Empty string to store decrypted text
            char rail[key][text.length()];   // Empty matrix to cipher plain text into rails
            for (int i = 0; i < key; i++)
                for (int j = 0; j < text.length(); j++)
                    rail[i][j] = '-'; // Filling the rail matrix to distinguish between filled and unfilled cells
            bool down = 0;            // Using a flag to check whether to move up or down
            int r = 0, c = 0;         //r defines the row number and c defines the coloumn number

            for (int i = 0; i < text.length(); i++) // iterating through each character of provided string to mark the cells to be filled
            {
                if (r == 0 || r == key - 1) // if at first or last row
                    down = !down;           // reverse the direction of filling
                rail[r][c++] = '*';         // Mark the cell and move one column forward
                if (down)
                {
                    r++; // if direction is down, move one row below
                }
                else
                {
                    r--; // if direction is up, move one row above
                }
            }
            int n = 0;
            for (int i = 0; i < key; i++)
            {
                for (int j = 0; j < text.length(); j++) // iterating through each element of rail matrix left to right
                {
                    if (rail[i][j] != '-')
                    {
                        rail[i][j] = text[n++]; // If matrix cell was marked, filling a character from input text
                    }
                }
            }
            down = 0;                               // reset the value of down
            r = 0, c = 0;                           // reset the value of c and r
            for (int i = 0; i < text.length(); i++) // Moving thhrough the rail matrix in zig-zag manner using down flag and r and c values
            {
                if (r == 0 || r == key - 1)     // if at first or last row
                    down = !down;               // reverse the direction of filling
                decrypted_text += rail[r][c++]; // Add the character in cell to output
                if (down)
                {
                    r++; // if direction is down, move one row below
                }
                else
                {
                    r--; // if direction is up, move one row above
                }
            }
            return decrypted_text; // Returning decrypted text
        }
    } // namespace railfence
} // namespace ciphers

/**
 * Function to test above algorithm
 */
void test()
{
    std::cout << "******************Test Cases******************" << std::endl;
    // Test 1
    std::string text1 = "ALANTURING";
    std::string encrypted1 = ciphers::railfence::encrypt(text1, 4);
    std::string decrypted1 = ciphers::railfence::decrypt(encrypted1, 4);
    assert(text1 == decrypted1);
    std::cout << "Original text : " << text1;
    std::cout << "\nEncrypted text (with rails = 4) : " << encrypted1;
    std::cout << "\nDecrypted text : " << decrypted1 << std::endl;
    std::cout << "**********************************************" << std::endl;

    // Test 2
    std::string text2 = "helloworld";
    std::string encrypted2 = ciphers::railfence::encrypt(text2, 3);
    std::string decrypted2 = ciphers::railfence::decrypt(encrypted2, 3);
    assert(text2 == decrypted2);
    std::cout << "Original text : " << text2;
    std::cout << "\nEncrypted text (with rails = 3) : " << encrypted2;
    std::cout << "\nDecrypted text : " << decrypted2 << std::endl;
    std::cout << "**********************************************" << std::endl;
}

/** Driver Code */
int main()
{
    // Testing
    test();
    return 0;
}
