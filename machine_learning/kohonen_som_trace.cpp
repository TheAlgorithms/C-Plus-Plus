/**
 * \addtogroup machine_learning Machine Learning Algorithms
 * @{
 * \file
 * \brief [Kohonen self organizing
 * map](https://en.wikipedia.org/wiki/Self-organizing_map) (data tracing)
 *
 * This example implements a powerful self organizing map algorithm.
 * The algorithm creates a connected network of weights that closely
 * follows the given data points. This this creates a chain of nodes that
 * resembles the given input shape.
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 *
 * \note This C++ version of the program is considerable slower than its [C
 * counterpart](https://github.com/kvedala/C/blob/master/machine_learning/kohonen_som_trace.c)
 * \note The compiled code is much slower when compiled with MS Visual C++ 2019
 * than with GCC on windows
 * \see kohonen_som_topology.cpp
 */
#define _USE_MATH_DEFINES  // required for MS Visual C++
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <valarray>
#include <vector>
#ifdef _OPENMP  // check if OpenMP based parallellization is available
#include <omp.h>
#endif

/**
 * Helper function to generate a random number in a given interval.
 * \n Steps:
 * 1. `r1 = rand() % 100` gets a random number between 0 and 99
 * 2. `r2 = r1 / 100` converts random number to be between 0 and 0.99
 * 3. scale and offset the random number to given range of \f$[a,b]\f$
 *
 * \param[in] a lower limit
 * \param[in] b upper limit
 * \returns random number in the range \f$[a,b]\f$
 */
double _random(double a, double b) {
    return ((b - a) * (std::rand() % 100) / 100.f) + a;
}

/**
 * Save a given n-dimensional data martix to file.
 *
 * \param[in] fname filename to save in (gets overwriten without confirmation)
 * \param[in] X matrix to save
 * \returns 0 if all ok
 * \returns -1 if file creation failed
 */
int save_nd_data(const char *fname,
                 const std::vector<std::valarray<double>> &X) {
    size_t num_points = X.size();       // number of rows
    size_t num_features = X[0].size();  // number of columns

    std::ofstream fp;
    fp.open(fname);
    if (!fp.is_open()) {
        // error with opening file to write
        std::cerr << "Error opening file " << fname << "\n";
        return -1;
    }

    // for each point in the array
    for (int i = 0; i < num_points; i++) {
        // for each feature in the array
        for (int j = 0; j < num_features; j++) {
            fp << X[i][j];               // print the feature value
            if (j < num_features - 1) {  // if not the last feature
                fp << ",";               // suffix comma
            }
        }
        if (i < num_points - 1) {  // if not the last row
            fp << "\n";            // start a new line
        }
    }

    fp.close();
    return 0;
}

/** \namespace machine_learning
 * \brief Machine learning algorithms
 */
