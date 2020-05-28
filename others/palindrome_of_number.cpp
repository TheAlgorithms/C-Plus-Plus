/**
 * @file
 * @brief Check if a number is
 * [palindrome](https://en.wikipedia.org/wiki/Palindrome) or not.
 *
 * This program cheats by using the STL library's std::reverse function.
 */
#include <algorithm>
#include <iostream>

#ifdef _MSC_VER
// Required to compile std::toString function using MSVC
#include <string>
#else
#include <cstring>
#endif

/** Main function */
int main() {
    int num;
    std::cout << "Enter number = ";
    std::cin >> num;

    std::string s1 = std::to_string(num);  // convert number to string
    std::string s2 = s1;

    std::reverse(s1.begin(), s1.end());  // reverse the string

    if (s1 == s2)  // check if reverse and original string are identical
        std::cout << "true";
    else
        std::cout << "false";

    return 0;
}
