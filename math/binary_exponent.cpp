/**
 * @file
 * @brief C++ Program to find Binary Exponent and Binary Modular Exponent Iteratively and Recursively.
 *
 * Calculate \f$a^b\f$ in \f$O(\log(b))\f$ by converting \f$b\f$ to a
 * binary number. Binary exponentiation is also known as exponentiation by
 * squaring. Calculating binary exponent modular m is known as modular exponentiation.
 * @note This is a far better approach compared to naive method which
 * provide \f$O(b)\f$ operations.
 *
 * Example:
 * </br>10 in base 2 is 1010.
 * \f{eqnarray*}{
 * 2^{10_d} &=& 2^{1010_b} = 2^8 * 2^2\\
 * 2^1 &=& 2\\
 * 2^2 &=& (2^1)^2 = 2^2 = 4\\
 * 2^4 &=& (2^2)^2 = 4^2 = 16\\
 * 2^8 &=& (2^4)^2 = 16^2 = 256\\
 * \f}
 * Hence to calculate 2^10 we only need to multiply \f$2^8\f$ and \f$2^2\f$
 * skipping \f$2^1\f$ and \f$2^4\f$.
 * 
 * Bitwise Operations Used:
 * a>>1 => is same as a/2.
 * a>>=1 => is same as a = a/2.
 * a&1 => is same as a%2. Checks wether number a is odd or not. Results to 1 i.e. True if a is odd and 0 or False otherwise.
 *
 * Modular Properties
 * ( a * a ) % m = ( a%m * a%m ) % m
 * Using this property of modular aithmetic we can efficiently calculate (a^b)%m. 
 */

#include <iostream>

/// Recursive function to calculate exponent in \f$O(\log(n))\f$ using binary
/// exponent.
uint64_t binExpo(uint64_t a, uint64_t b) {
    if (b == 0) {
        return 1;
    }
    uint64_t res = binExpo(a, b>>1); 
    if (b&1) { // Same as b%2==1. Result to true if b is odd.
        return res * res * a;
    } else {
        return res * res;
    }
}

/// Recursive function to calculate exponent modular m (a^b %m) in \f$O(\log(n))\f$ using 
/// binary exponentiation.
uint64_t binModExpo(uint64_t a, uint64_t b, uint64_t m) {
    if (b == 0) {
        return 1;
    }
    uint64_t res = binExpo(a, b>>1, m) % m;
    if (b&1) {
        return (res * res * a%m ) % m;
    } else {
        return (res * res) % m;
    }
}

/// Iterative function to calculate exponent in \f$O(\log(n))\f$ using binary
/// exponent.
uint64_t binExpo_alt(uint64_t a, uint64_t b) {
    uint64_t res = 1;
    while (b > 0) {
        if (b&2) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}


/// Iterative function to calculate exponent modular m (a^b %m) in \f$O(\log(n))\f$ using
/// binary exponentiation.
uint64_t binModExpo_alt(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;
    a %= m ;
    while (b > 0) {
        if (b&1) {
            res = (res * a) % m ;
        }
        a = (a * a) % m;
        b >>= 1 ;
    }
    return res;
}

/// Main function
int main() {
    uint64_t a, b, m;
    /// Give three numbers a, b, m.
    a = 1234; b = 12345; m = 1000000007;
    if (a == 0 && b == 0) {
        std::cout << "Math error" << std::endl;
    } else if (b < 0) {
        std::cout << "Exponent must be positive !!" << std::endl;
    } else if ( m == 0 ) {
        std::cout << "m cannot be zero." << std::endl;
    } else {
        std::cout << "Result of a^b Recursive : "   << binExpo(a,b)          << std::endl;
        std::cout << "Result of a^b%m Recursive : " << binModExpo(a,b,m)     << std::endl;
        std::cout << "Result of a^b Iterative : "   << binExpo_alt(a,b)      << std::endl;
        std::cout << "Result of a^b%m Iterative : " << binModExpo_alt(a,b,m) << std::endl;
    }
}
