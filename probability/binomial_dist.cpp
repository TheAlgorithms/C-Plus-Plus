#include <iostream>
#include <cmath>

// the binomial distribution models the number of
// successes in a sequence of n independent events

// n : number of trials
// p : probability of success
// x : desired successes

// finds the expected value of a binomial distribution

double binomial_expected(double n, double p) {
    return n * p;
}

// finds the variance of the binomial distribution

double binomial_variance(double n, double p) {
    return n * p * (1 - p);
}

// finds the standard deviation of the binomial distribution

double binomial_standard_deviation(double n, double p) {
    return sqrt(binomial_variance(n, p));
}

// Computes n choose r
// n being the trials and r being the desired successes

double nCr(double n, double r) {
    double numerator = n;
    double denominator = r;

    for (int i = n - 1 ; i >= ((n - r) + 1); i--) {
        numerator *= i;
    }

    for (int i = 1; i < r ; i++) {
        denominator *= i;
    }

    return numerator / denominator;
}

// calculates the probability of exactly x successes

double binomial_x_successes(double n, double p, double x) {
    return nCr(n, x) * pow(p, x) * pow(1-p, n-x);
}

// calculates the probability of a result within a range (inclusive, inclusive)

double binomial_range_successes(
    double n, double p, double lower_bound, double upper_bound) {
    double probability = 0;
    for (int i = lower_bound; i <= upper_bound; i++) {
        probability += nCr(n, i) * pow(p, i) * pow(1 - p, n - i);
    }
    return probability;
}

int main() {
    std::cout << "expected value : "
        <<binomial_expected(100, 0.5) << std::endl;

    std::cout << "variance : "
        << binomial_variance(100, 0.5) << std::endl;

    std::cout << "standard deviation : "
        << binomial_standard_deviation(100, 0.5) << std::endl;

    std::cout << "exactly 30 successes : "
        << binomial_x_successes(100, 0.5, 30) << std::endl;

    std::cout << "45 or more successes : "
        << binomial_range_successes(100, 0.5, 45, 100) << std::endl;

    return 0;
}
