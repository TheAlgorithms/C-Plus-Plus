/**
 * @file
 * @brief Implementation of [K-Nearest Neighbors algorithm]
 * (https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm).
 * @author [Luiz Carlos Cosmi Filho](https://github.com/luizcarloscf)
 * @details K-nearest neighbors algorithm, also known as KNN or k-NN, is a
 * supervised learning classifier, which uses proximity to make classifications.
 * This implementantion uses the Euclidean Distance as distance metric to find
 * the K-nearest neighbors.
 */

#include <algorithm>      /// for std::transform and std::sort
#include <cassert>        /// for assert
#include <cmath>          /// for std::pow and std::sqrt
#include <iostream>       /// for std::cout
#include <numeric>        /// for std::accumulate
#include <unordered_map>  /// for std::unordered_map
#include <vector>         /// for std::vector

/**
 * @namespace machine_learning
 * @brief Machine learning algorithms
 */
namespace machine_learning {

/**
 * @namespace k_nearest_neighbors
 * @brief Functions for the [K-Nearest Neighbors algorithm]
 * (https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm) implementation
 */
namespace k_nearest_neighbors {

/**
 * @brief Compute the Euclidean distance between two vectors.
 *
 * @tparam T typename of the vector
 * @param a first unidimentional vector
 * @param b second unidimentional vector
 * @return double scalar representing the Euclidean distance between provided
 * vectors
 */
template <typename T>
double euclidean_distance(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<double> aux;
    std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(aux),
                   [](T x1, T x2) { return std::pow((x1 - x2), 2); });
    aux.shrink_to_fit();
    return std::sqrt(std::accumulate(aux.begin(), aux.end(), 0.0));
}

/**
 * @brief K-Nearest Neighbors (Knn) class using Euclidean distance as
 * distance metric.
 */
class Knn {
 private:
    std::vector<std::vector<double>> X_{};  ///< attributes vector
    std::vector<int> Y_{};                  ///< labels vector

 public:
    /**
     * @brief Construct a new Knn object.
     * @details Using lazy-learning approch, just holds in memory the dataset.
     * @param X attributes vector
     * @param Y labels vector
     */
    explicit Knn(std::vector<std::vector<double>>& X, std::vector<int>& Y)
        : X_(X), Y_(Y){};

    /**
     * Copy Constructor for class Knn.
     *
     * @param model instance of class to be copied
     */
    Knn(const Knn& model) = default;

    /**
     * Copy assignment operator for class Knn
     */
    Knn& operator=(const Knn& model) = default;

    /**
     * Move constructor for class Knn
     */
    Knn(Knn&&) = default;

    /**
     * Move assignment operator for class Knn
     */
    Knn& operator=(Knn&&) = default;

    /**
     * @brief Destroy the Knn object
     */
    ~Knn() = default;

    /**
     * @brief Classify sample.
     * @param sample sample
     * @param k number of neighbors
     * @return int label of most frequent neighbors
     */
    int predict(std::vector<double>& sample, int k) {
        std::vector<int> neighbors;
        std::vector<std::pair<double, int>> distances;
        for (size_t i = 0; i < this->X_.size(); ++i) {
            auto current = this->X_.at(i);
            auto label = this->Y_.at(i);
            auto distance = euclidean_distance(current, sample);
            distances.emplace_back(distance, label);
        }
        std::sort(distances.begin(), distances.end());
        for (int i = 0; i < k; i++) {
            auto label = distances.at(i).second;
            neighbors.push_back(label);
        }
        std::unordered_map<int, int> frequency;
        for (auto neighbor : neighbors) {
            ++frequency[neighbor];
        }
        std::pair<int, int> predicted;
        predicted.first = -1;
        predicted.second = -1;
        for (auto& kv : frequency) {
            if (kv.second > predicted.second) {
                predicted.second = kv.second;
                predicted.first = kv.first;
            }
        }
        return predicted.first;
    }
};
}  // namespace k_nearest_neighbors
}  // namespace machine_learning

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::cout << "------- Test 1 -------" << std::endl;
    std::vector<std::vector<double>> X1 = {{0.0, 0.0}, {0.25, 0.25},
                                           {0.0, 0.5}, {0.5, 0.5},
                                           {1.0, 0.5}, {1.0, 1.0}};
    std::vector<int> Y1 = {1, 1, 1, 1, 2, 2};
    auto model1 = machine_learning::k_nearest_neighbors::Knn(X1, Y1);
    std::vector<double> sample1 = {1.2, 1.2};
    std::vector<double> sample2 = {0.1, 0.1};
    std::vector<double> sample3 = {0.1, 0.5};
    std::vector<double> sample4 = {1.0, 0.75};
    assert(model1.predict(sample1, 2) == 2);
    assert(model1.predict(sample2, 2) == 1);
    assert(model1.predict(sample3, 2) == 1);
    assert(model1.predict(sample4, 2) == 2);
    std::cout << "... Passed" << std::endl;
    std::cout << "------- Test 2 -------" << std::endl;
    std::vector<std::vector<double>> X2 = {
        {0.0, 0.0, 0.0}, {0.25, 0.25, 0.0}, {0.0, 0.5, 0.0}, {0.5, 0.5, 0.0},
        {1.0, 0.5, 0.0}, {1.0, 1.0, 0.0},   {1.0, 1.0, 1.0}, {1.5, 1.5, 1.0}};
    std::vector<int> Y2 = {1, 1, 1, 1, 2, 2, 3, 3};
    auto model2 = machine_learning::k_nearest_neighbors::Knn(X2, Y2);
    std::vector<double> sample5 = {1.2, 1.2, 0.0};
    std::vector<double> sample6 = {0.1, 0.1, 0.0};
    std::vector<double> sample7 = {0.1, 0.5, 0.0};
    std::vector<double> sample8 = {1.0, 0.75, 1.0};
    assert(model2.predict(sample5, 2) == 2);
    assert(model2.predict(sample6, 2) == 1);
    assert(model2.predict(sample7, 2) == 1);
    assert(model2.predict(sample8, 2) == 3);
    std::cout << "... Passed" << std::endl;
    std::cout << "------- Test 3 -------" << std::endl;
    std::vector<std::vector<double>> X3 = {{0.0}, {1.0}, {2.0}, {3.0},
                                           {4.0}, {5.0}, {6.0}, {7.0}};
    std::vector<int> Y3 = {1, 1, 1, 1, 2, 2, 2, 2};
    auto model3 = machine_learning::k_nearest_neighbors::Knn(X3, Y3);
    std::vector<double> sample9 = {0.5};
    std::vector<double> sample10 = {2.9};
    std::vector<double> sample11 = {5.5};
    std::vector<double> sample12 = {7.5};
    assert(model3.predict(sample9, 3) == 1);
    assert(model3.predict(sample10, 3) == 1);
    assert(model3.predict(sample11, 3) == 2);
    assert(model3.predict(sample12, 3) == 2);
    std::cout << "... Passed" << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @return int 0 on exit
 */
int main(int argc, char* argv[]) {
    test();  // run self-test implementations
    return 0;
}
