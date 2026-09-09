/**
 * \addtogroup machine_learning Machine Learning Algorithms
 * @{
 * \file
 * \brief [Logistic Regression](https://en.wikipedia.org/wiki/Logistic_regression)
 * implementation for binary classification
 *
 * \author [Aster Prajapati](https://github.com/Rosander0)
 *
 * \details
 * Logistic Regression is a supervised learning algorithm for binary
 * classification. It models the probability of a sample belonging to class 1
 * using the sigmoid function:
 * \f[
 * P(y=1|x) = \sigma(z) = \frac{1}{1 + e^{-z}}
 * \f]
 * where \f$z = \mathbf{w}^T \mathbf{x} + b\f$ is the linear combination of
 * features and weights.
 *
 * The model is trained using batch gradient descent to minimize binary
 * cross-entropy loss:
 * \f[
 * L = -\frac{1}{N} \sum_{i=1}^{N} \left[ y_i \log(p_i) + (1-y_i)
 * \log(1-p_i) \right]
 * \f]
 * where \f$p_i = \sigma(z_i)\f$ is the predicted probability and
 * \f$y_i \in \{0, 1\}\f$ is the true label.
 *
 * Gradient descent update:
 * \f[
 * \mathbf{w} := \mathbf{w} - \alpha \nabla_{\mathbf{w}} L
 * \f]
 * where \f$\alpha\f$ is the learning rate.
 *
 * **Time Complexity**: \f$O(N \cdot F \cdot I)\f$ where N is the number of
 * samples, F is the number of features, and I is the number of iterations.
 *
 * **Space Complexity**: \f$O(F)\f$ for storing weights.
 *
 * **Use Cases**:
 * - Binary classification problems (spam/not-spam, disease/healthy)
 * - Interpretable models (coefficients show feature importance)
 * - Fast training on moderately-sized datasets
 *
 * **Limitations**:
 * - Assumes linear decision boundary
 * - Sensitive to feature scaling
 * - May not converge if features are not normalized
 */

#include <cassert>   /// for assert
#include <cmath>     /// for std::exp, std::log, std::sqrt
#include <cstddef>   /// for size_t
#include <iostream>  /// for std::cout
#include <iomanip>   /// for std::fixed, std::setprecision
#include <numeric>   /// for std::accumulate
#include <vector>    /// for std::vector

/**
 * \namespace machine_learning
 * \brief Machine learning algorithms
 */
namespace machine_learning {

/**
 * \namespace logistic_regression
 * \brief Binary Logistic Regression implementation
 */
namespace logistic_regression {

/**
 * \brief Numerically stable sigmoid function.
 * \details Avoids overflow by using different formulas for positive and
 * negative inputs.
 * \f[
 * \sigma(z) = \begin{cases}
 * \frac{1}{1 + e^{-z}} & \text{if } z \geq 0 \\
 * \frac{e^z}{1 + e^z} & \text{if } z < 0
 * \end{cases}
 * \f]
 * \param z input value
 * \return sigmoid output in range (0, 1)
 */
inline double sigmoid(double z) {
    if (z >= 0.0) {
        double exp_neg_z = std::exp(-z);
        return 1.0 / (1.0 + exp_neg_z);
    } else {
        double exp_z = std::exp(z);
        return exp_z / (1.0 + exp_z);
    }
}

/**
 * \brief Binary Logistic Regression classifier using batch gradient descent.
 */
class LogisticRegression {
private:
    std::vector<double> weights_;  ///< Feature weights
    double bias_;                  ///< Bias term
    bool is_fitted_;               ///< Whether model has been fitted
    std::vector<double> loss_history_;  ///< Loss values during training

public:
    /**
     * \brief Construct a new LogisticRegression object.
     */
    LogisticRegression() : bias_(0.0), is_fitted_(false) {}

