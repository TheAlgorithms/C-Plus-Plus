/**
 * @file
 * @brief Get list of prime numbers
 * @see primes_up_to_billion.cpp sieve_of_eratosthenes.cpp
 */
#include <iostream>
#include <vector>

/** Generate an increasingly large number of primes
 * and store in a list
 */
std::vector<int> primes(int max)
{
    max++;
    std::vector<int> res;
    std::vector<bool> numbers(max, false);
    for (int i = 2; i < max; i++)
    {
        if (!numbers[i])
        {
            for (int j = i; j < max; j += i) numbers[j] = true;
            res.push_back(i);
        }
    }
    return res;
}

/** main function */
int main()
{
    std::cout << "Calculate primes up to:\n>> ";
    int n;
    std::cin >> n;
    std::vector<int> ans = primes(n);
    for (int i = 0; i < ans.size(); i++) std::cout << ans[i] << ' ';
    std::cout << std::endl;
}
