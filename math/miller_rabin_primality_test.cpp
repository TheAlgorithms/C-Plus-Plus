// Copyright 2020 @author tjgurwara99

#include <iostream>
#include <random>
#include <vector>

/**
 * A function to give a binary representation of a number in reverse order
 * example binary of 20 is 10100 so this function would return 00101
 */
std::vector<int> reverse_binary_representation(int num) {
    std::vector<int> result;
    int temp = num;
    while (temp > 0) {
        result.push_back(temp % 2);
        temp = temp / 2;
    }
    return result;
}

/**
 * This function is an efficient modular exponentation function.
 * It can be used with any big integer library such as Boost multiprecision
 * to give result any modular exponentation problem reletively quickly.
 */
int modular_exponentiation(int a, std::vector<int> reverse_binary, int n) {
    if (n == 1)
        return 0;
    int b = 1;
    if (reverse_binary.size() == 0)
        return b;
    int A = a;
    if (reverse_binary[0] == 1)
        b = a;

    for (std::vector<int>::iterator it = reverse_binary.begin() + 1;
         it != reverse_binary.end(); ++it) {
        A = A * A % n;
        if (*it == 1)
            b = A * b % n;
    }
    return b;
}

/**
 * A simple function to raise a number to a power. You can use the std::pow
 * function from algorithms header.
 */
int power(int num, int pow) {
    if (pow == 1) {
        return num;
    }
    return num * power(num, pow - 1);
}

/**
 * The probabilistic Miller-Rabin Primality test.
 * This function takes two inputs:
 * 1. Number that needs to be tested
 * 2. Number of loops to run to increase the chances of it being prime.
 *
 * First we check whether the num input is less than 4, if so we can determine
 * whther this is a prime or composite by a simple check. Next we check whether
 * this num is odd (as all primes greater than 2 are odd). Next we write our num
 * in the following format num = 2^r * d + 1 After finding r and d for our input
 * num, we use random number in [2,num - 2] inclusive repeats(second argument)
 * number of times. Within this loop we write d in reverse binary form and use
 * this to calculate mod which is mod = random^d % num. We check the conditions
 * necessary for Miller-Rabin test and continue and/or skip a loop depending on
 * the conditions. If we exit all loops with no issues, then the num is probably
 * prime.
 *
 */
void miller_rabin_primality_test(unsigned int num, unsigned int repeats) {
    if (num < 4) {
        if (num == 2 || num == 3) {
            std::cout << num << " is a prime number";
            return;
        } else {
            std::cout << num << " is not a prime number";
        }
    }

    if (num % 2 == 0) {
        std::cout << num << " is not a prime number";
        return;
    }
    unsigned int d = num - 1, r = 0;
    while (d % 2 == 0) {
        d = d / 2;
        r++;
    }
    std::random_device rd_seed;
    std::mt19937 gen(rd_seed());
    std::uniform_int_distribution<> distribution(2, num - 2);
    for (int i = 0; i < repeats; ++i) {
        int random = distribution(gen);
        std::vector<int> rev_binary = reverse_binary_representation(d);
        int mod = modular_exponentiation(random, rev_binary, num);
        if (mod == 1 || mod == num - 1) {
            continue;
        }
        for (int j = 0; j < r - 1; ++j) {
            mod = (mod * mod) % num;
            if (mod == num - 1) {
                goto outer;
            }
        }
        if (r != 1) {
            std::cout << num << " is not a prime number";
            return;
        }
    outer : {}
    }
    std::cout << num << " is probably a prime number";
}

int main() {
    miller_rabin_primality_test(23, 3);
    return 0;
}
