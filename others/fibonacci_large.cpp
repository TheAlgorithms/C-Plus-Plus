/**
 * Computes N^th Fibonacci number given as
 * input argument. Uses custom build arbitrary integers library
 * to perform additions and other operations.
 *
 * Took 0.608246 seconds to compute 50,000^th Fibonacci
 * number that contains 10450 digits!
 **/

#include "large_number.h"
#include <iostream>
#include <chrono>

large_number fib(unsigned long long n)
{
    large_number f0(1);
    large_number f1(1);

    do
    {
        large_number f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
        n--;
    } while (n > 2); // since we start from 2
    return f1;
}

int main(int argc, char *argv[])
{
    unsigned long long N;
    if (argc == 2)
        N = strtoull(argv[1], NULL, 10);
    else
    {
        std::cout << "Enter N: ";
        std::cin >> N;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    large_number result = fib(N);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_taken = end_time - start_time;

    std::cout
        << std::endl
        << N << "^th Fibonacci number: " << result << std::endl
        << "Number of digits: " << result.num_digits() << std::endl
        << "Time taken: " << time_taken.count() << " s" << std::endl;
    return 0;
}