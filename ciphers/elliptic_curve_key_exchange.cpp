/**
 * @file
 * @brief Implementation of [Elliptic Curve Diffie Hellman Key
 * Exchange](https://cryptobook.nakov.com/asymmetric-key-ciphers/ecdh-key-exchange).
 *
 * @details
 * The ECDH (Elliptic Curve Diffie–Hellman Key Exchange) is anonymous key
 * agreement scheme, which allows two parties, each having an elliptic-curve
 * public–private key pair, to establish a shared secret over an insecure
 * channel.
 * ECDH is very similar to the classical DHKE (Diffie–Hellman Key Exchange)
 * algorithm, but it uses ECC point multiplication instead of modular
 * exponentiations. ECDH is based on the following property of EC points:
 * (a * G) * b = (b * G) * a
 * If we have two secret numbers a and b (two private keys, belonging to Alice
 * and Bob) and an ECC elliptic curve with generator point G, we can exchange
 * over an insecure channel the values (a * G) and (b * G) (the public keys of
 * Alice and Bob) and then we can derive a shared secret:
 * secret = (a * G) * b = (b * G) * a.
 * Pretty simple. The above equation takes the following form:
 * alicePubKey * bobPrivKey = bobPubKey * alicePrivKey = secret
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

#include "uint256_t.hpp"  /// for 256-bit integer

/**
 * @namespace ciphers
 * @brief Cipher algorithms
 */
namespace ciphers {
/**
 * @brief namespace elliptic_curve_key_exchange
 * @details Demonstration of [Elliptic Curve
 * Diffie-Hellman](https://cryptobook.nakov.com/asymmetric-key-ciphers/ecdh-key-exchange)
 * key exchange.
 */
namespace elliptic_curve_key_exchange {

/**
 * @brief Definition of struct Point
 * @details Definition of Point in the curve.
 */
typedef struct Point {
    uint256_t x, y;  /// x and y co-ordinates

    /**
     * @brief operator == for Point
     * @details check whether co-ordinates are equal to the given point
     * @param p given point to be checked with this
     * @returns true if x and y are both equal with Point p, else false
     */
    inline bool operator==(const Point &p) { return x == p.x && y == p.y; }

    /**
     * @brief ostream operator for printing Point
     * @param op ostream operator
     * @param p Point to be printed on console
     * @returns op, the ostream object
     */
    friend std::ostream &operator<<(std::ostream &op, const Point &p) {
        op << p.x << " " << p.y;
        return op;
    }
} Point;

/**
 * @brief This function calculates number raised to exponent power under modulo
 * mod using [Modular
 * Exponentiation](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/math/modular_exponentiation.cpp).
 * @param number integer base
 * @param power unsigned integer exponent
 * @param mod integer modulo
 * @return number raised to power modulo mod
 */
uint256_t exp(uint256_t number, uint256_t power, const uint256_t &mod) {
    if (!power) {
        return uint256_t(1);
    }
    uint256_t ans(1);
    number = number % mod;
    while (power) {
        if ((power & 1)) {
            ans = (ans * number) % mod;
        }
        power >>= 1;
        if (power) {
            number = (number * number) % mod;
        }
    }
    return ans;
}

/**
 * @brief Addition of points
 * @details Add given point to generate third point. More description can be
 * found
 * [here](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Point_addition),
 * and
 * [here](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Point_doubling)
 * @param a First point
 * @param b Second point
 * @param curve_a_coeff Coefficient `a` of the given curve (y^2 = x^3 + ax + b)
 * % mod
 * @param mod Given field
 * @return the resultant point
 */
Point addition(Point a, Point b, const uint256_t &curve_a_coeff,
               uint256_t mod) {
    uint256_t lambda(0);  /// Slope
    uint256_t zero(0);    /// value zero
    lambda = zero = 0;
    uint256_t inf = ~zero;
    if (a.x != b.x || a.y != b.y) {
        // Slope being infinite.
        if (b.x == a.x) {
            return {inf, inf};
        }
        uint256_t num = (b.y - a.y + mod), den = (b.x - a.x + mod);
        lambda = (num * (exp(den, mod - 2, mod))) % mod;
    } else {
        /**
         *  slope when the line is tangent to curve. This operation is performed
         * while doubling. Taking derivative of `y^2 = x^3 + ax + b`
         * => `2y dy = (3 * x^2 + a)dx`
         * => `(dy/dx) = (3x^2 + a)/(2y)`
         */
        /**
         * if y co-ordinate is zero, the slope is infinite, return inf.
         * else calculate the slope (here % mod and store in lambda)
         */
        if (!a.y) {
            return {inf, inf};
        }
        uint256_t axsq = ((a.x * a.x)) % mod;
        // Mulitply by 3 adjustment
        axsq += (axsq << 1);
        axsq %= mod;
        // Mulitply by 2 adjustment
        uint256_t a_2 = (a.y << 1);
        lambda =
            (((axsq + curve_a_coeff) % mod) * exp(a_2, mod - 2, mod)) % mod;
    }
    Point c;
    // new point: x = ((lambda^2) - x1 - x2)
    // y = (lambda * (x1 - x)) - y1
    c.x = ((lambda * lambda) % mod + (mod << 1) - a.x - b.x) % mod;
    c.y = (((lambda * (a.x + mod - c.x)) % mod) + mod - a.y) % mod;
    return c;
}

/**
 * @brief multiply Point and integer
 * @details Multiply Point by a scalar factor (here it is a private key p). The
 * multiplication is called as [double and add
 * method](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Double-and-add)
 * @param a Point to multiply
 * @param curve_a_coeff Coefficient of given curve (y^2 = x^3 + ax + b) % mod
 * @param p The scalar value
 * @param mod Given field
 * @returns the resultant point
 */
Point multiply(const Point &a, const uint256_t &curve_a_coeff, uint256_t p,
               const uint256_t &mod) {
    Point N = a;
    N.x %= mod;
    N.y %= mod;
    uint256_t inf{};
    inf = ~uint256_t(0);
    Point Q = {inf, inf};
    while (p) {
        if ((p & 1)) {
            if (Q.x == inf && Q.y == inf) {
                Q.x = N.x;
                Q.y = N.y;
            } else {
                Q = addition(Q, N, curve_a_coeff, mod);
            }
        }
        p >>= 1;
        if (p) {
            N = addition(N, N, curve_a_coeff, mod);
        }
    }
    return Q;
}
}  // namespace elliptic_curve_key_exchange
}  // namespace ciphers

