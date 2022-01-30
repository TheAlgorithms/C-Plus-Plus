/**
 * @file
 * @brief Linear Algebra Utilities
 * @details
 * This file contains various functions that implement useful
 * linear algebra procedures such as determination of matrix
 * reduced row echelon form, inversion of a matrix, matrix -
 * matrix multiplication, matrix - vector multiplication 
 * and determining matrix equality. These functions operate
 * on data structures in the standard library.
 * @author [Jeya Iyadurai] (https://github.com/JeyaI)
 */

#include <cassert>   /// for assert
#include <vector>    /// for std::vector
#include <iostream>  /// for io operations

/**
 * @linear_algebra 
 */
namespace linear_algebra {

/**
 * @brief Returns reduced row echelon form of input matrix.
 * @param input_matrix reference to a matrix represented as a std::vector<std::vector<double>>
 * @returns reference to rref matrix represented as a std::vector<std::vector<double>>
 */

std::vector<std::vector<double>>& rref(std::vector<std::vector<double>>& input_matrix) {
    int rows = input_matrix.size();
	int columns = input_matrix[0].size();
	
	std::vector<std::vector<double>>* working_matrix = new std::vector<std::vector<double>>();
	*working_matrix = input_matrix;
	
	for(int k = 0; k < rows; k++){
		//Loop through each row of the matrix
		if((*working_matrix)[k][k] == 0){
			//If diagonal entry of a row is 0, swap it with row below
			if(k == rows - 1){
				break;
			}
			std::vector<double> temp = (*working_matrix)[k];
			(*working_matrix)[k] = (*working_matrix)[k+1];
			(*working_matrix)[k+1] = temp;
		}
		for(int l = k+1; l < rows; l++){
			//Subtract linear combinations to eliminate entries in kth column
			double ratio = (*working_matrix)[l][k] / (*working_matrix)[k][k];
			for(int i = k; i < (*working_matrix)[l].size(); i++){
				(*working_matrix)[l][i] -= (*working_matrix)[k][i] * ratio;
			}
		}
	}
	
	//working_matrix is now in echelon form
	
	for(int k = ((columns > rows) ? rows - 1 : columns - 1); k > 0; k--){
		//Loops "right to left" in matrix
		if ((*working_matrix)[k][k] == 0){
			continue;
		}
		for(int l = k-1; l >= 0; l--){
			//Subtract linear combinations to eliminate entries above diagonal
			double ratio = (*working_matrix)[l][k] / (*working_matrix)[k][k];
			for(int i = k; i < (*working_matrix)[l].size(); i++){
				(*working_matrix)[l][i] -= (*working_matrix)[k][i] * ratio;
			}
		}
	}
	
	for(int i = 0; i < rows && i < columns; i++){
		//Loop through each row and scale each row so leading entry is a "1"
		double scale = (*working_matrix)[i][i];
		if (scale == 0){
			continue;
		}
		(*working_matrix)[i][i] = 1;
		for(int j = i + 1; j < (*working_matrix)[i].size(); j++){
			(*working_matrix)[i][j] /= scale;
		}
	}
	
	//working_matrix is now in row reduced echelon form
	
	return *working_matrix;
}

/**
 * @brief Returns inverse of a matrix
 * @param input_matrix reference to an invertible matrix represented as a std::vector<std::vector<double>>
 * @returns eference to inverse of input invertible matrix represented as a std::vector<std::vector<double>>
 */

std::vector<std::vector<double>>& inverse(std::vector<std::vector<double>>& input_matrix) {
	
	int n = input_matrix.size();
	
	std::vector<std::vector<double>>* working_matrix = new std::vector<std::vector<double>>();
	*working_matrix = input_matrix;
	
	//Join identity block matrix 
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i==j){
				(*working_matrix)[i].push_back(1.00);
			}else{
				(*working_matrix)[i].push_back(0.00);
			}
		}
	}
	
	*working_matrix = rref(*working_matrix);
	
	//Desired inverted matrix is right half of working_matrix
	std::vector<std::vector<double>>* inverted_matrix = new std::vector<std::vector<double>>(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			(*inverted_matrix)[i].push_back((*working_matrix)[i][n+j]);
		}
	}
	
	delete working_matrix;
	
	return (*inverted_matrix);
	
}

