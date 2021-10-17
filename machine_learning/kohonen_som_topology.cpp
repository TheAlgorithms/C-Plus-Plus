/**
 * \addtogroup machine_learning Machine Learning Algorithms
 * @{
 * \file
 * \author [Krishna Vedala](https://github.com/kvedala)
 *
 * \brief [Kohonen self organizing
 * map](https://en.wikipedia.org/wiki/Self-organizing_map) (topological map)
 *
 * \details
 * This example implements a powerful unsupervised learning algorithm called as
 * a self organizing map. The algorithm creates a connected network of weights
 * that closely follows the given data points. This thus creates a topological
 * map of the given data i.e., it maintains the relationship between varipus
 * data points in a much higher dimesional space by creating an equivalent in a
 * 2-dimensional space.
 * <img alt="Trained topological maps for the test cases in the program"
 * src="https://raw.githubusercontent.com/TheAlgorithms/C-Plus-Plus/docs/images/machine_learning/2D_Kohonen_SOM.svg"
 * />
 * \note This C++ version of the program is considerable slower than its [C
 * counterpart](https://github.com/kvedala/C/blob/master/machine_learning/kohonen_som_trace.c)
 * \note The compiled code is much slower when compiled with MS Visual C++ 2019
 * than with GCC on windows
 * \see kohonen_som_trace.cpp
 */
