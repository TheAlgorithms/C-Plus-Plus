/**
 * @file
 * @brief Faster computation of Fibonacci series.
 *
 * @details
 * An efficient way to calculate nth fibonacci number faster and simpler than
 * \f$O(n\log n)\f$ method of matrix exponentiation. This works by using both
 * recursion and dynamic programming. As 93rd fibonacci exceeds 19 digits, which
 * cannot be stored in a single long long variable, we can only use it till 92nd
 * fibonacci we can use it for 10000th fibonacci etc, if we implement
 * bigintegers. This algorithm works with the fact that nth fibonacci can easily
 * found if we have already found \f$n/2\f$th or \f$(n+1)/2\f$th fibonacci. It is a property
 * of fibonacci similar to matrix exponentiation.
 *
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @see fibonacci_large.cpp, fibonacci.cpp, string_fibonacci.cpp
 */
#include <cinttypes>  /// for uint64_t
#include <cstdio>     /// for standard IO
#include <iostream>   /// for IO operations
#include <cassert>    /// for assert
#include <string>     /// for std::to_string
#include <stdexcept>  /// for std::invalid_argument

/**
 * @brief Maximum Fibonacci number that can be computed
 *
 * @details
 * The result after 93 cannot be stored in a `uint64_t` data type.
 */
constexpr uint64_t MAX = 93;

/**
 * @brief Function to compute the nth Fibonacci number
 * @param n The index of the Fibonacci number to compute
 * @return uint64_t The nth Fibonacci number
 */
uint64_t fib(uint64_t n) {
    // Using static keyword will retain the values of
    // f1 and f2 for the next function call.
    static uint64_t f1 = 1, f2 = 1;

    if (n <= 2) {
        return f2;
    } if (n >= MAX) {
        throw std::invalid_argument("Cannot compute for n>=" + std::to_string(MAX) +
                                    " due to limit of 64-bit integers");
        return 0;
    }
    
    // We do not need temp to be static.
    uint64_t temp = f2;  
    f2 += f1;
    f1 = temp;

    return f2;
}

/**
 * @brief Function to test the Fibonacci computation
 * @returns void
 */
static void test() {
    // Test for valid Fibonacci numbers
    assert(fib(1) == 1);
    assert(fib(2) == 1);
    assert(fib(3) == 2);
    assert(fib(4) == 3);
    assert(fib(5) == 5);
    assert(fib(6) == 8);
    assert(fib(7) == 13);
    assert(fib(8) == 21);
    assert(fib(9) == 34);
    assert(fib(10) == 55);
    assert(fib(11) == 89);
    assert(fib(12) == 144);
    assert(fib(13) == 233);
    assert(fib(14) == 377);
    assert(fib(15) == 610);
    assert(fib(16) == 987);
    assert(fib(17) == 1597);
    assert(fib(18) == 2584);
    assert(fib(19) == 4181);
    assert(fib(20) == 6765);
    assert(fib(21) == 10946);
    assert(fib(22) == 17711);
    assert(fib(23) == 28657);
    assert(fib(24) == 46368);
    assert(fib(25) == 75025);
    assert(fib(26) == 121393);
    assert(fib(27) == 196418);
    assert(fib(28) == 317811);
    assert(fib(29) == 514229);
    assert(fib(30) == 832040);
    assert(fib(31) == 1346269);
    assert(fib(32) == 2178309);
    assert(fib(33) == 3524578);
    assert(fib(34) == 5702887);
    assert(fib(35) == 9227465);
    assert(fib(36) == 14930352);
    assert(fib(37) == 24157817);
    assert(fib(38) == 39088169);
    assert(fib(39) == 63245986);
    assert(fib(40) == 102334155);
    assert(fib(41) == 165580141);
    assert(fib(42) == 267914296);
    assert(fib(43) == 433494437);
    assert(fib(44) == 701408733);
    assert(fib(45) == 1134903170);
    assert(fib(46) == 1836311903);
    assert(fib(47) == 2971215073);
    assert(fib(48) == 4807526976);
    assert(fib(49) == 7778742049);
    assert(fib(50) == 12586269025);
    assert(fib(51) == 20365011074);
    assert(fib(52) == 32951280099);
    assert(fib(53) == 53316291173);
    assert(fib(54) == 86267571272);
    assert(fib(55) == 139583862445);
    assert(fib(56) == 225851433717);
    assert(fib(57) == 365435296162);
    assert(fib(58) == 591286729879);
    assert(fib(59) == 956722026041);
    assert(fib(60) == 1548008755920);
    assert(fib(61) == 2504730781961);
    assert(fib(62) == 4052739537881);
    assert(fib(63) == 6557470319842);
    assert(fib(64) == 10610209857723);
    assert(fib(65) == 17167680177565);
    assert(fib(66) == 27777890035288);
    assert(fib(67) == 44945570212853);
    assert(fib(68) == 72723460248141);
    assert(fib(69) == 117669030460994);
    assert(fib(70) == 190392490709135);
    assert(fib(71) == 308061521170129);
    assert(fib(72) == 498454011879264);
    assert(fib(73) == 806515533049393);
    assert(fib(74) == 1304969544928657);
    assert(fib(75) == 2111485077978050);
    assert(fib(76) == 3416454622906707);
    assert(fib(77) == 5527939700884757);
    assert(fib(78) == 8944394323791464);
    assert(fib(79) == 14472334024676221);
    assert(fib(80) == 23416728348467685);
    assert(fib(81) == 37889062373143906);
    assert(fib(82) == 61305790721611591);
    assert(fib(83) == 99194853094755497);
    assert(fib(84) == 160500643816367088);
    assert(fib(85) == 259695496911122585);
    assert(fib(86) == 420196140727489673);
    assert(fib(87) == 679891637638612258);
    assert(fib(88) == 1100087778366101931);
    assert(fib(89) == 1779979416004714189);
    assert(fib(90) == 2880067194370816120);
    assert(fib(91) == 4660046610375530309);
    assert(fib(92) == 7540113804746346429);

    // Test for invalid Fibonacci numbers
    try {
        fib(MAX + 1);
        assert(false && "Expected an invalid_argument exception to be thrown");
    } catch (const std::invalid_argument& e) {
        const std::string expected_message = "Cannot compute for n>=" + std::to_string(MAX) +
                                             " due to limit of 64-bit integers";
        assert(e.what() == expected_message);
    }

    std::cout << "All Fibonacci tests have successfully passed!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
