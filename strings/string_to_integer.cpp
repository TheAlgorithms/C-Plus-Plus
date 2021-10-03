#include <iostream>

int charToDigit(const char& c) {
    switch(c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;

        default: return (int)c;
    }
}

/** string_to_integer function
 * \param [str] a string integer
 * \returns parsed integer from string
 */
int string_to_integer(const std::string &str) {
    unsigned int result = 0;
    int i = 0;

    if(str[i] == '-' || str[i] == '+') {
        i++;
    }
    std::cout << result << std::endl;

    while('0' <= str[i] && str[i] <= '9') {

        // if we are out of integer limit
        if(result >= 2147483647) {
            if(str[0] == '-' && result >= 2147483648)
                return -2147483648;

            return 2147483647;
        }

        result *= 10;
        result += charToDigit(str[i++]);
    }

    if(str[0] == '-')
        result *= -1;

    return result;
}

int main(int argc, char const* argv[]) {
    std::string stringNumber;
    std::cout << "Enter string integer: ";
    std::cin >> stringNumber;

    int number = string_to_integer(stringNumber);

    std::cout << "Number is: " << number << std::endl;

    return 0;
}
