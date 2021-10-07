#include <cassert>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>

namespace probability {

float generate_uniform() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

class geometric_distribution
{
private:
    float p;

public:
    explicit geometric_distribution(const float& p) : p(p) {}

    float expected_value() {
       return 1.0f/ p;
    }

    float variance() {
       return (1.0f - p) / (p * p);
    }

    float standard_deviation() {
       return std::sqrt(variance());
    }

    float probability_density(const uint32_t& k) {
        return std::pow((1.0f - p), static_cast<float>(k - 1)) * p;
    }

    float cumulative_distribution(const uint32_t& k) {
        return 1.0f - std::pow((1.0f - p), static_cast<float>(k));
    }

    float inverse_cumulative_distribution(const float& cdf) {
        return std::log(1.0f - cdf) / std::log(1.0f - p);
    }

    uint32_t draw_sample() {
        float uniform_sample = generate_uniform();
        return static_cast<uint32_t>(inverse_cumulative_distribution(uniform_sample)) + 1;
    }

    float range_tries(const uint32_t& min_tries = 0, const uint32_t& max_tries = std::numeric_limits<uint32_t>::max()) {
        float cdf_lower = cumulative_distribution(min_tries);
        float cdf_upper = max_tries == std::numeric_limits<uint32_t>::max() ? 1.0f : cumulative_distribution(max_tries);
        return cdf_upper - cdf_lower;
    }
};

}  // namespace probability

void sample_test(probability::geometric_distribution& dist) {
    uint32_t n_tries = 1000000;
    auto* tries = new float[n_tries];

    float mean = 0.0f;
    for (uint32_t i = 0; i < n_tries; ++i) {
        tries[i] = dist.draw_sample();
        mean += tries[i];
    }

    mean /= static_cast<float>(n_tries);

    float var = 0.0f;
    for (uint32_t i = 0; i < n_tries; ++i) {
        var += (tries[i] - mean) * (tries[i] - mean);
    }

    var /= static_cast<float>(n_tries - 1);

    delete[] tries;

    std::cout << "This value should be near " << dist.expected_value() << ": " << mean << std::endl;
    std::cout << "This value should be near " << dist.variance() << ": " << var << std::endl;
}

static void test() {
    probability::geometric_distribution dist(0.3);

    const float threshold = 1e-3f;

    std::cout << "Starting tests for p = 0.3..." << std::endl;
    assert(std::abs(dist.expected_value() - 3.33333333f) < threshold);
    assert(std::abs(dist.variance() - 7.77777777f) < threshold);
    assert(std::abs(dist.standard_deviation() - 2.788866755) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.07203) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.882351) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(dist.cumulative_distribution(8)) - 8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(2) - 0.49f) < threshold);
    assert(std::abs(dist.range_tries(4, 11) - 0.2203267f) < threshold);
    std::cout << "All tests passed" << std::endl;
    sample_test(dist);

    dist = probability::geometric_distribution(0.5f);

    std::cout << "Starting tests for p = 0.5..." << std::endl;
    assert(std::abs(dist.expected_value() - 2.0f) < threshold);
    assert(std::abs(dist.variance() - 2.0f) < threshold);
    assert(std::abs(dist.standard_deviation() - 1.4142135f) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.03125) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.984375) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(dist.cumulative_distribution(8)) - 8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(2) - 0.25f) < threshold);
    assert(std::abs(dist.range_tries(4, 11) - 0.062011f) < threshold);
    std::cout << "All tests passed" << std::endl;
    sample_test(dist);

    dist = probability::geometric_distribution(0.8f);

    std::cout << "Starting tests for p = 0.8..." << std::endl;
    assert(std::abs(dist.expected_value() - 1.25f) < threshold);
    assert(std::abs(dist.variance() - 0.3125f) < threshold);
    assert(std::abs(dist.standard_deviation() - 0.559016f) < threshold);
    assert(std::abs(dist.probability_density(5) - 0.00128) < threshold);
    assert(std::abs(dist.cumulative_distribution(6) - 0.999936) < threshold);
    assert(std::abs(dist.inverse_cumulative_distribution(dist.cumulative_distribution(8)) - 8) < threshold);
    assert(std::abs(dist.range_tries() - 1.0f) < threshold);
    assert(std::abs(dist.range_tries(2) - 0.04f) < threshold);
    assert(std::abs(dist.range_tries(4, 11) - 0.00159997f) < threshold);
    std::cout << "All tests passed" << std::endl;
    sample_test(dist);


}

int main() {
    srand(time(nullptr));
    test();
    return 0;
}
