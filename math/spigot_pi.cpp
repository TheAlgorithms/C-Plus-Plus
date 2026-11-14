/**
 * @file
 * @brief
 * Generate decimal digits of Pi with integer arithmetic.
 *
 * @details
 * Uses the [Rabinowitz–Wagon spigot
 * algorithm](https://en.wikipedia.org/wiki/Spigot_algorithm) to produce digits
 * sequentially without floating-point arithmetic.
 *
 * @author [AlexDev](https://github.com/alexdev8930)
 * @date 20 September 2026
 */

#include <cassert>   /// for assert
#include <cstddef>   /// for std::size_t
#include <iostream>  /// for std::cout
#include <string>    /// for std::string
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Helper to append digits safely to the output string with a decimal
 * point inserted after the leading `'3'`.
 * @param output string receiving the generated digits
 * @param max_len maximum total length including the decimal point
 * @param c digit character to append
 */
static void append_char(std::string &output, std::size_t max_len, char c) {
    if (output.size() < max_len) {
        if (output.size() == 1) {
            output.push_back('.');
        }
        output.push_back(c);
    }
}

/**
 * @brief Generate decimal digits of Pi into a std::string using the
 * Rabinowitz–Wagon spigot algorithm.
 * @param pi_digits number of fractional digits of Pi to generate after `"3."`
 * @return A std::string formatted as `"3.14159..."` of length `pi_digits + 2`
 */
std::string generate_pi(std::size_t pi_digits = 42) {
    const std::size_t array_size = (10 * pi_digits) / 3 + 1;
    const std::size_t max_len = pi_digits + 2;  // '3' + '.' + pi_digits

    // Each array cell stores a remainder initialized to 2.
    std::vector<int> remainder(array_size, 2);
    std::string output;
    output.reserve(max_len);

    int predigit = 0;
    int nines = 0;

    for (std::size_t digit = 0; digit < pi_digits + 2; ++digit) {
        int carry = 0;

        // Process the remainder array from right to left.
        for (std::size_t index = array_size; index > 0; --index) {
            const int idx_int = static_cast<int>(index);
            const int value = 10 * remainder[index - 1] + carry * idx_int;

            remainder[index - 1] = value % (2 * idx_int - 1);
            carry = value / (2 * idx_int - 1);
        }

        remainder[0] = carry % 10;
        const int next_digit = carry / 10;

        // Store the first digit (3) as predigit without appending it yet.
        if (digit == 0) {
            predigit = next_digit;
            continue;
        }

        if (next_digit == 9) {
            ++nines;
        } else if (next_digit == 10) {
            // A carry changes the previous digit and pending 9s become 0s.
            append_char(output, max_len, static_cast<char>('0' + predigit + 1));

            while (nines > 0) {
                append_char(output, max_len, '0');
                --nines;
            }

            predigit = 0;
        } else {
            // The previous digit is now safe to append.
            append_char(output, max_len, static_cast<char>('0' + predigit));

            predigit = next_digit;

            while (nines > 0) {
                append_char(output, max_len, '9');
                --nines;
            }
        }
    }

    // Append the final delayed digit.
    append_char(output, max_len, static_cast<char>('0' + predigit));
    return output;
}
}  // namespace math

/**
 * @brief Run automated tests to verify the correctness of the Pi generator.
 * @returns void
 */
static void tests() {
    const std::string output = math::generate_pi(42);
    const std::string expected = "3.141592653589793238462643383279502884197169";

    assert(output.size() == 44);
    assert(output.substr(0, 7) == "3.14159");
    assert(output == expected);

    std::cout << "Success: tests passed.\n";
    std::cout << "Result: " << output << '\n';
}

/**
 * @brief Program entry point.
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}