namespace machine_learning {

/**
 * Update weights of the SOM using Kohonen algorithm
 *
 * \param[in] X data point
 * \param[in,out] W weights matrix
 * \param[in,out] D temporary vector to store distances
 * \param[in] alpha learning rate \f$0<\alpha\le1\f$
 * \param[in] R neighborhood range
 */
void update_weights(const std::valarray<double> &x,
                    std::vector<std::valarray<double>> *W,
                    std::valarray<double> *D, double alpha, int R) {
    int j = 0, k = 0;
    int num_out = W->size();  // number of SOM output nodes
    // int num_features = x.size();  // number of data features

#ifdef _OPENMP
#pragma omp for
#endif
    // step 1: for each output point
    for (j = 0; j < num_out; j++) {
        // compute Euclidian distance of each output
        // point from the current sample
        (*D)[j] = (((*W)[j] - x) * ((*W)[j] - x)).sum();
    }

    // step 2:  get closest node i.e., node with snallest Euclidian distance to
    // the current pattern
    auto result = std::min_element(std::begin(*D), std::end(*D));
    // double d_min = *result;
    int d_min_idx = std::distance(std::begin(*D), result);

    // step 3a: get the neighborhood range
    int from_node = std::max(0, d_min_idx - R);
    int to_node = std::min(num_out, d_min_idx + R + 1);

    // step 3b: update the weights of nodes in the
    // neighborhood
#ifdef _OPENMP
#pragma omp for
#endif
    for (j = from_node; j < to_node; j++) {
        // update weights of nodes in the neighborhood
        (*W)[j] += alpha * (x - (*W)[j]);
    }
}

/**
 * Apply incremental algorithm with updating neighborhood and learning rates
 * on all samples in the given datset.
 *
 * \param[in] X data set
 * \param[in,out] W weights matrix
 * \param[in] alpha_min terminal value of alpha
 */
void kohonen_som_tracer(const std::vector<std::valarray<double>> &X,
                        std::vector<std::valarray<double>> *W,
                        double alpha_min) {
    int num_samples = X.size();  // number of rows
    // int num_features = X[0].size();  // number of columns
    int num_out = W->size();  // number of rows
    int R = num_out >> 2, iter = 0;
    double alpha = 1.f;

    std::valarray<double> D(num_out);

    // Loop alpha from 1 to slpha_min
    do {
        // Loop for each sample pattern in the data set
        for (int sample = 0; sample < num_samples; sample++) {
            // update weights for the current input pattern sample
            update_weights(X[sample], W, &D, alpha, R);
        }

        // every 10th iteration, reduce the neighborhood range
        if (iter % 10 == 0 && R > 1) {
            R--;
        }

        alpha -= 0.01;
        iter++;
    } while (alpha > alpha_min);
}

}  // namespace machine_learning

/** @} */

using machine_learning::kohonen_som_tracer;

/** Creates a random set of points distributed *near* the circumference
 * of a circle and trains an SOM that finds that circular pattern. The
 * generating function is
 * \f{eqnarray*}{
 * r &\in& [1-\delta r, 1+\delta r)\\
 * \theta &\in& [0, 2\pi)\\
 * x &=& r\cos\theta\\
 * y &=& r\sin\theta
 * \f}
 *
 * \param[out] data matrix to store data in
 */
void test_circle(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.75, dr = 0.3;
    double a_t = 0., b_t = 2.f * M_PI;  // theta random between 0 and 2*pi
    double a_r = R - dr, b_r = R + dr;  // radius random between R-dr and R+dr
    int i = 0;

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        double r = _random(a_r, b_r);      // random radius
        double theta = _random(a_t, b_t);  // random theta
        data[0][i][0] = r * cos(theta);    // convert from polar to cartesian
        data[0][i][1] = r * sin(theta);
    }
}

/** Test that creates a random set of points distributed *near* the
 * circumference of a circle and trains an SOM that finds that circular pattern.
 * The following [CSV](https://en.wikipedia.org/wiki/Comma-separated_values)
 * files are created to validate the execution:
 * * `test1.csv`: random test samples points with a circular pattern
 * * `w11.csv`: initial random map
 * * `w12.csv`: trained SOM map
 *
 * The outputs can be readily plotted in [gnuplot](https:://gnuplot.info) using
 * the following snippet
 * ```gnuplot
 * set datafile separator ','
 * plot "test1.csv" title "original", \
 *      "w11.csv" title "w1", \
 *      "w12.csv" title "w2"
 * ```
 * ![Sample execution
 * output](https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/machine_learning/kohonen/test1.svg)
 */
