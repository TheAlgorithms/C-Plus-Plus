#pragma once
#include "eigen_compat.hpp"
#include <string>
namespace ml::unsupervised {
class KMeans {
public:
    KMeans(int n_clusters=3, int max_iters=100, double lr=0.01);
    void fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y=Eigen::VectorXi());
    Eigen::VectorXi predict(const Eigen::MatrixXd& X) const;
    double score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y=Eigen::VectorXi()) const;
    void save(const std::string& filename) const; void load(const std::string& filename);
private:
    int n_clusters_, max_iters_; double lr_;
    Eigen::MatrixXd centroids_;
};
}
