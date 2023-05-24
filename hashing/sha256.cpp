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

#include <array>    /// For std::array
#include <cassert>  /// For assert
#include <cstdint>  /// For uint8_t, uint32_t and uint64_t data types
#include <iomanip>  /// For std::setfill and std::setw
#include <sstream>  /// For std::stringstream
#include <vector>   /// For std::vector

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
 * @brief Computes size of the padded input
 * @param input Input string
 * @return size_t Size of the padded input
 */
std::size_t compute_padded_size(const std::size_t input_size) {
    if (input_size % 64 < 56) {
        return input_size + 64 - (input_size % 64);
    }
    return input_size + 128 - (input_size % 64);
}

/**
 * @brief Returns the byte at position byte_num in in_value
 * @param in_value Input value
 * @param byte_num Position of byte to be returned
 * @return uint8_t Byte at position byte_num
 */
template <typename T>
uint8_t extract_byte(const T in_value, const std::size_t byte_num) {
    if (sizeof(in_value) <= byte_num) {
        throw std::out_of_range("Byte at index byte_num does not exist");
    }
    return ((in_value >> (byte_num * 8)) & 0xFF);
}

/**
 * @brief Returns the character at pos after the input is padded
 * @param input Input string
 * @param pos Position of character to be returned
 * @return char Character at the index pos in the padded string
 */
char get_char(const std::string &input, std::size_t pos) {
    const auto input_size = input.length();
    if (pos < input_size) {
        return input[pos];
    }
    if (pos == input_size) {
        return '\x80';
    }
    const auto padded_input_size = compute_padded_size(input_size);
    if (pos < padded_input_size - 8) {
        return '\x00';
    }
    if (padded_input_size <= pos) {
        throw std::out_of_range("pos is out of range");
    }
    return static_cast<char>(
        extract_byte<size_t>(input_size * 8, padded_input_size - pos - 1));
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
 * @brief Creates the message schedule array
 * @param input Input string
 * @param i Position of the first bit of the chunk
 * @return std::array<uint32_t, 64> Message schedule array
 */
std::array<uint32_t, 64> create_message_schedule_array(const std::string &input,
                                                       const size_t i) {
    std::array<uint32_t, 64> blocks{};

    // Copy chunk into first 16 words of the message schedule array
    for (size_t j = 0; j < 16; ++j) {
        blocks[j] =
            (static_cast<uint8_t>(get_char(input, i + j * 4)) << 24) |
            (static_cast<uint8_t>(get_char(input, i + j * 4 + 1)) << 16) |
            (static_cast<uint8_t>(get_char(input, i + j * 4 + 2)) << 8) |
            static_cast<uint8_t>(get_char(input, i + j * 4 + 3));
    }

    // Extend the first 16 words into remaining 48 words of the message schedule
    // array
    for (size_t j = 16; j < 64; ++j) {
        const auto s0 = right_rotate(blocks[j - 15], 7) ^
                        right_rotate(blocks[j - 15], 18) ^
                        (blocks[j - 15] >> 3);
        const auto s1 = right_rotate(blocks[j - 2], 17) ^
                        right_rotate(blocks[j - 2], 19) ^ (blocks[j - 2] >> 10);
        blocks[j] = blocks[j - 16] + s0 + blocks[j - 7] + s1;
    }

    return blocks;
}

/**
 * @brief Modifies the hash array
 * @param hash Hash array to be modified
 * @param blocks Message schedule array
 * @return void
 */
void modify_hash(std::array<uint32_t, 8> &hash,
                 const std::array<uint32_t, 64> &blocks) {
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

    // Initialize working variables
    auto a = hash[0];
    auto b = hash[1];
    auto c = hash[2];
    auto d = hash[3];
    auto e = hash[4];
    auto f = hash[5];
    auto g = hash[6];
    auto h = hash[7];

    // Compression function main loop
    for (size_t j = 0; j < 64; ++j) {
        const auto s1 =
            right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
        const auto ch = (e & f) ^ (~e & g);
        const auto temp1 = h + s1 + ch + k[j] + blocks[j];
        const auto s0 =
            right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
        const auto maj = (a & b) ^ (a & c) ^ (b & c);
        const auto temp2 = s0 + maj;

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

/**
 * @brief Computes the final hash array
 * @param input Input string
 * @return std::array<uint32_t, 8> The final hash array
 */
std::array<uint32_t, 8> compute_hash(const std::string &input) {
    // Initialize array of hash values with first 32 bits of the fractional
    // parts of the square roots of the first 8 primes 2..19
    std::array<uint32_t, 8> hash = {0x6A09E667, 0xBB67AE85, 0x3C6EF372,
                                    0xA54FF53A, 0x510E527F, 0x9B05688C,
                                    0x1F83D9AB, 0x5BE0CD19};

    // Process message in successive 512-bit (64-byte) chunks
    for (size_t i = 0; i < compute_padded_size(input.length()); i += 64) {
        modify_hash(hash, create_message_schedule_array(input, i));
    }

    return hash;
}

/**
 * @brief Convert the hash to a hexadecimal string
 * @param hash Hash array
 * @return std::string Final hash value
 */
std::string hash_to_string(const std::array<uint32_t, 8> &hash) {
    std::stringstream ss;
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            const uint32_t byte = extract_byte<uint32_t>(hash[i], 3 - j);
            ss << std::hex << std::setfill('0') << std::setw(2) << byte;
        }
    }
    return ss.str();
}

/**
 * @brief The SHA-256 algorithm
 * @param input The input string to hash
 * @return std::string The final hash value
 */
std::string sha256(const std::string &input) {
    return hash_to_string(compute_hash(input));
}
}  // namespace sha256
}  // namespace hashing

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    struct TestCase {
        const std::string input;
        const std::string expected_hash;
        TestCase(std::string input, std::string expected_hash)
            : input(std::move(input)),
              expected_hash(std::move(expected_hash)) {}
    };
    const std::vector<TestCase> test_cases{
        TestCase(
            "",
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"),
        TestCase(
            "test",
            "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"),
        TestCase(
            "Hello World",
            "a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e"),
        TestCase("Hello World!",
                 "7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9"
                 "069")};
    for (const auto &tc : test_cases) {
        assert(hashing::sha256::sha256(tc.input) == tc.expected_hash);
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run self-test implementations
    return 0;
}
