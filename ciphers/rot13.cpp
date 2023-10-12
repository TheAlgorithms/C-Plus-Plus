/**
 * @file rot13.cpp
 *
 * @brief Implementation of [ROT13](https://en.wikipedia.org/wiki/ROT13)
 * algorithm.
 *
 * @details
 * ROT13 ("rotate by 13 places") is a simple letter substitution cipher that
 * replaces a letter with the 13th letter after it in the latin alphabet.
 * ROT13 is a special case of the Caesar cipher which was developed
 * in ancient Rome.
 *
 * @author [pandfun](https://github.com/pandfun)
 */
#include <cassert>
#include <iostream>
#include <string>

/**
 * @namespace ciphers
 * @brief Cipher algorithms
 */
namespace ciphers {
/**
 * @namespace rot13_encoding
 * @brief Function for [ROT13 Encoding and
 * Decoding](https://en.wikipedia.org/wiki/ROT13) implementation.
 */
namespace rot13 {
/**
 * @brief ROT13 Encoder/Decoder
 * @details Converts the given string using ROT13 algorithm.
 * Because a second application of ROT13 would restore the original text,
 * we can use the same function to encrypt as well as decrypt.
 * @param input Input as a string
 * @returns ROT13 encoded/decoded string
 */
std::string rot13_convert(const std::string &input) {
    std::string result;

    for (uint32_t i = 0; i < input.length(); ++i) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            result.push_back('A' + ((input[i] - 'A' + 13) % 26));
        } else if (input[i] >= 'a' && input[i] <= 'z') {
            result.push_back('a' + ((input[i] - 'a' + 13) % 26));
        } else {
            result.push_back(input[i]);
        }
    }

    return result;
}
}  // namespace rot13
}  // namespace ciphers

/**
 * @brief Self test-implementations
 * @returns void
 */
static void test() {
    // 1st Test from [Wikipedia](https://en.wikipedia.org/wiki/ROT13)
    std::string str = "Why did the chicken cross the road?";
    std::string verify = "Jul qvq gur puvpxra pebff gur ebnq?";

    std::string rot13_result = ciphers::rot13::rot13_convert(str);
    // Verify encoding
    assert(rot13_result == verify);

    std::string original_str = ciphers::rot13::rot13_convert(rot13_result);
    // Verify decoding
    assert(original_str == str);

    // 2nd Test
    str =
        "Autumn leaves rustled in the gentle breeze as the sun dipped below "
        "the horizon, painting the sky with hues of orange and pink. The "
        "tranquil park was a haven for those seeking solace in the midst of "
        "the bustling city. Children laughed and played on the swings, their "
        "joy contagious to anyone who passed by. As the day turned into "
        "evening, a sense of calm settled over the world, a reminder that "
        "sometimes, in the simplest of moments, we find the greatest beauty.";
    verify =
        "Nhghza yrnirf ehfgyrq va gur tragyr oerrmr nf gur fha qvccrq orybj "
        "gur ubevmba, cnvagvat gur fxl jvgu uhrf bs benatr naq cvax. Gur "
        "genadhvy cnex jnf n unira sbe gubfr frrxvat fbynpr va gur zvqfg bs "
        "gur ohfgyvat pvgl. Puvyqera ynhturq naq cynlrq ba gur fjvatf, gurve "
        "wbl pbagntvbhf gb nalbar jub cnffrq ol. Nf gur qnl ghearq vagb "
        "riravat, n frafr bs pnyz frggyrq bire gur jbeyq, n erzvaqre gung "
        "fbzrgvzrf, va gur fvzcyrfg bs zbzragf, jr svaq gur terngrfg "
        "ornhgl.";

    rot13_result = ciphers::rot13::rot13_convert(str);
    // Verify encodig
    assert(rot13_result == verify);

    original_str = ciphers::rot13::rot13_convert(rot13_result);
    // Verify decoding
    assert(original_str == str);

    return;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Running some self-tests
    return 0;
}