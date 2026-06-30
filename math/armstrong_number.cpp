/**
 * @file
 * @brief Program to check if a number is an [Armstrong/Narcissistic
 * number](https://en.wikipedia.org/wiki/Narcissistic_number) in decimal system.
 *
 * @details
 * Armstrong number or [Narcissistic
 * number](https://en.wikipedia.org/wiki/Narcissistic_number) is a number that
 * is the sum of its own digits raised to the power of the number of digits.
 *
 * let n be the narcissistic number,
 * \f[F_b(n) = \sum_{i=0}^{k-1}d_{i}^{k}\f] for
 * \f$ b > 1 F_b : \N \to \N \f$ where
 * \f$ k = \lfloor log_b n\rfloor is the number of digits in the number in base
 * \f$b\f$, and \f$ d_i = \frac{n mod b^{i+1} - n mod b^{i}}{b^{i}} \f$
 *
 * @author [Neeraj Cherkara](https://github.com/iamnambiar)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Function to calculate the total number of digits in the number.
 * @param num Number
 * @return Total number of digits.
 */
int number_of_digits(int num) {
    if (num == 0) {
        return 1;
    }
    int total_digits = 0;
    while (num > 0) {
        ++total_digits;
        num /= 10;
    }
    return total_digits;
}

/**
 *@brief Computes base raised to the power exp using integer arithmetic.
 *@param base the base number.
 *@param exp The exponent.
 *@return base raised to the power exp.
 */
int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        --exp;
    }
    return result;
}

/**
 * @brief Function to check whether the number is armstrong number or not.
 * @param number The Number to check
 * @return `true` if the number is armstrong.
 * @return `false` if the number is not armstrong.
 */
bool is_armstrong(int number) {
    // If the number is less than 0, then it is not an armstrong number.
    if (number < 0) {
        return false;
    }

    int sum = 0;
    int temp = number;
    // Finding the total number of digits in the number
    int total_digits = number_of_digits(number);
    while (temp > 0) {
        int rem = temp % 10;
        // Finding each digit raised to the power total digit and add it to the
        // total sum
        sum += power(rem, total_digits);
        if ( sum > number) {
            return false;
        }
        temp = temp / 10;
    }
    return number == sum;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // is_armstrong(370) returns true.
    assert(is_armstrong(370) == true);

    // is_armstrong(225) returns false.
    assert(is_armstrong(225) == false);

    // is_armstrong(-23) returns false.
    assert(is_armstrong(-23) == false);

    // is_armstrong(153) returns true.
    assert(is_armstrong(153) == true);

    // is_armstrong(0) returns true.
    assert(is_armstrong(0) == true);

    // is_armstrong(12) returns false.
    assert(is_armstrong(12) == false);

    // is_armstrong(1) returns true.
    assert(is_armstrong(1) == true);

    // is_armstrong(9) returns true.
    assert(is_armstrong(9) == true);

    // is_armstrong(371) returns true.
    assert(is_armstrong(371) == true);

    // is_armstrong(407) returns true.
    assert(is_armstrong(407) == true);

    // is_armstrong(9474) returns true.
    assert(is_armstrong(9474) == true);

    // is_armstrong(100) returns false.
    assert(is_armstrong(100) == false);

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
