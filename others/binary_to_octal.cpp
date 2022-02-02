/**
 * @file
 * @brief Conversion from binary to octal
 * @details
 * This function takes in a binary string and returns an
 * octal string by converting binary digits in groups of 3
 * @author [Peter Lucchino](https://github.com/peterlucchino)
 */
#include <string>
#include <iostream>
#include <cassert>

std::string binary_to_octal(std::string f) {
    int rem = f.length() % 3;  // calculates the remainder to determine how many numbers to add
    if (rem == 1) {            // octal conversion can be done in groups of 3 binary digits
        f = "00" + f;          // if there is a lone digit remaining 00 must be prepended to make a group of 3 digits
    }
    else if (rem == 2) {
        f = "0" + f;           // if there are two remaining digits 0 must be prepended onto the binary string
    }

    int j = f.length() / 3;                  // counts the numbers of groups of 3 that need to be converted
    std::string output = "";
    int count = 0;                           // contains the binary count for each group of 3 digits to be converted to octal
    for (int i = 0; i < j; i++) {
        for (int q = 3 * i; q < 3 * i + 3; q++) {  // iterates through the 3 digits of each block
            count *= 2;
            if (f[q] == '1') {
                count += 1;
            }
        }
        output += std::to_string(count);
        count = 0;
    }
    return output;
}

int main() {
    assert(binary_to_octal("111101") == "75");
    assert(binary_to_octal("111101101110100010110011011") == "755642633");
    assert(binary_to_octal("1") == "1");
    assert(binary_to_octal("10") == "2");
    assert(binary_to_octal("1000101010") == "1052");
    return 0;
}