/**
 * @brief Performs matrix multiplication (matrix1 * matrix2)
 * @param matrix1 reference to an m x n matrix represented as a std::vector<std::vector<double>>
 * @param matrix2 reference to an n x m matrix represented as a std::vector<std::vector<double>>
 * @returns reference to resultant multiplied matrix represented as a std::vector<std::vector<double>>
 */

std::vector<std::vector<double>>& multiply(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2) {
    
	std::vector<std::vector<double>>* working_matrix = new std::vector<std::vector<double>>(matrix1.size());
	
	//Row/Column definition of matrix multiplication
	for(int m2column = 0; m2column < matrix2[0].size(); m2column++){
		for(int m1row = 0; m1row < matrix1.size(); m1row++){
			double sum = 0;
			for(int i = 0; i < matrix2.size(); i++){
				sum += matrix1[m1row][i] * matrix2[i][m2column];
			}
			(*working_matrix)[m1row].push_back(sum);
		}
	}
	
	return (*working_matrix);
}

/**
 * @brief Performs matrix - vector multiplication (matrix * vector)
 * @param matrix reference to an m x n matrix represented as a std::vector<std::vector<double>>
 * @param vector reference to an n x 1 vector represented as a std::vector<double>
 * @returns reference to resultant multiplied vector represented as a std::vector<double>
 */

std::vector<double>& multiply(std::vector<std::vector<double>>& matrix, std::vector<double>& vector) {
    
	std::vector<double>* working_vector = new std::vector<double>(matrix.size());
	
	//Standard definition of matrix - vector multiplication
	for(int mrow = 0; mrow < matrix.size(); mrow++){
		double sum = 0;
		for(int i = 0; i < vector.size(); i++){
			sum += matrix[mrow][i] * vector[i];
		}
		(*working_vector).push_back(sum);
	}

	return (*working_vector);
}


/**
 * @brief Prints the contents of a matrix
 * @param matrix reference to an m x n matrix represented as a std::vector<std::vector<double>>
 * @returns void
 */

void print_matrix(std::vector<std::vector<double>>& matrix){
	
	for(int i = 0; i < matrix.size(); i++){
		for(int j = 0; j < matrix[0].size(); j++){
			std::cout << matrix[i][j] << " "; 
		}
		std::cout << std::endl;
	}
}

/**
 * @brief Compares equality of two matrices, up to the level of a provided precision
 * @param matrix1 reference to an m x n matrix represented as a std::vector<std::vector<double>>
 * @param matrix2 reference to an m x n matrix represented as a std::vector<std::vector<double>>
 * @param precision optional double value that represents how close corresponding entries must be for equality (default value is 1/65536)
 * @returns `true` if all corresponding entries in the two matricies are within "precision" of each other
 * @returns `false` if at least one corresponding entry in the two matricies is farther than "precision" from the other
 */

