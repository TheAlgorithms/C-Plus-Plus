/**
 * Copyright 2020 @author iamnambiar
 * 
 * @file
 * A C++ Program to check whether a pair of number is amicable pair or not.
 * 
 * \brief
 * Amicable Pair are two different numbers such that sum of the proper divisor 
 * of each number is equal to the other number.
 *  
 * Wikipedia link for Reference: https://en.wikipedia.org/wiki/Amicable_numbers 
 */
#include <iostream>
#include <cassert>
#include <math.h>

/**
 * Function to calculate the sum of all the proper divisor 
 * of an integer.
 * @param num First number.
 * @return Sum of the proper divisor of the number.
 */
int sum_of_divisor(int num) {
    // Variable to store the sum of all proper divisors.
    int sum = 0;
    for(int div = 2; div <= sqrt(num); ++div) {
        // Check 'div' is divisor of 'num'.
        if(num % div == 0) {
            // If both divisor are same, add once to 'sum'
            if(div == (num/div)) {
                sum += div;
            }
            // If both divisor are not the same, add both to 'sum'.
            else {
                sum += (div + (num/div));
            }
        }
    }
    return sum + 1;
}

/**
 * Function to check whether the pair is amicable or not.
 * @param x First number.
 * @param y Second number.
 * @return true, if the pair is amicable. false, if the pair
 * is not amicable.
 */
bool is_amicable(int x, int y) {
    if(sum_of_divisor(x) != y) {
        return false;
    }
    return (sum_of_divisor(y) == x);
}

/**
 * Function for testing the is_amicable() function with a
 * first test case of (220, 284) and assert statement.
 * (220, 284) is an amicable pair.
 */
void test1() {
    // is_amicable(220, 284) returns true.
    assert(is_amicable(220, 284) == true);
}

/**
 * Function for testing the is_amicable() function with a
 * test case of (6232, 6368) and assert statement.
 * (6232, 6368) is an amicable pair.
 */
void test2() {
    // is_amicable(6232, 6368) returns true.
    assert(is_amicable(6368, 6232) == true);
}

/**
 * Function for testing the is_amicable() function with a
 * test case of (458, 232) and assert statement.
 * (458, 232) is not an amicable pair.
 */
void test3() {
    // is_amicable(458, 232) returns false.
    assert(is_amicable(458, 232) == false);
}

/**
 * Function for testing the is_amicable() with 
 * all the test cases.
 */
void test() {
    test1();
    test2();
    test3();
}

/**
 * Main Function
*/
int main() {
    test();
    std::cout << "Assertion Success." << std::endl;
    return 0;
}
