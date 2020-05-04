#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
ostream &operator<<(ostream &out, vector<vector<T>> const &v)
{
    const int width = 10;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++)
    {
        for (size_t col = 0; col < v[row].size(); col++)
            out
                << left << setw(width) << setfill(separator) << v[row][col];
        out << endl;
    }

    return out;
}

template <typename T>
ostream &operator<<(ostream &out, vector<T> const &v)
{
    const int width = 15;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++)
        out
            << left << setw(width) << setfill(separator) << v[row];

    return out;
}

template <typename T>
inline bool is_square(vector<vector<T>> const &A)
{
    size_t N = A.size(); // Assuming A is square matrix
    for (size_t i = 0; i < N; i++)
        if (A[i].size() != N)
            return false;
    return true;
}

/**
 * matrix multiplication
 **/
template <typename T>
vector<vector<T>> operator*(vector<vector<T>> const &A, vector<vector<T>> const &B)
{
    size_t N_A = A.size();    // Number of rows in A
    size_t N_B = B[0].size(); // Number of columns in B

    vector<vector<T>> result(N_A);

    if (A[0].size() != B.size())
    {
        cerr << "Number of columns in A != Number of rows in B (" << A[0].size() << ", " << B.size() << ")" << endl;
        return result;
    }

    for (size_t row = 0; row < N_A; row++)
    {
        vector<T> v(N_B);
        for (size_t col = 0; col < N_B; col++)
        {
            v[col] = static_cast<T>(0);
            for (size_t j = 0; j < B.size(); j++)
                v[col] += A[row][j] * B[j][col];
        }
        result[row] = v;
    }

    return result;
}

template <typename T>
vector<T> operator*(vector<vector<T>> const &A, vector<T> const &B)
{
    size_t N_A = A.size(); // Number of rows in A

    vector<T> result(N_A);

    if (A[0].size() != B.size())
    {
        cerr << "Number of columns in A != Number of rows in B (" << A[0].size() << ", " << B.size() << ")" << endl;
        return result;
    }

    for (size_t row = 0; row < N_A; row++)
    {
        result[row] = static_cast<T>(0);
        for (size_t j = 0; j < B.size(); j++)
            result[row] += A[row][j] * B[j];
    }

    return result;
}

template <typename T>
vector<float> operator*(float const scalar, vector<T> const &A)
{
    size_t N_A = A.size(); // Number of rows in A

    vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++)
    {
        result[row] += A[row] * static_cast<float>(scalar);
    }

    return result;
}

template <typename T>
vector<float> operator*(vector<T> const &A, float const scalar)
{
    size_t N_A = A.size(); // Number of rows in A

    vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++)
        result[row] = A[row] * static_cast<float>(scalar);

    return result;
}

template <typename T>
vector<float> operator/(vector<T> const &A, float const scalar)
{
    return (1.f / scalar) * A;
}

template <typename T>
vector<T> operator-(vector<T> const &A, vector<T> const &B)
{
    size_t N = A.size(); // Number of rows in A

    vector<T> result(N);

    if (B.size() != N)
    {
        cerr << "Vector dimensions shouldbe identical!" << endl;
        return A;
    }

    for (size_t row = 0; row < N; row++)
        result[row] = A[row] - B[row];

    return result;
}

