/**
 * @file hill_cipher.cpp
 * @brief Implementation of [Hill
 * cipher](https://en.wikipedia.org/wiki/Hill_cipher) algorithm.
 *
 * Program to generate the encryption-decryption key and perform encryption and
 * decryption of ASCII text using the famous block cipher algorithm. This is a
 * powerful encryption algorithm that is relatively easy to implement with a
 * given key. The strength of the algorithm depends on the size of the block
 * encryption matrix key; the bigger the matrix, the stronger the encryption and
 * more difficult to break it. However, the important requirement for the matrix
 * is that:
 * 1. matrix should be invertible - all inversion conditions should be satisfied
 * and
 * 2. its determinant must not have any common factors with the length of
 * character set
 * Due to this restriction, most implementations only implement with small 3x3
 * encryption keys and a small subset of ASCII alphabets.
 *
 * In the current implementation, I present to you an implementation for
 * generating larger encryption keys (I have attempted upto 10x10) and an ASCII
 * character set of 97 printable characters. Hence, a typical ASCII text file
 * could be easily encrypted with the module. The larger character set increases
 * the modulo of cipher and hence the matrix determinants can get very large
 * very quickly rendering them ill-defined.
 *
 * \note This program uses determinant computation using LU decomposition from
 * the file lu_decomposition.h
 * \note The matrix generation algorithm is very rudimentary and does not
 * guarantee an invertible modulus matrix. \todo Better matrix generation
 * algorithm.
 *
 * @author [Krishna Vedala](https://github.com/kvedala)
 */

#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "../numerical_methods/lu_decomposition.h"

/**
 * operator to print a matrix
 */
template <typename T>
static std::ostream &operator<<(std::ostream &out, matrix<T> const &v) {
    const int width = 15;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++)
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col];
        out << std::endl;
    }

    return out;
}

/** \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
namespace ciphers {
/** dictionary of characters that can be encrypted and decrypted */
static const char *STRKEY =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&"
    "*()_+`-=[]{}|;':\",./<>?\\\r\n \0";

/**
 * @brief Implementation of [Hill
 * Cipher](https://en.wikipedia.org/wiki/Hill_cipher) algorithm
 */
class HillCipher {
 private:
    /**
     * @brief Function to generate a random integer in a given interval
     *
     * @param a lower limit of interval
     * @param b upper limit of interval
     * @tparam T type of output
     * @return random integer in the interval \f$[a,b)\f$
     */
    template <typename T1, typename T2>
    static const T2 rand_range(T1 a, T1 b) {
        // generate random number between 0 and 1
        long double r = static_cast<long double>(std::rand()) / RAND_MAX;

        // scale and return random number as integer
        return static_cast<T2>(r * (b - a) + a);
    }

    /**
     * @brief Function overload to fill a matrix with random integers in a given
     * interval
     *
     * @param M pointer to matrix to be filled with random numbers
     * @param a lower limit of interval
     * @param b upper limit of interval
     * @tparam T1 type of input range
     * @tparam T2 type of matrix
     * @return determinant of generated random matrix
     *
     * @warning There will need to be a balance between the matrix size and the
     * range of random numbers. If the matrix is large, the range of random
     * numbers must be small to have a well defined keys. Or if the matrix is
     * smaller, the random numbers range can be larger. For an 8x8 matrix, range
     * should be no more than \f$[0,10]\f$
     */
    template <typename T1, typename T2>
    static double rand_range(matrix<T2> *M, T1 a, T1 b) {
        for (size_t i = 0; i < M->size(); i++) {
            for (size_t j = 0; j < M[0][0].size(); j++) {
                M[0][i][j] = rand_range<T1, T2>(a, b);
            }
        }

        return determinant_lu(*M);
    }

    /**
     * @brief Compute
     * [GCD](https://en.wikipedia.org/wiki/Greatest_common_divisor) of two
     * integers using Euler's algorithm
     *
     * @param a first number
     * @param b second number
     * @return GCD of \f$a\f$ and \f$b\f$
     */
    template <typename T>
    static const T gcd(T a, T b) {
        if (b > a)  // ensure always a < b
            std::swap(a, b);

        while (b != 0) {
            T tmp = b;
            b = a % b;
            a = tmp;
        }

        return a;
    }