void test1() {
    int j = 0, N = 500;
    int features = 2;
    int num_out = 50;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::valarray<double>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        // loop till max(N, num_out)
        if (i < N) {  // only add new arrays if i < N
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {  // only add new arrays if i < num_out
            W[i] = std::valarray<double>(features);

#ifdef _OPENMP
#pragma omp for
#endif
            for (j = 0; j < features; j++) {
                // preallocate with random initial weights
                W[i][j] = _random(-1, 1);
            }
        }
    }

    test_circle(&X);  // create test data around circumference of a circle
    save_nd_data("test1.csv", X);    // save test data points
    save_nd_data("w11.csv", W);      // save initial random weights
    kohonen_som_tracer(X, &W, 0.1);  // train the SOM
    save_nd_data("w12.csv", W);      // save the resultant weights
}

/** Creates a random set of points distributed *near* the locus
 * of the [Lamniscate of
 * Gerono](https://en.wikipedia.org/wiki/Lemniscate_of_Gerono).
 * \f{eqnarray*}{
 * \delta r &=& 0.2\\
 * \delta x &\in& [-\delta r, \delta r)\\
 * \delta y &\in& [-\delta r, \delta r)\\
 * \theta &\in& [0, \pi)\\
 * x &=& \delta x + \cos\theta\\
 * y &=& \delta y + \frac{\sin(2\theta)}{2}
 * \f}
 * \param[out] data matrix to store data in
 */
void test_lamniscate(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double dr = 0.2;
    int i = 0;

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        double dx = _random(-dr, dr);     // random change in x
        double dy = _random(-dr, dr);     // random change in y
        double theta = _random(0, M_PI);  // random theta
        data[0][i][0] = dx + cos(theta);  // convert from polar to cartesian
        data[0][i][1] = dy + sin(2. * theta) / 2.f;
    }
}

/** Test that creates a random set of points distributed *near* the locus
 * of the [Lamniscate of
 * Gerono](https://en.wikipedia.org/wiki/Lemniscate_of_Gerono) and trains an SOM
 * that finds that circular pattern. The following
 * [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) files are created
 * to validate the execution:
 * * `test2.csv`: random test samples points with a lamniscate pattern
 * * `w21.csv`: initial random map
 * * `w22.csv`: trained SOM map
 *
 * The outputs can be readily plotted in [gnuplot](https:://gnuplot.info) using
 * the following snippet
 * ```gnuplot
 * set datafile separator ','
 * plot "test2.csv" title "original", \
 *      "w21.csv" title "w1", \
 *      "w22.csv" title "w2"
 * ```
 * ![Sample execution
 * output](https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/machine_learning/kohonen/test2.svg)
 */
void test2() {
    int j = 0, N = 500;
    int features = 2;
    int num_out = 20;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::valarray<double>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        // loop till max(N, num_out)
        if (i < N) {  // only add new arrays if i < N
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {  // only add new arrays if i < num_out
            W[i] = std::valarray<double>(features);

#ifdef _OPENMP
#pragma omp for
#endif
            for (j = 0; j < features; j++) {
                // preallocate with random initial weights
                W[i][j] = _random(-1, 1);
            }
        }
    }

    test_lamniscate(&X);              // create test data around the lamniscate
    save_nd_data("test2.csv", X);     // save test data points
    save_nd_data("w21.csv", W);       // save initial random weights
    kohonen_som_tracer(X, &W, 0.01);  // train the SOM
    save_nd_data("w22.csv", W);       // save the resultant weights
}

/** Creates a random set of points distributed in six clusters in
 * 3D space with centroids at the points
 * * \f${0.5, 0.5, 0.5}\f$
 * * \f${0.5, 0.5, -0.5}\f$
 * * \f${0.5, -0.5, 0.5}\f$
 * * \f${0.5, -0.5, -0.5}\f$
 * * \f${-0.5, 0.5, 0.5}\f$
 * * \f${-0.5, 0.5, -0.5}\f$
 * * \f${-0.5, -0.5, 0.5}\f$
 * * \f${-0.5, -0.5, -0.5}\f$
 *
 * \param[out] data matrix to store data in
 */
