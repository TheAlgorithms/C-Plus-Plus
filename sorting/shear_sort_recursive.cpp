// Recursive Shear Sort implementation in C++
// This implementation was inspired by Professor Sandeep Sen's lecture on Shear
// Sort The pseudocode was provided in the JOURNAL OF PARALLEL AND DISTRIBUTED
// COMPUTING - Two Nearly Optimal Sorting Algorithms for Mesh-Connected
// Processor Arrays Using Shear-sort.

/// The Shear Sort algorithm is a parallel sorting algorithm that sorts a 2D
/// array (matrix) in a "snake-like" pattern (even rows sorted left-to-right,
/// odd rows sorted right-to-left). The recursive version divides the matrix
/// into four quadrants, sorts each recursively, and then merges them together.
/// Assumes the input matrix is square and has dimensions that are powers of 2
/// (e.g., 2x2, 4x4, 8x8, etc.) for simplicity.
// Note: Any mention of n in the code refers to the dimension of the square
// matrix (n x n) and not the total number of elements (which would be n^2).
#include <cassert>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace sorting {
// Forward declarations of the functions used
void merge2d(std::vector<std::vector<int>>& matrix, int startrow, int endrow,
             int startcol, int endcol);
void columnsort(std::vector<std::vector<int>>& matrix, int startrow, int endrow,
                int startcol, int endcol);
void rowsnakesort(std::vector<std::vector<int>>& matrix, int startrow,
                  int endrow, int startcol, int endcol);
void shearsort_recursive(std::vector<std::vector<int>>& matrix, int startrow,
                         int endrow, int startcol, int endcol);
void shearsort(std::vector<std::vector<int>>& matrix);
std::vector<int> flatten_snake(const std::vector<std::vector<int>>& matrix);
bool is_snake_sorted(const std::vector<std::vector<int>>& matrix);
void print_matrix(const std::vector<std::vector<int>>& matrix);
void run_fixed_test(const std::string& name,
                    std::vector<std::vector<int>> matrix, bool printMatrices);
void tests();

/// Recursive function to perform shear sort on a submatrix defined by the given
/// row and column boundaries by recursively dividing it into quadrants and
/// merging them back together in sorted order.
void shearsort_recursive(std::vector<std::vector<int>>& matrix, int startrow,
                         int endrow, int startcol, int endcol) {
    int n = endrow - startrow;
    if (n == 1)
        return;  // Base case: 1x1 matrix is already sorted
    if (n == 2) {
        // Sort the 2x2 matrix in 2 steps
        rowsnakesort(matrix, startrow, endrow, startcol, endcol);
        columnsort(matrix, startrow, endrow, startcol, endcol);
        rowsnakesort(matrix, startrow, endrow, startcol, endcol);
        columnsort(matrix, startrow, endrow, startcol, endcol);
        return;
    }
    // Recursive case: divide the matrix into four submatrices
    shearsort_recursive(matrix, startrow, startrow + n / 2, startcol,
                        startcol + n / 2);  // Top-left
    shearsort_recursive(matrix, startrow, startrow + n / 2, startcol + n / 2,
                        endcol);  // Top-right
    shearsort_recursive(matrix, startrow + n / 2, endrow, startcol,
                        startcol + n / 2);  // Bottom-left
    shearsort_recursive(matrix, startrow + n / 2, endrow, startcol + n / 2,
                        endcol);  // Bottom-right
    merge2d(matrix, startrow, endrow, startcol,
            endcol);  // Merge the four sorted submatrices
}

