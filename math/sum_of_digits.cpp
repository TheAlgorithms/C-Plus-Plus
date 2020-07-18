/**
 * Copyright 2020 @author iamnambiar
 *
 * @file
 * \brief A C++ Program to find the Sum of Digits of input integer.
 */
#include <cassert>
#include <iostream>

/**
 * Function to find the sum of the digits of an integer.
 * @param num The integer.
 * @return Sum of the digits of the integer.
 *
 * \detail
 * First the algorithm check whether the num is negative or positive,
 * if it is negative, then we neglect the negative sign.
 * Next, the algorithm extract the last digit of num by dividing by 10
 * and extracting the remainder and this is added to the sum.
 * The number is then divided by 10 to remove the last digit.
 * This loop continues until num becomes 0.
 */
int sum_of_digits(int num) {
    // If num is negative then negative sign is neglected.
    if (num < 0) {
        num = -1 * num;
    }
    int sum = 0;
    while (num > 0) {
        sum = sum + (num % 10);
        num = num / 10;
    }
    return sum;
}

/**
 * Function for testing the sum_of_digits() function with a
 * first test case of 119765 and assert statement.
 */
void test1() {
    int test_case_1 = sum_of_digits(119765);
    assert(test_case_1 == 29);
}

/**
 * Function for testing the sum_of_digits() function with a
 * second test case of -12256 and assert statement.
 */
void test2() {
    int test_case_2 = sum_of_digits(-12256);
    assert(test_case_2 == 16);
}

/**
 * Function for testing the sum_of_digits() with
 * all the test cases.
 */
void test() {
    // First test.
    test1();
    // Second test.
    test2();
}

/**
 * Main Function
 */
int main() {
    test();
    std::cout << "Success." << std::endl;
    return 0;
}
