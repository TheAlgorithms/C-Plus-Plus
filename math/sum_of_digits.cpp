/**
 * Copyright 2020 @author iamnambiar
 * 
 * @file
 * A C++ Program to find the Sum of Digits of input integer.
 */
#include <iostream>
#include <cassert>

/**
 * Function to find the sum of the digits of an integer.
 * @param num The integer.
 * @return Sum of the digits of the integer.
 */
int sum_of_digits(int num) {
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
 * Test function.
 */
void test() {
    int test_case_1 = sum_of_digits(119765);
    int test_case_2 = sum_of_digits(-12256);
    assert(test_case_1 == 29);
    assert(test_case_2 == 16);
    }

int main() {
    test();
    std::cout << "Success.";
    return 0;
}
