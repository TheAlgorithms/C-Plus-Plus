/**
 * @file vector_ops.hpp
 * @author [Deep Raval](https://github.com/imdeep2905)
 *
 * @brief Various functions for vectors associated with [NeuralNetwork (aka
 * Multilayer Perceptron)]
 * (https://en.wikipedia.org/wiki/Multilayer_perceptron).
 *
 */
#ifndef VECTOR_OPS_FOR_NN
#define VECTOR_OPS_FOR_NN

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <valarray>
#include <vector>

/**
 * @namespace machine_learning
 * @brief Machine Learning algorithms
 */
namespace machine_learning {
/**
 * Overloaded operator "<<" to print 2D vector
 * @tparam T typename of the vector
 * @param out std::ostream to output
 * @param A 2D vector to be printed
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::valarray<T>> const &A) {
    // Setting output precision to 4 in case of floating point numbers
    out.precision(4);
    for (const auto &a : A) {       // For each row in A
        for (const auto &x : a) {   // For each element in row
            std::cout << x << ' ';  // print element
        }
        std::cout << std::endl;
    }
    return out;
}

/**
 * Overloaded operator "<<" to print a pair
 * @tparam T typename of the pair
 * @param out std::ostream to output
 * @param A Pair to be printed
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::pair<T, T> &A) {
    // Setting output precision to 4 in case of floating point numbers
    out.precision(4);
    // printing pair in the form (p, q)
    std::cout << "(" << A.first << ", " << A.second << ")";
    return out;
}

/**
 * Overloaded operator "<<" to print a 1D vector
 * @tparam T typename of the vector
 * @param out std::ostream to output
 * @param A 1D vector to be printed
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::valarray<T> &A) {
    // Setting output precision to 4 in case of floating point numbers
    out.precision(4);
    for (const auto &a : A) {   // For every element in the vector.
        std::cout << a << ' ';  // Print element
    }
    std::cout << std::endl;
    return out;
}

/**
 * Function to insert element into 1D vector
 * @tparam T typename of the 1D vector and the element
 * @param A 1D vector in which element will to be inserted
 * @param ele element to be inserted
 * @return new resultant vector
 */
template <typename T>
std::valarray<T> insert_element(const std::valarray<T> &A, const T &ele) {
    std::valarray<T> B;      // New 1D vector to store resultant vector
    B.resize(A.size() + 1);  // Resizing it accordingly
    for (size_t i = 0; i < A.size(); i++) {  // For every element in A
        B[i] = A[i];                         // Copy element in B
    }
    B[B.size() - 1] = ele;  // Inserting new element in last position
    return B;               // Return resultant vector
}

/**
 * Function to remove first element from 1D vector
 * @tparam T typename of the vector
 * @param A 1D vector from which first element will be removed
 * @return new resultant vector
 */
template <typename T>
std::valarray<T> pop_front(const std::valarray<T> &A) {
    std::valarray<T> B;      // New 1D vector to store resultant vector
    B.resize(A.size() - 1);  // Resizing it accordingly
    for (size_t i = 1; i < A.size();
         i++) {           // // For every (except first) element in A
        B[i - 1] = A[i];  // Copy element in B with left shifted position
    }
    return B;  // Return resultant vector
}

/**
 * Function to remove last element from 1D vector
 * @tparam T typename of the vector
 * @param A 1D vector from which last element will be removed
 * @return new resultant vector
 */
template <typename T>
std::valarray<T> pop_back(const std::valarray<T> &A) {
    std::valarray<T> B;      // New 1D vector to store resultant vector
    B.resize(A.size() - 1);  // Resizing it accordingly
    for (size_t i = 0; i < A.size() - 1;
         i++) {       // For every (except last) element in A
        B[i] = A[i];  // Copy element in B
    }
    return B;  // Return resultant vector
}

/**
 * Function to equally shuffle two 3D vectors (used for shuffling training data)
 * @tparam T typename of the vector
 * @param A First 3D vector
 * @param B Second 3D vector
 */
template <typename T>
void equal_shuffle(std::vector<std::vector<std::valarray<T>>> &A,
                   std::vector<std::vector<std::valarray<T>>> &B) {
    // If two vectors have different sizes
    if (A.size() != B.size()) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr
            << "Can not equally shuffle two vectors with different sizes: ";
        std::cerr << A.size() << " and " << B.size() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < A.size(); i++) {  // For every element in A and B
        // Genrating random index < size of A and B
        std::srand(std::chrono::system_clock::now().time_since_epoch().count());
        size_t random_index = std::rand() % A.size();
        // Swap elements in both A and B with same random index
        std::swap(A[i], A[random_index]);
        std::swap(B[i], B[random_index]);
    }
    return;
}

/**
 * Function to initialize given 2D vector using uniform random initialization
 * @tparam T typename of the vector
 * @param A 2D vector to be initialized
 * @param shape required shape
 * @param low lower limit on value
 * @param high upper limit on value
 */
