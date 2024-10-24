/**
 * @file
 * @brief Creation of data using the [Pareto
 Distribution](https://en.wikipedia.org/wiki/Pareto_distribution)
 * @details
 * Given a shape (alpha), a scale (xm) and a size, it is possible to create a
 * sequence of data based on Pareto Distribution, better known as the 80/20
 * rule. When modeling phenomena with a heavy tail, including wealth distribution,
 * natural phenomena, or other skewed distributions where a few number of
 * occurrences account for the majority of the effect, this distribution is
 * especially helpful.

 * To generate random numbers from a Pareto distribution, it was used the
 * inverse transformation technique in Cumulative Distribution Function (CDF).
 * The idea is that if (u) is a uniform random variable in the interval ([0, 1]),
 * then we can find (x) such that: [ u = F(x) ]

 * @author [Lidia Domingos](https://github.com/LidiaDomingos)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

/**
 * @brief Function to generate values following the Pareto distribution
 * @param shape (alpha) A key parameter controlling the "steepness" of the
 * distribution's tail. Higher values of α produce fewer extreme values.
 * @param scale (xm) The minimum possible value for the distribution, sometimes
 * referred to as the "scale" parameter or lower bound of the distribution.
 * @param size The length of data you want to create
 * @return data vector, which contains size random
 * numbers generated according to the Pareto distribution.
 */
std::vector<double> pareto_distribution(double shape, double scale, int size) {
    std::vector<double> data;
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

    for (int i = 0; i < size; ++i) {
        double u = uniform(gen);  // Generates a random number
        double x =
            scale /
            std::pow(u, 1.0 / shape);  // Apply the Pareto distribution formula
        data.push_back(x);
    }

    return data;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    double shape = 3.0;
    double scale = 1.0;
    int size = 1000;

    std::vector<double> data = pareto_distribution(shape, scale, size);

    // Test 1: Verify that the correct number of values ​​were generated
    assert(data.size() == size);

    // Test 2: Check if all values ​​are greater than or equal to the value
    // minimum (scale)
    for (double value : data) {
        assert(value >= scale);
    }

    // Test 3: Check if the average of the generated values ​​is greater
    // than the parameter scale
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / size;
    std::cout << "Average " << mean << std::endl;

    // As the average tends to be greater than the scale parameter (xm) in
    // Pareto distribution
    assert(mean > scale);

    // Test 4: Check if the maximum value is significant in a distribution
    // Pareto (reasonably higher than average)
    double max_value = *std::max_element(data.begin(), data.end());
    std::cout << "Max value: " << max_value << std::endl;
    assert(max_value > mean);

    std::cout << "All the tests passed!\n";
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
