/**
 * @file
 * @brief Add one line description here. Should contain a Wikipedia
 * link or another source explaining the algorithm/implementation.
 * @details
 * This function takes an uint64_t and returns the fibonacci of that number. 
 * The Fiboncacci Sequence
 * @author [Robert Shepherd](https://github.com/robertshepherdcpp)
 * @see related_file.cpp, another_file.cpp
 */

#include <cassert>   /// for assert
#include <iostream> /// std::cout

namespace fib
{
/**
 * Just returns fibonacci for the number passed in,
 * for example fibonacci(5) == 5
 * param1 on-line 23 is the fibonacci Fn input.
 * The function returns the fibonacci of the uint64_t passed in.
 */
 constexpr uint64_t fibonacci(uint64_t n)
 {

    /* Add the last 2 values of the sequence to get next */
    return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));

 }
}  // namespace fib

static void test() {
    /* asserts that the result of fibonacci(5) is 5 */
    assert(fib::fibonacci(5) == 5); // 
}

int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    // code here
    return 0;
}
