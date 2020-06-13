/**
 * Copyright 2020 @author tjgurwara99
 */

#include <iostream>
#include <random>
#include <vector>

/**
 * Function to give a binary representation of a number in reverse order
 * @param integer number that we want to convert
 * @return vector of the number input in reverse binary
 */
std::vector<int> reverse_binary(int num) {
    std::vector<int> result;
    int temp = num;
    while (temp > 0) {
        result.push_back(temp % 2);
        temp = temp / 2;
    }
    return result;
}

/**
 * Function for modular exponentiation.
 * This function is an efficient modular exponentation function.
 * It can be used with any big integer library such as Boost multiprecision
 * to give result any modular exponentation problem reletively quickly.
 * @param base that is being raised to a power as integer
 * @param reverse binary of the power the base is being raised to
 * @param modulo
 * @return the modular exponentiation of a^(reverse_binary) % n
 */
int modular_exponentiation(int a, std::vector<int> rev_binary, int n) {
    if (n == 1)
        return 0;
    int b = 1;
    if (rev_binary.size() == 0)
        return b;
    int A = a;
    if (rev_binary[0] == 1)
        b = a;

    for (std::vector<int>::iterator it = rev_binary.begin() + 1;
         it != rev_binary.end(); ++it) {
        A = A * A % n;
        if (*it == 1)
            b = A * b % n;
    }
    return b;
}

/**
 * Function to raise a number to a power
 * @param base
 * @param power
 * @return base^power
 */
int power(int num, int pow) {
    if (pow == 1) {
        return num;
    }
    return num * power(num, pow - 1);
}

/** Function for testing the conditions that are satisfied when a number is
 * prime.
 * 	@param number d such that d * 2 ^ r = num - 1
 * 	@param number of repeats.
 * 	@return false if n is composite and true if n is probably prime.
 */
bool miller_test(int d, int num) {
    // random number seed
    std::random_device rd_seed;
    // random number generator
    std::mt19937 gen(rd_seed());
    // Uniformly distributed range [2, num - 2] for random numbers
    std::uniform_int_distribution<> distribution(2, num - 2);
    int random = distribution(gen);
    std::vector<int> power = reverse_binary(d);
    int x = modular_exponentiation(random, power, num);
    if (x == 1 || x == num - 1) {
        return true;
    }

    while (d != num - 1) {
        x = (x * x) % num;
        d *= 2;
        if (x == 1) {
            return false;
        }
        if (x == num - 1) {
            return true;
        }
    }
    return false;
}

/**
 * Function that test (probabilistically) whether a given number is a prime
 * based on the Miller-Rabin Primality Test.
 * @param number to be tested
 * @param number of repetitions for the test.
 * @return
 *
 * First we check whether the num input is less than 4, if so we can determine
 * whther this is a prime or composite by checking for 2 and 3.
 * Next we check whether this num is odd (as all primes greater than 2 are odd).
 * Next we write our num in the following format num = 2^r * d + 1. After
 * finding r and d for our input num, we use repeat(second param) number of
 * random number in range [2,num - 2] inclusive. Within this loop we write d in
 * reverse binary form and use this to calculate mod which is mod = random^d %
 * num. We check the conditions necessary for Miller-Rabin test and continue
 * and/or skip a loop depending on the conditions. If we exit all loops with no
 * issues, then the num is probably prime.
 */
bool miller_rabin_primality_test(unsigned int num, unsigned int repeats) {
    if (num < 4) {
        // If num == 2 or num == 3 then prime
        if (num == 2 || num == 3) {
            return true;
        } else {
            return false;
        }
    }
    // If num is even then not prime
    if (num % 2 == 0) {
        return false;
    }
    // Finding d and r in num = 2^r * d + 1
    unsigned int d = num - 1, r = 0;
    while (d % 2 == 0) {
        d = d / 2;
        r++;
    }

    for (int i = 0; i < repeats; ++i) {
        if (!miller_test(d, num)) {
            return false;
        }
    }
    return true;
}

/**
 * Functions for testing the miller_rabin_primality_test() function with some
 * assert statements.
 */
void tests() {
    // First test on 2
    assert(((void)"2 is prime but function says otherwise.\n",
            miller_rabin_primality_test(2, 1) == true));
    std::cout << "First test passes." << std::endl;
    // Second test on 5
    assert(((void)"5 should be prime but the function says otherwise.\n",
            miller_rabin_primality_test(5, 3) == true));
    std::cout << "Second test passes." << std::endl;
    // Third test on 23
    assert(((void)"23 should be prime but the function says otherwise.\n",
            miller_rabin_primality_test(23, 3) == true));
    std::cout << "Third test passes." << std::endl;
    // Fourth test on 16
    assert(((void)"16 is not a prime but the function says otherwise.\n",
            miller_rabin_primality_test(16, 3) == false));
    std::cout << "Fourth test passes." << std::endl;
    // Fifth test on 25
    assert(((void)"25 is not a prime but the function says otherwise.\n",
            miller_rabin_primality_test(27, 3) == false));
    std::cout << "Fifth test passes." << std::endl;
}

/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
