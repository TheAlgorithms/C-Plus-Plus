/**
 * @file
 * @brief Convert decimal number to hexadecimal representation
 */

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief converts a given decimal integer value to its equavalent hexadecimal
 * string
 *
 * @param value the value to be converted
 * @return std::string the hexadecimal string
 */
std::string decimal_to_hexadecimal(std::uint32_t value) {
    std::vector<uint32_t> hexArray{};
    std::string ret = "";
    size_t i = 0;
    const char HexValues[] = "0123456789ABCDEF";

    while (value > 15) {
        hexArray.at(i++) = value % 16;
        value /= 16;
    }
    while (i >= 0) ret.push_back(HexValues[i--]);
    return ret;
}

/**
 * @brief self test implementation
 * @returns void
 */
static void tests() {
    assert(decimal_to_hexadecimal(0) == "0");
    assert(decimal_to_hexadecimal(1) == "1");
    assert(decimal_to_hexadecimal(10) == "A");
}

/**
 * Main program
 */
int main(void) {
    tests();  // run self test imlementation
    return 0;
}