/// Merge the four sorted submatrices into a single sorted matrix
/// Pseudocode given on page 156 of
// https://pdf.sciencedirectassets.com/272438/1-s2.0-S0743731500X01530/1-s2.0-0743731589900476/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjENH%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJIMEYCIQClremfXXZwvQ2OHtoHUExVMKd2HkakPL4xnJapckfqzwIhALsX3cHw0XNAHPPVSnVpp3bGMlBZFtbYHJaSQ24mG2zpKrwFCJr%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQBRoMMDU5MDAzNTQ2ODY1IgyzeMel%2BZswr7tJlZQqkAVTHHMXWJlkt4HPdpvqoJBByx9UkXQrg0gxikE93jds3s511QuInGSXXBbuK2xkNR9faV%2BPwsj%2BXy3N629IT%2F%2BABisAs%2FDvA5kx1czMlOy%2FoRXa%2BhE0m5hxlIcx7tHUSkqyaQw9zyuUZ%2BTIZEJWU1gVYoTdn66cEOKs2CxDrV3Yt3WE2BM8GdLgDc7B8uS%2F5MmhgM5yNBxhRiyZvWUkF40QbzaxbfXW6VIFl5t59LahF5IDSJxeIyYa6sN5EGGMSJUBq1UbfKHyRrIhEWcEathfG%2BfYc3PPPMqQL2l0I1HnKSotvfIj5h6vqtkSrHXHlaYNipPSCJWktVvXSVMIjj6Sg5mB14YgBWcaR%2FB9k389AOVLygiiBRCa3yEzO%2FhsahBpKi8ZbsmMBwagZEd%2FZx5mzaQcSnD7mUEZUkIU%2B4eJ%2Bv7Wns6L2iwLY0PnP2i%2BiP13bjMM8oODYIhSwf8oTUCae%2FZfAaBTSqc92uQeE4W18Iju1iVmWggN8%2FrGRmcyb61OJOVa9BrUkAkHo9lT7SPYnv8W7SsgPMOff10g3QH4Z9uB7WMnKUQx2s%2F1kC9Lv6Vrr6WM55Ubhs4VZUDlNbI8oJ7j7oLqN3iSgMRAKl0KhjJWOgNFXlLGLZ8Uo4dYoqtAvdhN%2BrcQC6YVRSiUK0qCiEfMHvkI7kXGXH9XC4M3kV7HvrS11nXa5D1Pt2rqQXpKcEByy6fuMBZHv7seBvcxjZtLvtt%2B24r%2B%2Bj7nOY4k0GNbkFYlVoI6vhW7uXi7PZ1KjAxl5VJRr7F4yPvyG9fSOTy6CtJtFQv2WtybFsWj9Hlruy7Y2zHgHRia%2B7WniNm9au8DUqPSu0EiVwYc0na%2BTqEk1HjEfV0woYTXqDE6KjCr1tLNBjqwAUsfz%2FpRnvgQ31wMV3hrz1a0Vesj8k0QoA22krznrhEj8WICy49XYJqtKmYTOagqRPIDEpiPl9ZvfvR%2B2jZ87KUxY8R3x5BDAWzCR8%2B4zQ2YVotndRCm0usnFfYEdegDY%2BCFdbapBJ9iIiNjUqwUtkkmrxyT4cihjZS0hk%2Ba7Pw61mnac8igzFYSOso6VQs2GREHFfv8Q%2BbaO0VE1v2Hcy0Wdk7DqXhc8tgYagJEselV&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20260314T011358Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYRXJ3F6KE%2F20260314%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=02fdcb72fc3a0ba9de093fc3358fc30e2becc169a4a58daa8ef910c00357d377&hash=ea80c684dbb9b638bb798cd1208d3d6c23ac114aebb6f862ab41baa5bb1a5c3d&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=0743731589900476&tid=spdf-96344670-d1d0-4754-9a03-96c2ca3538d9&sid=d65b6c883b8e034de889d97679ff366950aagxrqb&type=client&tsoh=d3d3LnNjaWVuY2VkaXJlY3QuY29t&rh=d3d3LnNjaWVuY2VkaXJlY3QuY29t&ua=01055f0b0404560d565a&rr=9dbf6b397cb945b6&cc=gb
/// We first shift the odd rows to the right by n/2 positions, then sort all
/// columns in ascending order, and finally perform two iterations of shearsort.
void merge2d(std::vector<std::vector<int>>& matrix, int startrow, int endrow,
             int startcol, int endcol) {
    int n = endrow - startrow;
    int shift = n / 2;

    for (int row = startrow; row < endrow; row++) {
        int localRow = row - startrow;
        if (localRow % 2 == 1) {
            std::vector<int> temp(endcol - startcol);

            for (int col = startcol; col < endcol; col++) {
                temp[col - startcol] = matrix[row][col];
            }

            for (int col = 0; col < endcol - startcol; col++) {
                int newPos = (col + shift) % (endcol - startcol);
                matrix[row][startcol + newPos] = temp[col];
            }
        }
    }

    columnsort(matrix, startrow, endrow, startcol, endcol);

    for (int i = 0; i < 2; i++) {
        rowsnakesort(matrix, startrow, endrow, startcol, endcol);
        columnsort(matrix, startrow, endrow, startcol, endcol);
    }
}

/// sort columns in ascending order
void columnsort(std::vector<std::vector<int>>& matrix, int startrow, int endrow,
                int startcol, int endcol) {
    for (int col = startcol; col < endcol; col++) {
        std::vector<int> temp(endrow - startrow);
        for (int row = startrow; row < endrow; row++) {
            temp[row - startrow] = matrix[row][col];
        }
        std::sort(temp.begin(), temp.end());
        for (int row = startrow; row < endrow; row++) {
            matrix[row][col] = temp[row - startrow];
        }
    }
}

