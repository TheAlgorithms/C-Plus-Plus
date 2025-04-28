/**
 * Copyright 2025 @author princesharma2004
 *
 * @file
 * \brief A C++ Program to swap two numbers using reference variables.
 */
#include <cassert>
#include <iostream>

/**
 * Function to swap two numbers using reference variables.
 * @param a First number.
 * @param b Second number.
 *
 * \detail
 * The algorithm uses a temporary variable to store the value of a,
 * then assigns the value of b to a, and finally assigns the value
 * stored in the temporary variable to b.
 */
void swap_two_numbers(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

/**
 * Function for testing the swap_two_numbers() function with a
 * first test case of 5 and 10 and assert statement.
 */
void test1()
{
    int a = 5, b = 10;
    swap_two_numbers(a, b);
    assert(a == 10 && b == 5);
}

/**
 * Function for testing the swap_two_numbers() function with a
 * second test case of -5 and 10 and assert statement.
 */
void test2()
{
    int a = -5, b = 10;
    swap_two_numbers(a, b);
    assert(a == 10 && b == -5);
}

/**
 * Function for testing the swap_two_numbers() with
 * all the test cases.
 */
void test()
{
    // First test.
    test1();
    // Second test.
    test2();
}

/**
 * Main Function
 */
int main()
{
    test();
    std::cout << "Success." << std::endl;
    return 0;
}
