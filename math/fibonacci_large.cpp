/**
 * @file
 * @brief Computes N^th Fibonacci number given as
 * input argument. Uses custom build arbitrary integers library
 * to perform additions and other operations.
 *
 * Took 0.608246 seconds to compute 50,000^th Fibonacci
 * number that contains 10450 digits!
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 * @see fibonacci.cpp, fibonacci_fast.cpp, string_fibonacci.cpp
 */

#include <cinttypes>
#include <ctime>
#include <iostream>

#include "./large_number.h"

/** Compute fibonacci numbers using the relation
 * \f[f(n)=f(n-1)+f(n-2)\f]
 * and returns the result as a large_number type.
 */
large_number fib(uint64_t n) {
    large_number f0(1);
    large_number f1(1);

    do {
        large_number f2 = f1;
        f1 += f0;
        f0 = f2;
        n--;
    } while (n > 2);  // since we start from 2

    return f1;
}

int main(int argc, char *argv[]) {
    uint64_t N;
    if (argc == 2) {
        N = strtoull(argv[1], NULL, 10);
    } else {
        std::cout << "Enter N: ";
        std::cin >> N;
    }

    clock_t start_time = std::clock();
    large_number result = fib(N);
    clock_t end_time = std::clock();
    double time_taken = static_cast<double>(end_time - start_time) /
                        static_cast<double>(CLOCKS_PER_SEC);

    std::cout << std::endl
              << N << "^th Fibonacci number: " << result << std::endl
              << "Number of digits: " << result.num_digits() << std::endl
              << "Time taken: " << std::scientific << time_taken << " s"
              << std::endl;

    N = 5000;
    if (fib(N) ==
        large_number(
            "387896845438832563370191630832590531208212771464624510616059721489"
            "555013904403709701082291646221066947929345285888297381348310200895"
            "498294036143015691147893836421656394410691021450563413370655865623"
            "825465670071252592990385493381392883637834751890876297071203333705"
            "292310769300851809384980180384781399674888176555465378829164426891"
            "298038461377896902150229308247566634622492307188332480328037503913"
            "035290330450584270114763524227021093463769910400671417488329842289"
            "149127310405432875329804427367682297724498774987455569190770388063"
            "704683279481135897373999311010621930814901857081539785437919530561"
            "751076105307568878376603366735544525884488624161921055345749367589"
            "784902798823435102359984466393485325641195222185956306047536464547"
            "076033090242080638258492915645287629157575914234380914230291749108"
            "898415520985443248659407979357131684169286803954530954538869811466"
            "508206686289742063932343848846524098874239587380197699382031717420"
            "893226546887936400263079778005875912967138963421425257911687275560"
            "0360311370547754724604639987588046985178408674382863125"))
        std::cout << "Test for " << N << "^th Fibonacci number passed!"
                  << std::endl;
    else
        std::cerr << "Test for " << N << "^th Fibonacci number failed!"
                  << std::endl;

    return 0;
}
