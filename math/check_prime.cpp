/**
 * Copyright 2020 @author omkarlanghe
 *
 * @file
 * A simple program to check if the given number if prime or not.
 *
 * @brief
 * Reduced all possibilities of a number which cannot be prime.
 * Eg: No even number, except 2 can be a prime number, hence we will increment
 * our loop with i+2 jumping on all odd numbers only. If number is <= 1 or if it
 * is even except 2, break the loop and return false telling number is not
 * prime.
 */
#include <cassert>
#include <iostream>
/**
 * Function to check if the given number is prime or not.
 * @param num number to be checked.
 * @return if number is prime, it returns @ true, else it returns @ false.
 */
template <typename T>
bool is_prime(T num) {
    bool result = true;
    if (num <= 1) {
        return 0;
    } else if (num == 2) {
        return 1;
    } else if ((num & 1) == 0) {
        return 0;
    }
    if (num >= 3) {
        for (T i = 3; (i * i) <= (num); i = (i + 2)) {
            if ((num % i) == 0) {
                result = false;
                break;
            }
        }
    }
    return (result);
}

/**
 * Main function
 */
int main() {
    // perform self-test
    assert(is_prime(50) == false);
    assert(is_prime(115249) == true);

    int num;
    std::cout << "Enter the number to check if it is prime or not" << std::endl;
    std::cin >> num;
    bool result = is_prime(num);
    if (result) {
        std::cout << num << " is a prime number" << std::endl;
    } else {
        std::cout << num << " is not a prime number" << std::endl;
    }

    return 0;
}
