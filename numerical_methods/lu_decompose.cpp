/**
 * \file
 * \brief [LU decomposition](https://en.wikipedia.org/wiki/LU_decompositon) of a
 * square matrix
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <ctime>
#include <iomanip>
#include <iostream>

#include "./lu_decomposition.h"

/**
 * operator to print a matrix
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::valarray<T>> const &v) {
    const int width = 10;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++)
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col];
        out << std::endl;
    }

    return out;
}

/** Main function */
int main(int argc, char **argv) {
    int mat_size = 3;  // default matrix size
    const int range = 50;
    const int range2 = range >> 1;

    if (argc == 2)
        mat_size = atoi(argv[1]);

    std::srand(std::time(NULL));  // random number initializer

    /* Create a square matrix with random values */
    std::vector<std::valarray<double>> A(mat_size,
                                         std::valarray<double>(mat_size));
    std::vector<std::valarray<double>> L(
        mat_size, std::valarray<double>(mat_size));  // output
    std::vector<std::valarray<double>> U(
        mat_size, std::valarray<double>(mat_size));  // output
    for (int i = 0; i < mat_size; i++) {
        // calloc so that all valeus are '0' by default
        for (int j = 0; j < mat_size; j++)
            /* create random values in the limits [-range2, range-1] */
            A[i][j] = static_cast<double>(std::rand() % range - range2);
    }

    std::clock_t start_t = std::clock();
    lu_decomposition(A, &L, &U);
    std::clock_t end_t = std::clock();
    std::cout << "Time taken: "
              << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << "\n";

    std::cout << "A = \n" << A << "\n";
    std::cout << "L = \n" << L << "\n";
    std::cout << "U = \n" << U << "\n";

    return 0;
}
