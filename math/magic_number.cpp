/**
 * @file
 * @brief A simple program to check if the given number is a magic number or not.
 * A number is said to be a magic number, if the sum of its digits are calculated 
 * till a single digit recursively by adding the sum of the digits after every addition. 
 * If the single digit comes out to be 1,then the number is a magic number.
 *
 * This is a shortcut method to verify Magic Number. 
 * On dividing the input by 9, if the remainder is 1 then the number is a magic number else not. 
 * The divisibility rule of 9 says that a number is divisible by 9 if the sum of its digits 
 * are also divisible by 9. Therefore, if a number is divisible by 9, then, recursively, 
 * all the digit sums are also divisible by 9. The final digit sum is always 9. 
 * An increase of 1 in the original number will increase the ultimate value by 1, 
 * making it 10 and the ultimate sum will be 1, thus verifying that it is a magic number.
 * @author [Neha Hasija](https://github.com/neha-hasija17)
 */
#include <cassert>
#include <iostream>

/**
 * Function to check if the given number is magic number or not.
 * @param n number to be checked.
 * @return if number is a magic number, returns true, else false.
 */

bool magic_number(int n) {
    if (n <= 0) {
        return false;
    }
    // result stores the modulus of @param n with 9
    int result=n%9;
    //if result is 1 then the number is a magic number else not
    if(result==1) return true;
    else return false;
}

/** Test function
 * @returns void
 */
static void tests() {
    std::cout << "Test 1:\t n=60\n";
    assert(magic_number(60) == false);
    std::cout << "passed\n";

    std::cout << "Test 2:\t n=730\n";
    assert(magic_number(730) == true);
    std::cout << "passed\n";

    std::cout << "Test 3:\t n=0\n";
    assert(magic_number(0) == false);
    std::cout << "passed\n";

    std::cout << "Test 4:\t n=479001600\n";
    assert(magic_number(479001600) == false);
    std::cout << "passed\n";

    std::cout << "Test 5:\t n=-35\n";
    assert(magic_number(-35) == false);
    std::cout << "passed\n";
}

/** Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