    /**
     * @brief helper function to perform vector multiplication with encryption
     * or decryption matrix
     *
     * @param vector vector to multiply
     * @param key encryption or decryption key matrix
     * @return corresponding encrypted or decrypted text
     */
    static const std::valarray<uint8_t> mat_mul(
        const std::valarray<uint8_t> &vector, const matrix<int> &key) {
        std::valarray<uint8_t> out(vector);  // make a copy

        size_t L = std::strlen(STRKEY);

        for (size_t i = 0; i < key.size(); i++) {
            int tmp = 0;
            for (size_t j = 0; j < vector.size(); j++) {
                tmp += key[i][j] * vector[j];
            }
            out[i] = static_cast<uint8_t>(tmp % L);
        }

        return out;
    }

    /**
     * @brief Get the character at a given index in the ::STRKEY
     *
     * @param idx index value
     * @return character at the index
     */
    static inline char get_idx_char(const uint8_t idx) { return STRKEY[idx]; }

    /**
     * @brief Get the index of a character in the ::STRKEY
     *
     * @param ch character to search
     * @return index of character
     */
    static inline uint8_t get_char_idx(const char ch) {
        size_t L = std::strlen(STRKEY);

        for (size_t idx = 0; idx <= L; idx++)
            if (STRKEY[idx] == ch)
                return idx;

        std::cerr << __func__ << ":" << __LINE__ << ": (" << ch
                  << ") Should not reach here!\n";
        return 0;
    }

    /**
     * @brief Convenience function to perform block cipher operations. The
     * operations are identical for both encryption and decryption.
     *
     * @param text input text to encrypt or decrypt
     * @param key key for encryption or decryption
     * @return encrypted/decrypted output
     */
    static const std::string codec(const std::string &text,
                                   const matrix<int> &key) {
        size_t text_len = text.length();
        size_t key_len = key.size();

        // length of output string must be a multiple of key_len
        // create output string and initialize with '\0' character
        size_t L2 = text_len % key_len == 0
                        ? text_len
                        : text_len + key_len - (text_len % key_len);
        std::string coded_text(L2, '\0');

        // temporary array for batch processing
        int i;
#ifdef _OPENMP
#pragma parallel omp for private(i)
#endif
        for (i = 0; i < L2 - key_len + 1; i += key_len) {
            std::valarray<uint8_t> batch_int(key_len);
            for (size_t j = 0; j < key_len; j++) {
                batch_int[j] = get_char_idx(text[i + j]);
            }

            batch_int = mat_mul(batch_int, key);

            for (size_t j = 0; j < key_len; j++) {
                coded_text[i + j] =
                    STRKEY[batch_int[j]];  // get character at key
            }
        }

        return coded_text;
    }

