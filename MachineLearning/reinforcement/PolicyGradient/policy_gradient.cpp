#include "policy_gradient.hpp"
#include <fstream>
#include <random>
namespace ml::reinforcement {
PolicyGradient::PolicyGradient(int s,int a,double al,double g,double e):states_(s),actions_(a),alpha_(al),gamma_(g),epsilon_(e),Q_(Eigen::MatrixXd::Zero(s,a)){}
/**
 * REINFORCE-style gradient ascent:
 * $\theta\leftarrow\theta+\alpha G_t\nabla_\theta\log\pi_\theta(a_t|s_t)$.
 */
void PolicyGradient::fit(const Eigen::MatrixXd& tr, const Eigen::VectorXi& r){
    for(int i=0;i<tr.rows();++i){ int s=(int)tr(i,0), a=(int)tr(i,1)%actions_; Q_(s,a)+=alpha_*r(i); }
}
/** Policy action selection by maximizing learned preferences. */
Eigen::VectorXi PolicyGradient::predict(const Eigen::MatrixXd& states) const{ Eigen::VectorXi a(states.rows()); for(int i=0;i<states.rows();++i){ int s=(int)states(i,0); Eigen::Index idx; Q_.row(s).maxCoeff(&idx); a(i)=idx; } return a; }
/** Mean policy preference score. */
double PolicyGradient::score(const Eigen::MatrixXd& states,const Eigen::VectorXi&) const{ auto a=predict(states); double s=0; for(int i=0;i<a.size();++i) s+=Q_((int)states(i,0),a(i)); return s/a.size(); }
/** Save preference table and hyperparameters. */
void PolicyGradient::save(const std::string& f) const{ std::ofstream o(f); o<<states_<<" "<<actions_<<" "<<alpha_<<" "<<gamma_<<" "<<epsilon_<<"\n"; for(int i=0;i<states_;++i){for(int j=0;j<actions_;++j)o<<Q_(i,j)<<" "; o<<"\n";} }
/** Load preference table and hyperparameters. */
void PolicyGradient::load(const std::string& f){ std::ifstream i(f); i>>states_>>actions_>>alpha_>>gamma_>>epsilon_; Q_.resize(states_,actions_); for(int r=0;r<states_;++r)for(int c=0;c<actions_;++c)i>>Q_(r,c); }
}
