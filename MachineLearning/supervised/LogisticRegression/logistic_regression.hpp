#pragma once
#include "eigen_compat.hpp"
#include <string>
namespace ml::supervised {
class LogisticRegression {
public:
    LogisticRegression(double lr=0.1, int epochs=1000, double threshold=0.5);
    void fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);
    Eigen::VectorXi predict(const Eigen::MatrixXd& X) const;
    double score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y) const;
    void save(const std::string& filename) const; void load(const std::string& filename);
private: double lr_; int epochs_; double th_; Eigen::VectorXd w_; double b_{0};
};
}
