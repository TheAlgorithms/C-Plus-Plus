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

int main() {

    return 0;
}
