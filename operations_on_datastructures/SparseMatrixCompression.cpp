/**
 * @file
 * @brief Implementation of Sparse Matrix Compression (Row-Major and
 * Column-Major) with efficient retrieval and decompression.
 *
 * @details
 * This program provides:
 * - Compression: Stores only non-zero elements in both row-major and
 * column-major formats.
 * - Retrieval: Allows efficient retrieval of original matrix values.
 * - Decompression: Reconstructs the original matrix from compressed data.
 *
 * @author: [vrtarimala](https://github.com/vrtarimala)
 */

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class SparseMatrix {
 private:
    int rows;  ///< Number of rows in the original matrix.
    int cols;  ///< Number of columns in the original matrix.

    // Map to store non-zero elements as key-value pairs
    // Key: (row, col) pair; Value: non-zero element
    map<pair<int, int>, int> data;

 public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}

    /**
     * @brief Compresses a given sparse matrix in row-major order.
     * @param matrix 2D vector representing the sparse matrix.
     */
    void compressRowMajor(const vector<vector<int> > &matrix) {
        data.clear();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] != 0) {
                    data[{i, j}] = matrix[i][j];
                }
            }
        }
    }

    /**
     * @brief Compresses a given sparse matrix in column-major order.
     * @param matrix 2D vector representing the sparse matrix.
     */
    void compressColumnMajor(const vector<vector<int> > &matrix) {
        data.clear();
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                if (matrix[i][j] != 0) {
                    data[{i, j}] = matrix[i][j];
                }
            }
        }
    }

    /**
     * @brief Decompresses the sparse matrix to its original form.
     * @return 2D vector representing the original matrix.
     */
    vector<vector<int> > decompress() const {
        vector<vector<int> > matrix(rows, vector<int>(cols, 0));
        for (const auto &[key, value] : data) {
            matrix[key.first][key.second] = value;
        }
        return matrix;
    }

    /**
     * @brief Retrieves the value at a given row and column.
     * @param row Row index of the element.
     * @param col Column index of the element.
     * @return Value at the specified position (0 if not present).
     */
    int getValue(int row, int col) const {
        auto it = data.find({row, col});
        if (it != data.end()) {
            return it->second;
        }
        return 0;  // Default to 0 if the value is not stored.
    }

    /**
     * @brief Prints the compressed representation of the matrix.
     */
    void printCompressed() const {
        cout << "Compressed Representation:\n";
        for (const auto &[key, value] : data) {
            cout << "(" << key.first << ", " << key.second << ", " << value
                 << ")\n";
        }
    }
};

void runTests() {
    cout << "\nTest Case 1: Basic Row-Major Compression\n";
    vector<vector<int> > matrix1 = {{5, 0, 0}, {0, 8, 0}, {0, 0, 3}};

    SparseMatrix sparseMatrix1(3, 3);
    sparseMatrix1.compressRowMajor(matrix1);
    sparseMatrix1.printCompressed();

    // Test decompression
    auto decompressedMatrix1 = sparseMatrix1.decompress();
    assert(matrix1 == decompressedMatrix1);

    // Test retrieval
    assert(sparseMatrix1.getValue(0, 0) == 5);
    assert(sparseMatrix1.getValue(1, 1) == 8);
    assert(sparseMatrix1.getValue(2, 2) == 3);
    assert(sparseMatrix1.getValue(1, 2) == 0);

    cout << "Passed Test Case 1.\n";

    cout << "\nTest Case 2: Basic Column-Major Compression\n";
    SparseMatrix sparseMatrix2(3, 3);
    sparseMatrix2.compressColumnMajor(matrix1);
    sparseMatrix2.printCompressed();

    // Test decompression
    auto decompressedMatrix2 = sparseMatrix2.decompress();
    assert(matrix1 == decompressedMatrix2);

    // Test retrieval
    assert(sparseMatrix2.getValue(0, 0) == 5);
    assert(sparseMatrix2.getValue(1, 1) == 8);
    assert(sparseMatrix2.getValue(2, 2) == 3);
    assert(sparseMatrix2.getValue(1, 2) == 0);

    cout << "Passed Test Case 2.\n";

    cout << "\nTest Case 3: Matrix with All Zeros\n";
    vector<vector<int> > matrix2 = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    SparseMatrix sparseMatrix3(3, 3);
    sparseMatrix3.compressRowMajor(matrix2);
    sparseMatrix3.printCompressed();

    auto decompressedMatrix3 = sparseMatrix3.decompress();
    assert(matrix2 == decompressedMatrix3);

    assert(sparseMatrix3.getValue(0, 0) == 0);
    assert(sparseMatrix3.getValue(1, 1) == 0);

    cout << "Passed Test Case 3.\n";

    cout << "\nTest Case 4: Large Sparse Matrix\n";
    vector<vector<int> > matrix3(10, vector<int>(10, 0));
    matrix3[1][2] = 10;
    matrix3[3][4] = 20;
    matrix3[5][6] = 30;

    SparseMatrix sparseMatrix4(10, 10);
    sparseMatrix4.compressRowMajor(matrix3);
    sparseMatrix4.printCompressed();

    auto decompressedMatrix4 = sparseMatrix4.decompress();
    assert(matrix3 == decompressedMatrix4);

    assert(sparseMatrix4.getValue(1, 2) == 10);
    assert(sparseMatrix4.getValue(3, 4) == 20);
    assert(sparseMatrix4.getValue(5, 6) == 30);
    assert(sparseMatrix4.getValue(0, 0) == 0);

    cout << "Passed Test Case 4.\n";

    cout << "\nAll Test Cases Passed.\n";
}

int main() {
    runTests();
    return 0;
}