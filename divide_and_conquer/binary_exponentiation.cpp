/**
 * @file
 * @brief Implementation of Binary Exponentiation
 * @details
 * Binary Exponentiation is a way to calculate exponential
 * calculations using much less time complexity (O(logn))
 * using a divide and conquer technique through recursion.
 * [https://cp-algorithms.com/algebra/binary-exp.html]
 * @author [Timothy Chiles](https://github.com/TSChiles)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations

/**
 * @namespace divide_and_conquer
 */
namespace divide_and_conquer {

/**
 * @brief Function documentation
 * @param param1 is the base number
 * @param param2 is the exponent
 * @returns the base to the exponent operation
 */
    long long expo(long long param1, long long param2) {
        if (!param2){
            return 1;
        }
        //recursion until reaching 0
        long long sol = expo(param1, param2/2);
        //if odd, multiply by base again
        if(param2%2){
            return sol*sol*param1;
        }
        else{
            return sol*sol;
        }
    }
} // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* test 1 */
    std::cout << "TEST 1: ";
    long long test1a = 3;
    long long test1b =  4;
    assert(divide_and_conquer::expo(test1a, test1b) == 81); // this ensures that the algorithm works as expected
    std::cout << "passed" << std::endl;

    /* test 2 */
    std::cout << "TEST 2: ";
    long long test2a = 3;
    long long test2b =  8;
    assert(divide_and_conquer::expo(test2a, test2b) == 6561);
    std::cout << "passed" << std::endl;

    /* test 3 */
    std::cout << "TEST 3: ";
    long long test3a = 5;
    long long test3b =  4;
    assert(divide_and_conquer::expo(test3a, test3b) == 625);
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}