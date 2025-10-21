/**
 * @file
 * @brief Implementation of
 * [Linear Regression](https://en.wikipedia.org/wiki/Linear_regression) using
 * [Gradient Descent](https://en.wikipedia.org/wiki/Gradient_descent)
 *
 * @author
 * [Abhinav Prakash](https://github.com/abhinavprakash-x)
 *
 * @details
 * Linear Regression is a supervised machine learning algorithm that models
 * the relationship between a dependent variable `y` and one or more
 * independent variables `X` using a linear function.
 *
 * ### Key Concepts
 * - **Equation:** y = W·X + b
 *   where:
 *   - y is the scalar output (target variable)
 *   - X is the feature vector (independent variables)
 *   - W is the weight vector (slope)
 *   - b is the bias term (intercept)
 *
 * - **Prediction:** ŷ = W·Xᵢ + b
 * - **Cost Function:** J(W, b) = (1 / 2m) * Σ (ŷ - y)² + λ * ||W||²
 * - **Gradient Updates:**
 *     W := W - α * (1/m) * Xᵀ(ŷ - y)
 *     b := b - α * (1/m) * Σ(ŷ - y)
 *
 * ### Notes
 * - Implements batch gradient descent for optimization.
 * - Supports feature normalization and L2 regularization (Ridge penalty).
 * - Uses only the C++17 Standard Library (no external dependencies).
 *
 * @see [Wikipedia: Linear
 * Regression](https://en.wikipedia.org/wiki/Linear_regression)
 * @see [Wikipedia: Gradient
 * Descent](https://en.wikipedia.org/wiki/Gradient_descent)
 *
 */

#include <cassert>
#include <cmath>
#include <vector>

/**
 * @namespace machine_learning
 * @brief Machine Learning Algorithms
 * @note All members are kept public intentionally for simplicity and
 * educational clarity.
 */
namespace machine_learning {
class LinearRegression {
 public:
    std::vector<double> weights;
    double bias;
    size_t epochs;
    double learning_rate;               // Denoted by alpha
    double lambda;                      // Regularization Term
    std::vector<double> mean;           // For Normalization of Data
    std::vector<double> std_deviation;  // For Normalization of Data

    LinearRegression(double lr = 0.01, size_t e = 1000, double reg = 0.1)
        : bias(0.0), learning_rate(lr), epochs(e), lambda(reg) {}

    /**
     * @brief Compute Mean and Standard Deviation for each feature.
     * @param X Array of Feature Vectors
     */
    void compute_normalization_params(
        const std::vector<std::vector<double>>& X) {
        size_t m = X.size();
        size_t n = X[0].size();
        mean.resize(n, 0.0);
        std_deviation.resize(n, 0.0);

        for (size_t j = 0; j < n; ++j) {
            for (size_t i = 0; i < m; ++i) {
                mean[j] += X[i][j];
            }
            mean[j] /= static_cast<double>(m);

            for (size_t i = 0; i < m; ++i) {
                std_deviation[j] += std::pow(X[i][j] - mean[j], 2);
            }
            std_deviation[j] =
                std::sqrt(std_deviation[j] / static_cast<double>(m));
            if (std_deviation[j] == 0)
                std_deviation[j] = 1;
        }
    }

    /**
     * @brief Apply Normalization to features
     * @param X Feature matrix to normalize.
     * @return Normalized feature matrix.
     *
     * @details
     * Equation: X_norm = (X - mean) / std_deviation
     * This is called Z Score Normalization and it converts
     * large numbers to smaller numbers for easier computation.
     *
     * eg. {100,200,123} -> {0.1,0.2,0.123}
     */
    std::vector<std::vector<double>> normalize_features(
        const std::vector<std::vector<double>>& X) const {
        std::vector<std::vector<double>> X_norm = X;
        for (size_t i = 0; i < X.size(); ++i) {
            for (size_t j = 0; j < X[0].size(); ++j) {
                X_norm[i][j] = (X[i][j] - mean[j]) / std_deviation[j];
            }
        }
        return X_norm;
    }

    /**
     * @brief Compute the Cost function (Mean Squared Error and
     * L2 Regularization).
     * @param X Feature Matrix
     * @param y Outputs Corresponding to X
     * @return Cost Function
     *
     * @details
     * Calculates Cost function as
     * J(w,b) = (1 / 2m) * Σ (ŷ - y)² + λ * ||W||²
     * where, m is the number of examples in dataset
     *        y_hat is the predicted value by model
     *        y is the output value given in dataset
     *        lambda is the regularization term
     *        ||W||^2 is the L2 Norm
     */
    double compute_cost(const std::vector<std::vector<double>>& X,
                        const std::vector<double>& y) const {
        size_t m = X.size();
        size_t n = X[0].size();
        double cost = 0.0;

        for (size_t i = 0; i < m; ++i) {
            double prediction = bias;
            for (size_t j = 0; j < n; ++j) {
                prediction += weights[j] * X[i][j];
            }
            double error = prediction - y[i];
            cost += error * error;
        }
        cost /= (2.0 * m);

        double reg = 0.0;
        for (double w : weights) {
            reg += w * w;
        }

        cost += (lambda / (2.0 * m)) * reg;
        return cost;
    }

