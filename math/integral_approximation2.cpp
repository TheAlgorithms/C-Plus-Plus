#include <cmath>
#include <cstdint>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>

namespace math {

namespace monte_carlo {

using Function = std::function<double(double&)>;

std::vector<double> generate_samples(const double& start_point, const Function& pdf, const uint32_t& num_samples, const uint32_t& discard = 100000) {
    std::vector<double> samples;
    samples.reserve(num_samples);

    double x_t = start_point;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    std::normal_distribution<double> normal(0.0, 1.0);
    generator.seed(time(nullptr));

    for(uint32_t t = 0; t < num_samples + discard; ++t) {
        double x_dash = normal(generator) + x_t;
        double acceptance_probability = std::min(pdf(x_dash)/pdf(x_t), 1.0);
        double u = uniform(generator);

        if(u <= acceptance_probability) {
            x_t = x_dash;
        }

        if(t >= discard) {
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

static void test() {
    std::cout << "Disclaimer: Because this is a randomized algorithm," << std::endl;
    std::cout << "it may happen that singular samples deviate from the true result." << std::endl << std::endl;;

    math::monte_carlo::Function f;
    math::monte_carlo::Function pdf;
    double integral = 0;
    double lower_bound = 0, upper_bound = 0;

    /* \int_{-2}^{2} -x^2 + 4 dx */
    f = [&](double& x) {
        return -x*x + 4.0;
    };

    lower_bound = -2.0;
    upper_bound = 2.0;
    pdf = [&](double& x) {
        if(x >= lower_bound && x <= -1.0) {
            return 0.1;
        }
        if(x <= upper_bound && x >= 1.0) {
            return 0.1;
        }
        if(x > -1.0 && x < 1.0) {
            return 0.4;
        }
        return 0.0;
    };

    integral = math::monte_carlo::integral_monte_carlo((upper_bound - lower_bound) / 2.0, f, pdf);

    std::cout << "This number should be close to 10.666666: " << integral << std::endl;

    /* \int_{0}^{1} e^x dx */
    f = [&](double& x) {
        return std::exp(x);
    };

    lower_bound = 0.0;
    upper_bound = 1.0;
    pdf = [&](double& x) {
        if(x >= lower_bound && x <= 0.2) {
            return 0.1;
        }
        if(x > 0.2 && x <= 0.4) {
            return 0.4;
        }
        if(x > 0.4 && x < upper_bound) {
            return 1.5;
        }
        return 0.0;
    };

    integral = math::monte_carlo::integral_monte_carlo((upper_bound - lower_bound) / 2.0, f, pdf);

    std::cout << "This number should be close to 1.7182818: " << integral << std::endl;

    /* \int_{-\infty}^{\infty} sinc(x) dx, sinc(x) = sin(pi * x) / (pi * x)
       This is a difficult integral because of its infinite domain.
       Therefore, it may deviate largely from the expected result.
    */
    f = [&](double& x) {
        return std::sin(M_PI * x) / (M_PI * x);
    };

    pdf = [&](double& x) {
        return 1.0 / std::sqrt(2.0 * M_PI) * std::exp(-x * x / 2.0);
    };

    integral = math::monte_carlo::integral_monte_carlo(0.0, f, pdf, 10000000);

    std::cout << "This number should be close to 1.0: " << integral << std::endl;
}

int main() {
    test();
    return 0;
}
