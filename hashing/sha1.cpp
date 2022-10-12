/**
 * @file
 * @author [tGautot](https://github.com/tGautot)
 * @brief Simple C++ implementation of the [SHA-1 Hashing
 * Algorithm](https://en.wikipedia.org/wiki/SHA-1)
 *
 * @details
 * [SHA-1](https://en.wikipedia.org/wiki/SHA-1) is a cryptographic hash function
 * that was developped by the
 * [NSA](https://en.wikipedia.org/wiki/National_Security_Agency) 1995.
 * SHA-1 is not considered secure since around 2010.
 *
 * ### Algorithm
 * The first step of the algorithm is to pad the message for its length to
 * be a multiple of 64 (bytes). This is done by first adding 0x80 (10000000)
 * and then only zeroes until the last 8 bytes must be filled, where then the
 * 64 bit size of the input will be added
 *
 * Once this is done, the algo breaks down this padded message
 * into 64 bytes chunks. Each chunk is used for one *round*, a round
 * breaks the chunk into 16 blocks of 4 bytes. These 16 blocks are then extended
 * to 80 blocks using XOR operations on existing blocks (see code for more
 * details). The algorithm will then update its 160-bit state (here represented
 * used 5 32-bits integer) using partial hashes computed using special functions
 * on the blocks previously built. Please take a look at the [wikipedia
 * article](https://en.wikipedia.org/wiki/SHA-1#SHA-1_pseudocode) for more
 * precision on these operations
 * @note This is a simple implementation for a byte string but
 * some implmenetations can work on bytestream, messages of unknown length.
 */

#include <algorithm>  /// For std::copy
#include <array>      /// For std::array
#include <cassert>    /// For assert
#include <cstring>    /// For std::memcopy
#include <iostream>   /// For IO operations
#include <string>     /// For strings
#include <vector>     /// For std::vector

/**
 * @namespace hashing
 * @brief Hashing algorithms
 */