/**
 * @brief Function to test the
 * uint128_t header
 * @returns void
 */
static void uint128_t_tests() {
    // 1st test: Operations test
    uint128_t a("122"), b("2312");
    assert(a + b == 2434);
    assert(b - a == 2190);
    assert(a * b == 282064);
    assert(b / a == 18);
    assert(b % a == 116);
    assert((a & b) == 8);
    assert((a | b) == 2426);
    assert((a ^ b) == 2418);
    assert((a << 64) == uint128_t("2250502776992565297152"));
    assert((b >> 7) == 18);

    // 2nd test: Operations test
    a = uint128_t("12321421424232142122");
    b = uint128_t("23123212");
    assert(a + b == uint128_t("12321421424255265334"));
    assert(a - b == uint128_t("12321421424209018910"));
    assert(a * b == uint128_t("284910839733861759501135864"));
    assert(a / b == 532859423865LL);
    assert(a % b == 3887742);
    assert((a & b) == 18912520);
    assert((a | b) == uint128_t("12321421424236352814"));
    assert((a ^ b) == uint128_t("12321421424217440294"));
    assert((a << 64) == uint128_t("227290107637132170748078080907806769152"));
}

/**
 * @brief Function to test the
 * uint256_t header
 * @returns void
 */
static void uint256_t_tests() {
    // 1st test: Operations test
    uint256_t a("122"), b("2312");
    assert(a + b == 2434);
    assert(b - a == 2190);
    assert(a * b == 282064);
    assert(b / a == 18);
    assert(b % a == 116);
    assert((a & b) == 8);
    assert((a | b) == 2426);
    assert((a ^ b) == 2418);
    assert((a << 64) == uint256_t("2250502776992565297152"));
    assert((b >> 7) == 18);

    // 2nd test: Operations test
    a = uint256_t("12321423124513251424232142122");
    b = uint256_t("23124312431243243215354315132413213212");
    assert(a + b == uint256_t("23124312443564666339867566556645355334"));
    // Since a < b, the value is greater
    assert(a - b == uint256_t("115792089237316195423570985008687907853246860353"
                              "221642219366742944204948568846"));
    assert(a * b == uint256_t("284924437928789743312147393953938013677909398222"
                              "169728183872115864"));
    assert(b / a == uint256_t("1876756621"));
    assert(b % a == uint256_t("2170491202688962563936723450"));
    assert((a & b) == uint256_t("3553901085693256462344"));
    assert((a | b) == uint256_t("23124312443564662785966480863388892990"));
    assert((a ^ b) == uint256_t("23124312443564659232065395170132430646"));
    assert((a << 128) == uint256_t("4192763024643754272961909047609369343091683"
                                   "376561852756163540549632"));
}

/**
 * @brief Function to test the
 * provided algorithm above
 * @returns void
 */
static void test() {
    // demonstration of key exchange using curve secp112r1

    // Equation of the form y^2 = (x^3 + ax + b) % P (here p is mod)
    uint256_t a("4451685225093714772084598273548424"),
        b("2061118396808653202902996166388514"),
        mod("4451685225093714772084598273548427");

    // Generator value: is pre-defined for the given curve
    ciphers::elliptic_curve_key_exchange::Point ptr = {
        uint256_t("188281465057972534892223778713752"),
        uint256_t("3419875491033170827167861896082688")};

    // Shared key generation.
    // For alice
    std::cout << "For alice:\n";
    // Alice's private key (can be generated randomly)
    uint256_t alice_private_key("164330438812053169644452143505618");
    ciphers::elliptic_curve_key_exchange::Point alice_public_key =
        multiply(ptr, a, alice_private_key, mod);
    std::cout << "\tPrivate key: " << alice_private_key << "\n";
    std::cout << "\tPublic Key: " << alice_public_key << std::endl;

    // For Bob
    std::cout << "For Bob:\n";
    // Bob's private key (can be generated randomly)
    uint256_t bob_private_key("1959473333748537081510525763478373");
    ciphers::elliptic_curve_key_exchange::Point bob_public_key =
        multiply(ptr, a, bob_private_key, mod);
    std::cout << "\tPrivate key: " << bob_private_key << "\n";
    std::cout << "\tPublic Key: " << bob_public_key << std::endl;

    // After public key exchange, create a shared key for communication.
    // create shared key:
    ciphers::elliptic_curve_key_exchange::Point alice_shared_key = multiply(
                                                    bob_public_key, a,
                                                    alice_private_key, mod),
                                                bob_shared_key = multiply(
                                                    alice_public_key, a,
                                                    bob_private_key, mod);

    std::cout << "Shared keys:\n";
    std::cout << alice_shared_key << std::endl;
    std::cout << bob_shared_key << std::endl;

    // Check whether shared keys are equal
    assert(alice_shared_key == bob_shared_key);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    uint128_t_tests();  // running predefined 128-bit unsigned integer tests
    uint256_t_tests();  // running predefined 256-bit unsigned integer tests
    test();             // running self-test implementations
    return 0;
}
