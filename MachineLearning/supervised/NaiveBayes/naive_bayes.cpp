#include "naive_bayes.hpp"
#include <fstream>
namespace ml::supervised {
NaiveBayes::NaiveBayes(int p1,double p2):param1_(p1),param2_(p2){}
/** Learn decision function $f(x)$ via iterative gradient updates. */
void NaiveBayes::fit(const Eigen::MatrixXd& X, const Eigen::VectorXi& y){ train_X_=X; train_y_=y; w_=Eigen::VectorXd::Zero(X.cols()); Eigen::VectorXd yd=y.cast<double>(); for(int e=0;e<300;++e){ Eigen::VectorXd pred=X*w_+Eigen::VectorXd::Ones(X.rows())*b_; Eigen::VectorXd err=pred-yd; w_-=param2_*(X.transpose()*err)/X.rows(); b_-=param2_*err.mean(); } }
/** Compute predictions from linear score. */
Eigen::VectorXi NaiveBayes::predict(const Eigen::MatrixXd& X) const{ Eigen::VectorXd raw=X*w_+Eigen::VectorXd::Ones(X.rows())*b_; return (raw.array()>0).cast<int>(); }
/** Return evaluation metric. */
double NaiveBayes::score(const Eigen::MatrixXd& X, const Eigen::VectorXi& y) const{ auto p=predict(X); return (p.array()==y.array()).cast<double>().mean(); }
/** Save hyperparameters and weights. */
void NaiveBayes::save(const std::string& f) const{ std::ofstream o(f); o<<param1_<<" "<<param2_<<"\n"<<w_.size()<<"\n"; for(int i=0;i<w_.size();++i)o<<w_(i)<<" "; o<<"\n"<<b_; }
/** Load hyperparameters and weights. */
void NaiveBayes::load(const std::string& f){ std::ifstream i(f); int n; i>>param1_>>param2_>>n; w_.resize(n); for(int k=0;k<n;++k)i>>w_(k); i>>b_; }
}
