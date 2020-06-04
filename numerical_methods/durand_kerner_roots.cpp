/**
 * @file
 * Compute riots of any given polynomial.
 *
 * Test the algorithm online:
 * https://gist.github.com/kvedala/27f1b0b6502af935f6917673ec43bcd7
 *
 * Try the highly unstable Wilkinson's polynomial:
 * ```
 * ./numerical_methods/durand_kerner_roots 1 -210 20615 -1256850 53327946
 * -1672280820 40171771630 -756111184500 11310276995381 -135585182899530
 * 1307535010540395 -10142299865511450 63030812099294896 -311333643161390640
 * 1206647803780373360 -3599979517947607200 8037811822645051776
 * -12870931245150988800 13803759753640704000 -8752948036761600000
 * 2432902008176640000
 * ```
 */

#include <algorithm>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <valarray>
#ifdef _OPENMP
#include <omp.h>
#endif

#define ACCURACY 1e-10 /**< maximum accuracy limit */

/**
 * Evaluate the value of a polynomial with given coefficients
 * \param[in] coeffs coefficients of the polynomial
 * \param[in] degree degree of polynomial
 * \param[in] x point at which to evaluate the polynomial
 * \returns \f$f(x)\f$
 **/
std::complex<double> poly_function(const std::valarray<double> &coeffs,
                                   std::complex<double> x) {
    double real = 0.f, imag = 0.f;
    int n;

#ifdef _OPENMP
#pragma omp parallel for reduction(+ : real, imag)
#endif
    for (n = 0; n < coeffs.size(); n++) {
        std::complex<double> tmp =
            coeffs[n] * std::pow(x, coeffs.size() - n - 1);
        real += tmp.real();
        imag += tmp.imag();
    }

    return std::complex<double>(real, imag);
}

/**
 * create a textual form of complex number
 * \param[in] x point at which to evaluate the polynomial
 * \returns pointer to converted string
 */
const char *complex_str(const std::complex<double> &x) {
    static char msg[50];

    sprintf(msg, "% 7.04g%+7.04gj", x.real(), x.imag());

    return msg;
}

/**
 * check for termination condition
 * \param[in] delta point at which to evaluate the polynomial
 * \returns `false` if termination not reached
 * \returns `true` if termination reached
 */
bool check_termination(long double delta) {
    static long double past_delta = INFINITY;
    if (std::abs(past_delta - delta) <= ACCURACY || delta < ACCURACY)
        return true;
    past_delta = delta;
    return false;
}

/***
 * Main function.
 * The comandline input arguments are taken as coeffiecients of a polynomial.
 * For example, this command
 * ```sh
 * ./durand_kerner_roots 1 0 -4
 * ```
 * will find roots of the polynomial \f$1\cdot x^2 + 0\cdot x^1 + (-4)=0\f$
 **/
int main(int argc, char **argv) {
    unsigned int degree = 0;
    unsigned int n, i;

    if (argc < 2) {
        std::cout
            << "Please pass the coefficients of the polynomial as commandline "
               "arguments.\n";
        return 0;
    }

    degree = argc - 1;                     // detected polynomial degree
    std::valarray<double> coeffs(degree);  // create coefficiencts array

    /* initialize random seed: */
    std::srand(std::time(nullptr));

#if defined(DEBUG) || !defined(NDEBUG)
    /*
     * store intermediate values to a CSV file
     */
    std::ofstream log_file;
    log_file.open("durand_kerner.log.csv");
    if (!log_file.is_open()) {
        perror("Unable to create a storage log file!");
        return EXIT_FAILURE;
    }
    log_file << "iter#,";
#endif

    // number of roots = degree - 1
    std::valarray<std::complex<double>> s0(degree - 1);

    std::cout << "Computing the roots for:\n\t";
    for (n = 0; n < degree; n++) {
        coeffs[n] = strtod(argv[n + 1], nullptr);
        if (n < degree - 1 && coeffs[n] != 0)
            std::cout << "(" << coeffs[n] << ") x^" << degree - n - 1 << " + ,";
        else if (coeffs[n] != 0)
            std::cout << "(" << coeffs[n] << ") x^" << degree - n - 1
                      << " = 0\n";

        /* initialize root approximations with random values */
        if (n < degree - 1) {
            s0[n] = std::complex<double>(std::rand() % 100, std::rand() % 100);
            s0[n] -= 50.f;
            s0[n] /= 50.f;
#if defined(DEBUG) || !defined(NDEBUG)
            log_file << "root_" << n << ",";
#endif
        }
    }

    // numerical errors less when the first coefficient is "1"
    // hence, we normalize the first coefficient
    coeffs /= coeffs[0];

#if defined(DEBUG) || !defined(NDEBUG)
    log_file << "avg. correction";
    log_file << "\n0,";
    for (n = 0; n < degree - 1; n++) log_file << complex_str(s0[n]) << ",";
#endif

    double tol_condition = 1;
    unsigned long iter = 0;

    clock_t end_time, start_time = clock();
    while (!check_termination(tol_condition) && iter < INT_MAX) {
        std::complex<double> delta = 0;
        tol_condition = 0;
        iter++;

#if defined(DEBUG) || !defined(NDEBUG)
        log_file << "\n" << iter << ",";
#endif

        for (n = 0; n < degree - 1; n++) {
            std::complex<double> numerator, denominator;
            numerator = poly_function(coeffs, s0[n]);
            denominator = 1.0;
            for (i = 0; i < degree - 1; i++)
                if (i != n)
                    denominator *= s0[n] - s0[i];

            delta = numerator / denominator;

            if (std::isnan(std::abs(delta)) || std::isinf(std::abs(delta))) {
                std::cerr << "\n\nOverflow/underrun error - got value = "
                          << std::abs(delta);
                goto end;
            }

            s0[n] -= delta;

            tol_condition = std::max(tol_condition, std::abs(std::abs(delta)));

#if defined(DEBUG) || !defined(NDEBUG)
            log_file << complex_str(s0[n]) << ",";
#endif
        }
        // tol_condition /= (degree - 1);

#if defined(DEBUG) || !defined(NDEBUG)
        if (iter % 500 == 0) {
            std::cout << "Iter: " << iter << "\t";
            for (n = 0; n < degree - 1; n++)
                std::cout << "\t" << complex_str(s0[n]);
            std::cout << "\t\tabsolute average change: " << tol_condition
                      << "\n";
        }

        log_file << tol_condition;
#endif
    }
end:

    end_time = clock();

#if defined(DEBUG) || !defined(NDEBUG)
    log_file.close();
#endif

    std::cout << "\nIterations: " << iter << "\n";
    for (n = 0; n < degree - 1; n++)
        std::cout << "\t" << complex_str(s0[n]) << "\n";
    std::cout << "absolute average change: " << tol_condition << "\n";
    std::cout << "Time taken: "
              << (end_time - start_time) / (double)CLOCKS_PER_SEC << " sec\n";

    return 0;
}