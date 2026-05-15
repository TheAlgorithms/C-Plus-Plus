/**
 * @file
 * @brief 
 * A simple programa to check if the given number 'n' can be represented as
 * a^x + y*b
 *
 * @details
 * To check whether 'n' can be represented as a^x + y*b for some integer x,y
 * a^x + y*b = n
 * iterate over all possible powers of 'a' such that it doesnt exceed 'n'
 * check the remaining result; y*b = n - a^x
 * if there exist a integer y ((n-a^x)%b == 0) -> true, else -> no
 * 
 * Reference: [Codeforces](https://codeforces.com/contest/1542/problem/B)
 * 
 * @author [Rudraksh Tank](https://github.com/rudrakshtank)
 */

#include <iostream> /// for IO operations
#include <cmath> /// for std::pow
#include <cassert> /// for assert
#include <cstdint>

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Verifies if the given n
 * can be represented in terms of a^x + y*b 
 * n = a^x + y*b
 * @param n the number to check if its representable 
 * @param a the base whose powers are used in the representation
 * @param b the multiple factor used in the linear term
 * @return false if not representable
 * @return true if representable 
 */

bool is_representable(const uint64_t &n, const uint64_t &a, const uint64_t &b){
    /// if any number is negative -> no
    /// in this case we are assuming 'n' as positive
    if(n<=0 || a<0 || b<0){
        return false;
    }

    /// iterate through powers of a until a^x <= n

    for(uint64_t x=0;std::pow(a,x)<=n;x++){
        uint64_t power=std::pow(a,x); // a^x term
        uint64_t remaining=n-power; // remaing term; y*b

        /// check if there exist a multiple of b; y
        if(remaining%b==0){
            return true;
        }
    }
    return false;
}
} //namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // is_representable(24, 3, 5) returns true.
    assert(is_representable(24, 3, 5) == true);
    // is_representable(10, 3, 6) returns false.
    assert(is_representable(10, 3, 6) == false);
    // is_representable(2345, 1, 4) returns true.
    assert(is_representable(2345, 1, 4) == true);
    // is_representable(-15, 2, 3) returns false.
    assert(is_representable(-15, 2, 3) == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
