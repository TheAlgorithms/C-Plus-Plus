/**
 * @file
 * @brief Validates a given number using the Luhn Algorithm.
 * @details
 * Luhn Algorithm [Luhn Algorithm](https://wikipedia.org/wiki/Luhn_algorithm)
 * The Luhn algorithm or Luhn formula, also known as the "modulus 10" or
 * "mod 10" algorithm, is a simple checksum formula used to validate a
 * variety of identification numbers, such as credit card numbers,
 * IMEI numbers etc.
 *
 * Steps to validate a number with a check digit:
 * 1. From the rightmost digit (excluding the check digit) and moving left,
 *    double the value of every second digit. The check digit is neither
 *    doubled nor included in this calculation; the first digit doubled is
 *    the digit located immediately left of the check digit. If the result
 *    of this doubling operation is greater than 9 (e.g., 8 × 2 = 16),
 *    then add the digits of the result (e.g., 16: 1 + 6 = 7, 18: 1 + 8 = 9)
 *    or, alternatively, the same final result can be found by subtracting 9
 *    from that result (e.g., 16: 16 − 9 = 7, 18: 18 − 9 = 9).
 * 2. Take the sum of all the digits (including the check digit).
 * 3. If the total modulo 10 is equal to 0 (if the total ends in zero) then
 *    the number is valid according to the Luhn formula; otherwise it is not
 *    valid.
 *
 * @author [Jasir Zaeem](https://github.com/JasirZaeem)
 * @note
 * The code can be written in a faster executing way. But, this particular
 * implementation is written for readability and understandability.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

bool luhn(std::string const& cardNumber) {
    std::vector<int> digits;

    // Number of digits except the checksum at the end.
    int numberOfDigits = cardNumber.length() - 1;

    // Checksum digit
    int checksum = cardNumber.back() - '0';

    // Sum of digits.
    int digitSum = checksum;

    // Convert digit characters to integers, excluding the check digit.
    for (int i = 0; i < numberOfDigits; i++) {
        digits.push_back(cardNumber[i] - '0');
    }

    // Iterate over all digits starting from the right
    // other than the checksum (rightmost digit).
    for (int i = numberOfDigits - 1; i >= 0; i--) {
        int digit = digits[i];

        // If digit is an odd position, double it.
        if (!(i % 2)) {
            digit *= 2;

            // If doubled digit is greater than 10 add its digits
            // (same result as subtracting 9 from it).
            if (digit > 9) {
                digit -= 9;
            }
        }
        digitSum += digit;
    }

    // Check that sum of digits and checksum modulus 10 is not 0
    // Which would mean that the entered number is invalid
    if (digitSum % 10) {
        return false;
    } else {
        return true;
    }
}

void test() {
    std::string num1 = "79927398714";
    std::string num2 = "79927398713";
    std::string num3 = "12345674";

    assert(luhn("79927398714") == true);
    assert(luhn("79927398713") == false);
    assert(luhn("12345674") == true);

    std::cout << num1 << " is valid" << std::endl;
    std::cout << num2 << " is invalid" << std::endl;
    std::cout << num3 << " is valid" << std::endl;

    std::cout << "Tests Passed!";
}

int main() {
    test();
    return 0;
}