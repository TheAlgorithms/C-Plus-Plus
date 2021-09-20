/**
 * @file
 * @brief Implementation of [nth Fibonacci problem](https://medium.com/@andrewsouthard1/dynamic-programming-recursion-memoization-and-bottom-up-algorithms-61c882d1c7e)
 * using memoization
 * @details
 * nth Fibonacci number using memoization is used as a dynamic programming concept that
 * works in \f$O(n)\f$ time and works in \f$O(n)\f$ space.
 * Other solution is bottom up approach which uses \f$O(1)\f$ space. 
 * @author [Pradyumna Yadav](https://github.com/pradyyadav)
 */

#include <cassert>            /// for assert
#include <iostream>          /// for io operations
#include <cstring>           /// for memset

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace fibonacci_memoization
 * @brief Functions for the [nth Fibonacci](https://medium.com/@andrewsouthard1/dynamic-programming-recursion-memoization-and-bottom-up-algorithms-61c882d1c7e) using memoization implementation
 */
namespace fibonacci_memoization {
/**
 * @brief The function that implements the nth Fibonacci number problem using memoization.
 * @param n The index of the number in a Fibonacci series.
 * @param term The array which holds the ith fibonacci number at ith index.
 * @returns Element at the nth position in the Fibonacci series.
 */
uint32_t nthFibonacci(int n, int term[])
{
    if(n<=1)
    {
        return n;
    }
    if(term[n] != -1)
    {
        return term[n];
    }
    return term[n] = nthFibonacci(n-1,term) + nthFibonacci(n-2,term);
}
}  // namespace fibonacci_memoization
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    // 7 return 13.
    int num1 = 7;
    int term1[num1+1];\
    memset(term1,-1,sizeof(term1));
    std::cout << "Test 1... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num1, term1) == 13); // 7th fibonacci number is 13.
    std::cout<< "passed" << std::endl;


    // 2nd test
    // 45 return 1134903170.
    int num2 = 45;
    int term2[num2+1];
    memset(term2,-1,sizeof(term2));
    std::cout << "Test 2... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num2, term2) == 1134903170); // 45th fibonacci number is 1134903170.
    std::cout<< "passed" << std::endl;

    // 3rd test
    // 15 return 610.
    int num3 = 15;
    int term3[num3+1];
    memset(term3,-1,sizeof(term3));
    std::cout << "Test 3... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num3, term3) == 610); // 15th fibonacci number is 610.
    std::cout<< "passed" << std::endl;

    // 4th test
    // 31 return 1346269.
    int num4 = 31;
    int term4[num4 + 1] = {0};
    memset(term4,-1,sizeof(term4));
    std::cout << "Test 4... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num4, term4) ==  1346269); // 31th fibonacci number is 1346269.
    std::cout<< "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
