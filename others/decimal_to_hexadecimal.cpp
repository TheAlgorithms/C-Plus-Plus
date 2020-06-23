/**
 * @file
 * @brief Convert decimal number to hexadecimal representation
 */

#include <iostream>

/**
 * Main program
 */
int main(void) {
    int valueToConvert = 0;  // Holds user input
    int hexArray[8];         // Contains hex values backwards
    int i = 0;               // counter
    char HexValues[] = "0123456789ABCDEF";

    std::cout << "Enter a Decimal Value"
              << std::endl;  // Displays request to stdout
    std::cin >>
        valueToConvert;  // Stores value into valueToConvert via user input

    while (valueToConvert > 15) {             // Dec to Hex Algorithm
        hexArray[i++] = valueToConvert % 16;  // Gets remainder
        valueToConvert /= 16;
        // valueToConvert >>= 4;  // This will divide by 2^4=16 and is faster
    }
    hexArray[i] = valueToConvert;  // Gets last value

    std::cout << "Hex Value: ";
    while (i >= 0) std::cout << HexValues[hexArray[i--]];

    std::cout << std::endl;
    return 0;
}
