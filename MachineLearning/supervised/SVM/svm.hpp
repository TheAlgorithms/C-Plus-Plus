#pragma once
#include "eigen_compat.hpp"
#include <string>
namespace ml::supervised {
class SVM {
public:
    SVM(int param1=5, double param2=0.1);
    void fit(const Eigen::MatrixXd& X, const Eigen::VectorXd& y);
    Eigen::VectorXd predict(const Eigen::MatrixXd& X) const;
    double score(const Eigen::MatrixXd& X, const Eigen::VectorXd& y) const;
    void save(const std::string& filename) const; void load(const std::string& filename);
private:
    int param1_; double param2_;
    Eigen::VectorXd w_; double b_{0}; Eigen::VectorXd train_y_; Eigen::MatrixXd train_X_;
};
}