void test_3d_classes(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.1;  // radius of cluster
    int i = 0;
    const int num_classes = 8;
    const std::array<const std::array<double, 3>, num_classes> centres = {
        // centres of each class cluster
        std::array<double, 3>({.5, .5, .5}),    // centre of class 0
        std::array<double, 3>({.5, .5, -.5}),   // centre of class 1
        std::array<double, 3>({.5, -.5, .5}),   // centre of class 2
        std::array<double, 3>({.5, -.5, -.5}),  // centre of class 3
        std::array<double, 3>({-.5, .5, .5}),   // centre of class 4
        std::array<double, 3>({-.5, .5, -.5}),  // centre of class 5
        std::array<double, 3>({-.5, -.5, .5}),  // centre of class 6
        std::array<double, 3>({-.5, -.5, -.5})  // centre of class 7
    };

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        int cls =
            std::rand() % num_classes;  // select a random class for the point

        // create random coordinates (x,y,z) around the centre of the class
        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
        data[0][i][2] = _random(centres[cls][2] - R, centres[cls][2] + R);

        /* The follosing can also be used
        for (int j = 0; j < 3; j++)
            data[0][i][j] = _random(centres[cls][j] - R, centres[cls][j] + R);
        */
    }
}

/** Test that creates a random set of points distributed in six clusters in
 * 3D space. The following
 * [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) files are created
 * to validate the execution:
 * * `test3.csv`: random test samples points with a circular pattern
 * * `w31.csv`: initial random map
 * * `w32.csv`: trained SOM map
 *
 * The outputs can be readily plotted in [gnuplot](https:://gnuplot.info) using
 * the following snippet
 * ```gnuplot
 * set datafile separator ','
 * plot "test3.csv" title "original", \
 *      "w31.csv" title "w1", \
 *      "w32.csv" title "w2"
 * ```
 * ![Sample execution
 * output](https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/machine_learning/kohonen/test3.svg)
 */
void test3() {
    int j = 0, N = 200;
    int features = 3;
    int num_out = 20;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::valarray<double>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        // loop till max(N, num_out)
        if (i < N) {  // only add new arrays if i < N
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {  // only add new arrays if i < num_out
            W[i] = std::valarray<double>(features);

#ifdef _OPENMP
#pragma omp for
#endif
            for (j = 0; j < features; j++) {
                // preallocate with random initial weights
                W[i][j] = _random(-1, 1);
            }
        }
    }

    test_3d_classes(&X);              // create test data around the lamniscate
    save_nd_data("test3.csv", X);     // save test data points
    save_nd_data("w31.csv", W);       // save initial random weights
    kohonen_som_tracer(X, &W, 0.01);  // train the SOM
    save_nd_data("w32.csv", W);       // save the resultant weights
}

/**
 * Convert clock cycle difference to time in seconds
 *
 * \param[in] start_t start clock
 * \param[in] end_t end clock
 * \returns time difference in seconds
 */
double get_clock_diff(clock_t start_t, clock_t end_t) {
    return static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC;
}

/** Main function */
int main(int argc, char **argv) {
#ifdef _OPENMP
    std::cout << "Using OpenMP based parallelization\n";
#else
    std::cout << "NOT using OpenMP based parallelization\n";
#endif

    std::srand(std::time(nullptr));

    std::clock_t start_clk = std::clock();
    test1();
    auto end_clk = std::clock();
    std::cout << "Test 1 completed in " << get_clock_diff(start_clk, end_clk)
              << " sec\n";

    start_clk = std::clock();
    test2();
    end_clk = std::clock();
    std::cout << "Test 2 completed in " << get_clock_diff(start_clk, end_clk)
              << " sec\n";

    start_clk = std::clock();
    test3();
    end_clk = std::clock();
    std::cout << "Test 3 completed in " << get_clock_diff(start_clk, end_clk)
              << " sec\n";

    std::cout
        << "(Note: Calculated times include: creating test sets, training "
           "model and writing files to disk.)\n\n";
    return 0;
}