    /**
     * Get matrix inverse using Row-transformations. Given matrix must
     * be a square and non-singular.
     * \returns inverse matrix
     **/
    template <typename T>
    static matrix<double> get_inverse(matrix<T> const &A) {
        // Assuming A is square matrix
        size_t N = A.size();

        matrix<double> inverse(N, std::valarray<double>(N));
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++) {
                // create identity matrix
                inverse[row][col] = (row == col) ? 1.f : 0.f;
            }
        }

        if (A.size() != A[0].size()) {
            std::cerr << "A must be a square matrix!" << std::endl;
            return inverse;
        }

        // preallocate a temporary matrix identical to A
        matrix<double> temp(N, std::valarray<double>(N));
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++)
                temp[row][col] = static_cast<double>(A[row][col]);
        }

        // start transformations
        for (size_t row = 0; row < N; row++) {
            for (size_t row2 = row; row2 < N && temp[row][row] == 0; row2++) {
                // this to ensure diagonal elements are not 0
                temp[row] = temp[row] + temp[row2];
                inverse[row] = inverse[row] + inverse[row2];
            }

            for (size_t col2 = row; col2 < N && temp[row][row] == 0; col2++) {
                // this to further ensure diagonal elements are not 0
                for (size_t row2 = 0; row2 < N; row2++) {
                    temp[row2][row] = temp[row2][row] + temp[row2][col2];
                    inverse[row2][row] =
                        inverse[row2][row] + inverse[row2][col2];
                }
            }

            if (temp[row][row] == 0) {
                // Probably a low-rank matrix and hence singular
                std::cerr << "Low-rank matrix, no inverse!" << std::endl;
                return inverse;
            }

            // set diagonal to 1
            double divisor = temp[row][row];
            temp[row] = temp[row] / divisor;
            inverse[row] = inverse[row] / divisor;
            // Row transformations
            for (size_t row2 = 0; row2 < N; row2++) {
                if (row2 == row)
                    continue;
                double factor = temp[row2][row];
                temp[row2] = temp[row2] - factor * temp[row];
                inverse[row2] = inverse[row2] - factor * inverse[row];
            }
        }

        return inverse;
    }

    static int modulo(int a, int b) {
        int ret = a % b;
        if (ret < 0)
            ret += b;
        return ret;
    }

 public:
    /**
     * @brief Generate encryption matrix of a given size. Larger size matrices
     * are difficult to generate but provide more security. Important conditions
     * are:
     * 1. matrix should be invertible
     * 2. determinant must not have any common factors with the length of
     * character key
     * There is no head-fast way to generate hte matrix under the given
     * numerical restrictions of the machine but the conditions added achieve
     * the goals. Bigger the matrix, greater is the probability of the matrix
     * being ill-defined.
     *
     * @param size size of matrix (typically \f$\text{size}\le10\f$)
     * @param limit1 lower limit of range of random elements (default=0)
     * @param limit2 upper limit of range of random elements (default=10)
     * @return Encryption martix
     */
    static matrix<int> generate_encryption_key(size_t size, int limit1 = 0,
                                               int limit2 = 10) {
        matrix<int> encrypt_key(size, std::valarray<int>(size));
        matrix<int> min_mat = encrypt_key;
        int mat_determinant = -1;  // because matrix has only ints, the
                                   // determinant will also be an int
        int L = std::strlen(STRKEY);

        double dd;
        do {
            // keeping the random number range smaller generates better
            // defined matrices with more ease of cracking
            dd = rand_range(&encrypt_key, limit1, limit2);
            mat_determinant = static_cast<int>(dd);

            if (mat_determinant < 0)
                mat_determinant = (mat_determinant % L);
        } while (std::abs(dd) > 1e3 ||  // while ill-defined
                 dd < 0.1 ||  // while singular or negative determinant
                 !std::isfinite(dd) ||  // while determinant is not finite
                 gcd(mat_determinant, L) != 1);  // while no common factors
        // std::cout <<

        return encrypt_key;
    }

    /**
     * @brief Generate decryption matrix from an encryption matrix key.
     *
     * @param encrypt_key encryption key for which to create a decrypt key
     * @return Decryption martix
     */
    static matrix<int> generate_decryption_key(matrix<int> const &encrypt_key) {
        size_t size = encrypt_key.size();
        int L = std::strlen(STRKEY);

        matrix<int> decrypt_key(size, std::valarray<int>(size));
        int det_encrypt = static_cast<int>(determinant_lu(encrypt_key));

        int mat_determinant = det_encrypt < 0 ? det_encrypt % L : det_encrypt;

        matrix<double> tmp_inverse = get_inverse(encrypt_key);
        double d2 = determinant_lu(decrypt_key);

        // find co-prime factor for inversion
        int det_inv = -1;
        for (int i = 0; i < L; i++) {
            if (modulo(mat_determinant * i, L) == 1) {
                det_inv = i;
                break;
            }
        }

        if (det_inv == -1) {
            std::cerr << "Could not find a co-prime for inversion\n";
            std::exit(EXIT_FAILURE);
        }

        mat_determinant = det_inv * det_encrypt;

        // perform modular inverse of encryption matrix
        int i;
#ifdef _OPENMP
#pragma parallel omp for private(i)
#endif
        for (i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int temp = std::round(tmp_inverse[i][j] * mat_determinant);
                decrypt_key[i][j] = modulo(temp, L);
            }
        }
        return decrypt_key;
    }

    /**
     * @brief Generate encryption and decryption key pair
     *
     * @param size size of matrix key (typically \f$\text{size}\le10\f$)
     * @param limit1 lower limit of range of random elements (default=0)
     * @param limit2 upper limit of range of random elements (default=10)
     * @return std::pair<matrix<int>, matrix<int>> encryption and decryption
     * keys as a pair
     *
     * @see ::generate_encryption_key
     */
    static std::pair<matrix<int>, matrix<int>> generate_keys(size_t size,
                                                             int limit1 = 0,
                                                             int limit2 = 10) {
        matrix<int> encrypt_key = generate_encryption_key(size);
        matrix<int> decrypt_key = generate_decryption_key(encrypt_key);
        double det2 = determinant_lu(decrypt_key);
        while (std::abs(det2) < 0.1 || std::abs(det2) > 1e3) {
            encrypt_key = generate_encryption_key(size, limit1, limit2);
            decrypt_key = generate_decryption_key(encrypt_key);
            det2 = determinant_lu(decrypt_key);
        }
        return std::make_pair(encrypt_key, decrypt_key);
    }

    /**
     * @brief Encrypt a given text using a given key
     *
     * @param text string to encrypt
     * @param encrypt_key  key for encryption
     * @return encrypted text
     */
    static const std::string encrypt_text(const std::string &text,
                                          const matrix<int> &encrypt_key) {
        return codec(text, encrypt_key);
    }

    /**
     * @brief Decrypt a given text using a given key
     *
     * @param text string to decrypt
     * @param decrypt_key  key for decryption
     * @return decrypted text
     */
    static const std::string decrypt_text(const std::string &text,
                                          const matrix<int> &decrypt_key) {
        return codec(text, decrypt_key);
    }
};

}  // namespace ciphers

