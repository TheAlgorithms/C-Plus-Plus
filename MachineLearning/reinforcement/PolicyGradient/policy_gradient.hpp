#pragma once
#include "eigen_compat.hpp"
#include <string>
#include <vector>
namespace ml::reinforcement {
class PolicyGradient {
public:
    PolicyGradient(int states=16, int actions=4, double alpha=0.1, double gamma=0.95, double epsilon=0.1);
    void fit(const Eigen::MatrixXd& transitions, const Eigen::VectorXi& rewards);
    Eigen::VectorXi predict(const Eigen::MatrixXd& states) const;
    double score(const Eigen::MatrixXd& states, const Eigen::VectorXi& rewards) const;
    void save(const std::string& filename) const; void load(const std::string& filename);
private:
    int states_, actions_; double alpha_, gamma_, epsilon_;
    Eigen::MatrixXd Q_;
};
}
