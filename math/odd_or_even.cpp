/**
 * @file
 * \brief Program to check if a number is an odd or even number.
 *
 * \details
 * if a number is odd its remainder when divided by 2 is not zero. if the remainder is zero,
 * then it is an even number
 * @author nathalieleave
 */
#include <cassert>
#include <cmath>
#include <iostream>

/**
 * Function to calculate if a given number is even or odd
 * @param num Number
 * @return string "even" or "odd"
 */
string odd_or_even(int num) {
    if(num % 2 == 0) {
        return "even";
    }
    else {
        return "odd";
    }
}

/**
 * Function for testing the odd_or_even() function
 * with all the test cases.
 */
void test() {
    // odd_or_even(370) returns even
    assert(odd_or_even(370) == "even");
    // odd_or_even(371) returns odd
    assert(odd_or_even(371) == "odd");
    // odd_or_even(0) returns even
    assert(odd_or_even(0) == "even");
    // odd_or_even(1) returns odd
    assert(odd_or_even(1) == "odd");
    // odd_or_even(2) returns even
    assert(odd_or_even(2) == "even");
    // odd_or_even(4682327463) returns odd
    assert(odd_or_even(4682327463) == "odd");
}

/**
 * Main Function
 */
int main() {
    test();
    return 0;
}