template <typename T>
vector<T> operator+(vector<T> const &A, vector<T> const &B)
{
    size_t N = A.size(); // Number of rows in A

    vector<T> result(N);

    if (B.size() != N)
    {
        cerr << "Vector dimensions shouldbe identical!" << endl;
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
vector<vector<float>> get_inverse(vector<vector<T>> const &A)
{
    size_t N = A.size(); // Assuming A is square matrix

    vector<vector<float>> inverse(N);
    for (size_t row = 0; row < N; row++) // preallocatae a resultant identity matrix
    {
        inverse[row] = vector<float>(N);
        for (size_t col = 0; col < N; col++)
            inverse[row][col] = (row == col) ? 1.f : 0.f;
    }

    if (!is_square(A))
    {
        cerr << "A must be a square matrix!" << endl;
        return inverse;
    }

    vector<vector<float>> temp(N); // preallocatae a temporary matrix identical to A
    for (size_t row = 0; row < N; row++)
    {
        vector<float> v(N);
        for (size_t col = 0; col < N; col++)
            v[col] = static_cast<float>(A[row][col]);
        temp[row] = v;
    }

    // start transformations
    for (size_t row = 0; row < N; row++)
    {
        for (size_t row2 = row; row2 < N && temp[row][row] == 0; row2++) // this to ensure diagonal elements are not 0
        {
            temp[row] = temp[row] + temp[row2];
            inverse[row] = inverse[row] + inverse[row2];
        }

        for (size_t col2 = row; col2 < N && temp[row][row] == 0; col2++) // this to further ensure diagonal elements are not 0
        {
            for (size_t row2 = 0; row2 < N; row2++)
            {
                temp[row2][row] = temp[row2][row] + temp[row2][col2];
                inverse[row2][row] = inverse[row2][row] + inverse[row2][col2];
            }
        }

        if (temp[row][row] == 0)
        {
            // Probably a low-rank matrix and hence singular
            cerr << "Low-rank matrix, no inverse!" << endl;
            return inverse;
        }

        // set diagonal to 1
        float divisor = static_cast<float>(temp[row][row]);
        temp[row] = temp[row] / divisor;
        inverse[row] = inverse[row] / divisor;
        // Row transformations
        for (size_t row2 = 0; row2 < N; row2++)
        {
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
vector<vector<T>> get_transpose(vector<vector<T>> const &A)
{
    vector<vector<T>> result(A[0].size());

    for (size_t row = 0; row < A[0].size(); row++)
    {
        vector<T> v(A.size());
        for (size_t col = 0; col < A.size(); col++)
            v[col] = A[col][row];

        result[row] = v;
    }
    return result;
}

template <typename T>
vector<float> fit_OLS_regressor(vector<vector<T>> const &X, vector<T> const &Y)
{
    vector<vector<T>> X2 = X; //NxF
    for (size_t i = 0; i < X2.size(); i++)
        X2[i].push_back(1);                       // add Y-intercept -> Nx(F+1)
    vector<vector<T>> Xt = get_transpose(X2);     // (F+1)xN
    vector<vector<T>> tmp = get_inverse(Xt * X2); // (F+1)x(F+1)
    vector<vector<float>> out = tmp * Xt;         // (F+1)xN
    // cout << endl
    //      << "Projection matrix: " << X2 * out << endl;
    return out * Y; // Fx1,1    -> (F+1)^th element is the independent constant
}

/**
 * Given data and OLS model coeffficients, predict
 * regression estimates
 **/
template <typename T>
vector<float> predict_OLS_regressor(vector<vector<T>> const &X, vector<float> const &beta)
{
    vector<float> result(X.size());

    for (size_t rows = 0; rows < X.size(); rows++)
    {
        result[rows] = beta[X[0].size()]; // -> start with constant term
        for (size_t cols = 0; cols < X[0].size(); cols++)
            result[rows] += beta[cols] * X[rows][cols];
    }
    return result; // Nx1
}

int main()
{
    size_t N, F;

    cin >> F; // number of features = columns
    cin >> N; // number of samples = rows

    vector<vector<float>> data(N);
    vector<float> Y(N);

    for (size_t rows = 0; rows < N; rows++)
    {
        vector<float> v(F);
        for (size_t cols = 0; cols < F; cols++)
            cin >> v[cols]; // get the F features
        data[rows] = v;
        cin >> Y[rows]; // get the corresponding output
    }

    vector<float> beta = fit_OLS_regressor(data, Y);
    cout << endl
         << endl
         << "beta:" << beta << endl;

    size_t T;
    cin >> T; // number of test sample inputs
    vector<vector<float>> data2(T);
    // vector<float> Y2(T);

    for (size_t rows = 0; rows < T; rows++)
    {
        vector<float> v(F);
        for (size_t cols = 0; cols < F; cols++)
            cin >> v[cols];
        data2[rows] = v;
    }

    vector<float> out = predict_OLS_regressor(data2, beta);
    for (size_t rows = 0; rows < T; rows++)
        cout << out[rows] << endl;

    return 0;
}
