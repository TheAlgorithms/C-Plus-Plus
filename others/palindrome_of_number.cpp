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

    std::string s = std::to_string(num);

    int left = 0;
    int right = s.length() - 1;

    bool is_palindrome = true;

    while (left < right) {
        if (s[left] != s[right]) {
            is_palindrome = false;
            break;
        }
        left++;
        right--;
    }

    std::cout << (is_palindrome ? "true" : "false");

    return 0;
}
