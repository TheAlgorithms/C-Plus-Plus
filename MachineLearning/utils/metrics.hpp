#pragma once
#include "eigen_compat.hpp"
#include <cmath>

namespace ml::utils {
inline double accuracy(const Eigen::VectorXi& y_true, const Eigen::VectorXi& y_pred) {
    return (y_true.array() == y_pred.array()).cast<double>().mean();
}
inline double mse(const Eigen::VectorXd& y_true, const Eigen::VectorXd& y_pred) {
    return (y_true - y_pred).array().square().mean();
}
inline double rmse(const Eigen::VectorXd& y_true, const Eigen::VectorXd& y_pred) {
    return std::sqrt(mse(y_true, y_pred));
}
inline double precision(const Eigen::VectorXi& y_true, const Eigen::VectorXi& y_pred) {
    int tp=0, fp=0;
    for(int i=0;i<y_true.size();++i){ if(y_pred(i)==1){ if(y_true(i)==1) tp++; else fp++; } }
    return tp + fp == 0 ? 0.0 : static_cast<double>(tp)/(tp+fp);
}
inline double recall(const Eigen::VectorXi& y_true, const Eigen::VectorXi& y_pred) {
    int tp=0, fn=0;
    for(int i=0;i<y_true.size();++i){ if(y_true(i)==1){ if(y_pred(i)==1) tp++; else fn++; } }
    return tp + fn == 0 ? 0.0 : static_cast<double>(tp)/(tp+fn);
}
inline double f1_score(const Eigen::VectorXi& y_true, const Eigen::VectorXi& y_pred) {
    double p = precision(y_true, y_pred), r = recall(y_true, y_pred);
    return p + r == 0 ? 0.0 : 2.0*p*r/(p+r);
}
}
