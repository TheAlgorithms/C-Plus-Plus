/**
 * Copyright 2020 @author tjgurwara99
 * @file
 *
 * A basic implementation of LCM function
 */

#include <cassert>
#include <iostream>

/**
 * Function for finding greatest common divisor of two numbers.
 * @params two integers x and y whose gcd we want to find.
 * @return greatest common divisor of x and y.
 */
unsigned int gcd(unsigned int x, unsigned int y) {
    if (x == 0) {
        return y;
    }
    if (y == 0) {
        return x;
    }
    if (x == y) {
        return x;
    }
    if (x > y) {
        // The following is valid because we have checked whether y == 0

        unsigned int temp = x / y;
        return gcd(y, x - temp * y);
    }
    // Again the following is valid because we have checked whether x == 0

    unsigned int temp = y / x;
    return gcd(x, y - temp * x);
}

/**
 * Function for finding the least common multiple of two numbers.
 * @params integer x and y whose lcm we want to find.
 * @return lcm of x and y using the relation x * y = gcd(x, y) * lcm(x, y)
 */
unsigned int lcm(unsigned int x, unsigned int y) {
  return x / gcd(x, y) * y;
}

/**
 * Function for testing the lcm() functions with some assert statements.
 */
void tests() {
    // First test on lcm(5,10) == 10
    assert(((void)"LCM of 5 and 10 is 10 but lcm function gives a different "
                  "result.\n",
            lcm(5, 10) == 10));
    std::cout << "First assertion passes: LCM of 5 and 10 is " << lcm(5, 10)
              << std::endl;

    // Second test on lcm(2,3) == 6 as 2 and 3 are coprime (prime in fact)
    assert(((void)"LCM of 2 and 3 is 6 but lcm function gives a different "
                  "result.\n",
            lcm(2, 3) == 6));
    std::cout << "Second assertion passes: LCM of 2 and 3 is " << lcm(2, 3)
              << std::endl;

    // Testing an integer overflow.
    // The algorithm should work as long as the result fits into integer.
    assert(((void)"LCM of 987654321 and 987654321 is 987654321 but lcm function"
                  " gives a different result.\n",
            lcm(987654321, 987654321) == 987654321));
    std::cout << "Third assertion passes: LCM of 987654321 and 987654321 is "
              << lcm(987654321, 987654321)
              << std::endl;
}

/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
