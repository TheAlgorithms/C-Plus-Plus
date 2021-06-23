/**
 * @file
 * @brief A simple program to count the number of ciphers in a factorial of some
 * number.
 * @author [Swastika Gupta](https://github.com/swastyy)
 */
#include <cassert>
#include <iostream>

/**
 * Function to count the number of ciphers.
 * @param n is the number to be given as argument.
 * @return it returns the power of 5 in factorial of a given number.
 */

int count_of_number_of_ciphers_in_factorial_n(uint64_t n) {
    // count is to store the number of 5's in factorial(n)
    int count = 0;
 
    // Keep dividing n by powers of
    // 5 and update count
    for (int i = 5; n / i >= 1; i *= 5){
        count += n / i;
    }
 
    return count;
}

/** Test function
 * @returns void
 */
void tests() {
    std::cout << "Test 1:\t n=395\n";
    if(count_of_number_of_ciphers_in_factorial_n(395) == 97) {
        std::cout << "passed\n";
    }
    else{
        std::cout << "failed\n";
    }

    std::cout << "Test 2:\t n=977\n";
    if(count_of_number_of_ciphers_in_factorial_n(977) == 242) {
        std::cout << "passed\n";
    }
    else{
        std::cout << "failed\n";
    }

    std::cout << "Test 3:\t n=871\n";
    if(count_of_number_of_ciphers_in_factorial_n(871) == 215) {
        std::cout << "passed\n";
    }
    else{
        std::cout << "failed\n";
    }

    std::cout << "Test 4:\t n=239\n";
    if(count_of_number_of_ciphers_in_factorial_n(239) == 57) {
        std::cout << "passed\n";
    }
    else{
        std::cout << "failed\n";
    }
}

/** Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
