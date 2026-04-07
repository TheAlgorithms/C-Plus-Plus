#pragma once
#include "eigen_compat.hpp"

namespace ml::utils {
inline Eigen::ArrayXd sigmoid(const Eigen::ArrayXd& z){ return 1.0/(1.0+(-z).exp()); }
inline Eigen::ArrayXd relu(const Eigen::ArrayXd& z){ return z.max(0.0); }
inline Eigen::ArrayXd tanh_act(const Eigen::ArrayXd& z){ return z.tanh(); }
inline Eigen::ArrayXd leaky_relu(const Eigen::ArrayXd& z, double alpha=0.01){ return z.max(alpha*z); }
inline Eigen::ArrayXd softmax(const Eigen::ArrayXd& z){
    double m=z.maxCoeff();
    Eigen::ArrayXd e=(z-m).exp();
    return e/e.sum();
}
}
