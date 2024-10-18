/**
 * @file playfair_cipher.cpp
 * @brief Implementation of [Playfair cipher](https://en.wikipedia.org/wiki/Playfair_cipher) algorithm.
 *
 * @details
 * The Playfair cipher is a digraph substitution cipher, meaning that it encrypts pairs of letters (digraphs)
 * instead of individual letters. It uses a 5x5 grid filled with the letters of the alphabet (combining 'I' and 'J')
 * and a keyword to create the grid. Each pair of letters in the plaintext is encrypted by locating the letters in the grid.
 * 
 * @algorithm
 * The encryption process works by first finding the letters of the digraph in the 5x5 grid:
 *  - If the two letters are in the same row, each letter is replaced by the letter to its immediate right (wrapping to the leftmost letter if needed).
 *  - If the two letters are in the same column, each letter is replaced by the letter immediately below it (wrapping to the topmost letter if needed).
 *  - If the letters form a rectangle, each letter is replaced by the letter in its row at the other corner of the rectangle.
 * 
 * Decryption reverses these steps using the same key.
 * 
 * @example
 * For Example:
 * If the key is "PLAYFAIR", the 5x5 grid will be:
 * ```
 *  P L A Y F
 *  I R B C D
 *  E G H K M
 *  N O Q S T
 *  U V W X Z
 * ```
 * To encrypt the plaintext "HELLO", it would be first split into digraphs "HE", "LX", and "LO" (since "LL" forms a duplicate digraph, an 'X' is inserted).
 * The encrypted pairs would then be calculated using the rules above.
 *
 * \note This implementation assumes that all text is in lowercase and only handles alphabetic characters ('a'-'z'). The letter 'j' is replaced with 'i'.
 * 
 * @author [Jayditya Dhaka]
 */


#include <iostream>     // For input/output stream operations
#include <vector>       // For using vectors to create the 5x5 grid
#include <string>       // For handling strings
#include <cassert>      // For assertions in case of unexpected input

/** @namespace ciphers
 *  @brief Algorithms for encryption and decryption
 */
namespace ciphers {
    /** @namespace playfair
     *  @brief Functions for [Playfair cipher](https://en.wikipedia.org/wiki/Playfair_cipher) algorithm.
     */
    namespace playfair {

        namespace {
            /**
             * This function cleans the input string: converts to lowercase, replaces 'j' with 'i', and removes non-alphabet characters.
             * @param input the string to clean
             * @return cleaned string with only lowercase alphabetic characters
             */
            std::string cleanString(const std::string &input) {
                std::string cleaned;
                for (char c : input) {
                    if (std::isalpha(c)) {
                        cleaned += std::tolower(c == 'j' ? 'i' : c); // Replace 'j' with 'i' and ensure lowercase
                    }
                }
                return cleaned;
            }

            /**
             * This function removes duplicate characters from the string while preserving order.
             * @param input the string from which duplicates will be removed
             * @return string without duplicates
             */
            std::string removeDuplicates(const std::string &input) {
                std::string result;
                for (char c : input) {
                    if (result.find(c) == std::string::npos) {
                        result += c;
                    }
                }
                return result;
            }

            /**
             * This function formats the plain text by handling duplicate characters and appending 'z' if needed.
             * @param text the plain text to format
             * @return formatted text with no duplicate letters in pairs
             */
            std::string formatPlainText(const std::string &text) {
                std::string cleanedText = cleanString(text);
                std::string formattedText;

                for (size_t i = 0; i < cleanedText.length(); ++i) {
                    formattedText += cleanedText[i];
                    if (i < cleanedText.length() - 1 && cleanedText[i] == cleanedText[i + 1]) {
                        formattedText += 'x'; // Insert 'x' between repeating characters
                    }
                }

                if (formattedText.length() % 2 != 0) {
                    formattedText += 'z'; // Add 'z' if text length is odd
                }

                return formattedText;
            }

            /**
             * This function creates a Playfair cipher grid based on the cleaned key phrase.
             * @param key the key phrase for the Playfair cipher
             * @return 5x5 grid of characters for Playfair cipher
             */
            std::vector<std::vector<char>> createPlayfairGrid(const std::string &key) {
                std::vector<std::vector<char>> grid(5, std::vector<char>(5));
                size_t index = 0;
                for (int row = 0; row < 5; ++row) {
                    for (int col = 0; col < 5; ++col) {
                        grid[row][col] = key[index++];
                    }
                }
                return grid;
            }

