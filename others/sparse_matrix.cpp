/** @file
 * A sparse matrix is a matrix which has number of zeroes greater than
 * \f$\frac{m\times n}{2}\f$, where m and n are the dimensions of the matrix.
 */

#include <iostream>

/** main function */
int main() {
    int m, n;
    int counterZeros = 0;

    std::cout << "Enter dimensions of matrix (seperated with space): ";
    std::cin >> m;
    std::cin >> n;

    int **a = new int *[m];
    for (int i = 0; i < m; i++) a[i] = new int[n];

    std::cout << "Enter matrix elements:";
    std::cout << "\n";

    // reads the matrix from stdin
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "element? ";
            std::cin >> a[i][j];
        }
    }

    // counts the zero's
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 0)
                counterZeros++;  // Counting number of zeroes
        }
    }

    // makes sure the matrix is a sparse matrix
    if (counterZeros > ((m * n) / 2))  // Checking for sparse matrix
        std::cout << "Sparse matrix";
    else
        std::cout << "Not a sparse matrix";

    for (int i = 0; i < m; i++) delete[] a[i];
    delete[] a;
    return 0;
}
