/**
 * @file
 * @author [Md. Anisul Haque](https://github.com/mdanisulh)
 * @brief Simple C++ implementation of the [SHA-256 Hashing Algorithm]
 * (https://en.wikipedia.org/wiki/SHA-2)
 *
 * @details
 * [SHA-2](https://en.wikipedia.org/wiki/SHA-2) is a set of cryptographic hash
 * functions that was designed by the
 * [NSA](https://en.wikipedia.org/wiki/National_Security_Agency) and first
 * published in 2001. SHA-256 is a part of the SHA-2 family. SHA-256 is widely
 * used for authenticating software packages and secure password hashing.
 */

#include <array>     /// For std::array
#include <cassert>   /// For assert
#include <cstdint>   /// For uint8_t, uint32_t and uint64_t data types
#include <iomanip>   /// For std::setfill and std::setw
#include <iostream>  /// For IO operations
#include <sstream>   /// For std::stringstream

/**
 * @namespace hashing
 * @brief Hashing algorithms
 */
namespace hashing {
/**
 * @namespace SHA-256
 * @brief Functions for the [SHA-256](https://en.wikipedia.org/wiki/SHA-2)
 * algorithm implementation
 */
namespace sha256 {
/**
 * @brief Pads the input string to be a multiple of 512-bits
 * @param input Input string
 * @return std::string The padded input string
 */
std::string prepare_input(const std::string& input) {
    // Pre-processing
    std::string padded_input = input;
    uint64_t input_size = input.length() * 8;  // Message length in bits

    // Append a single '1' bit
    padded_input += '\x80';

    // Pad with zeros
    while ((padded_input.length() * 8) % 512 != 448) padded_input += '\x00';

    // Append length of the original input string as a 64-bit big-endian integer
    for (uint32_t i = 64; i != 0; i -= 8) {
        padded_input += static_cast<char>((input_size >> (i - 8)) & 0xFF);
    }

    return padded_input;
}

/**
 * @brief Rotates the bits of a 32-bit unsigned integer
 * @param n Integer to rotate
 * @param rotate Number of bits to rotate
 * @return uint32_t The rotated integer
 */
uint32_t right_rotate(uint32_t n, size_t rotate) {
    return (n >> rotate) | (n << (32 - rotate));
}

/**
 * @brief The SHA-256 algorithm
 * @param input The input string to hash
 * @return std::string The final hash value
 */
std::string sha256(const std::string& input) {
    // Initialize array of hash values with first 32 bits of the fractional
    // parts of the square roots of the first 8 primes 2..19
    std::array<uint32_t, 8> hash = {0x6A09E667, 0xBB67AE85, 0x3C6EF372,
                                    0xA54FF53A, 0x510E527F, 0x9B05688C,
                                    0x1F83D9AB, 0x5BE0CD19};

    // Initialize array of round constants with first 32 bits of the fractional
    // parts of the cube roots of the first 64 primes 2..311
    const std::array<uint32_t, 64> k = {
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1,
        0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
        0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786,
        0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
        0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
        0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
        0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
        0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
        0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A,
        0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
        0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

    const std::string padded_input = prepare_input(input);

    // Process message in successive 512-bit (64-byte) chunks
    for (size_t i = 0; i < padded_input.length(); i += 64) {
        std::array<uint32_t, 64> blocks{};

        // Copy chunk into first 16 words of the message schedule array
        for (size_t j = 0; j < 16; ++j) {
            blocks[j] =
                (static_cast<uint8_t>(padded_input[i + j * 4]) << 24) |
                (static_cast<uint8_t>(padded_input[i + j * 4 + 1]) << 16) |
                (static_cast<uint8_t>(padded_input[i + j * 4 + 2]) << 8) |
                static_cast<uint8_t>(padded_input[i + j * 4 + 3]);
        }

        for (size_t j = 16; j < 64; ++j) {
            uint32_t s0 = right_rotate(blocks[j - 15], 7) ^
                          right_rotate(blocks[j - 15], 18) ^
                          (blocks[j - 15] >> 3);
            uint32_t s1 = right_rotate(blocks[j - 2], 17) ^
                          right_rotate(blocks[j - 2], 19) ^
                          (blocks[j - 2] >> 10);
            blocks[j] = blocks[j - 16] + s0 + blocks[j - 7] + s1;
        }

        // Initialize working variables
        uint32_t a = hash[0];
        uint32_t b = hash[1];
        uint32_t c = hash[2];
        uint32_t d = hash[3];
        uint32_t e = hash[4];
        uint32_t f = hash[5];
        uint32_t g = hash[6];
        uint32_t h = hash[7];

        // Compression function main loop
        for (size_t j = 0; j < 64; ++j) {
            uint32_t s1 =
                right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + s1 + ch + k[j] + blocks[j];
            uint32_t s0 =
                right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = s0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Update hash values
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }

    // Convert the hash to a hexadecimal string
    std::string result;
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            uint32_t byte = (hash[i] >> (24 - j * 8)) & 0xFF;
            std::stringstream ss;
            ss << std::hex << std::setfill('0') << std::setw(2) << byte;
            result += ss.str();
        }
    }

    return result;
}
}  // namespace sha256
}  // namespace hashing

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st Test
    std::string input = "";
    std::string expected =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    std::string output = hashing::sha256::sha256(input);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "1st TEST PASSED\n\n";

    // 2nd Test
    input = "test";
    expected =
        "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08";
    output = hashing::sha256::sha256(input);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "2nd TEST PASSED\n\n";

    // 3rd Test
    input = "Hello World";
    expected =
        "a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e";
    output = hashing::sha256::sha256(input);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "3rd TEST PASSED\n\n";

    // 4th Test
    input = "Hello World!";
    expected =
        "7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9069";
    output = hashing::sha256::sha256(input);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(output == expected);
    std::cout << "4th TEST PASSED\n\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run self-test implementations

    // Custom Input
    std::string input;
    std::cout << "Enter a message to be hashed: ";
    getline(std::cin, input);
    std::string hash = hashing::sha256::sha256(input);
    std::cout << "SHA-256 Hash: " << hash << std::endl;

    return 0;
}