#define _USE_MATH_DEFINES  //< required for MS Visual C++
#include <algorithm>
#include <array>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
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
int save_2d_data(const char *fname,
                 const std::vector<std::valarray<double>> &X) {
    size_t num_points = X.size();       // number of rows
    size_t num_features = X[0].size();  // number of columns

    std::ofstream fp;
    fp.open(fname);
    if (!fp.is_open()) {
        // error with opening file to write
        std::cerr << "Error opening file " << fname << ": "
                  << std::strerror(errno) << "\n";
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

/**
 * Get minimum value and index of the value in a matrix
 * \param[in] X matrix to search
 * \param[in] N number of points in the vector
 * \param[out] val minimum value found
 * \param[out] idx_x x-index where minimum value was found
 * \param[out] idx_y y-index where minimum value was found
 */
void get_min_2d(const std::vector<std::valarray<double>> &X, double *val,
                int *x_idx, int *y_idx) {
    val[0] = INFINITY;  // initial min value
    size_t N = X.size();

    for (int i = 0; i < N; i++) {  // traverse each x-index
        auto result = std::min_element(std::begin(X[i]), std::end(X[i]));
        double d_min = *result;
        std::ptrdiff_t j = std::distance(std::begin(X[i]), result);

        if (d_min < val[0]) {  // if a lower value is found
                               // save the value and its index
            x_idx[0] = i;
            y_idx[0] = j;
            val[0] = d_min;
        }
    }
}

/** \namespace machine_learning
 * \brief Machine learning algorithms
 */
namespace machine_learning {
/** Minimum average distance of image nodes */
constexpr double MIN_DISTANCE = 1e-4;

/**
 * Create the distance matrix or
 * [U-matrix](https://en.wikipedia.org/wiki/U-matrix) from the trained
 * 3D weiths matrix and save to disk.
 *
 * \param [in] fname filename to save in (gets overwriten without
 * confirmation)
 * \param [in] W model matrix to save
 * \returns 0 if all ok
 * \returns -1 if file creation failed
 */
int save_u_matrix(const char *fname,
                  const std::vector<std::vector<std::valarray<double>>> &W) {
    std::ofstream fp(fname);
    if (!fp) {  // error with fopen
        std::cerr << "File error (" << fname << "): " << std::strerror(errno)
                  << std::endl;
        return -1;
    }

    // neighborhood range
    unsigned int R = 1;

    for (int i = 0; i < W.size(); i++) {         // for each x
        for (int j = 0; j < W[0].size(); j++) {  // for each y
            double distance = 0.f;

            int from_x = std::max<int>(0, i - R);
            int to_x = std::min<int>(W.size(), i + R + 1);
            int from_y = std::max<int>(0, j - R);
            int to_y = std::min<int>(W[0].size(), j + R + 1);
            int l = 0, m = 0;
#ifdef _OPENMP
#pragma omp parallel for reduction(+ : distance)
#endif
            for (l = from_x; l < to_x; l++) {      // scan neighborhoor in x
                for (m = from_y; m < to_y; m++) {  // scan neighborhood in y
                    auto d = W[i][j] - W[l][m];
                    double d2 = std::pow(d, 2).sum();
                    distance += std::sqrt(d2);
                    // distance += d2;
                }
            }

            distance /= R * R;          // mean distance from neighbors
            fp << distance;             // print the mean separation
            if (j < W[0].size() - 1) {  // if not the last column
                fp << ',';              // suffix comma
            }
        }
        if (i < W.size() - 1) {  // if not the last row
            fp << '\n';          // start a new line
        }
    }

    fp.close();
    return 0;
}

/**
 * Update weights of the SOM using Kohonen algorithm
 *
 * \param[in] X data point - N features
 * \param[in,out] W weights matrix - PxQxN
 * \param[in,out] D temporary vector to store distances PxQ
 * \param[in] alpha learning rate \f$0<\alpha\le1\f$
 * \param[in] R neighborhood range
 * \returns minimum distance of sample and trained weights
 */
double update_weights(const std::valarray<double> &X,
                      std::vector<std::vector<std::valarray<double>>> *W,
                      std::vector<std::valarray<double>> *D, double alpha,
                      int R) {
    int x = 0, y = 0;
    int num_out_x = static_cast<int>(W->size());       // output nodes - in X
    int num_out_y = static_cast<int>(W[0][0].size());  // output nodes - in Y
    // int num_features = static_cast<int>(W[0][0][0].size());  //  features =
    // in Z
    double d_min = 0.f;

#ifdef _OPENMP
#pragma omp for
#endif
    // step 1: for each output point
    for (x = 0; x < num_out_x; x++) {
        for (y = 0; y < num_out_y; y++) {
            (*D)[x][y] = 0.f;
            // compute Euclidian distance of each output
            // point from the current sample
            auto d = ((*W)[x][y] - X);
            (*D)[x][y] = (d * d).sum();
            (*D)[x][y] = std::sqrt((*D)[x][y]);
        }
    }

    // step 2:  get closest node i.e., node with snallest Euclidian distance
    // to the current pattern
    int d_min_x = 0, d_min_y = 0;
    get_min_2d(*D, &d_min, &d_min_x, &d_min_y);

    // step 3a: get the neighborhood range
    int from_x = std::max(0, d_min_x - R);
    int to_x = std::min(num_out_x, d_min_x + R + 1);
    int from_y = std::max(0, d_min_y - R);
    int to_y = std::min(num_out_y, d_min_y + R + 1);

    // step 3b: update the weights of nodes in the
    // neighborhood
#ifdef _OPENMP
#pragma omp for
#endif
    for (x = from_x; x < to_x; x++) {
        for (y = from_y; y < to_y; y++) {
            /* you can enable the following normalization if needed.
   personally, I found it detrimental to convergence */
            // const double s2pi = sqrt(2.f * M_PI);
            // double normalize = 1.f / (alpha * s2pi);

            /* apply scaling inversely proportional to distance from the
               current node */
            double d2 =
                (d_min_x - x) * (d_min_x - x) + (d_min_y - y) * (d_min_y - y);
            double scale_factor = std::exp(-d2 / (2.f * alpha * alpha));

            (*W)[x][y] += (X - (*W)[x][y]) * alpha * scale_factor;
        }
    }
    return d_min;
}

/**
 * Apply incremental algorithm with updating neighborhood and learning
 * rates on all samples in the given datset.
 *
 * \param[in] X data set
 * \param[in,out] W weights matrix
 * \param[in] alpha_min terminal value of alpha
 */
void kohonen_som(const std::vector<std::valarray<double>> &X,
                 std::vector<std::vector<std::valarray<double>>> *W,
                 double alpha_min) {
    size_t num_samples = X.size();  // number of rows
    // size_t num_features = X[0].size();  // number of columns
    size_t num_out = W->size();  // output matrix size
    size_t R = num_out >> 2, iter = 0;
    double alpha = 1.f;

    std::vector<std::valarray<double>> D(num_out);
    for (int i = 0; i < num_out; i++) D[i] = std::valarray<double>(num_out);

    double dmin = 1.f;        // average minimum distance of all samples
    double past_dmin = 1.f;   // average minimum distance of all samples
    double dmin_ratio = 1.f;  // change per step

    // Loop alpha from 1 to slpha_min
    for (; alpha > 0 && dmin_ratio > 1e-5; alpha -= 1e-4, iter++) {
        // Loop for each sample pattern in the data set
        for (int sample = 0; sample < num_samples; sample++) {
            // update weights for the current input pattern sample
            dmin += update_weights(X[sample], W, &D, alpha, R);
        }

        // every 100th iteration, reduce the neighborhood range
        if (iter % 300 == 0 && R > 1) {
            R--;
        }

        dmin /= num_samples;

        // termination condition variable -> % change in minimum distance
        dmin_ratio = (past_dmin - dmin) / past_dmin;
        if (dmin_ratio < 0) {
            dmin_ratio = 1.f;
        }
        past_dmin = dmin;

        std::cout << "iter: " << iter << "\t alpha: " << alpha << "\t R: " << R
                  << "\t d_min: " << dmin_ratio << "\r";
    }

    std::cout << "\n";
}

}  // namespace machine_learning

using machine_learning::kohonen_som;
using machine_learning::save_u_matrix;

/** @} */

/** Creates a random set of points distributed in four clusters in
 * 3D space with centroids at the points
 * * \f$(0,5, 0.5, 0.5)\f$
 * * \f$(0,5,-0.5, -0.5)\f$
 * * \f$(-0,5, 0.5, 0.5)\f$
 * * \f$(-0,5,-0.5, -0.5)\f$
 *
 * \param[out] data matrix to store data in
 */
void test_2d_classes(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.3;  // radius of cluster
    int i = 0;
    const int num_classes = 4;
    std::array<std::array<double, 2>, num_classes> centres = {
        // centres of each class cluster
        std::array<double, 2>({.5, .5}),   // centre of class 1
        std::array<double, 2>({.5, -.5}),  // centre of class 2
        std::array<double, 2>({-.5, .5}),  // centre of class 3
        std::array<double, 2>({-.5, -.5})  // centre of class 4
    };

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        // select a random class for the point
        int cls = std::rand() % num_classes;

        // create random coordinates (x,y,z) around the centre of the class
        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);

        /* The follosing can also be used
        for (int j = 0; j < 2; j++)
            data[i][j] = _random(centres[class][j] - R, centres[class][j] + R);
        */
    }
}

