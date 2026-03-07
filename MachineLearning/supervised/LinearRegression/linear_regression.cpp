#include "linear_regression.hpp"
#include <fstream>
namespace ml::supervised {
LinearRegression::LinearRegression(double lr,int epochs):lr_(lr),epochs_(epochs){}
/** $\hat{y}=Xw+b$, optimize $L=\frac{1}{n}\sum_i(\hat{y}_i-y_i)^2$ with gradient descent. */
void LinearRegression::fit(const Eigen::MatrixXd& X, const Eigen::VectorXd& y){
    w_=Eigen::VectorXd::Zero(X.cols()); b_=0; int n=X.rows();
    for(int e=0;e<epochs_;++e){ Eigen::VectorXd pred=X*w_+Eigen::VectorXd::Ones(n)*b_; Eigen::VectorXd err=pred-y; w_-=lr_*(2.0/n)*X.transpose()*err; b_-=lr_*(2.0/n)*err.sum(); }
}
/** Compute predictions $\hat{y}=Xw+b$. */
Eigen::VectorXd LinearRegression::predict(const Eigen::MatrixXd& X) const { return X*w_+Eigen::VectorXd::Ones(X.rows())*b_; }
/** Return mean squared error. */
double LinearRegression::score(const Eigen::MatrixXd& X, const Eigen::VectorXd& y) const { return (y-predict(X)).array().square().mean(); }
/** Save $(w,b)$ to file. */
void LinearRegression::save(const std::string& f) const { std::ofstream o(f); o<<w_.size()<<"\n"; for(int i=0;i<w_.size();++i)o<<w_(i)<<" "; o<<"\n"<<b_; }
/** Load $(w,b)$ from file. */
void LinearRegression::load(const std::string& f){ std::ifstream i(f); int n; i>>n; w_.resize(n); for(int k=0;k<n;++k)i>>w_(k); i>>b_; }
}
