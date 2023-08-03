/**
 * @file
 * @brief Program to check if a number is a strobogrammatic number in the decimal system.
 *
 * @details
 * A strobogrammatic number is a number that is the same or reads the same when rotated 180 degrees.
 * In this implementation, we will consider strobogrammatic numbers in decimal (base 10).
 * For example, 0, 1, and 8 are strobogrammatic because they remain the same when rotated,
 * and 6 and 9 are strobogrammatic because when rotated 180 degrees, they become each other.
 *
 * @see For more information, refer to the source at: https://en.wikipedia.org/wiki/Strobogrammatic_number
 *
 * @author [Himesh](https://github.com/HimeshKohad)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Function to check if a number is strobogrammatic.
 * @param number The number to be checked.
 * @return `true` if the number is strobogrammatic.
 * @return `false` if the number is not strobogrammatic.
 */
bool is_strobogrammatic(int number) {
    // Convert the number to a string for easier manipulation.
    std::string num_str = std::to_string(number);
    int left = 0;
    int right = num_str.size() - 1;

    while (left <= right) {
        char left_char = num_str[left];
        char right_char = num_str[right];

        // Check if the characters at left and right positions form a valid strobogrammatic pair.
        if ((left_char == '0' && right_char == '0') || (left_char == '1' && right_char == '1') ||
            (left_char == '8' && right_char == '8') || (left_char == '6' && right_char == '9') ||
            (left_char == '9' && right_char == '6')) {
            left++;
            right--;
        } 
          
        else {
            return false; // Not a strobogrammatic number.
        }
    }

    return true; // If the loop completes, it's a strobogrammatic number.
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // is_strobogrammatic(101) returns true.
    assert(is_strobogrammatic(101) == true);
    // is_strobogrammatic(69) returns true.
    assert(is_strobogrammatic(69) == true);
    // is_strobogrammatic(818) returns true.
    assert(is_strobogrammatic(818) == true);
    // is_strobogrammatic(88) returns true.
    assert(is_strobogrammatic(88) == true);
    // is_strobogrammatic(609) returns false.
    assert(is_strobogrammatic(609) == false);
    // is_strobogrammatic(120) returns false.
    assert(is_strobogrammatic(120) == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