template <typename T>
void uniform_random_initialization(std::vector<std::valarray<T>> &A,
                                   const std::pair<size_t, size_t> &shape,
                                   const T &low, const T &high) {
    A.clear();  // Making A empty
    // Uniform distribution in range [low, high]
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<T> distribution(low, high);
    for (size_t i = 0; i < shape.first; i++) {  // For every row
        std::valarray<T>
            row;  // Making empty row which will be inserted in vector
        row.resize(shape.second);
        for (auto &r : row) {             // For every element in row
            r = distribution(generator);  // copy random number
        }
        A.push_back(row);  // Insert new row in vector
    }
    return;
}

/**
 * Function to Intialize 2D vector as unit matrix
 * @tparam T typename of the vector
 * @param A 2D vector to be initialized
 * @param shape required shape
 */
template <typename T>
void unit_matrix_initialization(std::vector<std::valarray<T>> &A,
                                const std::pair<size_t, size_t> &shape) {
    A.clear();  // Making A empty
    for (size_t i = 0; i < shape.first; i++) {
        std::valarray<T>
            row;  // Making empty row which will be inserted in vector
        row.resize(shape.second);
        row[i] = T(1);     // Insert 1 at ith position
        A.push_back(row);  // Insert new row in vector
    }
    return;
}

/**
 * Function to Intialize 2D vector as zeroes
 * @tparam T typename of the vector
 * @param A 2D vector to be initialized
 * @param shape required shape
 */
template <typename T>
void zeroes_initialization(std::vector<std::valarray<T>> &A,
                           const std::pair<size_t, size_t> &shape) {
    A.clear();  // Making A empty
    for (size_t i = 0; i < shape.first; i++) {
        std::valarray<T>
            row;  // Making empty row which will be inserted in vector
        row.resize(shape.second);  // By default all elements are zero
        A.push_back(row);          // Insert new row in vector
    }
    return;
}

/**
 * Function to get sum of all elements in 2D vector
 * @tparam T typename of the vector
 * @param A 2D vector for which sum is required
 * @return returns sum of all elements of 2D vector
 */
template <typename T>
T sum(const std::vector<std::valarray<T>> &A) {
    T cur_sum = 0;             // Initially sum is zero
    for (const auto &a : A) {  // For every row in A
        cur_sum += a.sum();    // Add sum of that row to current sum
    }
    return cur_sum;  // Return sum
}

/**
 * Function to get shape of given 2D vector
 * @tparam T typename of the vector
 * @param A 2D vector for which shape is required
 * @return shape as pair
 */
template <typename T>
std::pair<size_t, size_t> get_shape(const std::vector<std::valarray<T>> &A) {
    const size_t sub_size = (*A.begin()).size();
    for (const auto &a : A) {
        // If supplied vector don't have same shape in all rows
        if (a.size() != sub_size) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Supplied vector is not 2D Matrix" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    return std::make_pair(A.size(), sub_size);  // Return shape as pair
}

/**
 * Function to scale given 3D vector using min-max scaler
 * @tparam T typename of the vector
 * @param A 3D vector which will be scaled
 * @param low new minimum value
 * @param high new maximum value
 * @return new scaled 3D vector
 */
template <typename T>
std::vector<std::vector<std::valarray<T>>> minmax_scaler(
    const std::vector<std::vector<std::valarray<T>>> &A, const T &low,
    const T &high) {
    std::vector<std::vector<std::valarray<T>>> B =
        A;                               // Copying into new vector B
    const auto shape = get_shape(B[0]);  // Storing shape of B's every element
    // As this function is used for scaling training data vector should be of
    // shape (1, X)
    if (shape.first != 1) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr
            << "Supplied vector is not supported for minmax scaling, shape: ";
        std::cerr << shape << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < shape.second; i++) {
        T min = B[0][0][i], max = B[0][0][i];
        for (size_t j = 0; j < B.size(); j++) {
            // Updating minimum and maximum values
            min = std::min(min, B[j][0][i]);
            max = std::max(max, B[j][0][i]);
        }
        for (size_t j = 0; j < B.size(); j++) {
            // Applying min-max scaler formula
            B[j][0][i] =
                ((B[j][0][i] - min) / (max - min)) * (high - low) + low;
        }
    }
    return B;  // Return new resultant 3D vector
}

/**
 * Function to get index of maximum element in 2D vector
 * @tparam T typename of the vector
 * @param A 2D vector for which maximum index is required
 * @return index of maximum element
 */
template <typename T>
size_t argmax(const std::vector<std::valarray<T>> &A) {
    const auto shape = get_shape(A);
    // As this function is used on predicted (or target) vector, shape should be
    // (1, X)
    if (shape.first != 1) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Supplied vector is ineligible for argmax" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // Return distance of max element from first element (i.e. index)
    return std::distance(std::begin(A[0]),
                         std::max_element(std::begin(A[0]), std::end(A[0])));
}

