#include "logistic_regression.hpp"
#include <fstream>
namespace ml::supervised {
static Eigen::VectorXd sig(const Eigen::VectorXd& z){ return 1.0/(1.0+(-z.array()).exp()); }
LogisticRegression::LogisticRegression(double lr,int e,double t):lr_(lr),epochs_(e),th_(t){}
/** $p=\sigma(Xw+b)$ and gradient descent on logistic cross-entropy. */
void LogisticRegression::fit(const Eigen::MatrixXd& X,const Eigen::VectorXi& y){ w_=Eigen::VectorXd::Zero(X.cols()); b_=0; int n=X.rows(); Eigen::VectorXd yd=y.cast<double>(); for(int e=0;e<epochs_;++e){ Eigen::VectorXd p=sig(X*w_+Eigen::VectorXd::Ones(n)*b_); Eigen::VectorXd err=p-yd; w_-=lr_*(X.transpose()*err)/n; b_-=lr_*err.mean(); } }
/** Threshold probabilities into labels. */
Eigen::VectorXi LogisticRegression::predict(const Eigen::MatrixXd& X) const{ Eigen::VectorXd p=sig(X*w_+Eigen::VectorXd::Ones(X.rows())*b_); return (p.array()>=th_).cast<int>(); }
/** Accuracy metric. */
double LogisticRegression::score(const Eigen::MatrixXd& X,const Eigen::VectorXi& y) const{ auto p=predict(X); return (p.array()==y.array()).cast<double>().mean(); }
/** Save model parameters. */
void LogisticRegression::save(const std::string& f) const{ std::ofstream o(f); o<<w_.size()<<"\n"; for(int i=0;i<w_.size();++i)o<<w_(i)<<" "; o<<"\n"<<b_<<" "<<th_; }
/** Load model parameters. */
void LogisticRegression::load(const std::string& f){ std::ifstream i(f); int n; i>>n; w_.resize(n); for(int k=0;k<n;++k)i>>w_(k); i>>b_>>th_; }
}
