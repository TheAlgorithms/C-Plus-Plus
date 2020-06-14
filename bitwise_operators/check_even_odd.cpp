/**
 * Copyright 2020 @author omkarlanghe.
 * 
 * @file
 * A simple program to check if the given number is odd or even without using any arithmetic operator.
 * 
 * @brief
 * The program illustrates the use of bitwise & (AND) operator to check if given number is odd or even.
 * To know more about bitwise operators, refer the given link: https://en.wikipedia.org/wiki/Bitwise_operation#Bitwise_operators
 * 
 * To understand this logic of how bitwise & (AND) check if given number is odd or even, you can take pen and paper
 * and simply write down binary values of a given number and & (AND) it with binary value of 1.
 * 
 * Once, you write the binary of a given number, as per the logic, bitwise & (AND) it with binary of 1 (0001) and check
 * its corresponding binary result. If result of bitwise & (AND)ing is 0, then the number is even else number is odd.
 * 
 *      Eg. Input = 7
 * 
 *      num      binary
 *      7        0 1 1 1
 *      1        0 0 0 1
 *      &        -------
 *               0 0 0 1 = result is not 0, hence it is odd number.
 * 
 *      Eg. Input = 6
 * 
 *      num      binary
 *      7        0 1 1 0
 *      1        0 0 0 1
 *      &        -------
 *               0 0 0 0 = result is 0, hence it is even number.
*/

#include <iostream>
#include <cassert>

/**
 * Function to check if the given number is odd or even.
 * @param num number to be checked.
 * @return if number is even, it returns @ true, else it returns @ false.
*/
template<typename T>
bool is_odd_even(T num) {
    if ((num & 1) == 0) {
        return (true);
    }
    return (false);
}

/**
 * Main function
*/
int main() {
    int num;
    std::cout << "Enter the number to check for even or odd : " <<
    std::endl;
    std::cin >> num;

    bool result = is_odd_even(num);

    if (result) {
        std::cout << "The given number " << num << " is even." <<
        std::endl;
    } else {
        std::cout << "The given number " << num << " is odd." <<
        std::endl;
    }

    assert(is_odd_even(4) == true);
    assert(is_odd_even(7) == false);
}
