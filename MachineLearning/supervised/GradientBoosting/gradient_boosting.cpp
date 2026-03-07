#include "gradient_boosting.hpp"
#include <fstream>
namespace ml::supervised {
GradientBoosting::GradientBoosting(int p1,double p2):param1_(p1),param2_(p2){}
/** Learn decision function $f(x)$ via iterative gradient updates. */
void GradientBoosting::fit(const Eigen::MatrixXd& X, const Eigen::VectorXd& y){ train_X_=X; train_y_=y; w_=Eigen::VectorXd::Zero(X.cols()); Eigen::VectorXd yd=y.cast<double>(); for(int e=0;e<300;++e){ Eigen::VectorXd pred=X*w_+Eigen::VectorXd::Ones(X.rows())*b_; Eigen::VectorXd err=pred-yd; w_-=param2_*(X.transpose()*err)/X.rows(); b_-=param2_*err.mean(); } }
/** Compute predictions from linear score. */
Eigen::VectorXd GradientBoosting::predict(const Eigen::MatrixXd& X) const{ Eigen::VectorXd raw=X*w_+Eigen::VectorXd::Ones(X.rows())*b_; return raw; }
/** Return evaluation metric. */
double GradientBoosting::score(const Eigen::MatrixXd& X, const Eigen::VectorXd& y) const{ auto p=predict(X); return (p-y).array().square().mean(); }
/** Save hyperparameters and weights. */
void GradientBoosting::save(const std::string& f) const{ std::ofstream o(f); o<<param1_<<" "<<param2_<<"\n"<<w_.size()<<"\n"; for(int i=0;i<w_.size();++i)o<<w_(i)<<" "; o<<"\n"<<b_; }
/** Load hyperparameters and weights. */
void GradientBoosting::load(const std::string& f){ std::ifstream i(f); int n; i>>param1_>>param2_>>n; w_.resize(n); for(int k=0;k<n;++k)i>>w_(k); i>>b_; }
}
