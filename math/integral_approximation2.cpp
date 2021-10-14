#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <cstdint>
#include <random>
#include <ctime>
#include <algorithm>

namespace math {

namespace monte_carlo {

using Function = std::function<double(double&)>;

std::vector<double> generate_samples(const double& start_point, const Function& pdf, const uint32_t& num_samples, const uint32_t& idling = 10000) {
    std::vector<double> samples;
    samples.reserve(num_samples);

    double x_t = start_point;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    std::normal_distribution<double> normal(0.0, 1.0);
    generator.seed(time(nullptr));

    for(uint32_t t = 0; t < num_samples + idling; ++t) {
        double x_dash = normal(generator) + x_t;
        double acceptance_probability = std::min(pdf(x_dash)/pdf(x_t), 1.0);
        double u = uniform(generator);

        if(u <= acceptance_probability) {
            x_t = x_dash;
        }

        if(t >= idling) {
            samples.push_back(x_t);
        }
    }

    return samples;
}

double integral_monte_carlo(const double& start_point, const Function& function, const Function& pdf, const uint32_t& num_samples = 1000000) {
    double integral = 0.0;
    std::vector<double> samples = generate_samples(start_point, pdf, num_samples);

    for(double sample : samples) {
        integral += function(sample) / pdf(sample);
    }

    return integral / static_cast<double>(samples.size());
}

} //namespace monte_carlo
} //namespace math

int main() {
    const math::monte_carlo::Function f = [](double& x) {
        return -x*x + 4.0;
    };

    const math::monte_carlo::Function pdf = [](double& x) {
        if(x >= -2.0 && x <= -1.0) {
            return 0.1;
        }
        if(x <= 2.0 && x >= 1.0) {
            return 0.1;
        }
        if(x > -1.0 && x < 1.0) {
            return 0.4;
        }
        return 0.0;
    };

    double integral = math::monte_carlo::integral_monte_carlo(1.0, f, pdf);

    std::cout << integral << std::endl;

    return 0;
}
