/**
 * @file
 * @brief Program to count number of ciphers in `n!`
 * @author [Swastika Gupta](https://github.com/swastyy)
 */
#include <cassert>
#include <iostream>

/**
 * Function to count the number of ciphers.
 * @param n Number for which `n!` ciphers are returned
 * @return count Number of ciphers in `n!`.
 */

int count_of_number_of_ciphers_in_factorial_n(uint64_t n) {
    // count is to store the number of 5's in factorial(n)
    int count = 0;

    // Keep dividing n by powers of
    // 5 and update count
    for (int i = 5; n / i >= 1; i *= 5) {
        count += static_cast<int>(n) / i;
    }

    return count;
}

/** Test function
 * @returns void
 */
void tests() {
    std::cout << "Running predefined tests...\n";
    assert(count_of_number_of_ciphers_in_factorial_n(871) == 215);
    assert(count_of_number_of_ciphers_in_factorial_n(977) == 242);
    assert(count_of_number_of_ciphers_in_factorial_n(395) == 97);
    assert(count_of_number_of_ciphers_in_factorial_n(669763357) == 167440831);
    assert(count_of_number_of_ciphers_in_factorial_n(239) == 57);
    assert(count_of_number_of_ciphers_in_factorial_n(535) == 132);
    assert(count_of_number_of_ciphers_in_factorial_n(374960399) == 93740092);
    std::cout << "Test Passed...!\n";
}

/** Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
