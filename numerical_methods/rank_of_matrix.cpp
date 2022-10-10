/**
 * The rank of a matrix is the largest number of 
 * 		linearly independent rows/columns of the matrix. 
 * 		The rank is not only defined for square matrices.
 * The rank of a matrix can also be defined as the largest 
 * 		order of any non-zero minor in the matrix.
 * Let the matrix be rectangular and have size N x M. 
 * 		Note that if the matrix is square and its determinant is non-zero, 
 * 		then the rank is  N (= M); otherwise it will be less. 
 * 		Generally, the rank of a matrix does not exceed min(N, M).
 */

#include <iostream>
#include <vector>
const double epsilon = 1E-9;
/**
 * We will be using Gaussian Elimination for computing rank
 * 
 */

int get_rank(std::vector<std::vector<double>> matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();
	int rank = 0;
	std::vector<bool> row_selected(rows, false);

	for(int i = 0; i < cols; i++) {
		int j;
		for(j = 0; j < rows; j++) {
			if(!row_selected[j] and abs(matrix[j][i]) > epsilon) {
				break;
			}
		}
		if(j != rows) {
			++rank;
			row_selected[j] = true;
			for(int p = i + 1; p < cols; p++) {
				matrix[j][p] /= matrix[j][i];
			}
			for(int k = 0; k < rows; k++) {
				if(k != cols and abs(matrix[k][i]) > epsilon) {
					for(int p = i + 1; p < cols; p++) {
						matrix[k][p] -= matrix[j][p] * matrix[k][i];
					}
				}
			}
		}
	}
	return rank;
}

/**
 * Main Function 
 */

int main() {
	std::vector<std::vector<double>> matrix = {{1, 2, 3},
												{4, 5, 6},
												{7, 8, 9}};
	std::cout << "Rank of the matrix " << "\n";
	for(auto row: matrix) {
		for(auto ele: row) {
			std::cout << ele << " ";
		}
		std::cout << "\n";
	}
	std::cout << "is " << get_rank(matrix) << "\n";
	return 0;
}
