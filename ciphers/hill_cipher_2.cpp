/**
 * @file
 * @brief [Hill cipher](https://en.wikipedia.org/wiki/Hill_cipher) encryption
 * algorithm implementation.
 * @details
 * This implementation uses modular matrix multiplication to encrypt plaintext
 * using a square key matrix. It includes data cleaning, key matrix usage,
 * encryption block processing, and formatted output. Only lowercase
 * alphabetical characters are supported. Non-letter characters are removed and
 * padding with 'x' is used to fit the block size.
 *
 * @author
 * Mohamed Khaled (https://github.com/mmohamedkhaled)
 */

#include <stdio.h>
#include <stdlib.h>

#include <cassert>  /// for assert
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <string>
using namespace std;
/**
 * @namespace ciphers
 * @brief Contains all cipher algorithm implementations.
 */
namespace ciphers {

/**
 * @brief Converts a lowercase character to its corresponding integer (a=0, ...,
 * z=25).
 * @param c Lowercase character.
 * @returns Integer value of the character.
 */
int convert_char_to_int(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    return -1;
}

/**
 * @brief Converts an integer to its corresponding lowercase character.
 * @param i Integer value (0-25).
 * @returns Corresponding lowercase character.
 */
char convert_int_to_char(int i) { return 'a' + (i % 26); }

/**
 * @brief Cleans a string by removing non-letter characters and padding with
 * 'x'.
 * @param s Input string.
 * @param matrix_dimension Key matrix size used for padding.
 * @returns Cleaned and padded string.
 */
string clean_and_pad(string s, int matrix_dimension) {
    string result = "";
    for (int i = 0; i < s.size(); i++) {
        if (isalpha(s[i])) {
            result += tolower(s[i]);
        }
    }
    while (result.size() % matrix_dimension != 0) {
        result += 'x';
    }
    return result;
}

/**
 * @brief Multiplies two matrices.
 * @param a First matrix.
 * @param b Second matrix.
 * @returns Resultant matrix after multiplication.
 */
vector<vector<int>> matrix_multiplication(vector<vector<int>> a,
                                          vector<vector<int>> b) {
    vector<vector<int>> result(a.size(), vector<int>(b[0].size(), 0));

    if (a[0].size() != b.size()) {
        cout << "Invalid matrices" << endl;
        return {};
    }

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

/**
 * @brief Converts a string to a vector of integers.
 * @param s Input string.
 * @returns Vector of integers representing characters.
 */
vector<int> convert_string_to_vector(string s) {
    vector<int> result(s.length(), 0);
    for (int i = 0; i < s.size(); i++) {
        result[i] = convert_char_to_int(s[i]);
    }
    return result;
}

/**
 * @brief Converts a flat vector into a square matrix.
 * @param v Input vector.
 * @param size Dimension of the square matrix.
 * @returns 2D square matrix.
 */
vector<vector<int>> convert_vector_to_matrix(const vector<int> &v, int size) {
    if (size < 2 || size > 9) {
        cout << "Invalid size" << endl;
    }

    vector<vector<int>> matrix(size, vector<int>(size, 0));
    int k = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (k < v.size()) {
                matrix[i][j] = v[k++];
            }
        }
    }

    return matrix;
}

/**
 * @brief Prints a key matrix to the console.
 * @param matrix Key matrix.
 */
void print_key_matrix(vector<vector<int>> matrix) {
    cout << "\nKey matrix:\n";
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            printf("%4d", matrix[i][j]);
        }
        cout << endl;
    }
}

/**
 * @brief Prints ciphertext as characters.
 * @param ciphertext Encrypted vector of integers.
 */
void print_ciphertext(const vector<int> &ciphertext) {
    cout << "\nCiphertext:\n";
    for (int i = 0; i < ciphertext.size(); i++) {
        cout << convert_int_to_char(ciphertext[i]);
        if ((i + 1) % 80 == 0)
            cout << endl;
    }
    cout << endl;
}

/**
 * @brief Prints plaintext as characters.
 * @param plaintext Plaintext vector of integers.
 */
void print_plain_text(const vector<int> &plaintext) {
    cout << "\nPlaintext:\n";
    for (int i = 0; i < plaintext.size(); i++) {
        cout << convert_int_to_char(plaintext[i]);
        if ((i + 1) % 80 == 0)
            cout << endl;
    }
    cout << endl;
}

/**
 * @brief Splits input vector into a list of column matrices of given size.
 * @param input_vector Input 1D vector.
 * @param size Matrix size.
 * @returns Vector of column matrices.
 */
vector<vector<vector<int>>> split_into_column_matrices(
    const vector<int> &input_vector, int size) {
    vector<vector<vector<int>>> matrices;
    int num_blocks = input_vector.size() / size;

    for (int i = 0; i < num_blocks; i++) {
        vector<vector<int>> col_matrix(size, vector<int>(1, 0));
        for (int j = 0; j < size; j++) {
            col_matrix[j][0] = input_vector[i * size + j];
        }
        matrices.push_back(col_matrix);
    }

    return matrices;
}

/**
 * @brief Applies matrix multiplication for each block to perform encryption.
 * @param key Key matrix.
 * @param plaintext_vector Vector representation of the plaintext.
 * @param size Size of key matrix.
 * @returns Encrypted vector.
 */
vector<int> Controller(vector<vector<int>> key,
                       const vector<int> &plaintext_vector, int size) {
    vector<vector<vector<int>>> column_matrices =
        split_into_column_matrices(plaintext_vector, size);
    vector<int> encrypted_result;

    for (int i = 0; i < column_matrices.size(); i++) {
        vector<vector<int>> encrypted =
            matrix_multiplication(key, column_matrices[i]);
        for (int j = 0; j < encrypted.size(); j++) {
            encrypted_result.push_back(encrypted[j][0]);
        }
    }

    return encrypted_result;
}

/**
 * @brief Self-test function for Hill cipher.
 */
static void test() {
    int size = 2;
    vector<vector<int>> key_matrix = {{2, 4}, {3, 5}};
    string plaintext = "testmessage";

    string cleaned = clean_and_pad(plaintext, size);
    vector<int> vectorized = convert_string_to_vector(cleaned);
    vector<int> encrypted = Controller(key_matrix, vectorized, size);

    assert(encrypted.size() == vectorized.size());
    for (int v : encrypted) {
        assert(v >= 0);  // ensure valid output
    }

    std::cout << "All tests passed!\n";
}

}  // namespace ciphers

/**
 * @brief Main function
 * @returns 0 on successful execution
 */
int main() {
    ciphers::test();  // Run self-test

    int size = 2;
    vector<vector<int>> key_matrix = {{2, 4}, {3, 5}};
    string plaintext =
        "notonlyistheuniversestrangerthanwethinkitisstrangerthanwecanthinkwerne"
        "rheisenbergx";

    string clean_plaintext = ciphers::clean_and_pad(plaintext, size);
    vector<int> v = ciphers::convert_string_to_vector(clean_plaintext);
    vector<int> encrypted = ciphers::Controller(key_matrix, v, size);

    ciphers::print_key_matrix(key_matrix);
    ciphers::print_plain_text(v);
    ciphers::print_ciphertext(encrypted);

    return 0;
}
