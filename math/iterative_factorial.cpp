/**
 * @file
 * @brief Iterative implementation of factorial
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 */

/// No need long long in argument because result can't fit anyways.
unsigned long long iterativeFactorial(unsigned int n) {
    /// 1 because 0! == 1
    unsigned long long accumulator = 1;

    while (n > 0) {
        accumulator *= n;
        --n;
    }

    return accumulator;
}
