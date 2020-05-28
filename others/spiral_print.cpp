/**
 * @file
 * @brief Print the elements of a matrix traversing it spirally
 */
#include <iostream>

/** Arrange sequence of numbers from '1' in a matrix form
 * \param [out] a matrix to fill
 * \param [in] r number of rows
 * \param [in] c number of columns
 */
void genArray(int **a, int r, int c) {
    int value = 1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = value;
            std::cout << a[i][j] << " ";
            value++;
        }
        std::cout << std::endl;
    }
}

/** Traverse the matrix spirally and print the sequence of elements
 * \param [in] a matrix to read from
 * \param [in] r number of rows
 * \param [in] c number of columns
 */
void spiralPrint(int **a, int r, int c) {
    int startRow = 0, endRow = r - 1;
    int startCol = 0, endCol = c - 1;
    int cnt = 0;

    while (startRow <= endRow && startCol <= endCol) {
        /// Print start row
        for (int i = startCol; i <= endCol; i++, cnt++) {
            std::cout << a[startRow][i] << " ";
        }
        startRow++;

        /// Print the end col
        for (int i = startRow; i <= endRow; i++, cnt++) {
            std::cout << a[i][endCol] << " ";
        }
        endCol--;

        /// Print the end row
        if (cnt == r * c) {
            break;
        }

        for (int i = endCol; i >= startCol; i--, cnt++) {
            std::cout << a[endRow][i] << " ";
        }
        endRow--;

        /// Print the start Col
        if (cnt == r * c) {
            break;
        }
        for (int i = endRow; i >= startRow; i--, cnt++) {
            std::cout << a[i][startCol] << " ";
        }
        startCol++;
    }
}

/** main function */
int main() {
    int r, c;
    std::cin >> r >> c;
    int **a = new int *[r];
    for (int i = 0; i < r; i++) a[i] = new int[c];

    genArray(a, r, c);
    spiralPrint(a, r, c);

    for (int i = 0; i < r; i++) delete[] a[i];
    delete[] a;
    return 0;
}