    /**
     * \brief Fit the model using batch gradient descent.
     *
     * \param X feature matrix (shape: n_samples x n_features)
     * \param y binary labels (0 or 1, shape: n_samples)
     * \param learning_rate gradient descent step size (default: 0.01)
     * \param max_iterations maximum number of iterations (default: 1000)
     * \param tolerance convergence threshold based on gradient norm
     * (default: 1e-6)
     * \param verbose print training progress (default: false)
     */
    void fit(const std::vector<std::vector<double>>& X,
             const std::vector<int>& y, double learning_rate = 0.01,
             size_t max_iterations = 1000, double tolerance = 1e-6,
             bool verbose = false) {
        // Input validation
        if (X.empty()) {
            throw std::invalid_argument("Feature matrix X cannot be empty");
        }
        if (y.size() != X.size()) {
            throw std::invalid_argument("Size mismatch: X and y must have same number of samples");
        }

        size_t n_samples = X.size();
        size_t n_features = X[0].size();

        if (n_features == 0) {
            throw std::invalid_argument("Each sample must have at least one feature");
        }

        // Check feature consistency and label validity
        for (size_t i = 0; i < n_samples; ++i) {
            if (X[i].size() != n_features) {
                throw std::invalid_argument("Inconsistent feature dimensions in X");
            }
            if (y[i] != 0 && y[i] != 1) {
                throw std::invalid_argument("Labels must be binary (0 or 1)");
            }
        }

        // Initialize weights and bias
        weights_.assign(n_features, 0.0);
        bias_ = 0.0;
        loss_history_.clear();

        // Batch gradient descent training loop
        for (size_t iter = 0; iter < max_iterations; ++iter) {
            // Forward pass: compute predictions
            std::vector<double> predictions(n_samples);
            for (size_t i = 0; i < n_samples; ++i) {
                double z = bias_;
                for (size_t j = 0; j < n_features; ++j) {
                    z += weights_[j] * X[i][j];
                }
                predictions[i] = sigmoid(z);
            }

            // Compute binary cross-entropy loss
            double loss = 0.0;
            const double eps = 1e-15;  // Clip to avoid log(0)
            for (size_t i = 0; i < n_samples; ++i) {
                double p = predictions[i];
                p = std::max(eps, std::min(1.0 - eps, p));
                loss -= (static_cast<double>(y[i]) * std::log(p) +
                         (1.0 - static_cast<double>(y[i])) * std::log(1.0 - p));
            }
            loss /= static_cast<double>(n_samples);
            loss_history_.push_back(loss);

            if (verbose && (iter % 100 == 0 || iter == max_iterations - 1)) {
                std::cout << "Iteration " << std::setw(5) << iter
                          << " | Loss: " << std::fixed << std::setprecision(6)
                          << loss << "\n";
            }

            // Compute gradients
            std::vector<double> d_weights(n_features, 0.0);
            double d_bias = 0.0;

            for (size_t i = 0; i < n_samples; ++i) {
                double error = predictions[i] - static_cast<double>(y[i]);
                d_bias += error;
                for (size_t j = 0; j < n_features; ++j) {
                    d_weights[j] += error * X[i][j];
                }
            }

            // Normalize gradients and compute gradient norm
            double grad_norm_sq = 0.0;
            double inv_n = 1.0 / static_cast<double>(n_samples);

            d_bias *= inv_n;
            grad_norm_sq += d_bias * d_bias;

            for (size_t j = 0; j < n_features; ++j) {
                d_weights[j] *= inv_n;
                grad_norm_sq += d_weights[j] * d_weights[j];
            }

            // Update parameters
            bias_ -= learning_rate * d_bias;
            for (size_t j = 0; j < n_features; ++j) {
                weights_[j] -= learning_rate * d_weights[j];
            }

            // Check convergence
            if (std::sqrt(grad_norm_sq) < tolerance) {
                if (verbose) {
                    std::cout << "Converged at iteration " << iter << "\n";
                }
                break;
            }
        }

        is_fitted_ = true;
    }

    /**
     * \brief Predict class probability P(y=1 | x) for a single sample.
     *
     * \param x feature vector
     * \return probability in range (0, 1)
     */
    double predict_proba(const std::vector<double>& x) const {
        if (!is_fitted_) {
            throw std::runtime_error("Model is not fitted. Call fit() first.");
        }
        if (x.size() != weights_.size()) {
            throw std::invalid_argument("Feature size mismatch");
        }

        double z = bias_;
        for (size_t j = 0; j < weights_.size(); ++j) {
            z += weights_[j] * x[j];
        }
        return sigmoid(z);
    }

    /**
     * \brief Predict class probabilities for multiple samples.
     *
     * \param X feature matrix (shape: n_samples x n_features)
     * \return vector of probabilities
     */
    std::vector<double> predict_proba(
        const std::vector<std::vector<double>>& X) const {
        std::vector<double> probas;
        probas.reserve(X.size());
        for (const auto& sample : X) {
            probas.push_back(predict_proba(sample));
        }
        return probas;
    }

    /**
     * \brief Predict binary class label for a single sample.
     *
     * \param x feature vector
     * \param threshold classification threshold (default: 0.5)
     * \return predicted class (0 or 1)
     */
    int predict(const std::vector<double>& x, double threshold = 0.5) const {
        return predict_proba(x) >= threshold ? 1 : 0;
    }

