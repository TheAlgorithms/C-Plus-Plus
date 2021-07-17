/**
 * @file
 * @brief Implementation of [nth Fibonacci problem](https://medium.com/@andrewsouthard1/dynamic-programming-recursion-memoization-and-bottom-up-algorithms-61c882d1c7e) using memoization
 * @details
 * nth Fibonacci number using memoization is used as a dynamic programming concept that
 * works in \f$O(n)\f$ time and works in \f$O(n)\f$ space.
 * Other solution is bottom up approach which uses \f$O(1)\f$ space. 
 * @author [Pradyumna Yadav](https://github.com/pradyyadav)
 */

#include <cassert>            /// for assert
#include <iostream>          /// for io operations
#include <unordered_map>    /// for std::unordered_map

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
 * @brief The function that implements the nth Fibonacci number problem using
 * memoization
 * @param n The index of the number in a fibonacci series.
 * @param map_elements A map that contains previously encountered index-value pair.
 * @returns Element at the nth position in the Fibonacci series.
 */
uint32_t nthFibonacci(int n, auto &map_elements)
{
    if (n <= 1)  // The numbers at index 0 and 1 are also 0 and 1.
        return n;
    if(map_elements.find(n) == map_elements.end())  // If the element with key: n is not present, find() returns the last element.
    {
        map_elements.insert({n, (nthFibonacci(n-1, map_elements) + nthFibonacci(n-2,map_elements))});
    }
    return map_elements.at(n);
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
    std::unordered_map<int,uint32_t> map_elements1;
    std::cout << "Test 1... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num1, map_elements1) == 13); // 7th fibonacci number is 13.
    std::cout<< "passed" << std::endl;


    // Test 2
    // 45 return 1134903170.
    int num2 = 45;
    std::unordered_map<int,uint32_t> map_elements2;
    std::cout << "Test 2... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num2, map_elements2) == 1134903170); // 45th fibonacci number is 1134903170.
    std::cout<< "passed" << std::endl;

    // Test 3
    // 15 return 610.
    int num3 = 15;
    std::unordered_map<int,uint32_t> map_elements3;
    std::cout << "Test 3... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num3, map_elements3) == 610); // 15th fibonacci number is 610.
    std::cout<< "passed" << std::endl;

    // Test 4
    // 31 return 1346269.
    int num4 = 31;
    std::unordered_map<int,uint32_t> map_elements4;
    std::cout << "Test 4... ";
    assert(dynamic_programming::fibonacci_memoization::nthFibonacci(num4, map_elements4) ==  1346269); // 31th fibonacci number is 1346269.
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
