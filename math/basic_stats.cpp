/**
 * @file
 * @brief Program to determine basic stats (e.g. various means, standard
 * deviation etc.) from an input vector. These are split into [Central
 * Tendancy](https://en.wikipedia.org/wiki/Central_tendency) and
 * [Dispersion](https://en.wikipedia.org/wiki/Statistical_dispersion)
 *
 * @remark As this is designed to be educational, the standard deviation and
 * standard error functions repeat the code from the variance. This better
 * matches the logic to common equation representations of the desired quantity.
 * In practice, avoiding repeated code by calling the variance function would
 * aid in maintainability of the code base.
 *
 * @author [Jordan Hembrow](https://github.com/JordanHembrow5)
 */
#include <cassert>   /// for assert
#include <cmath>     /// for std::pow, std::sqrt, std::abs
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

namespace math {
/**
 * @brief Calculates the arithmetic mean for a given distribution
 * @param dist a vector of numeric elements
 * @returns The arithmetic mean of `dist`
 */
template <class T>
double mean(const std::vector<T> &dist) {
    double sum = 0.0;
    for (const auto &ele : dist) {
        sum += ele;
    }
    return sum / static_cast<double>(dist.size());
}

/**
 * @brief Calculates the geometric mean for a given distribution
 * @param dist a vector of numeric elements
 * @returns The geometric mean of `dist`
 */
template <class T>
double geometric_mean(const std::vector<T> &dist) {
    double prod = 1.0;
    for (const auto &ele : dist) {
        prod *= ele;
    }
    return std::pow(prod, 1.0 / static_cast<double>(dist.size()));
}

/**
 * @brief Calculates the harmonic mean for a given distribution
 * @param dist a vector of numeric elements
 * @returns The harmonic mean of `dist`
 */
template <class T>
double harmonic_mean(const std::vector<T> &dist) {
    double sum = 0.0;
    for (const auto &ele : dist) {
        sum += 1.0 / ele;
    }
    return 1.0 / (sum / static_cast<double>(dist.size()));
}

/**
 * @brief Calculates the unbiased variance for a given distribution
 * @param dist a vector of numeric elements
 * @returns The unbiased variance of `dist`
 * @details
 * https://en.wikipedia.org/wiki/Standard_deviation#Corrected_sample_standard_deviation
 */
template <class T>
double variance(const std::vector<T> &input) {
    double mean_ = mean(input);
    double sq_diff = 0.;
    for (const auto &ele : input) {
        sq_diff += (ele - mean_) * (ele - mean_);
    }
    return sq_diff / (static_cast<double>(input.size()) - 1.);
}

/**
 * @brief Calculates the corrected standard deviation for a given distribution
 * @param dist a vector of numeric elements
 * @returns The corrected standard deviation of `dist`
 * @details
 * https://en.wikipedia.org/wiki/Standard_deviation#Corrected_sample_standard_deviation
 */
template <class T>
double std_dev(const std::vector<T> &input) {
    double mean_ = mean(input);
    double sq_diff = 0.;
    for (const auto &ele : input) {
        sq_diff += (ele - mean_) * (ele - mean_);
    }
    return std::sqrt(sq_diff / (static_cast<double>(input.size()) - 1.));
}

/**
 * @brief Calculates the standard error for a given distribution
 * @param dist a vector of numeric elements
 * @returns The standard error of `dist`
 * @details
 * https://en.wikipedia.org/wiki/Standard_deviation#Relationship_with_standard_error_and_statistical_significance
 */
template <class T>
double std_error(const std::vector<T> &input) {
    double mean_ = mean(input);
    double sq_diff = 0.;
    for (const auto &ele : input) {
        sq_diff += (ele - mean_) * (ele - mean_);
    }
    return std::sqrt(sq_diff) / (static_cast<double>(input.size()));
}

}  // namespace math

/**
 * @brief Checks if two double type numbers are equal by comparing their
 * difference to a defined small value
 *
 * @param f1 first of two floats to check
 * @param f2 second of two floats to check
 * @param epsilon maximum difference allowed to call `f1` and `f2` equal
 * @returns true if absolute difference of `f1` and `f2` is less than `epsilon`,
 * otherwise false
 */
bool double_eq(double f1, double f2, double epsilon = 1e-6) {
    return std::abs(f2 - f1) <= epsilon;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::vector<int> distribution = {1, 2, 3, 4, 5, 9, 8, 7, 6, 3};
    assert(double_eq(math::mean(distribution), 4.8));
    assert(double_eq(math::geometric_mean(distribution), 4.015026617435));
    assert(double_eq(math::harmonic_mean(distribution), 3.16225));
    assert(double_eq(math::variance(distribution), 7.0666667));
    assert(double_eq(math::std_dev(distribution), 2.6583203));
    assert(double_eq(math::std_error(distribution), 0.797496));
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}