/** Test that creates a random set of points distributed in four clusters in
 * circumference of a circle and trains an SOM that finds that circular pattern.
 * The following [CSV](https://en.wikipedia.org/wiki/Comma-separated_values)
 * files are created to validate the execution:
 * * `test1.csv`: random test samples points with a circular pattern
 * * `w11.csv`: initial random map
 * * `w12.csv`: trained SOM map
 */
void test1() {
    int j = 0, N = 300;
    int features = 2;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        // loop till max(N, num_out)
        if (i < N) {  // only add new arrays if i < N
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {  // only add new arrays if i < num_out
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);
#ifdef _OPENMP
#pragma omp for
#endif
                for (j = 0; j < features; j++) {
                    // preallocate with random initial weights
                    W[i][k][j] = _random(-10, 10);
                }
            }
        }
    }

    test_2d_classes(&X);  // create test data around circumference of a circle
    save_2d_data("test1.csv", X);  // save test data points
    save_u_matrix("w11.csv", W);   // save initial random weights
    kohonen_som(X, &W, 1e-4);      // train the SOM
    save_u_matrix("w12.csv", W);   // save the resultant weights
}

/** Creates a random set of points distributed in four clusters in
 * 3D space with centroids at the points
 * * \f$(0,5, 0.5, 0.5)\f$
 * * \f$(0,5,-0.5, -0.5)\f$
 * * \f$(-0,5, 0.5, 0.5)\f$
 * * \f$(-0,5,-0.5, -0.5)\f$
 *
 * \param[out] data matrix to store data in
 */
void test_3d_classes1(std::vector<std::valarray<double>> *data) {
    const size_t N = data->size();
    const double R = 0.3;  // radius of cluster
    int i = 0;
    const int num_classes = 4;
    const std::array<std::array<double, 3>, num_classes> centres = {
        // centres of each class cluster
        std::array<double, 3>({.5, .5, .5}),    // centre of class 1
        std::array<double, 3>({.5, -.5, -.5}),  // centre of class 2
        std::array<double, 3>({-.5, .5, .5}),   // centre of class 3
        std::array<double, 3>({-.5, -.5 - .5})  // centre of class 4
    };

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        // select a random class for the point
        int cls = std::rand() % num_classes;

        // create random coordinates (x,y,z) around the centre of the class
        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
        data[0][i][2] = _random(centres[cls][2] - R, centres[cls][2] + R);

        /* The follosing can also be used
        for (int j = 0; j < 3; j++)
            data[i][j] = _random(centres[class][j] - R, centres[class][j] + R);
        */
    }
}

