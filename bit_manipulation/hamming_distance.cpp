/**
 * @file
 * @brief Returns the Hamming distance between two integers
 *
 * @details
 * To find hamming distance between two integers, we take their xor, which will
 * have a set bit iff those bits differ in the two numbers.
 * Hence, we return the number of such set bits.
 *
 * @author [Ravishankar Joshi](https://github.com/ravibitsgoa)
 */

#include <iostream>
using std::cout, std::endl;

unsigned int bitCount(unsigned int value) {
    unsigned int count = 0;
    while (value) {       // until all bits are zero
        if (value & 1) {  // check lower bit
            count++;
        }
        value >>= 1;  // shift bits, removing lower bit
    }
    return count;
}

unsigned int hamming_distance(int a, int b) {
    if (a < 0 || b < 0) {
        throw "Both arguments must be >=0 for finding hamming distance.";
    }
    return bitCount(a ^ b);
}

int main() {
    int a = 11;  // 1011 in binary
    int b = 2;   // 0010 in binary

    std::cout << "Hamming distance between " << a << " and " << b << " is "
         << hamming_distance(a, b) << std::endl;
}