/**
 * Function which applys supplied function to every element of 2D vector
 * @tparam T typename of the vector
 * @param A 2D vector on which function will be applied
 * @param func Function to be applied
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> apply_function(
    const std::vector<std::valarray<T>> &A, T (*func)(const T &)) {
    std::vector<std::valarray<double>> B =
        A;                  // New vector to store resultant vector
    for (auto &b : B) {     // For every row in vector
        b = b.apply(func);  // Apply function to that row
    }
    return B;  // Return new resultant 2D vector
}

/**
 * Overloaded operator "*" to multiply given 2D vector with scaler
 * @tparam T typename of both vector and the scaler
 * @param A 2D vector to which scaler will be multiplied
 * @param val Scaler value which will be multiplied
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> operator*(const std::vector<std::valarray<T>> &A,
                                        const T &val) {
    std::vector<std::valarray<double>> B =
        A;               // New vector to store resultant vector
    for (auto &b : B) {  // For every row in vector
        b = b * val;     // Multiply row with scaler
    }
    return B;  // Return new resultant 2D vector
}

/**
 * Overloaded operator "/" to divide given 2D vector with scaler
 * @tparam T typename of the vector and the scaler
 * @param A 2D vector to which scaler will be divided
 * @param val Scaler value which will be divided
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> operator/(const std::vector<std::valarray<T>> &A,
                                        const T &val) {
    std::vector<std::valarray<double>> B =
        A;               // New vector to store resultant vector
    for (auto &b : B) {  // For every row in vector
        b = b / val;     // Divide row with scaler
    }
    return B;  // Return new resultant 2D vector
}

/**
 * Function to get transpose of 2D vector
 * @tparam T typename of the vector
 * @param A 2D vector which will be transposed
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> transpose(
    const std::vector<std::valarray<T>> &A) {
    const auto shape = get_shape(A);  // Current shape of vector
    std::vector<std::valarray<T>> B;  // New vector to store result
    // Storing transpose values of A in B
    for (size_t j = 0; j < shape.second; j++) {
        std::valarray<T> row;
        row.resize(shape.first);
        for (size_t i = 0; i < shape.first; i++) {
            row[i] = A[i][j];
        }
        B.push_back(row);
    }
    return B;  // Return new resultant 2D vector
}

/**
 * Overloaded operator "+" to add two 2D vectors
 * @tparam T typename of the vector
 * @param A First 2D vector
 * @param B Second 2D vector
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> operator+(
    const std::vector<std::valarray<T>> &A,
    const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // If vectors don't have equal shape
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Supplied vectors have different shapes ";
        std::cerr << shape_a << " and " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;
    for (size_t i = 0; i < A.size(); i++) {  // For every row
        C.push_back(A[i] + B[i]);            // Elementwise addition
    }
    return C;  // Return new resultant 2D vector
}

/**
 * Overloaded operator "-" to add subtract 2D vectors
 * @tparam T typename of the vector
 * @param A First 2D vector
 * @param B Second 2D vector
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> operator-(
    const std::vector<std::valarray<T>> &A,
    const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // If vectors don't have equal shape
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Supplied vectors have different shapes ";
        std::cerr << shape_a << " and " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;         // Vector to store result
    for (size_t i = 0; i < A.size(); i++) {  // For every row
        C.push_back(A[i] - B[i]);            // Elementwise substraction
    }
    return C;  // Return new resultant 2D vector
}

/**
 * Function to multiply two 2D vectors
 * @tparam T typename of the vector
 * @param A First 2D vector
 * @param B Second 2D vector
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> multiply(const std::vector<std::valarray<T>> &A,
                                       const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // If vectors are not eligible for multiplication
    if (shape_a.second != shape_b.first) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Vectors are not eligible for multiplication ";
        std::cerr << shape_a << " and " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;  // Vector to store result
    // Normal matrix multiplication
    for (size_t i = 0; i < shape_a.first; i++) {
        std::valarray<T> row;
        row.resize(shape_b.second);
        for (size_t j = 0; j < shape_b.second; j++) {
            for (size_t k = 0; k < shape_a.second; k++) {
                row[j] += A[i][k] * B[k][j];
            }
        }
        C.push_back(row);
    }
    return C;  // Return new resultant 2D vector
}

/**
 * Function to get hadamard product of two 2D vectors
 * @tparam T typename of the vector
 * @param A First 2D vector
 * @param B Second 2D vector
 * @return new resultant vector
 */
template <typename T>
std::vector<std::valarray<T>> hadamard_product(
    const std::vector<std::valarray<T>> &A,
    const std::vector<std::valarray<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    // If vectors are not eligible for hadamard product
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Vectors have different shapes ";
        std::cerr << shape_a << " and " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::valarray<T>> C;  // Vector to store result
    for (size_t i = 0; i < A.size(); i++) {
        C.push_back(A[i] * B[i]);  // Elementwise multiplication
    }
    return C;  // Return new resultant 2D vector
}
}  // namespace machine_learning

#endif