/** Test that creates a random set of points distributed in 4 clusters in
 * 3D space and trains an SOM that finds the topological pattern. The following
 * [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) files are created
 * to validate the execution:
 * * `test2.csv`: random test samples points with a lamniscate pattern
 * * `w21.csv`: initial random map
 * * `w22.csv`: trained SOM map
 */
void test2() {
    int j = 0, N = 300;
    int features = 3;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        // loop till max(N, num_out)
        if (i < N) {  // only add new arrays if i < N
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {  // only add new arrays if i < num_out
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);
#ifdef _OPENMP
#pragma omp for
#endif
                for (j = 0; j < features; j++) {
                    // preallocate with random initial weights
                    W[i][k][j] = _random(-10, 10);
                }
            }
        }
    }

    test_3d_classes1(&X);  // create test data around circumference of a circle
    save_2d_data("test2.csv", X);  // save test data points
    save_u_matrix("w21.csv", W);   // save initial random weights
    kohonen_som(X, &W, 1e-4);      // train the SOM
    save_u_matrix("w22.csv", W);   // save the resultant weights
}

/** Creates a random set of points distributed in four clusters in
 * 3D space with centroids at the points
 * * \f$(0,5, 0.5, 0.5)\f$
 * * \f$(0,5,-0.5, -0.5)\f$
 * * \f$(-0,5, 0.5, 0.5)\f$
 * * \f$(-0,5,-0.5, -0.5)\f$
 *
 * \param[out] data matrix to store data in
 */
void test_3d_classes2(std::vector<std::valarray<double>> *data) {
    const size_t N = data->size();
    const double R = 0.2;  // radius of cluster
    int i = 0;
    const int num_classes = 8;
    const std::array<std::array<double, 3>, num_classes> centres = {
        // centres of each class cluster
        std::array<double, 3>({.5, .5, .5}),    // centre of class 1
        std::array<double, 3>({.5, .5, -.5}),   // centre of class 2
        std::array<double, 3>({.5, -.5, .5}),   // centre of class 3
        std::array<double, 3>({.5, -.5, -.5}),  // centre of class 4
        std::array<double, 3>({-.5, .5, .5}),   // centre of class 5
        std::array<double, 3>({-.5, .5, -.5}),  // centre of class 6
        std::array<double, 3>({-.5, -.5, .5}),  // centre of class 7
        std::array<double, 3>({-.5, -.5, -.5})  // centre of class 8
    };

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        // select a random class for the point
        int cls = std::rand() % num_classes;

        // create random coordinates (x,y,z) around the centre of the class
        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
        data[0][i][2] = _random(centres[cls][2] - R, centres[cls][2] + R);

        /* The follosing can also be used
        for (int j = 0; j < 3; j++)
            data[i][j] = _random(centres[class][j] - R, centres[class][j] + R);
        */
    }
}

/** Test that creates a random set of points distributed in eight clusters in
 * 3D space and trains an SOM that finds the topological pattern. The following
 * [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) files are created
 * to validate the execution:
 * * `test3.csv`: random test samples points with a circular pattern
 * * `w31.csv`: initial random map
 * * `w32.csv`: trained SOM map
 */
void test3() {
    int j = 0, N = 500;
    int features = 3;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {
        // loop till max(N, num_out)
        if (i < N) {  // only add new arrays if i < N
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {  // only add new arrays if i < num_out
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);
#ifdef _OPENMP
#pragma omp for
#endif
                for (j = 0; j < features; j++) {
                    // preallocate with random initial weights
                    W[i][k][j] = _random(-10, 10);
                }
            }
        }
    }

    test_3d_classes2(&X);  // create test data around circumference of a circle
    save_2d_data("test3.csv", X);  // save test data points
    save_u_matrix("w31.csv", W);   // save initial random weights
    kohonen_som(X, &W, 1e-4);      // train the SOM
    save_u_matrix("w32.csv", W);   // save the resultant weights
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
