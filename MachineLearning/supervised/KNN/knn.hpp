#pragma once
#include "eigen_compat.hpp"
#include <string>
namespace ml::supervised {
class KNN {
public:
    KNN(int param1=5, double param2=0.1);
    void fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y);
    Eigen::VectorXi predict(const Eigen::MatrixXd& X) const;
    double score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y) const;
    void save(const std::string& filename) const; void load(const std::string& filename);
private:
    int param1_; double param2_;
    Eigen::VectorXd w_; double b_{0}; Eigen::VectorXi train_y_; Eigen::MatrixXd train_X_;
};
}
