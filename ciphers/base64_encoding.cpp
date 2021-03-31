/**
 * @brief [Base64 Encoding and
 * Decoding](https://en.wikipedia.org/wiki/Base64)
 * @details In programming, [Base64](https://en.wikipedia.org/wiki/Base64) is a
 * group of binary-to-text encoding schemes that represent binary data (more
 * specifically, a sequence of 8-bit bytes) in an ASCII string format by
 * translating the data into a radix-64 representation. The term Base64
 * originates from a specific MIME content transfer encoding. Each non-final
 * Base64 digit represents exactly 6 bits of data. Three 8-bit bytes (i.e., a
 * total of 24 bits) can therefore be represented by four 6-bit Base64
 * digits.
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <array>     /// for `std::array`
#include <cassert>   /// for `assert` operations
#include <iostream>  /// for IO operations

/**
 * @namespace ciphers
 * @brief Cipher algorithms
 */
namespace ciphers {
/**
 * @namespace base64_encoding
 * @brief Functions for [Base64 Encoding and
 * Decoding](https://en.wikipedia.org/wiki/Base64) implementation.
 */
namespace base64_encoding {
// chars denoting the format for encoding and decoding array.
// This array is already decided by
// [RFC4648](https://tools.ietf.org/html/rfc4648#section-4) standard
const std::string chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/**
 * @brief Base64 Encoder
 * @details Converts the given string to Base64 equivalent.
 * @param input Input as a string
 * @returns Base64 encoded string
 */
std::string base64_encode(const std::string &input) {
    std::string base64_string;  /// Output of this function: base64 string
    // base64 deals with 6-bit chars encoded as per chars, so
    // we will always filter 6-bits from input.
    for (uint32_t i = 0; i < input.size(); i += 3) {
        char first_byte = input[i];  /// First byte of the iteration
        // Take first six bits of first character.
        // Encode the first six bits with character defined in string `chars`
        base64_string.push_back(chars[first_byte >> 2]);

        if (i + 1 < input.size()) {
            char second_byte = input[i + 1];  /// Second byte of the iteration
            // Take remaining two bits of first character, and four first bits
            // from second character Combine two numbers as 6-bit digits and
            // encode by array chars (first two bits of first byte and next four
            // of second byte)
            base64_string.push_back(
                chars[(((first_byte & 3) << 4) | ((second_byte & 0xF0) >> 4))]);

            if (i + 2 < input.size()) {
                char third_byte = input[i + 2];  /// Third byte of the iteration
                // Take remaining four bits of second character, and first two
                // bits from third character Combine two numbers as 6-bit digits
                // and encode by array chars (remaining four bits of second byte
                // and first two of third byte)
                base64_string.push_back(chars[((third_byte & 0xC0) >> 6) |
                                              ((second_byte & 0x0F) << 2)]);
                // Encode remaining 6-bit of third byte by array chars
                base64_string.push_back(chars[(third_byte & 0x3F)]);
            } else {
                // Take remaining four bits of second character as 6-bit number
                base64_string.push_back(chars[((second_byte & 0x0F) << 2)]);
                base64_string.push_back('=');  // padding characters
            }
        } else {
            // Take remaining two bits of first character as 6-bit number
            base64_string.push_back(chars[((first_byte & 3) << 4)]);
            base64_string.push_back('=');  // padding characters
            base64_string.push_back('=');  // padding characters
        }
    }
    return base64_string;
}
/**
 * @brief Utility function for finding index
 * @details Utility function for finding the position of a character in array
 * `chars`
 * @param c character to search in array `chars`
 * @returns integer denoting position of character in array `chars`
 */
uint8_t find_idx(const char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    } else if (c >= '0' && c <= '9') {
        return c - '0' + 52;
    } else if (c == '+') {
        return 62;
    } else if (c == '/') {
        return 63;
    }
    return -1;
}
/**
 * @brief Base64 Decoder
 * @details Decodes the Base64 string
 * @param base64_str Input as a Base64 string
 * @returns Base64 decoded string
 */
std::string base64_decode(const std::string &base64_str) {
    std::string
        base64_decoded;  /// Output of this function: base64 decoded string
    for (uint32_t i = 0; i < base64_str.size(); i += 4) {
        /// First 6-bit representation of Base64
        char first_byte = base64_str[i];
        /// Second 6-bit representation of Base64
        char second_byte = base64_str[i + 1];
        // Actual str characters are of 8 bits (or 1 byte):
        // :: 8 bits are decode by taking 6 bits from 1st byte of base64 string
        // and first 2 bits from 2nd byte of base64 string.
        char first_actual_byte = static_cast<char>(
            (find_idx(first_byte) << 2) | ((find_idx(second_byte)) >> 4));
        base64_decoded.push_back(first_actual_byte);
        if (i + 2 < base64_str.size() && base64_str[i + 2] != '=') {
            /// Third 6-bit representation of Base64
            char third_byte = base64_str[i + 2];
            // :: Next 8 bits are decode by taking remaining 4 bits from 2nd
            // byte of base64 string and first 4 bits from 3rd byte of base64
            // string.
            char second_actual_byte =
                static_cast<char>(((find_idx(second_byte) & 0x0F) << 4) |
                                  (find_idx(third_byte) >> 2));
            base64_decoded.push_back(second_actual_byte);

            if (i + 3 < base64_str.size() && base64_str[i + 3] != '=') {
                /// Fourth 6-bit representation of Base64 string
                char fourth_byte = base64_str[i + 3];
                // :: Taking remaining 2 bits from 3rd byte of base64 string
                // and all 6 bits from 4th byte of base64 string.
                char third_actual_byte =
                    static_cast<char>(((find_idx(third_byte) & 0x03) << 6) |
                                      find_idx(fourth_byte));
                base64_decoded.push_back(third_actual_byte);
            }
        }
    }
    return base64_decoded;
}
}  // namespace base64_encoding
}  // namespace ciphers

/**
 * @brief Self test-implementations
 * @returns void
 */
static void test() {
    // 1st Test
    std::string str =
        "To err is human, but to really foul things up you need a computer.";
    std::string base64_str = ciphers::base64_encoding::base64_encode(str);
    std::string verify =
        "VG8gZXJyIGlzIGh1bWFuLCBidXQgdG8gcmVhbGx5IGZvdWwgdGhpbmdzIHVwIHlvdSBuZW"
        "VkIGEgY29tcHV0ZXIu";
    // verify encoding
    assert(base64_str == verify);
    std::string original_str =
        ciphers::base64_encoding::base64_decode(base64_str);
    // verify decoding
    assert(original_str == str);

    // 2nd Test from [Wikipedia](https://en.wikipedia.org/wiki/Base64)
    str =
        "Man is distinguished, not only by his reason, but by this singular "
        "passion from other animals, which is a lust of the mind, that by a "
        "perseverance of delight in the continued and indefatigable generation "
        "of knowledge, exceeds the short vehemence of any carnal pleasure.";

    base64_str = ciphers::base64_encoding::base64_encode(str);
    verify =
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieS"
        "B0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBh"
        "IGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodC"
        "BpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25v"
        "d2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbG"
        "Vhc3VyZS4=";
    // verify encoding
    assert(base64_str == verify);
    original_str = ciphers::base64_encoding::base64_decode(base64_str);
    // verify decoding
    assert(original_str == str);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