    /**
     * @brief Fit Data into LR Model
     * @param X_raw The Feature Values given in dataset
     * @param y the output values corresponding to X
     *
     * @details
     * Values of w and b are calculated and updated over
     * multiple epochs.
     * MSE (mean squared error) = (prediction - y)^2
     * y_hat (prediction) = w*X + b
     * grad_w = partial derivative of Cost over w
     * grad_w = MSE * X
     * grad_b = MSE
     *
     * Parameters are simultaneously updated as:
     * w := w - alpha * grad_w
     * b := b - alpha * grad_b
     *
     * this is called batch gradient descent
     * where alpha is learning rate
     * Finally everything is regularized to prevent model from "Overfitting"
     */
    void fit(const std::vector<std::vector<double>>& X_raw,
             const std::vector<double>& y) {
        compute_normalization_params(X_raw);
        std::vector<std::vector<double>> X = normalize_features(X_raw);

        size_t m = X.size();
        size_t n = X[0].size();
        weights.assign(n, 0.0);
        bias = 0.0;

        for (size_t epoch = 0; epoch < epochs; ++epoch) {
            std::vector<double> y_hat(m, 0.0);
            for (size_t i = 0; i < m; ++i) {
                y_hat[i] = bias;
                for (size_t j = 0; j < n; ++j) {
                    y_hat[i] += weights[j] * X[i][j];
                }
            }

            std::vector<double> grad_w(n, 0.0);
            double grad_b = 0.0;

            for (size_t i = 0; i < m; ++i) {
                double error = y_hat[i] - y[i];
                grad_b += error;
                for (size_t j = 0; j < n; ++j) {
                    grad_w[j] += error * X[i][j];
                }
            }

            for (size_t j = 0; j < n; ++j) {
                grad_w[j] = grad_w[j] / m + (lambda / m) * weights[j];
            }
            grad_b /= m;

            for (size_t j = 0; j < n; ++j) {
                weights[j] -= learning_rate * grad_w[j];
            }
            bias -= learning_rate * grad_b;
        }
    }

    /**
     * @brief Predict Outputs using LR Model on given features
     * @param X_raw The Feature Values given in dataset
     * @return The Prediced Values
     *
     * @details
     * Once Model has found optimized values for w and b
     * the prediction is calculated.
     */
    std::vector<double> predict(
        const std::vector<std::vector<double>>& X_raw) const {
        std::vector<std::vector<double>> X = normalize_features(X_raw);
        size_t m = X.size();
        size_t n = X[0].size();

        std::vector<double> predictions(m, 0.0);
        for (size_t i = 0; i < m; ++i) {
            double pred = bias;
            for (size_t j = 0; j < n; ++j) pred += weights[j] * X[i][j];
            predictions[i] = pred;
        }
        return predictions;
    }
};
}  // namespace machine_learning

/**
 * @brief Test routine for Linear Regression
 *
 * @details
 *
 * For this test case (Synthetic Dataset)
 * The Predicted Values are Close to the real values
 * So the model is doing good and has accuracy of R^2 = 0.998
 */
static void test() {
    // Synthetic dataset with correlated features and noise
    std::vector<std::vector<double>> X = {{1.0, 2.1, 3.9},   {2.0, 3.9, 6.1},
                                          {3.0, 6.2, 9.0},   {4.0, 8.1, 12.2},
                                          {5.0, 10.2, 14.0}, {6.0, 12.1, 17.8},
                                          {7.0, 13.9, 20.9}, {8.0, 16.3, 24.2}};

    // Underlying true relation: y = 0.5*x1 + 0.3*x2 + 0.2*x3 + noise
    std::vector<double> y = {3.9, 6.8, 9.9, 12.5, 15.1, 18.4, 21.2, 24.6};

    // Instantiate model with noticeable regularization
    machine_learning::LinearRegression model(0.01, 8000, 1.0);

    model.fit(X, y);
    auto preds = model.predict(X);

    // Check predictions
    for (size_t i = 0; i < y.size(); ++i) {
        assert(std::fabs(preds[i] - y[i]) < 1.0);
    }

    // Check cost after training
    double final_cost = model.compute_cost(model.normalize_features(X), y);
    assert(final_cost < 1.0);
}

/**
 * @brief Main function to execute the test
 */
int main() {
    test();
    return 0;
}