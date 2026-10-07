/**
 * @file
 * @brief C++ Program to find the modular inverse using [Fermat's Little
 * Theorem](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
 *
 * Fermat's Little Theorem state that \f[ϕ(m) = m-1\f]
 * where \f$m\f$ is a prime number.
 * \f{eqnarray*}{
 *  a \cdot x &≡& 1 \;\text{mod}\; m\\
 *  x &≡& a^{-1} \;\text{mod}\; m
 * \f}
 * Using Euler's theorem we can modify the equation.
 *\f[
 * a^{ϕ(m)} ≡ 1 \;\text{mod}\; m
 * \f]
 * (Where '^' denotes the exponent operator)
 *
 * Here 'ϕ' is Euler's Totient Function. For modular inverse existence 'a' and
 * 'm' must be relatively primes numbers. To apply Fermat's Little Theorem is
 * necessary that 'm' must be a prime number. Generally in many competitive
 * programming competitions 'm' is either 1000000007 (1e9+7) or 998244353.
 *
 * We considered m as large prime (1e9+7).
 * \f$a^{ϕ(m)} ≡ 1 \;\text{mod}\; m\f$ (Using Euler's Theorem)
 * \f$ϕ(m) = m-1\f$ using Fermat's Little Theorem.
 * \f$a^{m-1} ≡ 1 \;\text{mod}\; m\f$
 * Now multiplying both side by \f$a^{-1}\f$.
 * \f{eqnarray*}{
 * a^{m-1} \cdot a^{-1} &≡& a^{-1} \;\text{mod}\; m\\
 * a^{m-2} &≡&  a^{-1} \;\text{mod}\; m
 * \f}
 *
 * We will find the exponent using binary exponentiation such that the
 * algorithm works in \f$O(\log n)\f$ time.
 *
 * Examples: -
 * * a = 3 and m = 7
 * * \f$a^{-1} \;\text{mod}\; m\f$ is equivalent to
 * \f$a^{m-2} \;\text{mod}\; m\f$
 * * \f$3^5 \;\text{mod}\; 7 = 243 \;\text{mod}\; 7 = 5\f$
 * <br/>Hence, \f$3^{-1} \;\text{mod}\; 7 = 5\f$
 * or \f$3 \times 5  \;\text{mod}\; 7 = 1 \;\text{mod}\; 7\f$
 * (as \f$a\times a^{-1} = 1\f$)
 */

#include <cassert>  /// for assert
#include <cstdint>  /// for std::int64_t
#include <iostream> /// for IO implementations

/**
 * @namespace math
 * @brief Maths algorithms.
 */
namespace math {
/**
 * @namespace modular_inverse_fermat
 * @brief Calculate modular inverse using Fermat's Little Theorem.
 */
namespace modular_inverse_fermat {
/**
 * @brief Calculate exponent with modulo using binary exponentiation in \f$O(\log b)\f$ time.
 * @param a The base
 * @param b The exponent
 * @param m The modulo
 * @return The result of \f$a^{b} % m\f$
 */
std::int64_t binExpo(std::int64_t a, std::int64_t b, std::int64_t m) {
  a %= m;
  std::int64_t res = 1;
  while (b > 0) {
    if (b % 2 != 0) {
      res = res * a % m;
    }
    a = a * a % m;
    // Dividing b by 2 is similar to right shift by 1 bit
    b >>= 1;
  }
  return res;
}
/**
 * @brief Check if an integer is a prime number in \f$O(\sqrt{m})\f$ time.
 * @param m An intger to check for primality
 * @return true if the number is prime
 * @return false if the number is not prime
 */
bool isPrime(std::int64_t m) {
  if (m <= 1) {
    return false;
  } 
  for (std::int64_t i = 2; i * i <= m; i++) {
    if (m % i == 0) {
      return false;
    }
  }
  return true;
}
/**
 * @brief calculates the modular inverse.
 * @param a Integer value for the base
 * @param m Integer value for modulo
 * @return The result that is the modular inverse of a modulo m
 */
std::int64_t modular_inverse(std::int64_t a, std::int64_t m) {
  while (a < 0) {
    a += m;
  }

  // Check for invalid cases
  if (!isPrime(m) || a == 0) {
    return -1; // Invalid input
  }

  return binExpo(a, m - 2, m);  // Fermat's Little Theorem
}
} // namespace modular_inverse_fermat
} // namespace math

/**
 * @brief Self-test implementation
 * @return void
 */
static void test() {
  assert(math::modular_inverse_fermat::modular_inverse(0, 97) == -1);
  assert(math::modular_inverse_fermat::modular_inverse(15, -2) == -1);
  assert(math::modular_inverse_fermat::modular_inverse(3, 10) == -1);
  assert(math::modular_inverse_fermat::modular_inverse(3, 7) == 5);
  assert(math::modular_inverse_fermat::modular_inverse(1, 101) == 1);
  assert(math::modular_inverse_fermat::modular_inverse(-1337, 285179) == 165519);
  assert(math::modular_inverse_fermat::modular_inverse(123456789, 998244353) == 25170271);
  assert(math::modular_inverse_fermat::modular_inverse(-9876543210, 1000000007) == 784794281);
}

/**
 * @brief Main function
 * @return 0 on exit
 */
int main() {
  test();  // run self-test implementation
  return 0;
}
