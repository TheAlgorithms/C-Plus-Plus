/**
 * @file
 * @brief This program finds the Carmichael numbers between two bounds.
 * @details A Carmichael number is defined as a composite (not prime)
 * number that satisfies the following equality, `q` being natural.
 * 
 *         a^n = q*n + a (equivalent to pow(a,n) % n == a)
 * 
 * for all `a` that is coprime with `n`. The smallest example is 561.
 * Find out more on: https://en.wikipedia.org/wiki/Carmichael_number
 * 
 * -lgmp flag may be necessary, e.g.
 *         g++ -o carmichael carmichael.cpp -lgmp ; ./carmichael
 */ 
#include <cassert>    /// for assert
#include <gmp.h>      /// for mpz_*
#include <iostream>   /// for std::cout

/** 
 * @brief Check if a given number is a Carmichael number
 * @param[in] n number to be checked
 * @param[in] a base
 * @param[in] output temporary placeholder for comparison
 */
bool isCarmichael(mpz_t& n, mpz_t& a, mpz_t& output) 
{
    // If output = 0, n is definitely composite.
    if (mpz_probab_prime_p(n, 20) == 0) 
    {
        // While a < n, a++
        while (mpz_cmp(a, n) < 0) {

            // b = a^n % n
            mpz_powm(output, a, n, n);

            // If b != a
            if (mpz_cmp(output, a) != 0) return false;

            // a++
            mpz_add_ui(a, a, 1);
        }
        return true;
    }
    return false;
}

/** 
 * @brief Find Carmichael numbers between bounds, inclusive of both
 * @param[in] lo lower bound
 * @param[in] up upper bound
 */
void CarmichaelBetween(int lo, int up) 
{
    // Program doesn't check for even values, so must start at odd
    if (lo%2 == 0) {
        lo -= 1;
    }

    // Initialize all values as GMP integer type
    mpz_t a, n, N, output;

    // Initialize and set value
    mpz_init_set_ui(a, 2);
    mpz_init_set_ui(n, lo);
    mpz_init_set_ui(N, up);
    mpz_inits(output, NULL);
    while (mpz_cmp(n, N) <= 0) 
    {
        if (isCarmichael(n, a, output)) 
        {
            // Write n to stdout
            mpz_out_str(stdout,10,n);
            std::cout << "\n";
        }
        // Increment to next odd number
        mpz_add_ui(n, n, 2);
    }
    // Avoid memory leaks
    mpz_clear(a);
    mpz_clear(n);
    mpz_clear(N);
    mpz_clear(output);
}

/**
 * @brief Self-test implementations to test `isCarmichael`
 * @returns `void`
 */
static void tests()
{
    mpz_t a, n, output;
    mpz_init_set_ui(a, 2);
    mpz_inits(output, NULL);

    mpz_init_set_ui(n, 561);
    assert (isCarmichael(n, a, output) == true);

    mpz_set_ui(n, 334153);
    assert(isCarmichael(n, a, output) == true);
    
    mpz_set_ui(n, 1009);
    assert(isCarmichael(n, a, output) == false);
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{ 
    tests();
    return 0;
}