    /**
     * \brief Predict binary class labels for multiple samples.
     *
     * \param X feature matrix (shape: n_samples x n_features)
     * \param threshold classification threshold (default: 0.5)
     * \return vector of predicted labels (0 or 1)
     */
    std::vector<int> predict(const std::vector<std::vector<double>>& X,
                             double threshold = 0.5) const {
        std::vector<int> predictions;
        predictions.reserve(X.size());
        for (const auto& sample : X) {
            predictions.push_back(predict(sample, threshold));
        }
        return predictions;
    }

    /**
     * \brief Compute classification accuracy on a dataset.
     *
     * \param X feature matrix
     * \param y true binary labels
     * \param threshold classification threshold (default: 0.5)
     * \return accuracy in range [0, 1]
     */
    double score(const std::vector<std::vector<double>>& X,
                 const std::vector<int>& y,
                 double threshold = 0.5) const {
        if (X.size() != y.size()) {
            throw std::invalid_argument("Size mismatch between X and y");
        }
        if (X.empty()) return 0.0;

        std::vector<int> predictions = predict(X, threshold);
        size_t correct = 0;
        for (size_t i = 0; i < predictions.size(); ++i) {
            if (predictions[i] == y[i]) {
                ++correct;
            }
        }
        return static_cast<double>(correct) /
               static_cast<double>(predictions.size());
    }

    // Getters
    /**
     * \brief Get model weights.
     * \return reference to weights vector
     */
    const std::vector<double>& get_weights() const { return weights_; }

    /**
     * \brief Get model bias.
     * \return bias value
     */
    double get_bias() const { return bias_; }

    /**
     * \brief Get training loss history.
     * \return reference to loss history vector
     */
    const std::vector<double>& get_loss_history() const {
        return loss_history_;
    }

    /**
     * \brief Check if model is fitted.
     * \return true if fitted, false otherwise
     */
    bool is_fitted() const { return is_fitted_; }
};

}  // namespace logistic_regression
}  // namespace machine_learning

/**
 * \brief Self-test implementations
 * \returns void
 */
static void test() {
    using namespace machine_learning::logistic_regression;

    std::cout << "------- Test 1: Linearly Separable Data -------\n";

    // Create synthetic training data: simple 2D classification
    // Class 0: points near (0, 0), Class 1: points near (2, 2)
    std::vector<std::vector<double>> X_train = {
        {0.0, 0.0}, {0.5, 0.5}, {0.2, 0.3}, {-0.1, 0.1},  // Class 0
        {2.0, 2.0}, {1.8, 2.2}, {2.1, 1.9}, {2.2, 2.1}    // Class 1
    };
    std::vector<int> y_train = {0, 0, 0, 0, 1, 1, 1, 1};

    // Create and train model
    LogisticRegression model;
    model.fit(X_train, y_train, 0.1, 500, 1e-6, true);

    std::cout << "\nModel weights: ";
    const auto& weights = model.get_weights();
    for (double w : weights) {
        std::cout << w << " ";
    }
    std::cout << "\nBias: " << model.get_bias() << "\n";

    // Test predictions on training data
    std::cout << "\nPredictions on training data:\n";
    auto predictions = model.predict(X_train);
    for (size_t i = 0; i < X_train.size(); ++i) {
        double proba = model.predict_proba(X_train[i]);
        std::cout << "Sample " << i << " (" << X_train[i][0] << ", "
                  << X_train[i][1] << "): P(y=1)=" << std::fixed
                  << std::setprecision(4) << proba << ", Predicted="
                  << predictions[i] << ", True=" << y_train[i] << "\n";
    }

    double acc = model.score(X_train, y_train);
    std::cout << "\nTraining Accuracy: " << std::fixed << std::setprecision(4)
              << acc << "\n";

    // Test on a new sample
    std::cout << "\n------- Test 2: Single Sample Prediction -------\n";
    std::vector<double> test_sample_1 = {0.1, 0.2};
    std::vector<double> test_sample_2 = {1.9, 2.0};

    std::cout << "Test sample 1 " << test_sample_1[0] << ", "
              << test_sample_1[1] << ": ";
    std::cout << "P(y=1)=" << std::fixed << std::setprecision(4)
              << model.predict_proba(test_sample_1) << ", Predicted class="
              << model.predict(test_sample_1) << "\n";

    std::cout << "Test sample 2 " << test_sample_2[0] << ", "
              << test_sample_2[1] << ": ";
    std::cout << "P(y=1)=" << std::fixed << std::setprecision(4)
              << model.predict_proba(test_sample_2) << ", Predicted class="
              << model.predict(test_sample_2) << "\n";

    // Test assertions
    assert(model.is_fitted());
    assert(model.get_weights().size() == 2);
    assert(acc > 0.5);  // Should do better than random
}

/** Driver code */
int main() {
    test();
    return 0;
}
