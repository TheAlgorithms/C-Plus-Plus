#include "kmeans.hpp"
#include <fstream>
namespace ml::unsupervised {
KMeans::KMeans(int k,int m,double lr):n_clusters_(k),max_iters_(m),lr_(lr){}
/** Minimize within-cluster distortion $J=\sum_i ||x_i-\mu_{c_i}||^2$ by assignment/update iterations. */
void KMeans::fit(const Eigen::MatrixXd& X, const Eigen::VectorXi&){ centroids_=X.topRows(n_clusters_); Eigen::VectorXi labels=Eigen::VectorXi::Zero(X.rows()); for(int it=0;it<max_iters_;++it){ for(int i=0;i<X.rows();++i){ double best=1e18; int bi=0; for(int c=0;c<n_clusters_;++c){ double d=(X.row(i)-centroids_.row(c)).squaredNorm(); if(d<best){best=d;bi=c;} } labels(i)=bi; } for(int c=0;c<n_clusters_;++c){ Eigen::VectorXd cnt=Eigen::VectorXd::Zero(X.cols()); int n=0; for(int i=0;i<X.rows();++i) if(labels(i)==c){ cnt+=X.row(i).transpose(); n++; } if(n>0) centroids_.row(c)=cnt.transpose()/n; } } }
/** Assign nearest centroid to each sample. */
Eigen::VectorXi KMeans::predict(const Eigen::MatrixXd& X) const{ Eigen::VectorXi labels(X.rows()); for(int i=0;i<X.rows();++i){ double best=1e18; int bi=0; for(int c=0;c<centroids_.rows();++c){ double d=(X.row(i)-centroids_.row(c)).squaredNorm(); if(d<best){best=d;bi=c;} } labels(i)=bi; } return labels; }
/** Return negative inertia proxy. */
double KMeans::score(const Eigen::MatrixXd& X,const Eigen::VectorXi&) const{ auto l=predict(X); double s=0; for(int i=0;i<X.rows();++i)s+=(X.row(i)-centroids_.row(l(i))).squaredNorm(); return -s/X.rows(); }
/** Save centroids and hyperparameters. */
void KMeans::save(const std::string& f) const{ std::ofstream o(f); o<<n_clusters_<<" "<<max_iters_<<" "<<lr_<<"\n"<<centroids_.rows()<<" "<<centroids_.cols()<<"\n"; for(int i=0;i<centroids_.rows();++i){ for(int j=0;j<centroids_.cols();++j)o<<centroids_(i,j)<<" "; o<<"\n"; } }
/** Load centroids and hyperparameters. */
void KMeans::load(const std::string& f){ std::ifstream i(f); int r,c; i>>n_clusters_>>max_iters_>>lr_>>r>>c; centroids_.resize(r,c); for(int a=0;a<r;++a)for(int b=0;b<c;++b)i>>centroids_(a,b); }
}
