/**
 * \file
 * \brief Compute statistics for data entered in rreal-time
 *
 * This algorithm is really beneficial to compute statistics on data read in
 * realtime. For example, devices reading biometrics data. The algorithm is
 * simple enough to be easily implemented in an embedded system.
 */
#include <cmath>
#include <iostream>

/**
 * continuous mean and variance computance using
 * first value as an approximation for the mean
 **/
template <typename T>
class stats_computer1 {
 public:
    /** Constructor
     * \param[in] x new data sample
     */
    void new_val(T x) {
        if (n == 0) K = x;
        n++;
        T tmp = x - K;
        Ex += tmp;
        Ex2 += tmp * tmp;
    }

    /** return sample mean computed till last sample */
    double mean() const { return K + Ex / n; }

    /** return data variance computed till last sample */
    double variance() const { return (Ex2 - (Ex * Ex) / n) / (n - 1); }

    /** return sample standard deviation computed till last sample */
    double std() const { return std::sqrt(this->variance()); }

    /** short-hand operator to read new sample from input stream */
    friend std::istream &operator>>(std::istream &input,
                                    stats_computer1 &stat) {
        T val;
        input >> val;
        stat.new_val(val);
        return input;
    }

 private:
    unsigned int n = 0;
    double Ex, Ex2;
    T K;
};

/**
 * continuous mean and variance computance using
 * Welford's algorithm
 **/
template <typename T>
class stats_computer2 {
 public:
    /** Constructor
     * \param[in] x new data sample
     */
    void new_val(T x) {
        n++;
        double delta = x - mu;
        mu += delta / n;
        double delta2 = x - mu;
        M += delta * delta2;
    }

    /** return sample mean computed till last sample */
    double mean() const { return mu; }

    /** return data variance computed till last sample */
    double variance() const { return M / n; }

    /** return sample standard deviation computed till last sample */
    double std() const { return std::sqrt(this->variance()); }

    /** short-hand operator to read new sample from input stream */
    friend std::istream &operator>>(std::istream &input,
                                    stats_computer2 &stat) {
        T val;
        input >> val;
        stat.new_val(val);
        return input;
    }

 private:
    unsigned int n = 0;
    double mu = 0, var = 0, M = 0;
};

/** Main function */
int main(int argc, char **argv) {
    std::cout
        << "Enter data. Any non-numeric data will terminate the data input."
        << std::endl;

    stats_computer1<float> stats1;
    stats_computer2<float> stats2;

    while (1) {
        double val;
        std::cout << "Enter number: ";
        std::cin >> val;

        // check for failure to read input. Happens for
        // non-numeric data
        if (std::cin.fail()) break;

        stats1.new_val(val);
        stats2.new_val(val);

        std::cout << "\tMethod 1:"
                  << "\tMean: " << stats1.mean()
                  << "\t Variance: " << stats1.variance()
                  << "\t Std: " << stats1.std() << std::endl;
        std::cout << "\tMethod 2:"
                  << "\tMean: " << stats2.mean()
                  << "\t Variance: " << stats2.variance()
                  << "\t Std: " << stats2.std() << std::endl;
    }

    return 0;
}
