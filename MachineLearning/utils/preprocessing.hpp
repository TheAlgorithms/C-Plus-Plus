#pragma once
#include "eigen_compat.hpp"
#include <random>
#include <vector>
#include <algorithm>

namespace ml::utils {
inline Eigen::MatrixXd normalize(const Eigen::MatrixXd& X){
    Eigen::MatrixXd out=X;
    for(int j=0;j<X.cols();++j){
        double mn=X.col(j).minCoeff(), mx=X.col(j).maxCoeff();
        double denom = (mx-mn)==0?1.0:(mx-mn);
        out.col(j)=(X.col(j).array()-mn)/denom;
    }
    return out;
}
inline Eigen::MatrixXd standardize(const Eigen::MatrixXd& X){
    Eigen::MatrixXd out=X;
    for(int j=0;j<X.cols();++j){
        double mu=X.col(j).mean();
        double std=std::sqrt((X.col(j).array()-mu).square().mean());
        out.col(j)=(X.col(j).array()-mu)/(std==0?1.0:std);
    }
    return out;
}

template<typename Y>
inline void train_test_split(const Eigen::MatrixXd& X, const Y& y, double test_ratio,
                             Eigen::MatrixXd& X_train, Eigen::MatrixXd& X_test,
                             Y& y_train, Y& y_test, unsigned seed=42){
    std::vector<int> idx(X.rows());
    for(int i=0;i<X.rows();++i) idx[i]=i;
    std::mt19937 gen(seed);
    std::shuffle(idx.begin(), idx.end(), gen);
    int n_test=static_cast<int>(X.rows()*test_ratio);
    int n_train=X.rows()-n_test;
    X_train.resize(n_train,X.cols()); X_test.resize(n_test,X.cols());
    y_train.resize(n_train); y_test.resize(n_test);
    for(int i=0;i<n_train;++i){ X_train.row(i)=X.row(idx[i]); y_train(i)=y(idx[i]); }
    for(int i=0;i<n_test;++i){ X_test.row(i)=X.row(idx[n_train+i]); y_test(i)=y(idx[n_train+i]); }
}
}