namespace hashing {
/**
 * @namespace SHA-1
 * @brief Functions for the [SHA-1](https://en.wikipedia.org/wiki/SHA-1)
 * algorithm implementation
 */
namespace sha1 {
/**
 * @brief Rotates the bits of a 32-bit unsigned integer
 * @param n Integer to rotate
 * @param rotate How many bits for the rotation
 * @return uint32_t The rotated integer
 */
uint32_t leftRotate32bits(uint32_t n, std::size_t rotate) {
    return (n << rotate) | (n >> (32 - rotate));
}

/**
 * @brief Transforms the 160-bit SHA-1 signature into a 40 char hex string
 * @param sig The SHA-1 signature (Expected 20 bytes)
 * @return std::string The hex signature
 */
std::string sig2hex(void* sig) {
    const char* hexChars = "0123456789abcdef";
    auto* intsig = static_cast<uint8_t*>(sig);
    std::string hex = "";
    for (uint8_t i = 0; i < 20; i++) {
        hex.push_back(hexChars[(intsig[i] >> 4) & 0xF]);
        hex.push_back(hexChars[(intsig[i]) & 0xF]);
    }
    return hex;
}

/**
 * @brief The SHA-1 algorithm itself, taking in a bytestring
 * @param input_bs The bytestring to hash
 * @param input_size The size (in BYTES) of the input
 * @return void* Pointer to the 160-bit signature
 */
void* hash_bs(const void* input_bs, uint64_t input_size) {
    auto* input = static_cast<const uint8_t*>(input_bs);

    // Step 0: The initial 160-bit state
    uint32_t h0 = 0x67452301, a = 0;
    uint32_t h1 = 0xEFCDAB89, b = 0;
    uint32_t h2 = 0x98BADCFE, c = 0;
    uint32_t h3 = 0x10325476, d = 0;
    uint32_t h4 = 0xC3D2E1F0, e = 0;

    // Step 1: Processing the bytestring
    // First compute the size the padded message will have
    // so it is possible to allocate the right amount of memory
    uint64_t padded_message_size = 0;
    if (input_size % 64 < 56) {
        padded_message_size = input_size + 64 - (input_size % 64);
    } else {
        padded_message_size = input_size + 128 - (input_size % 64);
    }

    // Allocate the memory for the padded message
    std::vector<uint8_t> padded_message(padded_message_size);

    // Beginning of the padded message is the original message
    std::copy(input, input + input_size, padded_message.begin());

    // Afterwards comes a single 1 bit and then only zeroes
    padded_message[input_size] = 1 << 7;  // 10000000
    for (uint64_t i = input_size; i % 64 != 56; i++) {
        if (i == input_size) {
            continue;  // pass first iteration
        }
        padded_message[i] = 0;
    }

    // We then have to add the 64-bit size of the message in bits (hence the
    // times 8) in the last 8 bytes
    uint64_t input_bitsize = input_size * 8;
    for (uint8_t i = 0; i < 8; i++) {
        padded_message[padded_message_size - 8 + i] =
            (input_bitsize >> (56 - 8 * i)) & 0xFF;
    }

    // Already allocate memory for blocks
    std::array<uint32_t, 80> blocks{};

    // Rounds
    for (uint64_t chunk = 0; chunk * 64 < padded_message_size; chunk++) {
        // First, build 16 32-bits blocks from the chunk
        for (uint8_t bid = 0; bid < 16; bid++) {
            blocks[bid] = 0;

            // Having to build a 32-bit word from 4-bit words
            // Add each and shift them to the left
            for (uint8_t cid = 0; cid < 4; cid++) {
                blocks[bid] = (blocks[bid] << 8) +
                              padded_message[chunk * 64 + bid * 4 + cid];
            }

            // Extend the 16 32-bit words into 80 32-bit words
            for (uint8_t i = 16; i < 80; i++) {
                blocks[i] =
                    leftRotate32bits(blocks[i - 3] ^ blocks[i - 8] ^
                                         blocks[i - 14] ^ blocks[i - 16],
                                     1);
            }
        }

        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;

        // Main "hashing" loop
        for (uint8_t i = 0; i < 80; i++) {
            uint32_t F = 0, g = 0;
            if (i < 20) {
                F = (b & c) | ((~b) & d);
                g = 0x5A827999;
            } else if (i < 40) {
                F = b ^ c ^ d;
                g = 0x6ED9EBA1;
            } else if (i < 60) {
                F = (b & c) | (b & d) | (c & d);
                g = 0x8F1BBCDC;
            } else {
                F = b ^ c ^ d;
                g = 0xCA62C1D6;
            }

            // Update the accumulators
            uint32_t temp = leftRotate32bits(a, 5) + F + e + g + blocks[i];
            e = d;
            d = c;
            c = leftRotate32bits(b, 30);
            b = a;
            a = temp;
        }
        // Update the state with this chunk's hash
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // Build signature from state
    // Note, any type could be used for the signature
    // uint8_t was used to make the 20 bytes obvious
    auto* sig = new uint8_t[20];
    for (uint8_t i = 0; i < 4; i++) {
        sig[i] = (h0 >> (24 - 8 * i)) & 0xFF;
        sig[i + 4] = (h1 >> (24 - 8 * i)) & 0xFF;
        sig[i + 8] = (h2 >> (24 - 8 * i)) & 0xFF;
        sig[i + 12] = (h3 >> (24 - 8 * i)) & 0xFF;
        sig[i + 16] = (h4 >> (24 - 8 * i)) & 0xFF;
    }

    return sig;
}

/**
 * @brief Converts the string to bytestring and calls the main algorithm
 * @param message Plain character message to hash
 * @return void* Pointer to the SHA-1 signature
 */
void* hash(const std::string& message) {
    return hash_bs(&message[0], message.size());
}
}  // namespace sha1
}  // namespace hashing

/**
 * @brief Self-test implementations of well-known SHA-1 hashes
 * @returns void
 */
static void test() {
    // Hashes empty string and stores signature
    void* sig = hashing::sha1::hash("");
    std::cout << "Hashing empty string" << std::endl;
    // Prints signature hex representation
    std::cout << hashing::sha1::sig2hex(sig) << std::endl << std::endl;
    // Test with cassert wether sig is correct from expected value
    assert(hashing::sha1::sig2hex(sig).compare(
               "da39a3ee5e6b4b0d3255bfef95601890afd80709") == 0);

    // Hashes "The quick brown fox jumps over the lazy dog" and stores signature
    void* sig2 =
        hashing::sha1::hash("The quick brown fox jumps over the lazy dog");
    std::cout << "Hashing The quick brown fox jumps over the lazy dog"
              << std::endl;
    // Prints signature hex representation
    std::cout << hashing::sha1::sig2hex(sig2) << std::endl << std::endl;
    // Test with cassert wether sig is correct from expected value
    assert(hashing::sha1::sig2hex(sig2).compare(
               "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12") == 0);

    // Hashes "The quick brown fox jumps over the lazy dog." (notice the
    // additional period) and stores signature
    void* sig3 =
        hashing::sha1::hash("The quick brown fox jumps over the lazy dog.");
    std::cout << "Hashing "
                 "The quick brown fox jumps over the lazy dog."
              << std::endl;
    // Prints signature hex representation
    std::cout << hashing::sha1::sig2hex(sig3) << std::endl << std::endl;
    // Test with cassert wether sig is correct from expected value
    assert(hashing::sha1::sig2hex(sig3).compare(
               "408d94384216f890ff7a0c3528e8bed1e0b01621") == 0);

    // Hashes "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
    // and stores signature
    void* sig4 = hashing::sha1::hash(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    std::cout
        << "Hashing "
           "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
        << std::endl;
    // Prints signature hex representation
    std::cout << hashing::sha1::sig2hex(sig4) << std::endl << std::endl;
    // Test with cassert wether sig is correct from expected value
    assert(hashing::sha1::sig2hex(sig4).compare(
               "761c457bf73b14d27e9e9265c46f4b4dda11f940") == 0);
}

/**
 * @brief Puts user in a loop where inputs can be given and SHA-1 hash will be
 * computed and printed
 * @returns void
 */
static void interactive() {
    while (true) {
        std::string input;
        std::cout << "Enter a message to be hashed (Ctrl-C to exit): "
                  << std::endl;
        std::getline(std::cin, input);
        void* sig = hashing::sha1::hash(input);
        std::cout << "Hash is: " << hashing::sha1::sig2hex(sig) << std::endl;

        while (true) {
            std::cout << "Want to enter another message? (y/n) ";
            std::getline(std::cin, input);
            if (input.compare("y") == 0) {
                break;
            } else if (input.compare("n") == 0) {
                return;
            }
        }
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    // Launch interactive mode where user can input messages and see
    // their hash
    interactive();
    return 0;
}
