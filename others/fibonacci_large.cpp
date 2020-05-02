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

    if (fib(5000) == large_number("3878968454388325633701916308325905312082127714646245106160597214895550139044037097010822916462210669479293452858882973813483102008954982940361430156911478938364216563944106910214505634133706558656238254656700712525929903854933813928836378347518908762970712033337052923107693008518093849801803847813996748881765554653788291644268912980384613778969021502293082475666346224923071883324803280375039130352903304505842701147635242270210934637699104006714174883298422891491273104054328753298044273676822977244987749874555691907703880637046832794811358973739993110106219308149018570815397854379195305617510761053075688783766033667355445258844886241619210553457493675897849027988234351023599844663934853256411952221859563060475364645470760330902420806382584929156452876291575759142343809142302917491088984155209854432486594079793571316841692868039545309545388698114665082066862897420639323438488465240988742395873801976993820317174208932265468879364002630797780058759129671389634214252579116872755600360311370547754724604639987588046985178408674382863125"))
        std::cout << "Test for 5000^th Fibonacci number passed!" << std::endl;
    else
        std::cerr << "Test for 5000^th Fibonacci number failed!" << std::endl;

    return 0;
}