/**
 * @brief Self test 1 - using 3x3 randomly generated key
 *
 * @param text string to encrypt and decrypt
 */
void test1(const std::string &text) {
    // std::string text = "Hello world!";
    std::cout << "======Test 1 (3x3 key) ======\nOriginal text:\n\t" << text
              << std::endl;

    std::pair<matrix<int>, matrix<int>> p =
        ciphers::HillCipher::generate_keys(3, 0, 100);
    matrix<int> ekey = p.first;
    matrix<int> dkey = p.second;

    // matrix<int> ekey = {{22, 28, 25}, {5, 26, 15}, {14, 18, 9}};
    // std::cout << "Encryption key: \n" << ekey;
    std::string gibberish = ciphers::HillCipher::encrypt_text(text, ekey);
    std::cout << "Encrypted text:\n\t" << gibberish << std::endl;

    // matrix<int> dkey = ciphers::HillCipher::generate_decryption_key(ekey);
    // std::cout << "Decryption key: \n" << dkey;
    std::string txt_back = ciphers::HillCipher::decrypt_text(gibberish, dkey);
    std::cout << "Reconstruct text:\n\t" << txt_back << std::endl;

    std::ofstream out_file("hill_cipher_test1.txt");
    out_file << "Block size: " << ekey.size() << "\n";
    out_file << "Encryption Key:\n" << ekey;
    out_file << "\nDecryption Key:\n" << dkey;
    out_file.close();

    assert(txt_back == text);
    std::cout << "Passed :)\n";
}

/**
 * @brief Self test 2 - using 8x8 randomly generated key
 *
 * @param text string to encrypt and decrypt
 */
void test2(const std::string &text) {
    // std::string text = "Hello world!";
    std::cout << "======Test 2 (8x8 key) ======\nOriginal text:\n\t" << text
              << std::endl;

    std::pair<matrix<int>, matrix<int>> p =
        ciphers::HillCipher::generate_keys(8, 0, 3);
    matrix<int> ekey = p.first;
    matrix<int> dkey = p.second;

    std::string gibberish = ciphers::HillCipher::encrypt_text(text, ekey);
    std::cout << "Encrypted text:\n\t" << gibberish << std::endl;

    std::string txt_back = ciphers::HillCipher::decrypt_text(gibberish, dkey);
    std::cout << "Reconstruct text:\n\t" << txt_back << std::endl;

    std::ofstream out_file("hill_cipher_test2.txt");
    out_file << "Block size: " << ekey.size() << "\n";
    out_file << "Encryption Key:\n" << ekey;
    out_file << "\nDecryption Key:\n" << dkey;
    out_file.close();

    assert(txt_back.compare(0, text.size(), text) == 0);
    std::cout << "Passed :)\n";
}

/** Main function */
int main() {
    std::srand(std::time(nullptr));
    std::cout << "Key dictionary: (" << std::strlen(ciphers::STRKEY) << ")\n\t"
              << ciphers::STRKEY << "\n";

    std::string text = "This is a simple text with numb3r5 and exclamat!0n.";

    test1(text);
    test2(text);

    return 0;
}