bool is_equal(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2, double precision = 1.0/65536) {
    
	for(int i = 0; i < matrix1.size(); i++){
		for(int j = 0; j < matrix2.size(); j++){
			if(matrix1[i][j] - matrix2[i][j] > precision || matrix1[i][j] - matrix2[i][j] < -1 * precision){
				return false;
			}
		}
	}
	
	return true;
}

} // namespace linear_algebra

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    //assert(func(...) == ...); // this ensures that the algorithm works as expected
	
    // can have multiple checks
	
	/* TEST 1: is_equal */
	std::vector<std::vector<double>> matrix1{{2, -1, 5}, {1, -2, 4}, {5, -1, -1}};
	std::vector<std::vector<double>> matrix2{{2, -1, 5}, {1, -2, 4}, {5, -1, -1}};
	std::vector<std::vector<double>> matrix3{{2, -1, 5}, {1, -2, 4+1.0/262144}, {5, -1, -1}};
	std::vector<std::vector<double>> matrix4{{2, -10, 5}, {40, -2, 4}, {5, -1, -17}};
	std::vector<std::vector<double>> matrix5{{2, -1, 6}, {1, -2, 4}, {5, -1, -1}};
	
	assert(linear_algebra::is_equal(matrix1, matrix1) == true);
	assert(linear_algebra::is_equal(matrix1, matrix2) == true);
	assert(linear_algebra::is_equal(matrix1, matrix3) == true);
	assert(linear_algebra::is_equal(matrix1, matrix4) == false);
	assert(linear_algebra::is_equal(matrix1, matrix5) == false);
	assert(linear_algebra::is_equal(matrix1, matrix3, 1.0/524288) == false);
	
	/* TEST 2: multiply */
	std::vector<std::vector<double>> matrix6{{2, -1, 5}, {1, -2, 4}, {5, -1, -1}};
	std::vector<std::vector<double>> matrix7{{-2, -2, 3}, {6, 6, 2}, {-1, 2, -1}};
	std::vector<std::vector<double>> matrix8 = linear_algebra::multiply(matrix6, matrix7);
	std::vector<std::vector<double>> matrix9{{-15, 0, -1}, {-18, -6, -5}, {-15, -18, 14}};
	
	assert(linear_algebra::is_equal(matrix8, matrix9) == true);
	
	/* TEST 3: rref */
	std::vector<std::vector<double>> matrix10{{2, -1, 5}, {1, -2, 4}, {5, -1, -1}};
	std::vector<std::vector<double>> eye3{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	std::vector<std::vector<double>> matrix11 = linear_algebra::rref(matrix10);
	
	assert(linear_algebra::is_equal(matrix11, eye3) == true);
	
	std::vector<std::vector<double>> matrix12{{2, -1, 5, 7}, {1, -2, 4, -3}, {5, -1, -1, 2}};
	std::vector<std::vector<double>> matrix13 = linear_algebra::rref(matrix12);
	std::vector<std::vector<double>> matrix14{{1, 0, 0, 2}, {0, 1, 0, 37.0/6}, {0, 0, 1, 11.0/6}};
	
	assert(linear_algebra::is_equal(matrix13, matrix14) == true);
	
	/* TEST 4: inverse */
	std::vector<std::vector<double>> matrix15{{2, -1, 5}, {1, -2, 4}, {5, -1, -1}};
	std::vector<std::vector<double>> matrix16 = linear_algebra::inverse(matrix15);
	std::vector<std::vector<double>> matrix17 = linear_algebra::multiply(matrix16, matrix15);
	
	assert(linear_algebra::is_equal(matrix17, eye3) == true);
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    
	//A sample program utilizing linear_algebra::inverse
	
	int rows = 0;
	int columns = 0;
	double val = 0.0;
	
	std::cout << "Calculate Inverse Matrix (for expected results, please input an invertible square matrix):" << std::endl;
	std::cout << "Number of rows/columns in matrix: ";
	std::cin >> rows;
	std::cout << "Number of columns in matrix: ";
	std::cin >> columns;
	
	std::vector<std::vector<double>> input_matrix(rows);
	
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			std::cout << "Enter data for entry in row " << (i+1) << ", column " << (j+1) << ": ";
			std::cin >> val;
			input_matrix[i].push_back(val);
		}
	}
	
	std::vector<std::vector<double>> inverse_matrix = linear_algebra::inverse(input_matrix);
	
	std::cout << "Calculated Inverse Matrix: " << std::endl;
	linear_algebra::print_matrix(inverse_matrix);
	
    return 0;
}