/// sort rows in snake pattern :- odd rows in ascending order and even rows in
/// descending order
void rowsnakesort(std::vector<std::vector<int>>& matrix, int startrow,
                  int endrow, int startcol, int endcol) {
    for (int row = startrow; row < endrow; row++) {
        if ((row - startrow) % 2 == 0) {
            std::sort(matrix[row].begin() + startcol,
                      matrix[row].begin() + endcol);
        } else {
            std::sort(matrix[row].begin() + startcol,
                      matrix[row].begin() + endcol, std::greater<int>());
        }
    }
}

/// Check if the matrix is a non empty square matrix and then call the recursive
/// shearsort function
void shearsort(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.size() != matrix[0].size()) {
        throw std::invalid_argument("Input must be a non-empty square matrix.");
    }
    shearsort_recursive(matrix, 0, static_cast<int>(matrix.size()), 0,
                        static_cast<int>(matrix[0].size()));
}

// Below are some helper functions and test code to validate the implementation
// of shearsort_recursive

/// Flattens the matrix into a single vector in snake order (even rows
/// left-to-right, odd rows right-to-left)
std::vector<int> flatten_snake(const std::vector<std::vector<int>>& matrix) {
    int n = static_cast<int>(matrix.size());
    std::vector<int> out;
    out.reserve(n * n);

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++) out.push_back(matrix[i][j]);
        } else {
            for (int j = n - 1; j >= 0; j--) out.push_back(matrix[i][j]);
        }
    }
    return out;
}

/// checks if the matrix is sorted correctly
bool is_snake_sorted(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty())
        return true;

    std::vector<int> vals = flatten_snake(matrix);
    for (size_t i = 1; i < vals.size(); i++) {
        if (vals[i - 1] > vals[i])
            return false;
    }
    return true;
}

/// print the matrix in a formatted way
void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int x : row) {
            std::cout << std::setw(6) << x << ' ';
        }
        std::cout << '\n';
    }
}

/// Runs a fixed test case and reports the results
void run_fixed_test(const std::string& name,
                    std::vector<std::vector<int>> matrix,
                    bool printMatrices = false) {
    if (printMatrices) {
        std::cout << "===== " << name << " =====\n";
        std::cout << "Before:\n";
        print_matrix(matrix);
    }

    auto start = std::chrono::high_resolution_clock::now();
    shearsort(matrix);
    auto end = std::chrono::high_resolution_clock::now();

    double us = std::chrono::duration<double, std::micro>(end - start).count();

    if (printMatrices) {
        std::cout << "After:\n";
        print_matrix(matrix);

        std::cout << "Snake-sorted? "
                  << (is_snake_sorted(matrix) ? "PASS" : "FAIL") << '\n';
        std::cout << "Time: " << us << " us\n\n";
    }
    assert(is_snake_sorted(matrix));
}

// tests the implementation of shearsort_recursive with multiple fixed test
// cases and also checks for invalid input handling
void tests() {
    run_fixed_test("2x2", {{4, 1}, {3, 2}});

    run_fixed_test(
        "4x4", {{10, 3, 15, 8}, {1, 14, 6, 11}, {13, 2, 16, 5}, {7, 12, 4, 9}});

    run_fixed_test("8x8", {{64, 2, 3, 4, 5, 6, 7, 8},
                           {9, 10, 11, 12, 13, 14, 15, 16},
                           {17, 18, 19, 20, 21, 22, 23, 24},
                           {25, 26, 27, 28, 29, 30, 31, 32},
                           {33, 34, 35, 36, 37, 38, 39, 40},
                           {41, 42, 43, 44, 45, 46, 47, 48},
                           {49, 50, 51, 52, 53, 54, 55, 56},
                           {57, 58, 59, 60, 61, 62, 63, 1}});

    bool invalidinput = false;
    try {
        std::vector<std::vector<int>> bad = {{1, 2, 3}, {4, 5, 6}};
        shearsort(bad);
    } catch (const std::invalid_argument&) {
        invalidinput = true;
    }
    assert(invalidinput);

    std::cout << "All tests passed!\n";
}
}  // namespace sorting

int main() {
    sorting::tests();

    std::vector<std::vector<int>> demo = {
        {10, 3, 15, 8}, {1, 14, 6, 11}, {13, 2, 16, 5}, {7, 12, 4, 9}};

    sorting::run_fixed_test("Demo 4x4", demo, true);
}
