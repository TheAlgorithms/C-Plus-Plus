/**
 * @brief [Strassen's
 * algorithm](https://en.wikipedia.org/wiki/Strassen_algorithm) is one of the
 * methods for multiplying two matrices. It is one of the faster algorithms for
 * larger matrices than naive multiplication method.
 *
 * It involves dividing each matrices into 4 blocks, given they are evenly
 * divisible, and are combined with new defined matrices involving 7 matrix
 * multiplications instead of eight, yielding O(n^2.8073) complexity.
 *
 * @author [AshishYUO](https://github.com/AshishYUO)
 */
#include <cassert>   /// For assert operation
#include <chrono>    /// For std::chrono; time measurement
#include <iostream>  /// For I/O operations
#include <tuple>     /// For std::tuple
#include <vector>    /// For creating dynamic arrays

/**
 * @namespace divide_and_conquer
 * @brief Divide and Conquer algorithms
 */
namespace divide_and_conquer {

/**
 * @namespace strassens_multiplication
 * @brief Namespace for performing strassen's multiplication
 */
namespace strassens_multiplication {

/// Complement of 0 is a max integer.
constexpr size_t MAX_SIZE = ~0ULL;
/**
 * @brief Matrix class.
 */
template <typename T,
          typename = typename std::enable_if<
              std::is_integral<T>::value || std::is_floating_point<T>::value,
              bool>::type>
class Matrix {
    std::vector<std::vector<T>> _mat;

 public:
    /**
     * @brief Constructor
     * @tparam Integer ensuring integers are being evaluated and not other
     * data types.
     * @param size denoting the size of Matrix as size x size
     */
    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    explicit Matrix(const Integer size) {
        for (size_t i = 0; i < size; ++i) {
            _mat.emplace_back(std::vector<T>(size, 0));
        }
    }

    /**
     * @brief Constructor
     * @tparam Integer ensuring integers are being evaluated and not other
     * data types.
     * @param rows denoting the total rows of Matrix
     * @param cols denoting the total elements in each row of Matrix
     */
    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    Matrix(const Integer rows, const Integer cols) {
        for (size_t i = 0; i < rows; ++i) {
            _mat.emplace_back(std::vector<T>(cols, 0));
        }
    }

    /**
     * @brief Get the matrix shape
     * @returns pair of integer denoting total rows and columns
     */
    inline std::pair<size_t, size_t> size() const {
        return {_mat.size(), _mat[0].size()};
    }

    /**
     * @brief returns the address of the element at ith place
     * (here ith row of the matrix)
     * @tparam Integer any valid integer
     * @param index index which is requested
     * @returns the address of the element (here ith row or array)
     */
    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    inline std::vector<T> &operator[](const Integer index) {
        return _mat[index];
    }

    /**
     * @brief Creates a new matrix and returns a part of it.
     * @param row_start start of the row
     * @param row_end end of the row
     * @param col_start start of the col
     * @param col_end end of the column
     * @returns A slice of (row_end - row_start) x (col_end - col_start) size of
     * array starting from row_start row and col_start column
     */
    Matrix slice(const size_t row_start, const size_t row_end = MAX_SIZE,
                 const size_t col_start = MAX_SIZE,
                 const size_t col_end = MAX_SIZE) const {
        const size_t h_size =
            (row_end != MAX_SIZE ? row_end : _mat.size()) - row_start;
        const size_t v_size = (col_end != MAX_SIZE ? col_end : _mat[0].size()) -
                              (col_start != MAX_SIZE ? col_start : 0);
        Matrix result = Matrix<T>(h_size, v_size);

        const size_t v_start = (col_start != MAX_SIZE ? col_start : 0);
        for (size_t i = 0; i < h_size; ++i) {
            for (size_t j = 0; j < v_size; ++j) {
                result._mat[i][j] = _mat[i + row_start][j + v_start];
            }
        }
        return result;
    }

