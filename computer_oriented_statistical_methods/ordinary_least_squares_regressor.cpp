/**
 * Program that gets the number of data samples and number of features per
 * sample along with output per sample. It applies OLS regression to compute
 * the regression output for additional test data samples.
 **/
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::vector<T>> const &v) {
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

template <typename T>
std::ostream &operator<<(std::ostream &out, std::vector<T> const &v) {
  const int width = 15;
  const char separator = ' ';

  for (size_t row = 0; row < v.size(); row++)
    out << std::left << std::setw(width) << std::setfill(separator) << v[row];

  return out;
}

template <typename T>
inline bool is_square(std::vector<std::vector<T>> const &A) {
  // Assuming A is square matrix
  size_t N = A.size();
  for (size_t i = 0; i < N; i++)
    if (A[i].size() != N)
      return false;
  return true;
}

/**
 * matrix multiplication
 **/
template <typename T>
std::vector<std::vector<T>> operator*(std::vector<std::vector<T>> const &A,
                                      std::vector<std::vector<T>> const &B) {
  // Number of rows in A
  size_t N_A = A.size();
  // Number of columns in B
  size_t N_B = B[0].size();

  std::vector<std::vector<T>> result(N_A);

  if (A[0].size() != B.size()) {
    std::cerr << "Number of columns in A != Number of rows in B ("
              << A[0].size() << ", " << B.size() << ")" << std::endl;
    return result;
  }

  for (size_t row = 0; row < N_A; row++) {
    std::vector<T> v(N_B);
    for (size_t col = 0; col < N_B; col++) {
      v[col] = static_cast<T>(0);
      for (size_t j = 0; j < B.size(); j++)
        v[col] += A[row][j] * B[j][col];
    }
    result[row] = v;
  }

  return result;
}

template <typename T>
std::vector<T> operator*(std::vector<std::vector<T>> const &A,
                         std::vector<T> const &B) {
  // Number of rows in A
  size_t N_A = A.size();

  std::vector<T> result(N_A);

  if (A[0].size() != B.size()) {
    std::cerr << "Number of columns in A != Number of rows in B ("
              << A[0].size() << ", " << B.size() << ")" << std::endl;
    return result;
  }

  for (size_t row = 0; row < N_A; row++) {
    result[row] = static_cast<T>(0);
    for (size_t j = 0; j < B.size(); j++)
      result[row] += A[row][j] * B[j];
  }

  return result;
}

template <typename T>
std::vector<float> operator*(float const scalar, std::vector<T> const &A) {
  // Number of rows in A
  size_t N_A = A.size();

  std::vector<float> result(N_A);

  for (size_t row = 0; row < N_A; row++) {
    result[row] += A[row] * static_cast<float>(scalar);
  }

  return result;
}

template <typename T>
std::vector<float> operator*(std::vector<T> const &A, float const scalar) {
  // Number of rows in A
  size_t N_A = A.size();

  std::vector<float> result(N_A);

  for (size_t row = 0; row < N_A; row++)
    result[row] = A[row] * static_cast<float>(scalar);

  return result;
}

template <typename T>
std::vector<float> operator/(std::vector<T> const &A, float const scalar) {
  return (1.f / scalar) * A;
}

template <typename T>
std::vector<T> operator-(std::vector<T> const &A, std::vector<T> const &B) {
  // Number of rows in A
  size_t N = A.size();

  std::vector<T> result(N);

  if (B.size() != N) {
    std::cerr << "Vector dimensions shouldbe identical!" << std::endl;
    return A;
  }

  for (size_t row = 0; row < N; row++)
    result[row] = A[row] - B[row];

  return result;
}

template <typename T>
std::vector<T> operator+(std::vector<T> const &A, std::vector<T> const &B) {
  // Number of rows in A
  size_t N = A.size();

  std::vector<T> result(N);

  if (B.size() != N) {
    std::cerr << "Vector dimensions shouldbe identical!" << std::endl;
    return A;
  }

  for (size_t row = 0; row < N; row++)
    result[row] = A[row] + B[row];

  return result;
}

/**
 * Get matrix inverse using Row-trasnformations
 **/
template <typename T>
std::vector<std::vector<float>>
get_inverse(std::vector<std::vector<T>> const &A) {
  // Assuming A is square matrix
  size_t N = A.size();

  std::vector<std::vector<float>> inverse(N);
  for (size_t row = 0; row < N; row++) {
    // preallocatae a resultant identity matrix
    inverse[row] = std::vector<float>(N);
    for (size_t col = 0; col < N; col++)
      inverse[row][col] = (row == col) ? 1.f : 0.f;
  }

  if (!is_square(A)) {
    std::cerr << "A must be a square matrix!" << std::endl;
    return inverse;
  }

  // preallocatae a temporary matrix identical to A
  std::vector<std::vector<float>> temp(N);
  for (size_t row = 0; row < N; row++) {
    std::vector<float> v(N);
    for (size_t col = 0; col < N; col++)
      v[col] = static_cast<float>(A[row][col]);
    temp[row] = v;
  }

  // start transformations
  for (size_t row = 0; row < N; row++) {
    for (size_t row2 = row; row2 < N && temp[row][row] == 0; row2++) {
      // this to ensure diagonal elements are not 0
      temp[row] = temp[row] + temp[row2];
      inverse[row] = inverse[row] + inverse[row2];
    }

    for (size_t col2 = row; col2 < N && temp[row][row] == 0; col2++) {
      // this to further ensure diagonal elements are not 0
      for (size_t row2 = 0; row2 < N; row2++) {
        temp[row2][row] = temp[row2][row] + temp[row2][col2];
        inverse[row2][row] = inverse[row2][row] + inverse[row2][col2];
      }
    }

    if (temp[row][row] == 0) {
      // Probably a low-rank matrix and hence singular
      std::cerr << "Low-rank matrix, no inverse!" << std::endl;
      return inverse;
    }

    // set diagonal to 1
    float divisor = static_cast<float>(temp[row][row]);
    temp[row] = temp[row] / divisor;
    inverse[row] = inverse[row] / divisor;
    // Row transformations
    for (size_t row2 = 0; row2 < N; row2++) {
      if (row2 == row)
        continue;
      float factor = temp[row2][row];
      temp[row2] = temp[row2] - factor * temp[row];
      inverse[row2] = inverse[row2] - factor * inverse[row];
    }
  }

  return inverse;
}

/**
 * matrix transpose
 **/
template <typename T>
std::vector<std::vector<T>>
get_transpose(std::vector<std::vector<T>> const &A) {
  std::vector<std::vector<T>> result(A[0].size());

  for (size_t row = 0; row < A[0].size(); row++) {
    std::vector<T> v(A.size());
    for (size_t col = 0; col < A.size(); col++)
      v[col] = A[col][row];

    result[row] = v;
  }
  return result;
}

template <typename T>
std::vector<float> fit_OLS_regressor(std::vector<std::vector<T>> const &X,
                                     std::vector<T> const &Y) {
  // NxF
  std::vector<std::vector<T>> X2 = X;
  for (size_t i = 0; i < X2.size(); i++)
    // add Y-intercept -> Nx(F+1)
    X2[i].push_back(1);
  // (F+1)xN
  std::vector<std::vector<T>> Xt = get_transpose(X2);
  // (F+1)x(F+1)
  std::vector<std::vector<T>> tmp = get_inverse(Xt * X2);
  // (F+1)xN
  std::vector<std::vector<float>> out = tmp * Xt;
  // cout << endl
  //      << "Projection matrix: " << X2 * out << endl;

  // Fx1,1    -> (F+1)^th element is the independent constant
  return out * Y;
}

/**
 * Given data and OLS model coeffficients, predict
 * regression estimates
 **/
template <typename T>
std::vector<float> predict_OLS_regressor(std::vector<std::vector<T>> const &X,
                                         std::vector<float> const &beta) {
  std::vector<float> result(X.size());

  for (size_t rows = 0; rows < X.size(); rows++) {
    // -> start with constant term
    result[rows] = beta[X[0].size()];
    for (size_t cols = 0; cols < X[0].size(); cols++)
      result[rows] += beta[cols] * X[rows][cols];
  }
  // Nx1
  return result;
}

int main() {
  size_t N, F;

  std::cout << "Enter number of features: ";
  // number of features = columns
  std::cin >> F;
  std::cout << "Enter number of samples: ";
  // number of samples = rows
  std::cin >> N;

  std::vector<std::vector<float>> data(N);
  std::vector<float> Y(N);

  std::cout
      << "Enter training data. Per sample, provide features ad one output."
      << std::endl;

  for (size_t rows = 0; rows < N; rows++) {
    std::vector<float> v(F);
    std::cout << "Sample# " << rows + 1 << ": ";
    for (size_t cols = 0; cols < F; cols++)
      // get the F features
      std::cin >> v[cols];
    data[rows] = v;
    // get the corresponding output
    std::cin >> Y[rows];
  }

  std::vector<float> beta = fit_OLS_regressor(data, Y);
  std::cout << std::endl << std::endl << "beta:" << beta << std::endl;

  size_t T;
  std::cout << "Enter number of test samples: ";
  // number of test sample inputs
  std::cin >> T;
  std::vector<std::vector<float>> data2(T);
  // vector<float> Y2(T);

  for (size_t rows = 0; rows < T; rows++) {
    std::cout << "Sample# " << rows + 1 << ": ";
    std::vector<float> v(F);
    for (size_t cols = 0; cols < F; cols++)
      std::cin >> v[cols];
    data2[rows] = v;
  }

  std::vector<float> out = predict_OLS_regressor(data2, beta);
  for (size_t rows = 0; rows < T; rows++)
    std::cout << out[rows] << std::endl;

  return 0;
}
