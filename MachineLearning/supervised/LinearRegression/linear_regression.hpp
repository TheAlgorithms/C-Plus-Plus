#pragma once
#include "eigen_compat.hpp"
#include <string>

namespace ml::supervised {
class LinearRegression {
public:
    LinearRegression(double lr=0.01, int epochs=1000);
    void fit(const Eigen::MatrixXd& X, const Eigen::VectorXd& y);
    Eigen::VectorXd predict(const Eigen::MatrixXd& X) const;
    double score(const Eigen::MatrixXd& X, const Eigen::VectorXd& y) const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
private:
    double lr_; int epochs_; Eigen::VectorXd w_; double b_{0.0};
};
}