            /**
             * This function returns the coordinates of a character in the Playfair grid.
             * @param c the character to find in the grid
             * @param grid the 5x5 Playfair grid
             * @return coordinates of the character in the grid as a pair (row, column)
             */
            std::pair<int, int> getCharacterCoordinates(char c, const std::vector<std::vector<char>> &grid) {
                for (int row = 0; row < 5; ++row) {
                    for (int col = 0; col < 5; ++col) {
                        if (grid[row][col] == c) {
                            return {row, col};
                        }
                    }
                }
                return {-1, -1}; // Should never reach here with valid input
            }
        } // unnamed namespace

        /**
         * Encrypts the plain text using the Playfair cipher.
         * @param plainText the text to encrypt
         * @param keyPhrase the key used for encryption
         * @return encrypted text
         */
        std::string encrypt(const std::string &plainText, const std::string &keyPhrase) {
            std::string formattedText = formatPlainText(plainText);
            std::string cleanedKey = cleanString(keyPhrase) + "abcdefghiklmnopqrstuvwxyz";
            cleanedKey = removeDuplicates(cleanedKey);
            auto grid = createPlayfairGrid(cleanedKey);

            std::string encryptedText;
            for (size_t i = 0; i < formattedText.length(); i += 2) {
                char char1 = formattedText[i];
                char char2 = formattedText[i + 1];
                std::pair<int, int> coord1 = getCharacterCoordinates(char1, grid);
                std::pair<int, int> coord2 = getCharacterCoordinates(char2, grid);

                int row1 = coord1.first, col1 = coord1.second;
                int row2 = coord2.first, col2 = coord2.second;

                if (row1 == row2) {
                    col1 = (col1 + 1) % 5;
                    col2 = (col2 + 1) % 5;
                } else if (col1 == col2) {
                    row1 = (row1 + 1) % 5;
                    row2 = (row2 + 1) % 5;
                } else {
                    std::swap(col1, col2);
                }

                encryptedText += grid[row1][col1];
                encryptedText += grid[row2][col2];
            }

            return encryptedText;
        }

        /**
         * Decrypts the encrypted text using the Playfair cipher.
         * @param cipherText the text to decrypt
         * @param keyPhrase the key used for decryption
         * @return decrypted text
         */
        std::string decrypt(const std::string &cipherText, const std::string &keyPhrase) {
            std::string cleanedKey = cleanString(keyPhrase) + "abcdefghiklmnopqrstuvwxyz";
            cleanedKey = removeDuplicates(cleanedKey);
            auto grid = createPlayfairGrid(cleanedKey);

            std::string decryptedText;
            for (size_t i = 0; i < cipherText.length(); i += 2) {
                char char1 = cipherText[i];
                char char2 = cipherText[i + 1];
                std::pair<int, int> coord1 = getCharacterCoordinates(char1, grid);
                std::pair<int, int> coord2 = getCharacterCoordinates(char2, grid);

                int row1 = coord1.first, col1 = coord1.second;
                int row2 = coord2.first, col2 = coord2.second;

                if (row1 == row2) {
                    col1 = (col1 - 1 + 5) % 5;
                    col2 = (col2 - 1 + 5) % 5;
                } else if (col1 == col2) {
                    row1 = (row1 - 1 + 5) % 5;
                    row2 = (row2 - 1 + 5) % 5;
                } else {
                    std::swap(col1, col2);
                }

                decryptedText += grid[row1][col1];
                decryptedText += grid[row2][col2];
            }

            return decryptedText;
        }

    } // namespace playfair
} // namespace ciphers

void test() {
    // Test 1
    std::string text1 = "HEYO";
    std::string encrypted1 = ciphers::playfair::encrypt(text1, "OLDTAVERN");
    std::string decrypted1 = ciphers::playfair::decrypt(encrypted1, "OLDTAVERN");
    std::cout << "Original text: " << text1;
    std::cout << " , Encrypted text (key = OLDTAVERN): " << encrypted1;
    std::cout << " , Decrypted text: " << decrypted1 << std::endl;

    // Test 2
    std::string text2 = "HELLO";
    std::string encrypted2 = ciphers::playfair::encrypt(text2, "OLDTAVERN");
    std::string decrypted2 = ciphers::playfair::decrypt(encrypted2, "OLDTAVERN");
    std::cout << "Original text: " << text2;
    std::cout << " , Encrypted text (key = OLDTAVERN): " << encrypted2;
    std::cout << " , Decrypted text: " << decrypted2 << std::endl;
}

/** Driver Code */
int main() {
    test();
    return 0;
}
