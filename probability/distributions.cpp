/**
 * \file
 * \brief Implementation of Discrete Distributions
 * \author [Tuan Ho](https://github.com/ttuanho)
 * \note
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>


namespace Distribution {

    /**
     * \brief []()
     * \details
     */
    namespace Binom {

    }
    /**
     * \brief [Uniform
     * distribution](https://en.wikipedia.org/wiki/Uniform_distribution_(continuous))
     * \details The distribution describes an experiment where there is an
     * arbitrary outcome that lies between certain bounds.
     */
    namespace Uniform {

    /**
     * \details A random variable \f$X\f$ is said to be ***uniformly distributed***
     * over an interval \f$[\alpha,\beta]\f$ if its probability density function is given
     * by
     * 
     * 
     * \f$
     * f(x)=\begin{cases}
     * \frac{1}{\beta - \alpha}\text{ if }x\in [\alpha,\beta] \\
     * 0\quad \text{otherwise}
     * \end{cases}
     * \f$
     * \param x the outcome
     * \param alpha min bound
     * \param beta max bound
    */
    double pdf(double x, double alpha, double beta) { 
        assert(beta > alpha); 
        if (alpha <= x && x <= beta) {
            return 1 / (beta - alpha);
        } else {
            return 0;
        }
    }

    /**
     * \details The cdf for a uniform distribution is given by
     * \f$
     * F(x)=
     * \begin{cases}
     *   0 &\text{ if }x<\alpha\\
     *   \frac{x-\alpha}{\beta-\alpha} &\text{ if }\alpha \leq x\leq \beta\\
     *   1 &\text{ if }x>\beta
     * \end{cases}
     * \f$
     * \param x the outcome
     * \param alpha min bound
     * \param beta max bound
     */

    double cdf(double x, double alpha, double beta) {
        assert(beta > alpha); 
        if (x < alpha) {
            return 0;
        } else if (x > beta) {
            return 1;
        } else {
            return (x - alpha) / (beta - alpha);
        }
    }

    namespace Normal {

    }

    namespace Poiss {

    }

    namespace Exp {
        void cdf(double x) {

        }
    }

    namespace Gauss {

    }
}
}

/**
 * Main function.
 * Exit and return 0.
 */
int main() {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "      Example of Uniform Distribution" << std::endl;
    std::cout << std::endl;
    double sig = 0, var = 23;
    double alpha = 2, beta = 18;
    double x = 12;
    std::cout << "Given x=" << x << " in X that is uniformly distributed with U("
              << sig << "," << var << "), then" << std::endl;
    std::cout << "cdf = "<< Distribution::Uniform::cdf(x,alpha, beta)<< std::endl;
    std::cout << "pdf = "<< Distribution::Uniform::pdf(x,alpha, beta)<< std::endl;
    std::cout << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "      Example of Distribution" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}

