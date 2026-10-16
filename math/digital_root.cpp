/**
 * @file
 * @brief Calculates the digital root of a non-negative integer.
 */
#include <cassert>
#include <iostream>

/**
 * Calculates the digital root of a non-negative integer.
 *
 * The digital root is the single-digit value obtained by repeatedly summing
 * the decimal digits of the number. For positive values, it can be calculated
 * directly using the number's remainder modulo 9.
 *
 * @param number A non-negative integer.
 * @return The digital root, in the range [0, 9].
 */
int digital_root(unsigned long long number) {
    return number == 0 ? 0 : 1 + static_cast<int>((number - 1) % 9);
}

/**
 * Runs assertions covering zero, single-digit values, and multi-digit values.
 */
void test_digital_root() {
    assert(digital_root(0) == 0);
    assert(digital_root(7) == 7);
    assert(digital_root(10) == 1);
    assert(digital_root(38) == 2);  // 3 + 8 = 11, then 1 + 1 = 2.
    assert(digital_root(999999999ULL) == 9);
}

/**
 * Runs the self-tests and reports success.
 *
 * @return 0 when all assertions pass.
 */
int main() {
    test_digital_root();
    std::cout << "Success." << std::endl;
    return 0;
}
