#include <cmath>
#include <iostream>
#include <string>

/*
Check if a number is a Disarium number.

A Disarium number is a number in which the sum of its digits
powered with their respective positions is equal to the number itself.

Args:
    num (int): The number to check.

Returns:
    bool: true if num is a Disarium number, false otherwise.

Examples:
    is_disarium(135) -> true
    is_disarium(89)  -> true
    is_disarium(75)  -> false
    is_disarium(9)   -> true
*/
bool is_disarium(int num) {
    std::string digits = std::to_string(num);
    int total = 0;
    int position = 1;

    for (char c : digits) {
        int digit = c - '0';  // convert char to int
        total += std::pow(digit, position);
        position++;
    }

    return total == num;
}

int main() {
    // Test examples
    int test_numbers[] = {135, 89, 75, 9};
    for (int n : test_numbers) {
        std::cout << n << " is "
                  << (is_disarium(n) ? "a Disarium number"
                                     : "not a Disarium number")
                  << std::endl;
    }

    return 0;
}