    /**
     * @brief Horizontally stack the matrix (one after the other)
     * @tparam Number any type of number
     * @param other the other matrix: note that this array is not modified
     * @returns void, but modifies the current array
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   Number>::type>
    void h_stack(const Matrix<Number> &other) {
        assert(_mat.size() == other._mat.size());
        for (size_t i = 0; i < other._mat.size(); ++i) {
            for (size_t j = 0; j < other._mat[i].size(); ++j) {
                _mat[i].push_back(other._mat[i][j]);
            }
        }
    }

    /**
     * @brief Horizontally stack the matrix (current matrix above the other)
     * @tparam Number any type of number (Integer or floating point)
     * @param other the other matrix: note that this array is not modified
     * @returns void, but modifies the current array
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   Number>::type>
    void v_stack(const Matrix<Number> &other) {
        assert(_mat[0].size() == other._mat[0].size());
        for (size_t i = 0; i < other._mat.size(); ++i) {
            _mat.emplace_back(std::vector<T>(other._mat[i].size()));
            for (size_t j = 0; j < other._mat[i].size(); ++j) {
                _mat.back()[j] = other._mat[i][j];
            }
        }
    }

    /**
     * @brief Add two matrices and returns a new matrix
     * @tparam Number any real value to add
     * @param other Other matrix to add to this
     * @returns new matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix operator+(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] + other._mat[i][j];
            }
        }
        return C;
    }

    /**
     * @brief Add another matrices to current matrix
     * @tparam Number any real value to add
     * @param other Other matrix to add to this
     * @returns reference of current matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator+=(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] += other._mat[i][j];
            }
        }
        return this;
    }

    /**
     * @brief Subtract two matrices and returns a new matrix
     * @tparam Number any real value to multiply
     * @param other Other matrix to subtract to this
     * @returns new matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix operator-(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] - other._mat[i][j];
            }
        }
        return C;
    }

    /**
     * @brief Subtract another matrices to current matrix
     * @tparam Number any real value to Subtract
     * @param other Other matrix to Subtract to this
     * @returns reference of current matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator-=(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] -= other._mat[i][j];
            }
        }
        return this;
    }

    /**
     * @brief Multiply two matrices and returns a new matrix
     * @tparam Number any real value to multiply
     * @param other Other matrix to multiply to this
     * @returns new matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    inline Matrix operator*(const Matrix<Number> &other) const {
        assert(_mat[0].size() == other._mat.size());
        auto size = this->size();
        const size_t row = size.first, col = size.second;
        // Main condition for applying strassen's method:
        // 1: matrix should be a square matrix
        // 2: matrix should be of even size (mat.size() % 2 == 0)
        return (row == col && (row & 1) == 0)
                   ? this->strassens_multiplication(other)
                   : this->naive_multiplication(other);
    }

    /**
     * @brief Multiply matrix with a number and returns a new matrix
     * @tparam Number any real value to multiply
     * @param other Other real number to multiply to current matrix
     * @returns new matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    inline Matrix operator*(const Number other) const {
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] * other;
            }
        }
        return C;
    }

    /**
     * @brief Multiply a number to current matrix
     * @tparam Number any real value to multiply
     * @param other Other matrix to multiply to this
     * @returns reference of current matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator*=(const Number other) const {
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] *= other;
            }
        }
        return this;
    }

    /**
     * @brief Naive multiplication performed on this
     * @tparam Number any real value to multiply
     * @param other Other matrix to multiply to this
     * @returns new matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix naive_multiplication(const Matrix<Number> &other) const {
        Matrix C = Matrix<Number>(_mat.size(), other._mat[0].size());

        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t k = 0; k < _mat[0].size(); ++k) {
                for (size_t j = 0; j < other._mat[0].size(); ++j) {
                    C._mat[i][j] += _mat[i][k] * other._mat[k][j];
                }
            }
        }
        return C;
    }

    /**
     * @brief Strassens method of multiplying two matrices
     * References: https://en.wikipedia.org/wiki/Strassen_algorithm
     * @tparam Number any real value to multiply
     * @param other Other matrix to multiply to this
     * @returns new matrix
     */
    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix strassens_multiplication(const Matrix<Number> &other) const {
        const size_t size = _mat.size();
        // Base case: when a matrix is small enough for faster naive
        // multiplication, or the matrix is of odd size, then go with the naive
        // multiplication route;
        // else; go with the strassen's method.
        if (size <= 64ULL || (size & 1ULL)) {
            return this->naive_multiplication(other);
        } else {
            const Matrix<Number>
                A = this->slice(0ULL, size >> 1, 0ULL, size >> 1),
                B = this->slice(0ULL, size >> 1, size >> 1, size),
                C = this->slice(size >> 1, size, 0ULL, size >> 1),
                D = this->slice(size >> 1, size, size >> 1, size),
                E = other.slice(0ULL, size >> 1, 0ULL, size >> 1),
                F = other.slice(0ULL, size >> 1, size >> 1, size),
                G = other.slice(size >> 1, size, 0ULL, size >> 1),
                H = other.slice(size >> 1, size, size >> 1, size);

            Matrix P1 = A.strassens_multiplication(F - H);
            Matrix P2 = (A + B).strassens_multiplication(H);
            Matrix P3 = (C + D).strassens_multiplication(E);
            Matrix P4 = D.strassens_multiplication(G - E);
            Matrix P5 = (A + D).strassens_multiplication(E + H);
            Matrix P6 = (B - D).strassens_multiplication(G + H);
            Matrix P7 = (A - C).strassens_multiplication(E + F);

            // Building final matrix C11 would be
            //     [      |      ]
            //     [ C11  |  C12 ]
            // C = [ ____ | ____ ]
            //     [      |      ]
            //     [ C21  |  C22 ]
            //     [      |      ]

            Matrix C11 = P5 + P4 - P2 + P6;
            Matrix C12 = P1 + P2;
            Matrix C21 = P3 + P4;
            Matrix C22 = P1 + P5 - P3 - P7;

            C21.h_stack(C22);
            C11.h_stack(C12);
            C11.v_stack(C21);

            return C11;
        }
    }

    /**
     * @brief Compares two matrices if each of them are equal or not
     * @param other other matrix to compare
     * @returns whether they are equal or not
     */
    bool operator==(const Matrix<T> &other) const {
        if (_mat.size() != other._mat.size() ||
            _mat[0].size() != other._mat[0].size()) {
            return false;
        }
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                if (_mat[i][j] != other._mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &mat) {
        for (auto &row : mat._mat) {
            for (auto &elem : row) {
                out << elem << " ";
            }
            out << "\n";
        }
        return out << "\n";
    }
};

}  // namespace strassens_multiplication

}  // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    const size_t s = 512;
    auto matrix_demo =
        divide_and_conquer::strassens_multiplication::Matrix<size_t>(s, s);

    for (size_t i = 0; i < s; ++i) {
        for (size_t j = 0; j < s; ++j) {
            matrix_demo[i][j] = i + j;
        }
    }

    auto matrix_demo2 =
        divide_and_conquer::strassens_multiplication::Matrix<size_t>(s, s);
    for (size_t i = 0; i < s; ++i) {
        for (size_t j = 0; j < s; ++j) {
            matrix_demo2[i][j] = 2 + i + j;
        }
    }

    auto start = std::chrono::system_clock::now();
    auto Mat3 = matrix_demo2 * matrix_demo;
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> time = (end - start);
    std::cout << "Strassen time: " << time.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
    auto conf = matrix_demo2.naive_multiplication(matrix_demo);
    end = std::chrono::system_clock::now();

    time = end - start;
    std::cout << "Normal time: " << time.count() << "s" << std::endl;

    // std::cout << Mat3 << conf << std::endl;
    assert(Mat3 == conf);
}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementation
    return 0;
}
